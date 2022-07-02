#pragma once

typedef void *RapidJsonVal;
typedef void *RapidJsonValues;
typedef void *RapidJsonDocument;

#include <string.h>
#include <stdint.h>
#include "JsonFieldsContainer.h"

class JsonField {
  public:
	const char *Name;

	JsonField(JsonFieldsContainer *container, const char *name, bool optional);
	virtual ~JsonField(){};
	virtual size_t GetSize() = 0;

	bool ReadFromJson(RapidJsonValues values);
	virtual bool ReadFromJsonCore(RapidJsonVal value) = 0;

	void WriteToJson(RapidJsonDocument doc);
	virtual void WriteToJsonCore(RapidJsonVal value) = 0;
	virtual void CloneFrom(JsonField *other) = 0;
	virtual bool Equals(JsonField *other);

  protected:
	bool optional;

	bool HasMember(RapidJsonValues values);
	virtual void ResetValue() = 0;
};

class JsonIntField : public JsonField {
  public:
	int Value;
	JsonIntField(JsonIntField &&) = delete;
	JsonIntField(const JsonIntField &) = delete;
	JsonIntField(JsonFieldsContainer *container, const char *name, bool optional = false);

	size_t GetSize() {
		return sizeof(int);
	}

	bool ReadFromJsonCore(RapidJsonVal value) override;
	void WriteToJsonCore(RapidJsonVal value) override;
	void CloneFrom(JsonField *other) override;
	void SetValue(int value) {
		Value = value;
	}
	bool Equals(JsonField *other) override;

  protected:
	void ResetValue() override {
		SetValue(0);
	}
};