
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonField.h"

JsonField::JsonField(JsonFieldsContainer *container, const char *name, bool optional) {
	Name = name;
	this->optional = optional;
	container->Add(this);
}

bool JsonField::Equals(JsonField *other) {
	return strcmp(Name, other->Name) == 0;
};

bool JsonField::HasMember(RapidJsonValues values) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)values;
	if (jsonValue->HasMember(Name)) {
		return true;
	}
	return false;
}

bool JsonField::ReadFromJson(RapidJsonValues values) {
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

void JsonField::WriteToJson(RapidJsonDocument doc) {
	rapidjson::Value jsonVal;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();

	WriteToJsonCore(&jsonVal);

	jsonDoc->AddMember(rapidjson::StringRef(Name), jsonVal, allocator);
}

JsonIntField::JsonIntField(JsonFieldsContainer *container, const char *name, bool optional) : JsonField(container, name, optional) {
	ResetValue();
}

bool JsonIntField::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsInt()) {
		SetValue(jsonValue->GetInt());
		return true;
	}
	return false;
}

void JsonIntField::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetInt(*((int *)Value));
}

void JsonIntField::CloneFrom(JsonField *other) {
	Value = ((JsonIntField *)other)->Value;
}

bool JsonIntField::Equals(JsonField *other) {
	return JsonField::Equals(other) //
		   && Value == ((JsonIntField *)other)->Value;
}