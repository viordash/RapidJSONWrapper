#pragma once

#include "LibJson.h"
#include "JsonValue.h"
#include "JsonFieldsContainer.h"

class JsonObject : public JsonFieldsContainer {
  public:
	virtual bool TryParse(TJsonDocument *doc);
	virtual bool TryParse(const char *jsonStr, int length = -1);

	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1);
	void EndTryParse(TJsonDocument *doc);

	void WriteToDoc(TJsonDocument *doc);
	int WriteToString(char *outBuffer, int outBufferSize);

	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady);

	virtual bool Validate() { return true; }

  protected:
  private:
};
