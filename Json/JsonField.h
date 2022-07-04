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

	bool ReadFromJsonCore(RapidJsonVal value) override final;
	void WriteToJsonCore(RapidJsonVal value) override final;
	void CloneFrom(JsonBaseField *other) override final {
		Value = ((JsonField *)other)->Value;
	}
	void SetValue(const T value) {
		Value = value;
	}
	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other)		//
			   && GetSize() == other->GetSize() //
			   && Value == ((JsonField *)other)->Value;
	}

	void ResetValue() override {
		SetValue(0);
	}
};
