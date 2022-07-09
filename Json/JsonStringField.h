#pragma once

#include "JsonField.h"

template <bool optional>
class JsonField<char *, optional> : public JsonOptionalField<optional> {
	class JsonFieldValue {
	  public:
		JsonFieldValue(JsonField *owner, const char *value, size_t len) : JsonFieldValue(owner) {
			owner->SetCore(value, len);
		}
		JsonFieldValue(JsonField *owner) {
			this->owner = owner;
			owner->value = NULL;
			owner->size = 0;
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

	JsonField(JsonFieldsContainer *container, const char *name, const char *value, size_t len = 0)
		: JsonOptionalField<optional>(container, name), Value(this, value, len) {
	}

	JsonField(JsonFieldsContainer *container, const char *name) : JsonOptionalField<optional>(container, name), Value(this) {
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

	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other) //
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
