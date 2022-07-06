
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonBaseField.h"

JsonBaseField::JsonBaseField(JsonFieldsContainer *container, const char *name) {
	Name = name;
	container->Add(this);
}

bool JsonBaseField::EqualTo(JsonBaseField *other) {
	return strcmp(Name, other->Name) == 0;
};

bool JsonBaseField::HasMember(RapidJsonValues values) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)values;
	if (jsonValue->HasMember(Name)) {
		return true;
	}
	return false;
}

#define TryParse_T(values, optional)                                                                                                                           \
	{                                                                                                                                                          \
		if (!HasMember(values)) {                                                                                                                              \
			this->Reset();                                                                                                                                \
			return optional;                                                                                                                                   \
		}                                                                                                                                                      \
		rapidjson::Value *jsonValue = (rapidjson::Value *)values;                                                                                              \
		auto &jsonVal = (*jsonValue)[Name];                                                                                                                    \
		if (this->TryParseInternal(&jsonVal)) {                                                                                                                \
			return true;                                                                                                                                       \
		}                                                                                                                                                      \
		if (jsonVal.IsNull()) {                                                                                                                                \
			this->Reset();                                                                                                                                \
			return true;                                                                                                                                       \
		}                                                                                                                                                      \
		return false;                                                                                                                                          \
	}

template <>
bool JsonOptionalField<true>::TryParse(RapidJsonValues values) {
	TryParse_T(values, true);
}
template <>
bool JsonOptionalField<false>::TryParse(RapidJsonValues values) {
	TryParse_T(values, false);
}