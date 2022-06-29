#pragma once

typedef void *RapidJsonValue;
typedef void *RapidJsonDocument;

#include <string.h>
#include <stdint.h>
#include <type_traits>

struct JsonBaseField {
  public:
	JsonBaseField(const char *name, bool optional);
	const char *Name;

	virtual int GetSize() {
		return -1;
	};

	virtual bool ReadFromJson(RapidJsonValue value) {
		return false;
	};

	virtual void WriteToJson(RapidJsonDocument doc){};
	virtual void CloneFrom(JsonBaseField *other){};
	virtual bool Equals(JsonBaseField *other);

  protected:
	bool optional;

	bool HasMember(RapidJsonValue value);
};
