#pragma once

#include "JsonField.h"

template <bool optional>
class JsonField<char *, optional> : public JsonBaseField {
  public:
	char *Value;

	JsonField(JsonFieldsContainer *container, const char *name, size_t maxSize = 8192) : JsonBaseField(container, name, optional) {
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

	bool ReadFromJsonCore(RapidJsonVal value) override final {
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;
		if (jsonValue->IsString()) {
			SetValue(jsonValue->GetString(), jsonValue->GetStringLength());
			return true;
		}
		return false;
	}
	void WriteToJsonCore(RapidJsonVal value) override final {
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;
		jsonValue->SetString(Value, GetSize() - 1);
	}
	void CloneFrom(JsonBaseField *other) override final {
		Value = ((JsonField *)other)->Value;
	}
	void SetValue(const char *value, size_t len = 0) {
		if (value != NULL) {
			if (len == 0) {
				len = strlen(value);
			}
		} else {
			len = 0;
		}
		if (len >= maxSize) {
			len = maxSize - 1;
		}

		if (len == size - 1) {
			if (value != NULL) {
				memcpy(Value, value, len);
			}
			Value[len] = 0;
			return;
		}

		if (Value != NULL) {
			char *t = Value;
			Value = NULL;
			delete[] t;
		}

		size = len + 1;
		Value = new char[size];
		if (value != NULL) {
			memcpy(Value, value, len);
		}
		Value[len] = 0;
	}
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