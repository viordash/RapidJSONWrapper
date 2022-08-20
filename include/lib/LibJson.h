#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>

typedef rapidjson::Document TJsonDocument;
typedef rapidjson::Value::Array TJsonArray;
typedef rapidjson::Value TJsonValue;
typedef rapidjson::GenericStringRef<char> TJsonValueName;

class JsonValueBase;
class JsonObject;
template <class T> class JsonValue;
template <class T> class JsonCommonValue;

class JsonArrayBase {
  public:
	virtual bool TryDocParse(TJsonDocument *doc) = 0;
	bool TryParse(const char *jsonStr, size_t length = 0);
	TJsonDocument *BeginTryParse(const char *jsonStr, size_t length = 0);
	void EndTryParse(TJsonDocument *doc);

	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	size_t WriteToString(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Equals(JsonArrayBase *other) = 0;
	virtual void CloneTo(JsonArrayBase *other) = 0;

  protected:
};

class JsonFieldsContainer {
  public:
	std::vector<JsonValueBase *> Fields;
	void Add(JsonValueBase *field) { Fields.push_back(field); }
	JsonValueBase *GetField(const char *name);
};

class JsonValueBase {
  public:
	TJsonValueName Name;
	JsonValueBase(JsonValueBase &&) = delete;
	JsonValueBase(const JsonValueBase &) = delete;

	JsonValueBase(JsonFieldsContainer *container, const char *name, size_t nameLen) : Name(name, nameLen) { container->Add(this); }
	virtual ~JsonValueBase(){};

	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(JsonValueBase *other) = 0;
	virtual void CloneTo(JsonValueBase *other) = 0;

  protected:
};

template <class T> struct ValueProvider {
  public:
	ValueProvider(const T value) { InitValue(value); }

	T operator=(const T right) {
		SetValue(right);
		return value;
	}
	T operator->() { return value; }
	operator T() const { return value; }

  private:
	template <class T> friend class JsonValue;
	template <class T> friend class JsonCommonValue;

	~ValueProvider() { DeleteValue(); }
	T value;

	void InitValue(T value);
	void SetValue(T value);
	void DeleteValue();
};