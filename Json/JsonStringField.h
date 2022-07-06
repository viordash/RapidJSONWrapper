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
		SetValue(((JsonField *)other)->Value, ((JsonField *)other)->GetSize());
	}
	void SetValue(const char *value, size_t len = 0) {
		SetValueCore(value, len);
	}
	bool EqualTo(JsonBaseField *other) override final {
		return JsonBaseField::EqualTo(other) //
			   && strcmp(Value, ((JsonField *)other)->Value) == 0;
	}

	void Reset() override final {
		SetValue(NULL);
	}

  protected:
	size_t size;

  private:
	void SetValueCore(const char *value, size_t len);
};
