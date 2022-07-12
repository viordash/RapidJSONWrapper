#pragma once

#include "JsonField.h"
#include "JsonFieldsContainer.h"

class JsonObject : public JsonFieldsContainer {
  public:
	virtual bool TryParse(RapidJsonValues value);
	bool TryParseByObject(RapidJsonValues value, const char *objectName);
	virtual bool TryParse(const char *jsonStr, int length = -1);

	RapidJsonDocument BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(RapidJsonDocument doc);

	void WriteToDoc(RapidJsonDocument doc);
	int WriteToString(char *outBuffer, int outBufferSize);

	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	virtual void CloneFrom(JsonObject *other);

	int GetSize();
	virtual bool Equals(JsonObject *other);

	virtual bool Validate() {
		return true;
	}
	void Reset();

  protected:
  private:
	JsonBaseField *SeachFieldByName(const char *name);
};
