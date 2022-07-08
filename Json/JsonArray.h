#pragma once

#include "JsonField.h"
#include "JsonFieldsContainer.h"

class JsonObject;

class JsonArray {
  public:
	JsonArray(bool destroyItems = true);
	virtual ~JsonArray();

	std::vector<JsonObject *> Items;
	inline JsonObject *operator[](int index) {
		return Items[index];
	}

	virtual bool Add(JsonObject *item);
	virtual void Remove(JsonObject *item);
	std::vector<JsonObject *>::iterator Find(JsonObject *item);

	virtual bool TryParse(RapidJsonValues value);
	bool TryParseByObject(RapidJsonValues value, const char *objectName);
	virtual bool TryParse(const char *jsonStr, int length = -1);

	RapidJsonDocument BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(RapidJsonDocument doc);

	void WriteTo(RapidJsonDocument doc);
	int WriteTo(char *outBuffer, int outBufferSize);

	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int WriteTo(void *parent, TOnReady onReady);

	virtual void CloneFrom(JsonArray *other);

	int GetSize();
	virtual bool Equals(JsonArray *other);

	void Reset();

  protected:
	virtual JsonObject *CreateItem() = 0;
	virtual bool ParseItem(RapidJsonVal value, JsonObject *newItem);
	virtual bool Validate() = 0;

  private:
	bool destroyItems;
};
