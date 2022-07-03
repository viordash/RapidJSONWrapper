#pragma once

#include "JsonBaseField.h"

template <class T>
class JsonField : public JsonBaseField {
  public:
	T Value;

	JsonField(JsonFieldsContainer *container, const char *name, bool optional = false) : JsonBaseField(container, name, optional) {
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
	void SetValue(T value) {
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