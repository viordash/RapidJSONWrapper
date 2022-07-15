
#include "JsonObject.h"

bool JsonObject::TryParse(TJsonDocument *doc) {
	if (!doc->IsObject()) { return false; }

	for (std::vector<JsonValueBase *>::iterator item = Fields.begin(); item != Fields.end(); item++) {
		auto field = *item;
		if (!field->TryParse(doc)) { return false; }
	}
	return true;
}

TJsonDocument *JsonObject::BeginTryParse(const char *jsonStr, int length) {
	if (jsonStr == NULL || length == 0) { return NULL; }

	auto doc = new rapidjson::Document();
	if (length < 0) {
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

bool JsonObject::TryParse(const char *jsonStr, int length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) { return false; }
	EndTryParse(doc);
	return true;
}

void JsonObject::WriteToDoc(TJsonDocument *doc) {
	doc->SetObject();
	for (const auto &field : Fields) { field->WriteToDoc(doc); }
}

int JsonObject::WriteToString(char *outBuffer, int outBufferSize) {
	rapidjson::Document doc;
	WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	int size = buffer.GetSize();
	if (size > outBufferSize - 1) { size = outBufferSize - 1; }
	strncpy(outBuffer, jsonStr, size);
	outBuffer[size] = 0;
	return size;
}

int JsonObject::DirectWriteTo(void *parent, TOnReady onReady) {
	rapidjson::Document doc;
	WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *json = buffer.GetString();
	int size = buffer.GetSize();
	onReady(parent, json, size);
	return size;
}
