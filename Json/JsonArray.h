#pragma once

#include "LibJson.h"

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
	if (item == NULL) { return; }
	auto iter = Find(item);
	if (iter != Items.end()) { Items.erase(iter); }
}

template <class TItem> typename std::vector<TItem>::iterator JsonArray<TItem>::Find(TItem item) {
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

template <class TItem> bool operator!=(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) {
	typedef typename std::remove_pointer<TItem>::type TNewObjectItem;
	if (v1.Items.size() != v1.Items.size()) { return true; }

	if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
		for (size_t i = 0; i < v1.Items.size(); i++) {
			if (*((JsonObject *)v1.Items[i]) != *((JsonObject *)v2.Items[i])) { return true; }
		}
	}
	return false;
}
template <> bool operator!=(const JsonArray<char *> &v1, const JsonArray<char *> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }

	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (strcmp(v1.Items[i], v2.Items[i]) != 0) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<TBoolArray> &v1, const JsonArray<TBoolArray> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<int64_t> &v1, const JsonArray<int64_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<uint64_t> &v1, const JsonArray<uint64_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<int32_t> &v1, const JsonArray<int32_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<uint32_t> &v1, const JsonArray<uint32_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<int16_t> &v1, const JsonArray<int16_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<uint16_t> &v1, const JsonArray<uint16_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<int8_t> &v1, const JsonArray<int8_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<uint8_t> &v1, const JsonArray<uint8_t> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<double> &v1, const JsonArray<double> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}
template <> bool operator!=(const JsonArray<float> &v1, const JsonArray<float> &v2) {
	if (v1.Items.size() != v1.Items.size()) { return true; }
	for (size_t i = 0; i < v1.Items.size(); i++) {
		if (v1.Items[i] != v2.Items[i]) { return true; }
	}
	return false;
}

template <class TItem> bool operator==(const JsonArray<TItem> &v1, const JsonArray<TItem> &v2) { return !(v1 != v2); }

template <class TItem> bool JsonArray<TItem>::Equals(JsonArrayBase *other) { return *this == *((JsonArray<TItem> *)other); }