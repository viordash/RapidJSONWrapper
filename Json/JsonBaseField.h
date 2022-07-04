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

	virtual bool ReadFromJson(RapidJsonValues values) = 0;

	void WriteToJson(RapidJsonDocument doc);
	virtual void WriteToJsonCore(RapidJsonVal value) = 0;
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

	bool ReadFromJson(RapidJsonValues values) override final {
		if (!HasMember(values)) {
			this->ResetValue();
			return optional;
		}
		rapidjson::Value *jsonValue = (rapidjson::Value *)values;
		auto &jsonVal = (*jsonValue)[Name];

		if (this->ReadFromJsonCore(&jsonVal)) {
			return true;
		}

		if (jsonVal.IsNull()) {
			this->ResetValue();
			return true;
		}
		return false;
	}
	virtual bool ReadFromJsonCore(RapidJsonVal value) = 0;

  protected:
};
