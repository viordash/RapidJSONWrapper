#pragma once

typedef void *RapidJsonValue;
typedef void *RapidJsonDocument;

#include <string.h>
#include <stdint.h>
#include <type_traits>

class JsonBaseField {
  public:
	JsonBaseField(const char *name, bool optional);
	virtual ~JsonBaseField();
	const char *Name;

	JsonBaseField(JsonBaseField &&) = delete;
	JsonBaseField(const JsonBaseField &) = delete;

	virtual int GetSize() = 0;

	virtual bool ReadFromJson(RapidJsonValue value) = 0;
	virtual void WriteToJson(RapidJsonDocument doc) = 0;
	virtual void CloneFrom(JsonBaseField *otherJsonBaseField) = 0;
	virtual bool Equals(JsonBaseField *otherJsonBaseField);

	virtual int IsNull() {
		return !hasValue;
	}

  protected:
	bool hasValue;
	bool optional;

	bool HasMember(RapidJsonValue value);
};
