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
	virtual void CloneFrom(JsonBaseArray *other) = 0;
	virtual bool Equals(JsonBaseArray *other) = 0;
	virtual void Reset() = 0;

  protected:
	virtual bool TryParseItem(RapidJsonValues value) = 0;
	void WriteToCore(RapidJsonDocument doc, std::vector<JsonObject *> *items);
};

template <class TItem>
class JsonArray : public JsonBaseArray {
  public:
	virtual ~JsonArray() {
		Reset();
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

	virtual void CloneFrom(JsonBaseArray *other) override {
		if (other == NULL) {
			return;
		}

		Reset();

		for (const auto &item : ((JsonArray *)other)->Items) {
			auto newItem = new TItem();
			newItem->CloneFrom(item);
			if (!Add(newItem)) {
				delete newItem;
				return;
			}
		}
	}

	virtual bool Equals(JsonBaseArray *other) override {
		if (other == NULL) {
			return false;
		}
		if (Items.size() != ((JsonArray *)other)->Items.size()) {
			return false;
		}

		for (size_t i = 0; i < Items.size(); i++) {
			if (!Items[i]->Equals(((JsonArray *)other)->Items[i])) {
				return false;
			}
		}
		return true;
	}

	virtual void Reset() override {
		for (const auto &item : Items) {
			delete item;
		}
		Items.clear();
	}

	virtual void WriteToDoc(RapidJsonDocument doc) override {
		WriteToCore(doc, (std::vector<JsonObject *> *)&Items);
	}

  protected:
	virtual bool TryParseItem(RapidJsonValues value) {
		auto newItem = new TItem();
		if (!newItem->TryParse(value) || !Add(newItem)) {
			delete newItem;
			return false;
		}
		return true;
	}
	virtual bool Validate(TItem *item) = 0;

  private:
};
