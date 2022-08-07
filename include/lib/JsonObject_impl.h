#pragma once

#include "LibJson.h"

bool JsonObject::TryParse(TJsonDocument *doc) {
	if (!doc->IsObject()) { return false; }

	for (size_t i = 0; i < Names.size(); i++) {
		auto value = Values[i];
		const char *name = *(Names[i]);

		rapidjson::Value::MemberIterator member = doc->MemberBegin();
		while (member != doc->MemberEnd()) {
			auto memberName = member->name.GetString();
			if (memberName == name || strcmp(memberName, name) == 0) {
				rapidjson::Value &jsonVal = member->value;
				if (!value->TryParse(&jsonVal)) { return false; }
				break;
			};
			member++;
		}
		if (member == doc->MemberEnd()) {
			if (value->TryNotPresented()) {
				value->Reset();
			} else {
				return false;
			}
		}
	}
	return true;
}

TJsonDocument *JsonObject::BeginTryParse(const char *jsonStr, size_t length) {
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

void JsonObject::EndTryParse(TJsonDocument *doc) { delete doc; }

bool JsonObject::TryParse(const char *jsonStr, size_t length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) { return false; }
	EndTryParse(doc);
	return true;
}

void JsonObject::WriteToDoc(TJsonDocument *doc) {
	doc->SetObject();
	for (size_t i = 0; i < Names.size(); i++) { Values[i]->WriteToDoc(doc, Names[i]); }
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
	if (Names.size() != other->Names.size()) { return false; }

	for (size_t i = 0; i < Names.size(); i++) {
		if (strcmp(*(Names[i]), *(other->Names[i])) != 0) { return false; }
		if (!Values[i]->Equals(other->Values[i])) { return false; }
	}
	return true;
}

void JsonObject::CloneTo(JsonObject *other) {
	for (size_t i = 0; i < Names.size(); i++) {
		auto otherValue = other->GetField(Names[i]);
		if (otherValue != NULL) { Values[i]->CloneTo(other->Values[i]); }
	}
}