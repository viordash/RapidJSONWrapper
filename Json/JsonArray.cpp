
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"
#include "JsonArray.h"

JsonArray::JsonArray(bool destroyItems) : destroyItems(destroyItems) {
}

JsonArray::~JsonArray() {
	if (destroyItems) {
		for (auto item : Items) {
			delete item;
		}
	}
	Items.clear();
}

bool JsonArray::Add(JsonObject *item) {
	if (item == NULL) {
		return false;
	}
	if (!Validate()) {
		return false;
	}
	Items.push_back(item);
	return true;
}

void JsonArray::Remove(JsonObject *item) {
	if (item == NULL) {
		return;
	}
	auto iter = Find(item);
	if (iter != Items.end()) {
		Items.erase(iter);
	}
}

std::vector<JsonObject *>::iterator JsonArray::Find(JsonObject *item) {
	for (std::vector<JsonObject *>::iterator iter = Items.begin(); iter != Items.end(); iter++) {
		if ((*iter)->Equals(item)) {
			return iter;
		}
	}
	return Items.end();
}

bool JsonArray::TryParse(RapidJsonValues value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (!jsonValue->IsArray()) {
		return false;
	}

	for (const auto &item : jsonValue->GetArray()) {
		auto newItem = CreateItem();
		if (!ParseItem((RapidJsonVal)&item, newItem)) {
			delete newItem;
			return false;
		}
	}
	return true;
}

bool JsonArray::TryParseByObject(RapidJsonValues value, const char *objectName) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;

	rapidjson::Value::ConstMemberIterator itr = jsonValue->FindMember(objectName);
	if (itr == jsonValue->MemberEnd()) {
		return false;
	}
	return TryParse((RapidJsonValues) & (itr->value));
}

RapidJsonDocument JsonArray::BeginTryParse(const char *jsonStr, int length) {
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

void JsonArray::EndTryParse(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	delete jsonDoc;
}

bool JsonArray::TryParse(const char *jsonStr, int length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) {
		return false;
	}
	EndTryParse(doc);
	return true;
}

bool JsonArray::ParseItem(RapidJsonVal value, JsonObject *newItem) {
	if (!newItem->TryParse(value) || !newItem->Validate()) {
		for (const auto &item : Items) {
			delete item;
		}
		Items.clear();
		return false;
	}
	return Add(newItem);
}

void JsonArray::WriteTo(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	jsonDoc->SetArray();
	for (const auto &item : Items) {
		rapidjson::Document aChildDoc(&allocator);
		item->WriteTo(&aChildDoc);
		jsonDoc->PushBack(aChildDoc, allocator);
	}
}

int JsonArray::WriteTo(char *outBuffer, int outBufferSize) {
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

int JsonArray::WriteTo(void *parent, TOnReady onReady) {
	rapidjson::Document doc;
	WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *json = buffer.GetString();
	int size = buffer.GetSize();
	onReady(parent, json, size);
	return size;
}

void JsonArray::CloneFrom(JsonArray *other) {
	if (other == NULL) {
		return;
	}

	for (const auto &item : Items) {
		delete item;
	}
	Items.clear();

	for (const auto &item : other->Items) {
		auto newItem = CreateItem();
		newItem->CloneFrom(item);
		if (!Add(newItem)) {
			delete newItem;
			return;
		}
	}
}

int JsonArray::GetSize() {
	rapidjson::Document doc;
	WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	return buffer.GetSize();
}

bool JsonArray::Equals(JsonArray *other) {
	if (other == NULL) {
		return false;
	}
	if (Items.size() != other->Items.size()) {
		return false;
	}

	for (size_t i = 0; i < Items.size(); i++) {
		if (!Items[i]->Equals(other->Items[i])) {
			return false;
		}
	}
	return true;
}

void JsonArray::Reset() {
	for (const auto &item : Items) {
		item->Reset();
	}
}