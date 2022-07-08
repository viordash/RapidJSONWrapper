#pragma once

#include "JsonField.h"

template <bool optional>
class JsonField<char *, optional> : public JsonOptionalField<optional> {
	class JsonFieldValue {
	  public:
		JsonFieldValue(JsonField *owner) {
			this->owner = owner;
		}

		char *operator=(const char *right) {
			owner->SetCore(right, 0);
			return owner->value;
		}

		operator char *() const {
			return owner->value;
		}

		void Set(const char *value, size_t len) {
			owner->SetCore(value, len);
		}

	  private:
		JsonField *owner;
	};

  public:
	JsonFieldValue Value;

	JsonField(JsonFieldsContainer *container, const char *name) : JsonOptionalField<optional>(container, name), Value(this) {
		value = NULL;
		size = 0;
		Reset();
	}

	~JsonField() {
		delete[] value;
	}

	size_t GetSize() override final {
		return size;
	}

	bool TryParseInternal(RapidJsonVal value) override final;
	void WriteTo(RapidJsonDocument doc) override final;

	void CloneFrom(JsonBaseField *other) override final {
		SetCore(((JsonField *)other)->value, ((JsonField *)other)->GetSize());
	}

	bool EqualTo(JsonBaseField *other) override final {
		return JsonBaseField::EqualTo(other) //
			   && strcmp(value, ((JsonField *)other)->value) == 0;
	}

	void Reset() override final {
		SetCore(NULL, 0);
	}

  protected:
	char *value;
	size_t size;

  private:
	void SetCore(const char *value, size_t len);
};
