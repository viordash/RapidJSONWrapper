
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

void JsonBaseField::WriteToJson(RapidJsonDocument doc) {
	rapidjson::Value jsonVal;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();

	this->WriteToJsonCore(&jsonVal);

	jsonDoc->AddMember(rapidjson::StringRef(Name), jsonVal, allocator);
}
