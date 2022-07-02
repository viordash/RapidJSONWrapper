#pragma once

#include "JsonField.h"
#include "JsonFieldsContainer.h"

class JsonObject : public JsonFieldsContainer {
  public:
	JsonObject();
	virtual ~JsonObject();

  protected:
  private:
	JsonField *SeachFieldByName(const char *name);
};
