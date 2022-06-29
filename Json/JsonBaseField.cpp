
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonBaseField.h"

JsonBaseField::JsonBaseField(const char *name, bool optional) {
	Name = name;
	this->optional = optional;
}

bool JsonBaseField::Equals(JsonBaseField *other) {
	return strcmp(Name, other->Name) == 0;
};

bool JsonBaseField::HasMember(RapidJsonValue value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->HasMember(Name)) {
		return true;
	}
	return false;
}