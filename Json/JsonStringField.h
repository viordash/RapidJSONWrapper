#pragma once

#include "JsonBaseField.h"

struct JsonStringField : public JsonBaseField {
  public:
	JsonStringField(const char *name, const char *value, int size = 256, bool optional = false);
	virtual ~JsonStringField();
	char *Value;

	int GetSize() override {
		return size;
	}
	bool ReadFromJson(RapidJsonValue value) override;
	void WriteToJson(RapidJsonDocument doc) override;
	void CloneFrom(JsonBaseField *otherJsonField) override;
	void SetValue(const char *data);
	bool Equals(JsonBaseField *otherJsonField) override;

  protected:
	int size;
};
