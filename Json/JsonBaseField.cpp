
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonBaseField.h"

JsonBaseField::JsonBaseField(JsonFieldsContainer *container, const char *name, bool optional) {
	Name = name;
	this->optional = optional;
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

bool JsonBaseField::ReadFromJson(RapidJsonValues values) {
	if (!HasMember(values)) {
		ResetValue();
		return optional;
	}
	rapidjson::Value *jsonValue = (rapidjson::Value *)values;
	auto &jsonVal = (*jsonValue)[Name];

	if (ReadFromJsonCore(&jsonVal)) {
		return true;
	}

	if (jsonVal.IsNull()) {
		ResetValue();
		return true;
	}
	return false;
}

void JsonBaseField::WriteToJson(RapidJsonDocument doc) {
	rapidjson::Value jsonVal;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();

	WriteToJsonCore(&jsonVal);

	jsonDoc->AddMember(rapidjson::StringRef(Name), jsonVal, allocator);
}