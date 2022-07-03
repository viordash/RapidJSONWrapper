#pragma once

#include "JsonField.h"

template <>
class JsonField<char *> : public JsonBaseField {
  public:
	char *Value;

	JsonField(JsonFieldsContainer *container, const char *name, size_t maxSize = 8192, bool optional = false) : JsonBaseField(container, name, optional) {
		this->maxSize = maxSize;
		Value = NULL;
		size = 0;
		ResetValue();
	}

	~JsonField() {
		delete[] Value;
	}

	size_t GetSize() override final {
		return size;
	}

	bool ReadFromJsonCore(RapidJsonVal value) override final;
	void WriteToJsonCore(RapidJsonVal value) override final;
	void CloneFrom(JsonBaseField *other) override final {
		Value = ((JsonField *)other)->Value;
	}
	void SetValue(char *value, size_t len = 0);
	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other) //
			   && strcmp(Value, ((JsonField *)other)->Value) == 0;
	}

	void ResetValue() override {
		SetValue(NULL);
	}

  protected:
	size_t maxSize;
	size_t size;
};