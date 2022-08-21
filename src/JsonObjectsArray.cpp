
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

JsonObjectsArray::~JsonObjectsArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}

bool JsonObjectsArray::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());

	for (const auto &jItem : jArray) {
		auto newItem = CreateItem();
		if (!newItem->TryParse((TJsonDocument *)&jItem) || !Add(newItem)) {
			delete newItem;
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}

bool JsonObjectsArray::Add(JsonObject *item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}

void JsonObjectsArray::AddInternal(JsonObject *item) { Items.push_back(item); }

bool JsonObjectsArray::Update(size_t index, JsonObject *item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = (JsonObject *)item;
	return true;
}

void JsonObjectsArray::Remove(JsonObject *item) {
	auto iter = Find(item);
	if (iter != Items.end()) {
		DeleteItem(*iter);
		Items.erase(iter);
	}
}
std::vector<JsonObject *>::iterator JsonObjectsArray::Find(JsonObject *item) {
	if (item != NULL) {
		for (auto iter = Items.begin(); iter != Items.end(); iter++) {
			if (*((JsonObject *)*iter) == *((JsonObject *)item)) { return iter; }
		}
	}
	return Items.end();
}

void JsonObjectsArray::DeleteItem(JsonObject *item) { delete ((JsonObject *)item); }

void JsonObjectsArray::WriteToDoc(TJsonDocument *doc) {
	auto &allocator = doc->GetAllocator();
	doc->SetArray();
	doc->Reserve(Items.size(), allocator);

	for (const auto &item : Items) {
		rapidjson::Document childDoc(&allocator);
		JsonObject *jObject = (JsonObject *)item;
		jObject->WriteToDoc(&childDoc);
		doc->PushBack(childDoc, allocator);
	}
}

bool operator!=(const JsonObjectsArray &v1, const JsonObjectsArray &v2) { return !((JsonObjectsArray *)&v1)->Equals((JsonObjectsArray *)&v2); }
bool operator==(const JsonObjectsArray &v1, const JsonObjectsArray &v2) { return !(v1 != v2); }

bool JsonObjectsArray::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonObjectsArray *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (*((JsonObject *)Items[i]) != *((JsonObject *)((JsonObjectsArray *)other)->Items[i])) { return false; }
	}
	return true;
}

void JsonObjectsArray::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonObjectsArray *)other);
	for (const auto &item : otherArray->Items) { delete (JsonObject *)item; }
	otherArray->Items.clear();

	for (const auto &item : Items) {
		auto newItem = CreateItem();
		item->CloneTo(newItem);
		otherArray->AddInternal(newItem);
	}
}