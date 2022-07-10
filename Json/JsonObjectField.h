#pragma once

#include "JsonField.h"

class JsonObject;

template <bool optional>
class JsonField<JsonObject *, optional> : public JsonOptionalField<optional> {
  public:
	JsonField(JsonFieldsContainer *container, const char *name, JsonObject *object) : JsonOptionalField<optional>(container, name) {
		this->object = object;
	}

	size_t GetSize() override final {
		return object->GetSize();
	}

	bool TryParseInternal(RapidJsonValues value) override final;
	void WriteToDoc(RapidJsonDocument doc) override final;

	void CloneFrom(JsonBaseField *other) override final {
		object->CloneFrom((((JsonField *)other)->object));
	}
	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other) //
			   && object->Equals(((JsonField *)other)->object);
	}

	template <typename TObj>
	TObj *Cast() const {
		return (TObj *)object;
	}

  protected:
	JsonObject *object;

	void Reset() override final {
		object->Reset();
	}

  private:
};
