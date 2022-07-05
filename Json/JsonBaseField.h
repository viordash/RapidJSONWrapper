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

	JsonBaseField(JsonFieldsContainer *container, const char *name);
	virtual ~JsonBaseField(){};
	virtual size_t GetSize() = 0;

	virtual bool TryParse(RapidJsonValues values) = 0;

	void WriteTo(RapidJsonDocument doc);
	virtual void WriteToInternal(RapidJsonVal value) = 0;
	virtual void CloneFrom(JsonBaseField *other) = 0;
	virtual bool Equals(JsonBaseField *other);

  protected:
	bool HasMember(RapidJsonValues values);
	virtual void ResetValue() = 0;
};

template <bool optional>
class JsonOptionalField : public JsonBaseField {
  public:
	JsonOptionalField(JsonFieldsContainer *container, const char *name) : JsonBaseField(container, name) {
	}
	virtual ~JsonOptionalField(){};

	bool TryParse(RapidJsonValues values) override final;
	virtual bool TryParseInternal(RapidJsonVal value) = 0;

  protected:
};
