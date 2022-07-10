#pragma once

#include "JsonField.h"

template <class TItem>
class JsonArray;

template <class TItem, bool optional>
class JsonField<JsonArray<TItem> *, optional> : public JsonOptionalField<optional> {
  public:
	JsonField(JsonFieldsContainer *container, const char *name, JsonArray<TItem> *array) : JsonOptionalField<optional>(container, name) {
		this->array = array;
	}

	size_t GetSize() override final {
		return array->GetSize();
	}

	bool TryParseInternal(RapidJsonValues value) override final {
	}
	void WriteToDoc(RapidJsonDocument doc) override final {
	}

	void CloneFrom(JsonBaseField *other) override final {
		array->CloneFrom((((JsonField *)other)->array));
	}
	bool Equals(JsonBaseField *other) override final {
		return JsonBaseField::Equals(other) //
			   && array->Equals(((JsonField *)other)->array);
	}

	template <typename TObj>
	TObj *Cast() const {
		return (TObj *)array;
	}

  protected:
	JsonArray<TItem> *array;

	void Reset() override final {
		array->Reset();
	}

  private:
};
