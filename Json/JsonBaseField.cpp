
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonBaseField.h"

JsonBaseField::JsonBaseField(const char *name, bool optional) {
	Name = name;
	hasValue = false;
	this->optional = optional;
}

JsonBaseField::~JsonBaseField() {
}

bool JsonBaseField::Equals(JsonBaseField *otherJsonBaseField) {
	return strcmp(Name, otherJsonBaseField->Name) == 0;
};

bool JsonBaseField::HasMember(RapidJsonValue value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->HasMember(Name)) {
		hasValue = true;
		return true;
	}
	hasValue = false;
	return false;
}