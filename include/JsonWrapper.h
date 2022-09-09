#pragma once

#include "lib/LibJson.h"

typedef char TBoolArray;
typedef struct {
	uint8_t *Data;
	size_t Size;
} TJsonRawData;

template <class T> class JsonValue : public JsonValueBase {
  public:
	typedef typename std::conditional<std::is_same<T, char *>::value, const char *, typename std::add_const<T>::type>::type ConstT;

	JsonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, size_t valueLen, ConstT value) : JsonValueBase(container, name, nameLen) { InitValue(value, valueLen); }
	JsonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, ConstT value = T()) : JsonValue(container, nameLen, name, size_t(), value) {}
	template <size_t N> JsonValue(JsonFieldsContainer *container, const char (&name)[N], ConstT value = T()) : JsonValue(container, N - 1, name, value) {}

	virtual ~JsonValue() { DeleteValue(); }

	bool TryParse(TJsonDocument *doc) override final;
	void WriteToDoc(TJsonDocument *doc) override final;

	bool Equals(JsonValueBase *other) override final;
	void CloneTo(JsonValueBase *other) override final;

	T Get() { return value; }

	void Set(ConstT newValue, size_t newValueLen = size_t()) {
		DeleteValue();
		InitValue(newValue, newValueLen);
	}

  protected:
	T value;
	void InitValue(ConstT value, size_t valueLen);
	void DeleteValue();
};

template <class T> class JsonCommonValue : public JsonValueBase {
  public:
	typedef typename std::conditional<std::is_same<T, char *>::value, const char *, typename std::add_const<T>::type>::type ConstT;

	JsonCommonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, size_t valueLen, ConstT value) : JsonValueBase(container, name, nameLen), presented(false), isNull(false) {
		InitValue(value, valueLen);
	}
	JsonCommonValue(JsonFieldsContainer *container, size_t nameLen, const char *name, ConstT value = T()) : JsonCommonValue(container, nameLen, name, size_t(), value) {}
	template <size_t N> JsonCommonValue(JsonFieldsContainer *container, const char (&name)[N], ConstT value = T()) : JsonCommonValue(container, N - 1, name, value) {}

	virtual ~JsonCommonValue() { DeleteValue(); }

	bool TryParse(TJsonDocument *doc) override final;
	void WriteToDoc(TJsonDocument *doc) override final;

	bool Equals(JsonValueBase *other) override final;
	void CloneTo(JsonValueBase *other) override final;

	bool Presented() { return presented; }
	bool IsNull();
	void ResetToNull();

	T Get() { return value; }
	void Set(ConstT newValue, size_t newValueLen = size_t()) {
		DeleteValue();
		InitValue(newValue, newValueLen);
	}

  protected:
	bool presented;
	bool isNull;
	T value;
	void InitValue(ConstT value, size_t valueLen);
	void DeleteValue();
};

class JsonObject : public JsonFieldsContainer {
  public:
	virtual ~JsonObject(){};

	virtual bool TryParse(TJsonDocument *doc);
	virtual bool TryStringParse(const char *jsonStr, size_t length = 0);
	TJsonDocument *BeginTryStringParse(const char *jsonStr, size_t length = 0);
	void EndTryStringParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc);
	size_t WriteToString(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Validate() { return true; }
	virtual bool Equals(JsonObject *other);
	virtual void CloneTo(JsonObject *other);

	friend bool operator!=(const JsonObject &v1, const JsonObject &v2);
	friend bool operator==(const JsonObject &v1, const JsonObject &v2);

  protected:
  private:
};

template <class TItem> class JsonArray : public JsonArrayBase {
  public:
	virtual ~JsonArray();

	TItem Item(size_t index) { return (TItem)Items[index]; }
	size_t Size() { return Items.size(); }
	typename std::vector<TItem>::iterator const Begin() { return Items.begin(); }
	typename std::vector<TItem>::iterator const End() { return Items.end(); }
	void Reserve(size_t capacity) { Items.reserve(capacity); }
	bool Empty() { return Items.empty(); }

	bool TryDocParse(TJsonDocument *doc) override final;
	void WriteToDoc(TJsonDocument *doc) override final;

	virtual bool Add(TItem item);
	virtual bool Update(size_t index, TItem item);
	virtual void Remove(TItem item);
	typename std::vector<TItem>::iterator Find(TItem item);

	bool Equals(JsonArrayBase *other) override final;
	void CloneTo(JsonArrayBase *other) override final;

	friend bool operator!=(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) { return !((JsonArray<TItem> *)&v1)->Equals((JsonArray<TItem> *)&v2); }
	friend bool operator==(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) { return !(v1 != v2); }

  protected:
	std::vector<TItem> Items;
	virtual bool Validate(TItem item) = 0;
	void AddInternal(TItem item);
	void DeleteItem(TItem item);
};

class JsonObjectsArray : public JsonArrayBase {
  public:
	virtual ~JsonObjectsArray();

	template <class TItem> TItem Item(size_t index) { return (TItem)Items[index]; }
	size_t Size() { return Items.size(); }
	typename std::vector<JsonObject *>::iterator const Begin() { return Items.begin(); }
	typename std::vector<JsonObject *>::iterator const End() { return Items.end(); }
	void Reserve(size_t capacity) { Items.reserve(capacity); }
	bool Empty() { return Items.empty(); }

	bool TryDocParse(TJsonDocument *doc) override final;
	void WriteToDoc(TJsonDocument *doc) override final;

	virtual bool Add(JsonObject *item);
	virtual bool Update(size_t index, JsonObject *item);
	virtual void Remove(JsonObject *item);

	typename std::vector<JsonObject *>::iterator Find(JsonObject *item);

	bool Equals(JsonArrayBase *other) override final;
	void CloneTo(JsonArrayBase *other) override final;
	virtual bool Validate(JsonObject *item) = 0;
	virtual JsonObject *CreateItem() = 0;

	friend bool operator!=(const JsonObjectsArray &v1, const JsonObjectsArray &v2);
	friend bool operator==(const JsonObjectsArray &v1, const JsonObjectsArray &v2);

  protected:
	std::vector<JsonObject *> Items;
	void AddInternal(JsonObject *item);
	void DeleteItem(JsonObject *item);
};