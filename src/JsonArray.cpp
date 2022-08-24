
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <> std::vector<char *>::iterator JsonArray<char *>::Find(char *item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
		if (*iter != NULL && item != NULL && strcmp(*iter, item) == 0) { return iter; }
	}
	return Items.end();
}

template <> std::vector<TBoolArray>::iterator JsonArray<TBoolArray>::Find(TBoolArray item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int64_t>::iterator JsonArray<int64_t>::Find(int64_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint64_t>::iterator JsonArray<uint64_t>::Find(uint64_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int32_t>::iterator JsonArray<int32_t>::Find(int32_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint32_t>::iterator JsonArray<uint32_t>::Find(uint32_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int16_t>::iterator JsonArray<int16_t>::Find(int16_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint16_t>::iterator JsonArray<uint16_t>::Find(uint16_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int8_t>::iterator JsonArray<int8_t>::Find(int8_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint8_t>::iterator JsonArray<uint8_t>::Find(uint8_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<double>::iterator JsonArray<double>::Find(double item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<float>::iterator JsonArray<float>::Find(float item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
/*


*/
template <> void JsonArray<char *>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		if ((char *)item != NULL) {
			doc->PushBack(rapidjson::Value(rapidjson::StringRef((char *)item)).Move(), allocator);
		} else {
			rapidjson::Value json_val;
			doc->PushBack(json_val.SetNull(), allocator);
		}
	}
}
template <> void JsonArray<TBoolArray>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((bool)item).Move(), allocator); }
}
template <> void JsonArray<int64_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((int64_t)item).Move(), allocator); }
}
template <> void JsonArray<uint64_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((uint64_t)item).Move(), allocator); }
}
template <> void JsonArray<int32_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((int32_t)item).Move(), allocator); }
}
template <> void JsonArray<uint32_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((uint32_t)item).Move(), allocator); }
}
template <> void JsonArray<int16_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((int16_t)item).Move(), allocator); }
}
template <> void JsonArray<uint16_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((uint16_t)item).Move(), allocator); }
}
template <> void JsonArray<int8_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((int8_t)item).Move(), allocator); }
}
template <> void JsonArray<uint8_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((uint8_t)item).Move(), allocator); }
}
template <> void JsonArray<double>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((double)item).Move(), allocator); }
}
template <> void JsonArray<float>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) { doc->PushBack(rapidjson::Value((float)item).Move(), allocator); }
}
/*


*/
template <> void JsonArray<char *>::AddInternal(char *item) {
	if (item == NULL) {
		Items.push_back(item);
	} else {
		auto len = strlen((char *)item);
		auto newItem = new char[len + 1];
		memcpy(newItem, (char *)item, len);
		newItem[len] = 0;
		Items.push_back(newItem);
	}
}
template <> void JsonArray<TBoolArray>::AddInternal(TBoolArray item) { Items.push_back(item); }
template <> void JsonArray<int64_t>::AddInternal(int64_t item) { Items.push_back(item); }
template <> void JsonArray<uint64_t>::AddInternal(uint64_t item) { Items.push_back(item); }
template <> void JsonArray<int32_t>::AddInternal(int32_t item) { Items.push_back(item); }
template <> void JsonArray<uint32_t>::AddInternal(uint32_t item) { Items.push_back(item); }
template <> void JsonArray<int16_t>::AddInternal(int16_t item) { Items.push_back(item); }
template <> void JsonArray<uint16_t>::AddInternal(uint16_t item) { Items.push_back(item); }
template <> void JsonArray<int8_t>::AddInternal(int8_t item) { Items.push_back(item); }
template <> void JsonArray<uint8_t>::AddInternal(uint8_t item) { Items.push_back(item); }
template <> void JsonArray<double>::AddInternal(double item) { Items.push_back(item); }
template <> void JsonArray<float>::AddInternal(float item) { Items.push_back(item); }
/*


*/
template <> bool JsonArray<char *>::Add(char *item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<TBoolArray>::Add(TBoolArray item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int64_t>::Add(int64_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint64_t>::Add(uint64_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int32_t>::Add(int32_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint32_t>::Add(uint32_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int16_t>::Add(int16_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint16_t>::Add(uint16_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int8_t>::Add(int8_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint8_t>::Add(uint8_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<double>::Add(double item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<float>::Add(float item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
/*


*/
template <> void JsonArray<char *>::DeleteItem(char *item) { delete[] item; }
template <> void JsonArray<TBoolArray>::DeleteItem(TBoolArray item) {}
template <> void JsonArray<int64_t>::DeleteItem(int64_t item) {}
template <> void JsonArray<uint64_t>::DeleteItem(uint64_t item) {}
template <> void JsonArray<int32_t>::DeleteItem(int32_t item) {}
template <> void JsonArray<uint32_t>::DeleteItem(uint32_t item) {}
template <> void JsonArray<int16_t>::DeleteItem(int16_t item) {}
template <> void JsonArray<uint16_t>::DeleteItem(uint16_t item) {}
template <> void JsonArray<int8_t>::DeleteItem(int8_t item) {}
template <> void JsonArray<uint8_t>::DeleteItem(uint8_t item) {}
template <> void JsonArray<double>::DeleteItem(double item) {}
template <> void JsonArray<float>::DeleteItem(float item) {}
/*


*/
template <> void JsonArray<char *>::Remove(char *item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<TBoolArray>::Remove(TBoolArray item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int64_t>::Remove(int64_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint64_t>::Remove(uint64_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int32_t>::Remove(int32_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint32_t>::Remove(uint32_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int16_t>::Remove(int16_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint16_t>::Remove(uint16_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int8_t>::Remove(int8_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint8_t>::Remove(uint8_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<double>::Remove(double item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<float>::Remove(float item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
/*


*/
template <> bool JsonArray<char *>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<char *> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		char *s1 = Items[i];
		char *s2 = ((JsonArray<char *> *)other)->Items[i];

		if (s1 == s2) { continue; }
		if (s1 == NULL || s2 == NULL) { return false; }
		if (strcmp(s1, s2) != 0) { return false; }
	}
	return true;
}
template <> bool JsonArray<TBoolArray>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<TBoolArray> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<TBoolArray> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<int64_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<int64_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<int64_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint64_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<uint64_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<uint64_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<int32_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<int32_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<int32_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint32_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<uint32_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<uint32_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<int16_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<int16_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<int16_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint16_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<uint16_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<uint16_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<int8_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<int8_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<int8_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint8_t>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<uint8_t> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<uint8_t> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<double>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<double> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<double> *)other)->Items[i]) { return false; }
	}
	return true;
}
template <> bool JsonArray<float>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<float> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (Items[i] != ((JsonArray<float> *)other)->Items[i]) { return false; }
	}
	return true;
}
/*


*/
template <> void JsonArray<char *>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<char *> *)other);
	for (const auto &item : otherArray->Items) { delete[] item; }
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((char *)item); }
}
template <> void JsonArray<TBoolArray>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<TBoolArray> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((TBoolArray)item); }
}
template <> void JsonArray<int64_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int64_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((int64_t)item); }
}
template <> void JsonArray<uint64_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint64_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((uint64_t)item); }
}
template <> void JsonArray<int32_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int32_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((int32_t)item); }
}
template <> void JsonArray<uint32_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint32_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((uint32_t)item); }
}
template <> void JsonArray<int16_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int16_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((int16_t)item); }
}
template <> void JsonArray<uint16_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint16_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((uint16_t)item); }
}
template <> void JsonArray<int8_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int8_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((int8_t)item); }
}
template <> void JsonArray<uint8_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint8_t> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((uint8_t)item); }
}
template <> void JsonArray<double>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<double> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((double)item); }
}
template <> void JsonArray<float>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<float> *)other);
	otherArray->Items.clear();
	for (const auto &item : Items) { otherArray->AddInternal((float)item); }
}
/*


*/
template <> bool JsonArray<char *>::Update(size_t index, char *item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	if (item == NULL) {
		Items[index] = item;
	} else {
		auto len = strlen(item);
		auto newItem = new char[len + 1];
		memcpy(newItem, item, len);
		newItem[len] = 0;
		Items[index] = newItem;
	}
	return true;
}
template <> bool JsonArray<TBoolArray>::Update(size_t index, TBoolArray item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int64_t>::Update(size_t index, int64_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint64_t>::Update(size_t index, uint64_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int32_t>::Update(size_t index, int32_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint32_t>::Update(size_t index, uint32_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int16_t>::Update(size_t index, int16_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint16_t>::Update(size_t index, uint16_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int8_t>::Update(size_t index, int8_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint8_t>::Update(size_t index, uint8_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<double>::Update(size_t index, double item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<float>::Update(size_t index, float item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
/*


*/
template <> bool JsonArray<char *>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (jItem.IsString()) {
			if (!Add((char *)jItem.GetString())) {
				Items.shrink_to_fit();
				return false;
			}
		} else if (jItem.IsNull()) {
			if (!Add(NULL)) {
				Items.shrink_to_fit();
				return false;
			}
		} else {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<TBoolArray>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsBool() || !Add((TBoolArray)jItem.GetBool())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<int64_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsInt64() || !Add((int64_t)jItem.GetInt64())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<uint64_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsUint64() || !Add((uint64_t)jItem.GetUint64())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<int32_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsInt() || !Add((int32_t)jItem.GetInt())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<uint32_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsUint() || !Add((uint32_t)jItem.GetUint())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<int16_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsInt() || !Add((int16_t)jItem.GetInt())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<uint16_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsUint() || !Add((uint16_t)jItem.GetUint())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<int8_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsInt() || !Add((int8_t)jItem.GetInt())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<uint8_t>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsUint() || !Add((uint8_t)jItem.GetUint())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<double>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsDouble() || !Add((double)jItem.GetDouble())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
template <> bool JsonArray<float>::TryDocParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	for (const auto &jItem : jArray) {
		if (!jItem.IsFloat() || !Add((float)jItem.GetFloat())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
/*


*/
template <> JsonArray<char *>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<TBoolArray>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<int64_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<uint64_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<int32_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<uint32_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<int16_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<uint16_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<int8_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<uint8_t>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<double>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}
template <> JsonArray<float>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}