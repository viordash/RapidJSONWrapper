#pragma once

#include "JsonField.h"

class JsonObject;

template <bool optional>
class JsonField<JsonObject *, optional> : public JsonOptionalField<optional> {
  public:
	JsonObject *Object;

	JsonField(JsonFieldsContainer *container, const char *name, JsonObject *object) : JsonOptionalField<optional>(container, name) {
		this->Object = object;
	}

	size_t GetSize() override final {
		return Object->GetSize();
	}

	bool TryParseInternal(RapidJsonVal value) override final;
	void WriteTo(RapidJsonDocument doc) override final;

	void CloneFrom(JsonBaseField *other) override final {
		Object->CloneFrom((((JsonField *)other)->Object));
	}
	void SetObject(const JsonObject *object) {
		if (object != NULL) {
			Object->CloneFrom((JsonObject *)object);
		}
	}
	bool EqualTo(JsonBaseField *other) override final {
		return JsonBaseField::EqualTo(other) //
			   && Object->EqualTo(((JsonField *)other)->Object);
	}

  protected:
	void ResetValue() override final {
	}

  private:
};
