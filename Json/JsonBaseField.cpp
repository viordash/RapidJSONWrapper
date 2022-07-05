
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonBaseField.h"

JsonBaseField::JsonBaseField(JsonFieldsContainer *container, const char *name) {
	Name = name;
	container->Add(this);
}

bool JsonBaseField::Equals(JsonBaseField *other) {
	return strcmp(Name, other->Name) == 0;
};

bool JsonBaseField::HasMember(RapidJsonValues values) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)values;
	if (jsonValue->HasMember(Name)) {
		return true;
	}
	return false;
}

void JsonBaseField::WriteTo(RapidJsonDocument doc) {
	rapidjson::Value jsonVal;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();

	this->WriteToInternal(&jsonVal);

	jsonDoc->AddMember(rapidjson::StringRef(Name), jsonVal, allocator);
}

#define TryParse_T(values, optional)                                                                                                                       \
	{                                                                                                                                                          \
		if (!HasMember(values)) {                                                                                                                              \
			this->ResetValue();                                                                                                                                \
			return optional;                                                                                                                                   \
		}                                                                                                                                                      \
		rapidjson::Value *jsonValue = (rapidjson::Value *)values;                                                                                              \
		auto &jsonVal = (*jsonValue)[Name];                                                                                                                    \
		if (this->TryParseInternal(&jsonVal)) {                                                                                                                \
			return true;                                                                                                                                       \
		}                                                                                                                                                      \
		if (jsonVal.IsNull()) {                                                                                                                                \
			this->ResetValue();                                                                                                                                \
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