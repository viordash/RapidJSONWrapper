#pragma once

#include "JsonBaseField.h"

template <class T, bool optional = false>
class JsonField : public JsonOptionalField<optional> {
  public:
	T Value;

	JsonField(JsonFieldsContainer *container, const char *name) : JsonOptionalField<optional>(container, name) {
		ResetValue();
	}

	size_t GetSize() override final {
		return sizeof(Value);
	}

	bool TryParseInternal(RapidJsonVal value) override final;
	void WriteTo(RapidJsonDocument doc) override final;
	void CloneFrom(JsonBaseField *other) override final {
		Value = ((JsonField *)other)->Value;
	}
	void SetValue(const T value) {
		Value = value;
	}
	bool EqualTo(JsonBaseField *other) override final {
		return JsonBaseField::EqualTo(other)	//
			   && GetSize() == other->GetSize() //
			   && Value == ((JsonField *)other)->Value;
	}

  protected:
	void ResetValue() override final {
		SetValue(0);
	}
};
