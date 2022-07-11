#pragma once

#include "JsonField.h"

class JsonBaseArray;

template <bool optional>
class JsonField<JsonBaseArray *, optional> : public JsonOptionalField<optional> {
  public:
	JsonField(JsonFieldsContainer *container, const char *name, JsonBaseArray *array) : JsonOptionalField<optional>(container, name) {
		this->array = array;
	}

	size_t GetSize() override final {
		return array->GetSize();
	}

	bool TryParseInternal(RapidJsonValues value) override final;
	void WriteToDoc(RapidJsonDocument doc) override final;

	void CloneFrom(JsonBaseField *other) override final {
		array->CloneFrom((((JsonField *)other)->array));
	}
	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other) //
			   && array->Equals(((JsonField *)other)->array);
	}

  protected:
	JsonBaseArray *array;

	void Reset() override final {
		array->Reset();
	}

  private:
};
