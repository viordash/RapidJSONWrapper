#pragma once

#include "JsonField.h"
#include "JsonFieldsContainer.h"

class JsonObject;

class JsonBaseArray {
  public:
	virtual bool TryParse(RapidJsonValues value);

	RapidJsonDocument BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(RapidJsonDocument doc);

	virtual void WriteToDoc(RapidJsonDocument doc) = 0;
	int WriteToString(char *outBuffer, int outBufferSize);

	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	int GetSize();
	virtual void CloneFrom(JsonBaseArray *other) = 0;
	virtual bool Equals(JsonBaseArray *other) = 0;
	virtual void Reset() = 0;

  protected:
	virtual bool TryParseItem(RapidJsonValues value) = 0;
	void WriteToCore(RapidJsonDocument doc, std::vector<JsonObject *> *items);
};
