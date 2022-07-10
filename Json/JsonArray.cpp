
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"
#include "JsonArray.h"

bool JsonBaseArray::TryParse(RapidJsonValues value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (!jsonValue->IsArray()) {
		return false;
	}

	for (const auto &item : jsonValue->GetArray()) {
		if (!ParseItem((RapidJsonVal)&item)) {
			return false;
		}
	}
	return true;
}

bool JsonBaseArray::TryParseByObject(RapidJsonValues value, const char *objectName) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;

	rapidjson::Value::ConstMemberIterator itr = jsonValue->FindMember(objectName);
	if (itr == jsonValue->MemberEnd()) {
		return false;
	}
	return TryParse((RapidJsonValues) & (itr->value));
}

RapidJsonDocument JsonBaseArray::BeginTryParse(const char *jsonStr, int length) {
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

	if (!this->TryParse(doc)) {
		delete doc;
		return NULL;
	}
	return (RapidJsonDocument)doc;
}

void JsonBaseArray::EndTryParse(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	delete jsonDoc;
}

void JsonBaseArray::WriteToCore(RapidJsonDocument doc, std::vector<JsonBaseField *> *items) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	jsonDoc->SetArray();
	for (const auto &item : *items) {
		rapidjson::Document aChildDoc(&allocator);
		item->WriteTo(&aChildDoc);
		jsonDoc->PushBack(aChildDoc, allocator);
	}
}

int JsonBaseArray::WriteTo(char *outBuffer, int outBufferSize) {
	rapidjson::Document doc;
	this->WriteTo(&doc);
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

int JsonBaseArray::WriteToAsync(void *parent, TOnReady onReady) {
	rapidjson::Document doc;
	this->WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *json = buffer.GetString();
	int size = buffer.GetSize();
	onReady(parent, json, size);
	return size;
}

int JsonBaseArray::GetSize() {
	rapidjson::Document doc;
	this->WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	return buffer.GetSize();
}
