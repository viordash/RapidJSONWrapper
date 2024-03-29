
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

JsonValueBase *JsonFieldsContainer::GetField(const char *name) {
	for (std::vector<JsonValueBase *>::iterator item = Fields.begin(); item != Fields.end(); item++) {
		auto field = *item;
		if (field->Name == name || strcmp(field->Name, name) == 0) { return field; }
	}
	return NULL;
}

bool JsonObject::TryParse(TJsonDocument *doc) {
	if (!doc->IsObject()) { return false; }

	for (std::vector<JsonValueBase *>::iterator item = Fields.begin(); item != Fields.end(); item++) {
		auto field = *item;
		if (!field->TryParse(doc)) { return false; }
	}
	if (!this->Validate()) { return false; }
	return true;
}

TJsonDocument *JsonObject::BeginTryStringParse(const char *jsonStr, size_t length) {
	if (jsonStr == NULL) { return NULL; }

	auto doc = new rapidjson::Document();
	if (length == 0) {
		doc->Parse(jsonStr);
	} else {
		doc->Parse(jsonStr, length);
	}
	if (doc->HasParseError() || !TryParse(doc)) {
		delete doc;
		return NULL;
	}
	return doc;
}

void JsonObject::EndTryStringParse(TJsonDocument *doc) { delete doc; }

bool JsonObject::TryStringParse(const char *jsonStr, size_t length) {
	auto doc = BeginTryStringParse(jsonStr, length);
	if (doc == NULL) { return false; }
	EndTryStringParse(doc);
	return true;
}

void JsonObject::WriteToDoc(TJsonDocument *doc) {
	doc->SetObject();
	for (const auto &field : Fields) { field->WriteToDoc(doc); }
}

size_t JsonObject::WriteToString(char *outBuffer, size_t outBufferSize) {
	rapidjson::Document doc;
	WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	size_t size = buffer.GetSize();
	if (size > outBufferSize - 1) { size = outBufferSize - 1; }
	strncpy(outBuffer, jsonStr, size);
	outBuffer[size] = 0;
	return size;
}

size_t JsonObject::DirectWriteTo(void *parent, TOnReady onReady) {
	rapidjson::Document doc;
	WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *json = buffer.GetString();
	size_t size = buffer.GetSize();
	onReady(parent, json, size);
	return size;
}

bool operator!=(const JsonObject &v1, const JsonObject &v2) { return !((JsonObject *)&v1)->Equals((JsonObject *)&v2); }
bool operator==(const JsonObject &v1, const JsonObject &v2) { return !(v1 != v2); }

bool JsonObject::Equals(JsonObject *other) {
	if (Fields.size() != other->Fields.size()) { return false; }

	for (size_t i = 0; i < other->Fields.size(); i++) {
		if (!Fields[i]->Equals(other->Fields[i])) { return false; }
	}
	return true;
}

void JsonObject::CloneTo(JsonObject *other) {
	for (const auto &field : Fields) {
		auto otherField = other->GetField(field->Name);
		if (otherField != NULL) { field->CloneTo(otherField); }
	}
}