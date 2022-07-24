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
	virtual void CloneTo(JsonArrayBase *other) = 0;
};

class JsonValueBase;

class JsonFieldsContainer {
  public:
	std::vector<JsonValueBase *> Fields;
	void Add(JsonValueBase *field) { Fields.push_back(field); }
	JsonValueBase *GetField(const char *name);
};

class JsonValueBase {
  public:
	const char *Name;
	JsonValueBase(JsonValueBase &&) = delete;
	JsonValueBase(const JsonValueBase &) = delete;

	JsonValueBase(JsonFieldsContainer *container, const char *name) : Name(name) { container->Add(this); }
	virtual ~JsonValueBase(){};

	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(JsonValueBase *other) = 0;
	virtual void CloneTo(JsonValueBase *other) = 0;

  protected:
};

template <class T, bool optional = false> //
class JsonValue : public JsonValueBase {
	class ValueWrapper {
	  public:
		ValueWrapper(JsonValue *owner, const T value) {
			this->owner = owner;
			owner->InitValue(value);
		}

		T operator=(const T right) {
			owner->SetValue(right);
			return owner->value;
		}

		operator T() const { return owner->value; }

	  private:
		JsonValue *owner;
	};

  public:
	ValueWrapper Value;

	JsonValue(JsonFieldsContainer *container, const char *name, T value) : JsonValueBase(container, name), Value(this, value) {}
	JsonValue(JsonFieldsContainer *container, const char *name) : JsonValue(container, name, T()) {}
	virtual ~JsonValue() { DeleteValue(); }

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
	virtual ~JsonObject(){};

	virtual bool TryParse(TJsonDocument *doc);
	virtual bool TryParse(const char *jsonStr, int length = -1);
	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc);
	int WriteToString(char *outBuffer, int outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Validate() { return true; }
	bool Equals(JsonObject *other);
	void CloneTo(JsonObject *other);

  protected:
  private:
};

template <class TItem> class JsonArray : public JsonArrayBase {
	typedef typename std::remove_pointer<TItem>::type TNewObjectItem;

	struct ItemWrapper {
	  public:
		ItemWrapper(JsonArray *owner, int index) {
			this->owner = owner;
			this->index = index;
		}
		virtual ~ItemWrapper(){};

		TItem operator=(const TItem right) {
			owner->Update(index, right);
			return owner->Items[index];
		}
		TItem operator->() { return owner->Items[index]; }
		operator TItem() const { return owner->Items[index]; }

	  private:
		JsonArray *owner;
		int index;
	};

  public:
	virtual ~JsonArray();

	ItemWrapper Get(int index) { return ItemWrapper(this, index); }

	ItemWrapper operator[](int index) { return ItemWrapper(this, index); }
	size_t Size() { return Items.size(); }
	typename std::vector<TItem>::iterator const Begin() { return Items.begin(); }
	typename std::vector<TItem>::iterator const End() { return Items.end(); }

	bool TryParse(TJsonDocument *doc) override final;
	bool TryParse(const char *jsonStr, int length = -1);
	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc) override final;
	int WriteToString(char *outBuffer, int outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Add(TItem item);
	virtual bool Update(int index, TItem item);
	virtual void Remove(TItem item);
	typename std::vector<TItem>::iterator Find(TItem item);

	bool Equals(JsonArrayBase *other) override final;
	void CloneTo(JsonArrayBase *other) override final;

  protected:
	std::vector<TItem> Items;
	virtual bool Validate(TItem item) = 0;

  private:
	bool TryParseInternal(TJsonArray *jArray);
	void WriteToDocInternal(TJsonDocument *doc);
	void AddInternal(TItem item);
	void DeleteItem(TItem item);
};
