
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

JsonObjectsArray::~JsonObjectsArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}

bool JsonObjectsArray::TryParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());

	for (const auto &jItem : jArray) {
		auto newItem = CreateInstance();
		if (!newItem->TryParse((TJsonDocument *)&jItem) || !Add(newItem)) {
			delete newItem;
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}

bool JsonObjectsArray::TryParse(const char *jsonStr, size_t length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) { return false; }
	EndTryParse(doc);
	return true;
}

TJsonDocument *JsonObjectsArray::BeginTryParse(const char *jsonStr, size_t length) {
	if (jsonStr == NULL) { return NULL; }

	rapidjson::Document *doc = new rapidjson::Document();
	if (length == 0) {
		doc->Parse(jsonStr);
	} else {
		doc->Parse(jsonStr, length);
	}
	if (doc->HasParseError() || !this->TryParse(doc)) {
		delete doc;
		return NULL;
	}
	return doc;
}

void JsonObjectsArray::EndTryParse(TJsonDocument *doc) { delete doc; }

bool JsonObjectsArray::Add(JsonObject *item) {
	if (!Validate(item)) { return false; }
	Items.push_back(item);
	return true;
}

void JsonObjectsArray::DeleteItem(JsonObject *item) { delete ((JsonObject *)item); }