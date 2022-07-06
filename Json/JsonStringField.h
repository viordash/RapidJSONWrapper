#pragma once

#include "JsonField.h"

template <bool optional>
class JsonField<char *, optional> : public JsonOptionalField<optional> {
  public:
	char *Value;

	JsonField(JsonFieldsContainer *container, const char *name) : JsonOptionalField<optional>(container, name) {
		Value = NULL;
		size = 0;
		Reset();
	}

	~JsonField() {
		delete[] Value;
	}

	size_t GetSize() override final {
		return size;
	}

	bool TryParseInternal(RapidJsonVal value) override final;
	void WriteTo(RapidJsonDocument doc) override final;

	void CloneFrom(JsonBaseField *other) override final {
		Value = ((JsonField *)other)->Value;
	}
	void SetValue(const char *value, size_t len = 0) {
		SetValueCore(value, len);
	}
	bool EqualTo(JsonBaseField *other) override final {
		return JsonBaseField::EqualTo(other) //
			   && strcmp(Value, ((JsonField *)other)->Value) == 0;
	}

  protected:
	size_t size;
	void Reset() override final {
		SetValue(NULL);
	}

  private:
	void SetValueCore(const char *value, size_t len);
};
