#pragma once

#include "JsonBaseField.h"

template <class T, bool optional = false>
class JsonField : public JsonOptionalField<optional> {
	class JsonFieldValue {
	  public:
		JsonFieldValue(JsonField *owner, const T value) : JsonFieldValue(owner) {
			owner->SetValue(value);
		}
		JsonFieldValue(JsonField *owner) {
			this->owner = owner;
		}

		T operator=(const T right) {
			owner->SetValue(right);
			return owner->value;
		}

		operator T() const {
			return owner->value;
		}

	  private:
		JsonField *owner;
	};

  public:
	JsonFieldValue Value;

	JsonField(JsonFieldsContainer *container, const char *name, const T value) : JsonOptionalField<optional>(container, name), Value(this, value) {
	}

	JsonField(JsonFieldsContainer *container, const char *name) : JsonOptionalField<optional>(container, name), Value(this) {
		Reset();
	}

	size_t GetSize() override final {
		return sizeof(value);
	}

	bool TryParseInternal(RapidJsonVal value) override final;
	void WriteToDoc(RapidJsonDocument doc) override final;
	void CloneFrom(JsonBaseField *other) override final {
		value = ((JsonField *)other)->value;
	}

	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other)		//
			   && GetSize() == other->GetSize() //
			   && value == ((JsonField *)other)->value;
	}

	void Reset() override final {
		SetValue(0);
	}

  protected:
	T value;
	void SetValue(const T value) {
		this->value = value;
	}
};
