#pragma once

typedef void *RapidJsonVal;
typedef void *RapidJsonValues;
typedef void *RapidJsonDocument;

#include <string.h>
#include <stdint.h>
#include "JsonFieldsContainer.h"

class JsonBaseField {
  public:
	const char *Name;

	JsonBaseField(JsonFieldsContainer *container, const char *name, bool optional);
	virtual ~JsonBaseField(){};
	virtual size_t GetSize() = 0;

	bool ReadFromJson(RapidJsonValues values);
	virtual bool ReadFromJsonCore(RapidJsonVal value) = 0;

	void WriteToJson(RapidJsonDocument doc);
	virtual void WriteToJsonCore(RapidJsonVal value) = 0;
	virtual void CloneFrom(JsonBaseField *other) = 0;
	virtual bool Equals(JsonBaseField *other);

  protected:
	bool optional;

	bool HasMember(RapidJsonValues values);
	virtual void ResetValue() = 0;
};
