#pragma once

#include "JsonBaseField.h"
#include "JsonStringField.h"
#include "JsonNumericField.h"

#include <set>
#include <vector>

class JsonObject {
  public:
	JsonObject();
	virtual ~JsonObject();

	//   protected:
	std::vector<JsonBaseField *> fields;
	JsonStringField *InsertValue(const char *name, const char *value, int size = 256, bool optional = false);
	JsonNumericField<uint32_t> *InsertValue(const char *name, uint32_t value, bool optional = false);

  private:
	JsonBaseField *SeachFieldByName(const char *name);
};

