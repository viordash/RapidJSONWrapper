
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <> bool JsonValue<bool>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsBool()) { return false; }
	Set(jsonVal->GetBool());
	return true;
}
template <> bool JsonValue<int8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Set(jsonVal->GetInt());
	return true;
}
template <> bool JsonValue<int16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Set(jsonVal->GetInt());
	return true;
}
template <> bool JsonValue<int32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Set(jsonVal->GetInt());
	return true;
}
template <> bool JsonValue<int64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt64()) { return false; }
	Set(jsonVal->GetInt64());
	return true;
}
template <> bool JsonValue<uint8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Set(jsonVal->GetUint());
	return true;
}
template <> bool JsonValue<uint16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Set(jsonVal->GetUint());
	return true;
}
template <> bool JsonValue<uint32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Set(jsonVal->GetUint());
	return true;
}
template <> bool JsonValue<uint64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint64()) { return false; }
	Set(jsonVal->GetUint64());
	return true;
}
template <> bool JsonValue<float>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsFloat()) { return false; }
	Set((float)jsonVal->GetFloat());
	return true;
}
template <> bool JsonValue<double>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsDouble()) { return false; }
	Set(jsonVal->GetDouble());
	return true;
}
template <> bool JsonValue<char *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) { return false; }
	if (!jsonVal->IsString()) {
		if (jsonVal->IsNull()) {
			Set(NULL);
			return true;
		}
		return false;
	}
	Set(jsonVal->GetString(), jsonVal->GetStringLength());
	return true;
}
template <> bool JsonValue<TJsonRawData>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) { return false; }
	if (!jsonVal->IsString()) {
		if (jsonVal->IsNull()) {
			Set({});
			return true;
		}
		return false;
	}
	TJsonRawData rawData = {(uint8_t *)jsonVal->GetString(), jsonVal->GetStringLength()};
	Set(rawData);
	return true;
}
template <> bool JsonValue<JsonObject *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	return jsonVal != NULL && jsonVal->IsObject() && (/*jsonVal->ObjectEmpty() ||*/ value->TryParse((TJsonDocument *)jsonVal));
}
template <> bool JsonValue<JsonArrayBase *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	return jsonVal != NULL && jsonVal->IsArray() && value->TryDocParse((TJsonDocument *)jsonVal);
}
/*


*/
template <> bool JsonValue<bool>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<bool> *)other)->value; }
template <> bool JsonValue<int8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<int8_t> *)other)->value; }
template <> bool JsonValue<int16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<int16_t> *)other)->value; }
template <> bool JsonValue<int32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<int32_t> *)other)->value; }
template <> bool JsonValue<int64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<int64_t> *)other)->value; }
template <> bool JsonValue<uint8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<uint8_t> *)other)->value; }
template <> bool JsonValue<uint16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<uint16_t> *)other)->value; }
template <> bool JsonValue<uint32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<uint32_t> *)other)->value; }
template <> bool JsonValue<uint64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<uint64_t> *)other)->value; }
template <> bool JsonValue<float>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<float> *)other)->value; }
template <> bool JsonValue<double>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonValue<double> *)other)->value; }
template <> bool JsonValue<char *>::Equals(JsonValueBase *other) { //
	return JsonValueBase::NamesCompare(Name, other->Name)
		&& (value == ((JsonValue<char *> *)other)->value || (value != NULL && ((JsonValue<char *> *)other)->value != NULL && strcmp(value, ((JsonValue<char *> *)other)->value) == 0));
}
template <> bool JsonValue<TJsonRawData>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name)												  //
		&& ((TJsonRawData)value).Data == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->value)).Data //
		&& ((TJsonRawData)value).Size == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->value)).Size;
}
template <> bool JsonValue<JsonObject *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)value->Equals((JsonObject *)((JsonValue<JsonObject *> *)other)->value);
}
template <> bool JsonValue<JsonArrayBase *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)value->Equals((JsonArrayBase *)(((JsonValue<JsonArrayBase *> *)other)->value));
}
/*


*/
template <> void JsonValue<bool>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<int8_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<int16_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<int32_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<int64_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<uint8_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<uint16_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<uint32_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<uint64_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<float>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<double>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, value, doc->GetAllocator()); }
template <> void JsonValue<char *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (value == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef(value));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	TJsonRawData rawData = value;
	if (rawData.Data == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)rawData.Data, (rapidjson::SizeType)rawData.Size));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonValue<JsonObject *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	value->WriteToDoc(&jObject);
	doc->AddMember(Name, jObject, allocator);
}
template <> void JsonValue<JsonArrayBase *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	value->WriteToDoc(&jArray);
	doc->AddMember(Name, jArray, allocator);
}
/*


*/
template <> void JsonValue<bool>::CloneTo(JsonValueBase *other) { ((JsonValue<bool> *)other)->Set(this->value); }
template <> void JsonValue<int8_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int8_t> *)other)->Set(this->value); }
template <> void JsonValue<int16_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int16_t> *)other)->Set(this->value); }
template <> void JsonValue<int32_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int32_t> *)other)->Set(this->value); }
template <> void JsonValue<int64_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int64_t> *)other)->Set(this->value); }
template <> void JsonValue<uint8_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint8_t> *)other)->Set(this->value); }
template <> void JsonValue<uint16_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint16_t> *)other)->Set(this->value); }
template <> void JsonValue<uint32_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint32_t> *)other)->Set(this->value); }
template <> void JsonValue<uint64_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint64_t> *)other)->Set(this->value); }
template <> void JsonValue<float>::CloneTo(JsonValueBase *other) { ((JsonValue<float> *)other)->Set(this->value); }
template <> void JsonValue<double>::CloneTo(JsonValueBase *other) { ((JsonValue<double> *)other)->Set(this->value); }
template <> void JsonValue<char *>::CloneTo(JsonValueBase *other) { ((JsonValue<char *> *)other)->Set(this->value); }
template <> void JsonValue<TJsonRawData>::CloneTo(JsonValueBase *other) { ((JsonValue<TJsonRawData> *)other)->Set((TJsonRawData)this->value); }
template <> void JsonValue<JsonObject *>::CloneTo(JsonValueBase *other) {
	auto thisObject = ((JsonObject *)value);
	auto otherObject = ((JsonObject *)((JsonValue<JsonObject *> *)other)->value);
	thisObject->CloneTo(otherObject);
}
template <> void JsonValue<JsonArrayBase *>::CloneTo(JsonValueBase *other) {
	auto thisArray = ((JsonArrayBase *)value);
	auto otherArray = ((JsonArrayBase *)((JsonValue<JsonArrayBase *> *)other)->value);
	thisArray->CloneTo(otherArray);
}
/*


*/
template <> void JsonValue<bool>::DeleteValue() {}
template <> void JsonValue<int8_t>::DeleteValue() {}
template <> void JsonValue<int16_t>::DeleteValue() {}
template <> void JsonValue<int32_t>::DeleteValue() {}
template <> void JsonValue<int64_t>::DeleteValue() {}
template <> void JsonValue<uint8_t>::DeleteValue() {}
template <> void JsonValue<uint16_t>::DeleteValue() {}
template <> void JsonValue<uint32_t>::DeleteValue() {}
template <> void JsonValue<uint64_t>::DeleteValue() {}
template <> void JsonValue<float>::DeleteValue() {}
template <> void JsonValue<double>::DeleteValue() {}
template <> void JsonValue<char *>::DeleteValue() { delete[] this->value; }
template <> void JsonValue<TJsonRawData>::DeleteValue() {}
template <> void JsonValue<JsonObject *>::DeleteValue() {}
template <> void JsonValue<JsonArrayBase *>::DeleteValue() {}
/*


*/
template <> void JsonValue<bool>::InitValue(const bool value, size_t valueLen) { this->value = value; }
template <> void JsonValue<int8_t>::InitValue(const int8_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<int16_t>::InitValue(const int16_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<int32_t>::InitValue(const int32_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<int64_t>::InitValue(const int64_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<uint8_t>::InitValue(const uint8_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<uint16_t>::InitValue(const uint16_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<uint32_t>::InitValue(const uint32_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<uint64_t>::InitValue(const uint64_t value, size_t valueLen) { this->value = value; }
template <> void JsonValue<float>::InitValue(const float value, size_t valueLen) { this->value = value; }
template <> void JsonValue<double>::InitValue(const double value, size_t valueLen) { this->value = value; }
template <> void JsonValue<char *>::InitValue(const char *value, size_t valueLen) {
	if (value == NULL) {
		this->value = NULL;
	} else {
		size_t len = valueLen != size_t() //
					   ? valueLen		  //
					   : strlen(value);
		this->value = new char[len + 1];
		memcpy(this->value, value, len);
		this->value[len] = 0;
	}
}
template <> void JsonValue<TJsonRawData>::InitValue(const TJsonRawData value, size_t valueLen) { this->value = value; }
template <> void JsonValue<JsonObject *>::InitValue(JsonObject *value, size_t valueLen) { this->value = value; }
template <> void JsonValue<JsonArrayBase *>::InitValue(JsonArrayBase *value, size_t valueLen) { this->value = value; }