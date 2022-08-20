#pragma once

#include "lib/LibJson.h"

typedef char TBoolArray;
typedef struct {
	uint8_t *Data;
	size_t Size;
} TJsonRawData;

template <class T> class JsonValue;
template <class T> class JsonCommonValue : public JsonValue<T> {
  public:
	JsonCommonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, T value = T()) : JsonValue<T>(container, nameLen, name, value), presented(false), isNull(false) {}
	template <size_t N> JsonCommonValue(JsonFieldsContainer *container, const char (&name)[N], T value = T()) : JsonCommonValue(container, N - 1, name, value) {}

	virtual ~JsonCommonValue() {}

	bool TryParse(TJsonDocument *doc) override final;
	bool Presented() { return presented; }
	bool IsNull();

  protected:
	bool presented;
	bool isNull;
};

template <class T> class JsonValue : public JsonValueBase {
  public:
	ValueProvider<T> Value;

	JsonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, T value = T()) : JsonValueBase(container, name, nameLen), Value(value) {}
	template <size_t N> JsonValue(JsonFieldsContainer *container, const char (&name)[N], T value = T()) : JsonValue(container, N - 1, name, value) {}

	virtual ~JsonValue() {}

	bool TryParse(TJsonDocument *doc) override;
	void WriteToDoc(TJsonDocument *doc) override final;

	bool Equals(JsonValueBase *other) override final;
	void CloneTo(JsonValueBase *other) override final;

	friend bool operator!=(const JsonValue<T> &v1, const JsonValue<T> &v2);
	friend bool operator==(const JsonValue<T> &v1, const JsonValue<T> &v2);

  protected:
	static TJsonValue *GetMember(TJsonDocument *doc, const char *name);
};

class JsonObject : public JsonFieldsContainer {
  public:
	virtual ~JsonObject(){};

	virtual bool TryParse(TJsonDocument *doc);
	virtual bool TryParse(const char *jsonStr, size_t length = 0);
	TJsonDocument *BeginTryParse(const char *jsonStr, size_t length = 0);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc);
	size_t WriteToString(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Validate() { return true; }
	virtual bool Equals(JsonObject *other);
	void CloneTo(JsonObject *other);

	friend bool operator!=(const JsonObject &v1, const JsonObject &v2);
	friend bool operator==(const JsonObject &v1, const JsonObject &v2);

  protected:
  private:
};

template <class TItem> class JsonArray : public JsonArrayBase {
  public:
	typedef typename std::remove_pointer<TItem>::type TNewObjectItem;
	struct ItemWrapper {
	  public:
		ItemWrapper(JsonArray *owner, size_t index) {
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
		size_t index;
	};

	virtual ~JsonArray() {
		for (const auto &item : Items) { DeleteItem(item); }
	}

	ItemWrapper operator[](size_t index) { return ItemWrapper(this, index); }
	size_t Size() { return Items.size(); }
	typename std::vector<TItem>::iterator const Begin() { return Items.begin(); }
	typename std::vector<TItem>::iterator const End() { return Items.end(); }
	void Reserve(size_t capacity) { Items.reserve(capacity); }

	bool TryParse(TJsonDocument *doc) override final {
		if (!doc->IsArray()) { return false; }
		auto jArray = doc->GetArray();
		Items.reserve(jArray.Size());
		if (TryParseInternal(&jArray)) { return true; }
		Items.shrink_to_fit();
		return false;
	}
	bool TryParse(const char *jsonStr, size_t length = 0) {
		auto doc = BeginTryParse(jsonStr, length);
		if (doc == NULL) { return false; }
		EndTryParse(doc);
		return true;
	}
	TJsonDocument *BeginTryParse(const char *jsonStr, size_t length = 0) {
		if (jsonStr == NULL) { return NULL; }

		rapidjson::Document *doc = new rapidjson::Document();
		if (length == 0) {
			doc->Parse(jsonStr);
		} else {
			doc->Parse(jsonStr, length);
		}
		if (doc->HasParseError() || !this->TryParse(doc)) {
			delete doc;
			return NULL;
		}
		return doc;
	}
	void EndTryParse(TJsonDocument *doc) { delete doc; }

	void WriteToDoc(TJsonDocument *doc) override final {
		doc->SetArray();
		doc->Reserve(Items.size(), doc->GetAllocator());
		WriteToDocInternal(doc);
	}
	size_t WriteToString(char *outBuffer, size_t outBufferSize) {
		rapidjson::Document doc;
		this->WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		const char *jsonStr = buffer.GetString();
		size_t size = buffer.GetSize();
		if (size > outBufferSize - 1) { size = outBufferSize - 1; }
		strncpy(outBuffer, jsonStr, size);
		outBuffer[size] = 0;
		return size;
	}
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady) {
		rapidjson::Document doc;
		this->WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		const char *json = buffer.GetString();
		size_t size = buffer.GetSize();
		onReady(parent, json, size);
		return size;
	}

	virtual bool Add(TItem item) {
		if (!Validate(item)) { return false; }
		AddInternal(item);
		return true;
	}
	virtual bool Update(size_t index, TItem item);
	virtual void Remove(TItem item) {
		auto iter = Find(item);
		if (iter != Items.end()) {
			DeleteItem(*iter);
			Items.erase(iter);
		}
	}
	typename std::vector<TItem>::iterator Find(TItem item);

	bool Equals(JsonArrayBase *other) override final;
	void CloneTo(JsonArrayBase *other) override final;

	friend bool operator!=(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) { return !((JsonArray<TItem> *)&v1)->Equals((JsonArray<TItem> *)&v2); }
	friend bool operator==(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) { return !(v1 != v2); }

  protected:
	std::vector<TItem> Items;
	virtual bool Validate(TItem item) = 0;

  private:
	bool TryParseInternal(TJsonArray *jArray);
	void WriteToDocInternal(TJsonDocument *doc);
	void AddInternal(TItem item);
	void DeleteItem(TItem item);
	typename std::vector<TItem>::iterator GenericFind(TItem item) {
		for (auto iter = Items.begin(); iter != Items.end(); iter++) {
			if (*iter == item) { return iter; }
		}
		return Items.end();
	}
};

class JsonObjectsArray : public JsonArrayBase {
  public:
	virtual ~JsonObjectsArray();

	template <class TItem> TItem Item(size_t index) { return (TItem)Items[index]; }
	size_t Size() { return Items.size(); }
	typename std::vector<JsonObject *>::iterator const Begin() { return Items.begin(); }
	typename std::vector<JsonObject *>::iterator const End() { return Items.end(); }
	void Reserve(size_t capacity) { Items.reserve(capacity); }

	bool TryParse(TJsonDocument *doc) override final;

	bool TryParse(const char *jsonStr, size_t length = 0);
	TJsonDocument *BeginTryParse(const char *jsonStr, size_t length = 0);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc) override final;
	size_t WriteToString(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Add(JsonObject *item);
	virtual bool Update(size_t index, JsonObject *item);
	virtual void Remove(JsonObject *item);

	typename std::vector<JsonObject *>::iterator Find(JsonObject *item);

	bool Equals(JsonArrayBase *other) override final;
	void CloneTo(JsonArrayBase *other) override final;

	friend bool operator!=(const JsonObjectsArray &v1, const JsonObjectsArray &v2);
	friend bool operator==(const JsonObjectsArray &v1, const JsonObjectsArray &v2);

  protected:
	std::vector<JsonObject *> Items;
	virtual bool Validate(JsonObject *item) = 0;
	virtual JsonObject *CreateInstance() = 0;
	void DeleteItem(JsonObject *item);

  private:
	void AddInternal(JsonObject *item);
};