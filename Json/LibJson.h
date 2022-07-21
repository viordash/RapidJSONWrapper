#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>

typedef rapidjson::Document TJsonDocument;
typedef rapidjson::Value::Array TJsonArray;
typedef rapidjson::Value TJsonValue;

typedef char TBoolArray;

class JsonArrayBase {
  public:
	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(JsonArrayBase *other) = 0;
};

class JsonValueBase;

class JsonFieldsContainer {
  public:
	std::vector<JsonValueBase *> Fields;
	void Add(JsonValueBase *field) { Fields.push_back(field); }
};

class JsonValueBase {
  public:
	JsonValueBase(JsonValueBase &&) = delete;
	JsonValueBase(const JsonValueBase &) = delete;

	JsonValueBase(JsonFieldsContainer *container) { container->Add(this); }
	virtual ~JsonValueBase(){};

	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(JsonValueBase *other) = 0;
	virtual void CloneTo(JsonValueBase *other) = 0;

  protected:
};

template <class T, bool optional = false> //
class JsonValue : JsonValueBase {
	class ValueWrapper {
	  public:
		ValueWrapper(JsonValue *owner, const T value) {
			this->owner = owner;
			owner->InitValue(value);
		}

		~ValueWrapper() { owner->DeleteValue(); }

		T operator=(const T right) {
			owner->SetValue(right);
			return owner->value;
		}

		operator T() const { return owner->value; }

	  private:
		JsonValue *owner;
	};

  public:
	const char *Name;
	ValueWrapper Value;

	JsonValue(JsonFieldsContainer *container, const char *name, T value) : JsonValueBase(container), Name(name), Value(this, value) {}
	JsonValue(JsonFieldsContainer *container, const char *name) : JsonValue(container, name, T()) {}

	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(TJsonDocument *doc);
	bool TryParse(const char *jsonStr, int length = -1);
	bool TryParse(TJsonDocument *doc) override final;

	void WriteToDoc(TJsonDocument *doc) override final;
	int WriteToString(char *outBuffer, int outBufferSize);
	typedef void (*TOnCompleted)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnCompleted onCompleted);

	void Reset();
	bool Equals(JsonValueBase *other) override final;
	void CloneTo(JsonValueBase *other) override final;

  protected:
  private:
	T value;
	void InitValue(T value);
	bool SetValue(T value);
	void DeleteValue();
	bool TryParseCore(TJsonValue *value);
};

class JsonObject : public JsonFieldsContainer {
  public:
	virtual bool TryParse(TJsonDocument *doc);
	virtual bool TryParse(const char *jsonStr, int length = -1);
	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc);
	int WriteToString(char *outBuffer, int outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Validate() { return true; }

  protected:
  private:
};

template <class TItem> class JsonArray : public JsonArrayBase {
	typedef typename std::remove_pointer<TItem>::type TNewObjectItem;

  public:
	std::vector<TItem> Items;
	TItem operator[](int index) { return Items[index]; }

	bool TryParse(TJsonDocument *doc) override final;
	bool TryParse(const char *jsonStr, int length = -1);
	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc) override final;
	int WriteToString(char *outBuffer, int outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Add(TItem item);
	virtual void Remove(TItem item);
	typename std::vector<TItem>::iterator Find(TItem item);

	bool Equals(JsonArrayBase *other) override final;

  protected:
	virtual bool Validate(TItem item) = 0;

  private:
	bool TryParseInternal(TJsonArray *jArray);
	void WriteToDocInternal(TJsonDocument *doc);
	void AddInternal(TItem item);
};
