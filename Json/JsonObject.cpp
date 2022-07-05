
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"

JsonObject::JsonObject() {
}

JsonObject::~JsonObject() {
}

bool JsonObject::TryParse(RapidJsonValues value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (!jsonValue->IsObject()) {
		return false;
	}

	for (std::vector<JsonBaseField *>::iterator item = Fields.begin(); item != Fields.end(); item++) {
		auto field = *item;
		if (!field->TryParse(jsonValue)) {
			return false;
		}
	}
	return true;
}

bool JsonObject::TryParseByObject(RapidJsonValues value, const char *objectName) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;

	rapidjson::Value::ConstMemberIterator itr = jsonValue->FindMember(objectName);
	if (itr == jsonValue->MemberEnd()) {
		return false;
	}
	return TryParse((RapidJsonValues)&itr->value);
}

RapidJsonDocument JsonObject::BeginTryParse(const char *jsonStr, int length) {
	if (jsonStr == NULL || length == 0) {
		return NULL;
	}

	rapidjson::Document *doc = new rapidjson::Document();
	if (length < 0) {
		doc->Parse(jsonStr);
	} else {
		doc->Parse(jsonStr, length);
	}
	if (doc->HasParseError()) {
		delete doc;
		return NULL;
	}

	if (!TryParse(doc)) {
		delete doc;
		return NULL;
	}
	return (RapidJsonDocument)doc;
}

void JsonObject::EndTryParse(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	delete jsonDoc;
}

bool JsonObject::TryParse(const char *jsonStr, int length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) {
		return false;
	}
	EndTryParse(doc);
	return true;
}

void JsonObject::WriteTo(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	jsonDoc->SetObject();

	for (const auto &field : Fields) {
		field->WriteTo(jsonDoc);
	}
}

int JsonObject::WriteTo(char *outBuffer, int outBufferSize) {
	rapidjson::Document doc;
	WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	int size = buffer.GetSize();
	if (size > outBufferSize - 1) {
		size = outBufferSize - 1;
	}
	strncpy(outBuffer, jsonStr, size);
	outBuffer[size] = 0;
	return size;
}

int JsonObject::WriteTo(void *parent, TOnJsonStringReady onJsonStringReady) {
	rapidjson::Document doc;
	WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	int size = buffer.GetSize();
	onJsonStringReady(parent, jsonStr, size);
	return size;
}

void JsonObject::CloneFrom(JsonObject *other) {
	if (other == NULL) {
		return;
	}

	for (const auto &field : Fields) {
		auto otherField = other->SeachFieldByName(field->Name);
		if (otherField != NULL) {
			field->CloneFrom(otherField);
		}
	}
}

JsonBaseField *JsonObject::SeachFieldByName(const char *name) {
	for (const auto &field : Fields) {
		if (strcmp(field->Name, name) == 0) {
			return field;
		}
	}
	return NULL;
}

int JsonObject::GetSize() {
	rapidjson::Document doc;
	WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	return buffer.GetSize();
}

bool JsonObject::Equals(JsonObject *other) {
	if (other == NULL) {
		return false;
	}

	if (Fields.size() != other->Fields.size()) {
		return false;
	}

	for (size_t i = 0; i < Fields.size(); i++) {
		if (!Fields[i]->Equals(other->Fields[i])) {
			return false;
		}
	}

	return true;
}