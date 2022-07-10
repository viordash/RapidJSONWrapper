#pragma once

#include "JsonField.h"
#include "JsonFieldsContainer.h"

class JsonObject;

class JsonBaseArray {
  public:
	virtual bool TryParse(RapidJsonValues value);
	bool TryParseByObject(RapidJsonValues value, const char *objectName);

	RapidJsonDocument BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(RapidJsonDocument doc);

	virtual void WriteToDoc(RapidJsonDocument doc) = 0;
	int WriteToString(char *outBuffer, int outBufferSize);

	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int WriteToAsync(void *parent, TOnReady onReady);

	int GetSize();

  protected:
	virtual bool ParseItem(RapidJsonVal value) = 0;
	void WriteToCore(RapidJsonDocument doc, std::vector<JsonObject *> *items);
};

template <class TItem>
class JsonArray : public JsonBaseArray {
  public:
	JsonArray(bool destroyItems = true) : destroyItems{destroyItems} {
	}

	virtual ~JsonArray() {
		if (destroyItems) {
			for (auto item : Items) {
				delete item;
			}
		}
		Items.clear();
	}

	std::vector<TItem *> Items;
	TItem *operator[](int index) {
		return Items[index];
	}

	virtual bool Add(TItem *item) {
		if (item == NULL) {
			return false;
		}
		if (!Validate(item)) {
			return false;
		}
		Items.push_back(item);
		return true;
	}

	virtual void Remove(TItem *item) {
		if (item == NULL) {
			return;
		}
		auto iter = Find(item);
		if (iter != Items.end()) {
			Items.erase(iter);
		}
	}

	typename std::vector<TItem *>::iterator Find(TItem *item) {
		for (auto iter = Items.begin(); iter != Items.end(); iter++) {
			if ((*iter)->Equals(item)) {
				return iter;
			}
		}
		return Items.end();
	}

	virtual bool TryParse(const char *jsonStr, int length = -1) {
		auto doc = BeginTryParse(jsonStr, length);
		if (doc == NULL) {
			return false;
		}
		EndTryParse(doc);
		return true;
	}

	virtual void CloneFrom(JsonArray *other) {
		if (other == NULL) {
			return;
		}

		for (const auto &item : Items) {
			delete item;
		}
		Items.clear();

		for (const auto &item : other->Items) {
			auto newItem = new TItem();
			newItem->CloneFrom(item);
			if (!Add(newItem)) {
				delete newItem;
				return;
			}
		}
	}

	virtual bool Equals(JsonArray *other) {
		if (other == NULL) {
			return false;
		}
		if (Items.size() != other->Items.size()) {
			return false;
		}

		for (size_t i = 0; i < Items.size(); i++) {
			if (!Items[i]->Equals(other->Items[i])) {
				return false;
			}
		}
		return true;
	}

	void Reset() {
		for (const auto &item : Items) {
			item->Reset();
		}
	}

	virtual void WriteToDoc(RapidJsonDocument doc) override {
		WriteToCore(doc, (std::vector<JsonObject *> *)&Items);
	}

  protected:
	virtual bool ParseItem(RapidJsonVal value) {
		auto newItem = new TItem();
		if (!newItem->TryParse(value) || !Add(newItem)) {
			delete newItem;
			return false;
		}
		return true;
	}
	virtual bool Validate(TItem *item) = 0;

  private:
	bool destroyItems;
};
