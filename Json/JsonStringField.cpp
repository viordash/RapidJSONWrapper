
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonStringField.h"

JsonStringField::JsonStringField(const char *name, const char *value, int size, bool optional) : JsonBaseField(name, optional) {
	Value = new char[size];
	this->size = size;
	SetValue(value);
	printf("ctor JsonStringField: %s\n", name);
}

JsonStringField::~JsonStringField() {
	delete[] Value;
	printf("~JsonStringField: %s\n", Name);
}

bool JsonStringField::ReadFromJson(RapidJsonValue value) {
	if (!HasMember(value)) {
		return optional;
	}

	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	auto &jsonVal = (*jsonValue)[Name];

	if (jsonVal.IsString()) {
		SetValue(jsonVal.GetString());
		return true;
	}

	if (jsonVal.IsNull()) {
		return true;
	}
	return false;
}

void JsonStringField::WriteToJson(RapidJsonDocument doc) {
	rapidjson::Value json_val;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();

	json_val.SetString(rapidjson::StringRef(Value));
	jsonDoc->AddMember(rapidjson::StringRef(Name), json_val, allocator);
}

void JsonStringField::CloneFrom(JsonBaseField *otherJsonField) {
	SetValue(((JsonStringField *)otherJsonField)->Value);
}

void JsonStringField::SetValue(const char *value) {
	if (value == NULL) {
		Value[0] = 0;
	} else {
		strncpy(Value, value, GetSize() - 1);
		Value[GetSize() - 1] = 0;
	}
}

bool JsonStringField::Equals(JsonBaseField *otherJsonField) {
	return JsonBaseField::Equals(otherJsonField) //
		   && strcmp(Value, ((JsonStringField *)otherJsonField)->Value) == 0;
}