#pragma once

#include "LibJson.h"

template <class TItem> JsonArray<TItem>::~JsonArray() {
	for (const auto &item : Items) { DeleteItem(item); }
}

template <class TItem> bool JsonArray<TItem>::TryParse(TJsonDocument *doc) {
	if (!doc->IsArray()) { return false; }
	auto jArray = doc->GetArray();
	Items.reserve(jArray.Size());
	if (TryParseInternal(&jArray)) { return true; }
	Items.shrink_to_fit();
	return false;
}

template <class TItem> bool JsonArray<TItem>::TryParse(const char *jsonStr, int length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) { return false; }
	EndTryParse(doc);
	return true;
}

template <class TItem> TJsonDocument *JsonArray<TItem>::BeginTryParse(const char *jsonStr, int length) {
	if (jsonStr == NULL || length == 0) { return NULL; }

	rapidjson::Document *doc = new rapidjson::Document();
	if (length < 0) {
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

template <class TItem> void JsonArray<TItem>::EndTryParse(TJsonDocument *doc) { delete doc; }

template <class TItem> void JsonArray<TItem>::WriteToDoc(TJsonDocument *doc) {
	doc->SetArray();
	WriteToDocInternal(doc);
}

template <class TItem> int JsonArray<TItem>::WriteToString(char *outBuffer, int outBufferSize) {
	rapidjson::Document doc;
	this->WriteToDoc(&doc);
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

template <class TItem> int JsonArray<TItem>::DirectWriteTo(void *parent, TOnReady onReady) {
	rapidjson::Document doc;
	this->WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *json = buffer.GetString();
	int size = buffer.GetSize();
	onReady(parent, json, size);
	return size;
}

template <class TItem> bool JsonArray<TItem>::Add(TItem item) {
	if (!Validate(item)) { return false; }
	AddInternal(item);
	return true;
}
template <class TItem> void JsonArray<TItem>::Remove(TItem item) {
	auto iter = Find(item);
	if (iter != Items.end()) {
		DeleteItem(*iter);
		Items.erase(iter);
	}
}
/*


*/
template <class TItem> typename std::vector<TItem>::iterator JsonArray<TItem>::Find(TItem item) {
	if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
		if (item != NULL) {
			for (auto iter = Items.begin(); iter != Items.end(); iter++) {
				if (*((JsonObject *)*iter) == *((JsonObject *)item)) { return iter; }
			}
		}
	}
	return Items.end();
}
template <> std::vector<char *>::iterator JsonArray<char *>::Find(char *item) {
	if (item != NULL) {
		for (auto iter = Items.begin(); iter != Items.end(); iter++) {
			if (strcmp(*iter, item) == 0) { return iter; }
		}
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

template <class TItem> bool JsonArray<TItem>::TryParseInternal(TJsonArray *jArray) {
	if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
		for (const auto &jItem : *jArray) {
			auto newItem = new TNewObjectItem();
			if (!((JsonObject *)newItem)->TryParse((TJsonDocument *)&jItem) || !Add((TItem)newItem)) {
				delete newItem;
				return false;
			}
		}
		return true;
	}
}
template <> bool JsonArray<char *>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsString() || !Add((char *)jItem.GetString())) { return false; }
	}
	return true;
}
template <> bool JsonArray<TBoolArray>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsBool() || !Add((TBoolArray)jItem.GetBool())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int64_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt64() || !Add((int64_t)jItem.GetInt64())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint64_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint64() || !Add((uint64_t)jItem.GetUint64())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int32_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt() || !Add((int32_t)jItem.GetInt())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint32_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((uint32_t)jItem.GetUint())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int16_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt() || !Add((int16_t)jItem.GetInt())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint16_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((uint16_t)jItem.GetUint())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int8_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt() || !Add((int8_t)jItem.GetInt())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint8_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((uint8_t)jItem.GetUint())) { return false; }
	}
	return true;
}
template <> bool JsonArray<double>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsDouble() || !Add((double)jItem.GetDouble())) { return false; }
	}
	return true;
}
template <> bool JsonArray<float>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsFloat() || !Add((float)jItem.GetFloat())) { return false; }
	}
	return true;
}
/*


*/
template <class TItem> void JsonArray<TItem>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
		for (const auto &item : Items) {
			rapidjson::Document childDoc(&allocator);
			JsonObject *jObject = (JsonObject *)item;
			jObject->WriteToDoc(&childDoc);
			doc->PushBack(childDoc, allocator);
		}
	}
}
template <> void JsonArray<char *>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(rapidjson::StringRef((char *)item));
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<TBoolArray>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp((bool)item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int64_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint64_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int32_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint32_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int16_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint16_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int8_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint8_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<double>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<float>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
/*


*/
template <class TItem> void JsonArray<TItem>::AddInternal(TItem item) { Items.push_back(item); }
template <> void JsonArray<char *>::AddInternal(char *item) {
	auto len = strlen((char *)item);
	auto newItem = new char[len + 1];
	memcpy(newItem, (char *)item, len);
	newItem[len] = 0;
	Items.push_back(newItem);
}
/*


*/
template <class TItem> bool operator!=(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) { return !((JsonArray<TItem> *)&v1)->Equals((JsonArray<TItem> *)&v2); }
template <class TItem> bool operator==(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) { return !(v1 != v2); }
/*


*/
template <class TItem> bool JsonArray<TItem>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<TItem> *)other)->Items.size()) { return false; }
	if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
		for (size_t i = 0; i < Items.size(); i++) {
			if (*((JsonObject *)Items[i]) != *((JsonObject *)((JsonArray<TItem> *)other)->Items[i])) { return false; }
		}
	}
	return true;
}
template <> bool JsonArray<char *>::Equals(JsonArrayBase *other) {
	if (Items.size() != ((JsonArray<char *> *)other)->Items.size()) { return false; }
	for (size_t i = 0; i < Items.size(); i++) {
		if (strcmp(Items[i], ((JsonArray<char *> *)other)->Items[i]) != 0) { return false; }
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
template <class TItem> void JsonArray<TItem>::CloneTo(JsonArrayBase *other) {
	if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
		auto otherArray = ((JsonArray<TItem> *)other);
		for (const auto &item : otherArray->Items) { delete (JsonObject *)item; }
		otherArray->Items.clear();

		for (const auto &item : Items) {
			auto newItem = new TNewObjectItem();
			item->CloneTo(newItem);
			otherArray->AddInternal((TItem)newItem);
		}
	}
}
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
template <class TItem> void JsonArray<TItem>::DeleteItem(TItem item) {
	if (std::is_base_of<JsonObject, TNewObjectItem>::value) { //
		delete ((JsonObject *)item);
	}
}
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
template <class TItem> bool JsonArray<TItem>::Update(int index, TItem item) {
	if (!Validate(item)) { return false; }
	DeleteItem(Items[index]);
	Items.push_back(item);
	return true;
}
template <> bool JsonArray<char *>::Update(int index, char *item) {
	if (!Validate(item)) { return false; }
	DeleteItem(Items[index]);
	auto len = strlen((char *)item);
	auto newItem = new char[len + 1];
	memcpy(newItem, (char *)item, len);
	newItem[len] = 0;
	Items[index] = newItem;
	return true;
}
