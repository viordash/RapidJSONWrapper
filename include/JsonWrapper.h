#pragma once

#include "lib/LibJson.h"

typedef char TBoolArray;
typedef struct {
	uint8_t *Data;
	size_t Size;
} TJsonRawData;

template <class T> //
class JsonValue : public JsonValueBase {
  public:
	struct ValueWrapper {
	  public:
		ValueWrapper(const T value) { InitValue(value); }
		~ValueWrapper() { DeleteValue(); }

		T operator=(const T right) {
			SetValue(right);
			return value;
		}
		T operator->() { return value; }

		operator T() const { return value; }

	  private:
		T value;
		void InitValue(T value);
		void SetValue(T value);
		void DeleteValue();
	};

	ValueWrapper Value;

	JsonValue(JsonFieldsContainer *container, const char *name, T value) : JsonValueBase(container, name), Value(value) {}
	JsonValue(JsonFieldsContainer *container, const char *name) : JsonValue(container, name, T()) {}
	virtual ~JsonValue() {}

	TJsonDocument *BeginTryParse(const char *jsonStr, size_t length = 0);
	void EndTryParse(TJsonDocument *doc);
	bool TryParse(const char *jsonStr, size_t length = 0);
	bool TryParse(TJsonDocument *doc) override;

	void WriteToDoc(TJsonDocument *doc) override final;
	size_t WriteToString(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnCompleted)(void *parent, const char *json, int size);
	size_t DirectWriteTo(void *parent, TOnCompleted onCompleted);

	void Reset();
	bool Equals(JsonValueBase *other) override final;
	void CloneTo(JsonValueBase *other) override final;

  protected:
	bool TryParseCore(TJsonValue *value);
};

template <class T> //
class JsonOptionalValue : public JsonValue<T> {
  public:
	JsonOptionalValue(JsonFieldsContainer *container, const char *name, T value) : JsonValue(container, name, value), presented(false) {}
	JsonOptionalValue(JsonFieldsContainer *container, const char *name) : JsonOptionalValue(container, name, T()) {}
	virtual ~JsonOptionalValue() {}

	bool TryParse(TJsonDocument *doc) override final;
	bool Presented();

  protected:
	bool presented;
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
	bool Equals(JsonObject *other);
	void CloneTo(JsonObject *other);

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

	virtual ~JsonArray();

	ItemWrapper operator[](size_t index) { return ItemWrapper(this, index); }
	size_t Size() { return Items.size(); }
	typename std::vector<TItem>::iterator const Begin() { return Items.begin(); }
	typename std::vector<TItem>::iterator const End() { return Items.end(); }

	bool TryParse(TJsonDocument *doc) override final;
	bool TryParse(const char *jsonStr, size_t length = 0);
	TJsonDocument *BeginTryParse(const char *jsonStr, size_t length = 0);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc) override final;
	size_t WriteToString(char *outBuffer, size_t outBufferSize);
	typedef void (*TOnReady)(void *parent, const char *json, size_t size);
	size_t DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Add(TItem item);
	virtual bool Update(size_t index, TItem item);
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
	void GenericWriteToDocInternal(TJsonDocument *doc);
	void AddInternal(TItem item);
	void DeleteItem(TItem item);
	typename std::vector<TItem>::iterator GenericFind(TItem item);
	bool GenericEquals(JsonArrayBase *other);
	void GenericCloneTo(JsonArrayBase *other);
};

#include "lib/JsonValue_impl.h"
#include "lib/JsonOptionalValue_impl.h"
#include "lib/JsonObject_impl.h"
#include "lib/JsonArray_impl.h"