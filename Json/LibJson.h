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

  protected:
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

	virtual bool TryParse(TJsonDocument *doc);

	bool TryParse(const char *jsonStr, int length = -1);

	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1);

	void EndTryParse(TJsonDocument *doc);

	virtual void WriteToDoc(TJsonDocument *doc);

	int WriteToString(char *outBuffer, int outBufferSize);

	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Add(TItem item);

  protected:
	virtual bool Validate(TItem item) = 0;

  private:
	bool TryParseInternal(TJsonArray *jArray);

	void WriteToDocInternal(TJsonDocument *doc);

	void AddInternal(TItem item);
};

