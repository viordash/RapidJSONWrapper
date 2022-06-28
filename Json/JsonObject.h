#pragma once

#include "JsonBaseField.h"
#include "JsonStringField.h"
#include "JsonNumericField.h"

#include <set>
#include <vector>

struct JsonObjectFields {
	std::vector<JsonBaseField> Items;
	JsonObjectFields(std::initializer_list<JsonBaseField> list) : Items(list) {
		printf("constructed with a %d-element list\n", list.size());
	}

	JsonObjectFields() = default;
};

class JsonObject {
  public:
	JsonObject();
	virtual ~JsonObject();

	JsonObjectFields Fields;

  protected:
  private:
	JsonBaseField *SeachFieldByName(const char *name);
};
