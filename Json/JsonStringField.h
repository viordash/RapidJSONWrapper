#pragma once

#include "JsonField.h"

template <bool optional>
class JsonField<char *, optional> : public JsonOptionalField<optional> {
  public:
	char *Value;

	JsonField(JsonFieldsContainer *container, const char *name) : JsonOptionalField<optional>(container, name) {
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
	void SetValue(const char *value, size_t len = 0) {
		SetValueCore(value, len);
	}
	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other) //
			   && strcmp(Value, ((JsonField *)other)->Value) == 0;
	}

	void ResetValue() override {
		SetValue(NULL);
	}

  protected:
	size_t size;

  private:
	void SetValueCore(const char *value, size_t len);
};
