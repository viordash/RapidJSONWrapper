
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

bool JsonArrayBase::TryParse(const char *jsonStr, size_t length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) { return false; }
	EndTryParse(doc);
	return true;
}

TJsonDocument *JsonArrayBase::BeginTryParse(const char *jsonStr, size_t length) {
	if (jsonStr == NULL) { return NULL; }

	rapidjson::Document *doc = new rapidjson::Document();
	if (length == 0) {
		doc->Parse(jsonStr);
	} else {
		doc->Parse(jsonStr, length);
	}
	if (doc->HasParseError() || !this->TryDocParse(doc)) {
		delete doc;
		return NULL;
	}
	return doc;
}

void JsonArrayBase::EndTryParse(TJsonDocument *doc) { delete doc; }

size_t JsonArrayBase::WriteToString(char *outBuffer, size_t outBufferSize) {
	rapidjson::Document doc;
	this->WriteToDoc(&doc);
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

size_t JsonArrayBase::DirectWriteTo(void *parent, TOnReady onReady) {
	rapidjson::Document doc;
	this->WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *json = buffer.GetString();
	size_t size = buffer.GetSize();
	onReady(parent, json, size);
	return size;
}