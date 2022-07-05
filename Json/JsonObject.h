#pragma once

#include "JsonField.h"
#include "JsonFieldsContainer.h"

class JsonObject : public JsonFieldsContainer {
  public:
	JsonObject();
	virtual ~JsonObject();

	virtual bool TryParse(RapidJsonValues value);
	bool TryParseByObject(RapidJsonValues value, const char *objectName);
	virtual bool TryParse(const char *jsonStr, int length = -1);

	RapidJsonDocument BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(RapidJsonDocument doc);

	void WriteTo(RapidJsonDocument doc);
	int WriteTo(char *outBuffer, int outBufferSize);

	typedef void (*TOnJsonStringReady)(void *parent, const char *jsonStr, int size);
	int WriteTo(void *parent, TOnJsonStringReady onJsonStringReady);

	virtual void CloneFrom(JsonObject *other);

	int GetSize();
	virtual bool EqualTo(JsonObject *other);

  protected:
  private:
	JsonBaseField *SeachFieldByName(const char *name);
};
