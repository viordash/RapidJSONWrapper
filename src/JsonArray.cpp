
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <> std::vector<char *>::iterator JsonArray<char *>::Find(const char *item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
		if (*iter != NULL && item != NULL && strcmp(*iter, item) == 0) { return iter; }
	}
	return Items.end();
}

template <> std::vector<TBoolArray>::iterator JsonArray<TBoolArray>::Find(const TBoolArray item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int64_t>::iterator JsonArray<int64_t>::Find(const int64_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint64_t>::iterator JsonArray<uint64_t>::Find(const uint64_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int32_t>::iterator JsonArray<int32_t>::Find(const int32_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint32_t>::iterator JsonArray<uint32_t>::Find(const uint32_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int16_t>::iterator JsonArray<int16_t>::Find(const int16_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint16_t>::iterator JsonArray<uint16_t>::Find(const uint16_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<int8_t>::iterator JsonArray<int8_t>::Find(const int8_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<uint8_t>::iterator JsonArray<uint8_t>::Find(const uint8_t item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<double>::iterator JsonArray<double>::Find(const double item) {
	for (auto iter = Items.begin(); iter != Items.end(); iter++) {
		if (*iter == item) { return iter; }
	}
	return Items.end();
}
template <> std::vector<float>::iterator JsonArray<float>::Find(const float item) {
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
	for (const auto& item : Items) {
		if (item != NULL) {
			doc->PushBack(rapidjson::Value(rapidjson::StringRef(item)).Move(), allocator);
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
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value((bool)item).Move(), allocator); }
}
template <> void JsonArray<int64_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<uint64_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<int32_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<uint32_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<int16_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<uint16_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<int8_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<uint8_t>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<double>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
template <> void JsonArray<float>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	doc->Reserve(Items.size(), doc->GetAllocator());
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto& item : Items) { doc->PushBack(rapidjson::Value(item).Move(), allocator); }
}
/*


*/
template <> void JsonArray<char *>::AddInternal(const char *item) {
	if (item == NULL) {
		Items.push_back((char *)item);
	} else {
		auto len = strlen(item);
		auto newItem = new char[len + 1];
		memcpy(newItem, item, len);
		newItem[len] = 0;
		Items.push_back(newItem);
	}
}
template <> void JsonArray<TBoolArray>::AddInternal(const TBoolArray item) { Items.push_back(item); }
template <> void JsonArray<int64_t>::AddInternal(const int64_t item) { Items.push_back(item); }
template <> void JsonArray<uint64_t>::AddInternal(const uint64_t item) { Items.push_back(item); }
template <> void JsonArray<int32_t>::AddInternal(const int32_t item) { Items.push_back(item); }
template <> void JsonArray<uint32_t>::AddInternal(const uint32_t item) { Items.push_back(item); }
template <> void JsonArray<int16_t>::AddInternal(const int16_t item) { Items.push_back(item); }
template <> void JsonArray<uint16_t>::AddInternal(const uint16_t item) { Items.push_back(item); }
template <> void JsonArray<int8_t>::AddInternal(const int8_t item) { Items.push_back(item); }
template <> void JsonArray<uint8_t>::AddInternal(const uint8_t item) { Items.push_back(item); }
template <> void JsonArray<double>::AddInternal(const double item) { Items.push_back(item); }
template <> void JsonArray<float>::AddInternal(const float item) { Items.push_back(item); }
/*


*/
template <> bool JsonArray<char *>::Add(const char *item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<TBoolArray>::Add(const TBoolArray item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int64_t>::Add(const int64_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint64_t>::Add(const uint64_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int32_t>::Add(const int32_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint32_t>::Add(const uint32_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int16_t>::Add(const int16_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint16_t>::Add(const uint16_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<int8_t>::Add(const int8_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<uint8_t>::Add(const uint8_t item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<double>::Add(const double item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <> bool JsonArray<float>::Add(const float item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
/*


*/
template <> void JsonArray<char *>::DeleteItem(const char *item) { delete[] item; }
template <> void JsonArray<TBoolArray>::DeleteItem(const TBoolArray item) {}
template <> void JsonArray<int64_t>::DeleteItem(const int64_t item) {}
template <> void JsonArray<uint64_t>::DeleteItem(const uint64_t item) {}
template <> void JsonArray<int32_t>::DeleteItem(const int32_t item) {}
template <> void JsonArray<uint32_t>::DeleteItem(const uint32_t item) {}
template <> void JsonArray<int16_t>::DeleteItem(const int16_t item) {}
template <> void JsonArray<uint16_t>::DeleteItem(const uint16_t item) {}
template <> void JsonArray<int8_t>::DeleteItem(const int8_t item) {}
template <> void JsonArray<uint8_t>::DeleteItem(const uint8_t item) {}
template <> void JsonArray<double>::DeleteItem(const double item) {}
template <> void JsonArray<float>::DeleteItem(const float item) {}
/*


*/
template <> void JsonArray<char *>::Remove(const char *item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<TBoolArray>::Remove(const TBoolArray item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int64_t>::Remove(const int64_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint64_t>::Remove(const uint64_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int32_t>::Remove(const int32_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint32_t>::Remove(const uint32_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int16_t>::Remove(const int16_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint16_t>::Remove(const uint16_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<int8_t>::Remove(const int8_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<uint8_t>::Remove(const uint8_t item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<double>::Remove(const double item) {
	auto iter = Find(item);
	if (iter == Items.end()) { return; }
	DeleteItem(*iter);
	Items.erase(iter);
}
template <> void JsonArray<float>::Remove(const float item) {
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
	for (const auto& item : otherArray->Items) { delete[] item; }
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<TBoolArray>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<TBoolArray> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<int64_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int64_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<uint64_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint64_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<int32_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int32_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<uint32_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint32_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<int16_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int16_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<uint16_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint16_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<int8_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<int8_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<uint8_t>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<uint8_t> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<double>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<double> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
template <> void JsonArray<float>::CloneTo(JsonArrayBase *other) {
	auto otherArray = ((JsonArray<float> *)other);
	otherArray->Items.clear();
	for (const auto& item : Items) { otherArray->AddInternal(item); }
}
/*


*/
template <> bool JsonArray<char *>::Update(size_t index, const char *item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	if (item == NULL) {
		Items[index] = (char *)item;
	} else {
		auto len = strlen(item);
		auto newItem = new char[len + 1];
		memcpy(newItem, item, len);
		newItem[len] = 0;
		Items[index] = newItem;
	}
	return true;
}
template <> bool JsonArray<TBoolArray>::Update(size_t index, const TBoolArray item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int64_t>::Update(size_t index, const int64_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint64_t>::Update(size_t index, const uint64_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int32_t>::Update(size_t index, const int32_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint32_t>::Update(size_t index, const uint32_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int16_t>::Update(size_t index, const int16_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint16_t>::Update(size_t index, const uint16_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<int8_t>::Update(size_t index, const int8_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<uint8_t>::Update(size_t index, const uint8_t item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<double>::Update(size_t index, const double item) {
	if (index >= Size() || !Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items[index] = item;
	return true;
}
template <> bool JsonArray<float>::Update(size_t index, const float item) {
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
			if (!Add(jItem.GetString())) {
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
		if (!jItem.IsInt64() || !Add(jItem.GetInt64())) {
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
		if (!jItem.IsUint64() || !Add(jItem.GetUint64())) {
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
		if (!jItem.IsInt() || !Add(jItem.GetInt())) {
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
		if (!jItem.IsUint() || !Add(jItem.GetUint())) {
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
		if (!jItem.IsInt() || !Add(jItem.GetInt())) {
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
		if (!jItem.IsUint() || !Add(jItem.GetUint())) {
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
		if (!jItem.IsInt() || !Add(jItem.GetInt())) {
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
		if (!jItem.IsUint() || !Add(jItem.GetUint())) {
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
		if (!jItem.IsDouble() || !Add(jItem.GetDouble())) {
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
		if (!jItem.IsFloat() || !Add(jItem.GetFloat())) {
			Items.shrink_to_fit();
			return false;
		}
	}
	Items.shrink_to_fit();
	return true;
}
/*


*/
template <> void JsonArray<char *>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<TBoolArray>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<int64_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<uint64_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<int32_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<uint32_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<int16_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<uint16_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<int8_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<uint8_t>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<double>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}
template <> void JsonArray<float>::Clear() {
	for (const auto &item : Items) { DeleteItem(item); }
	Items.clear();
}