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

	typedef std::vector<JsonBaseField *> TFields;
	TFields fields;

  protected:
  private:
	JsonBaseField *SeachFieldByName(const char *name);
};
