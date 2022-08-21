
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <> bool JsonValue<bool>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsBool()) { return false; }
	Value = jsonVal->GetBool();
	return true;
}
template <> bool JsonValue<int8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Value = jsonVal->GetInt();
	return true;
}
template <> bool JsonValue<int16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Value = jsonVal->GetInt();
	return true;
}
template <> bool JsonValue<int32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Value = jsonVal->GetInt();
	return true;
}
template <> bool JsonValue<int64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt64()) { return false; }
	Value = jsonVal->GetInt64();
	return true;
}
template <> bool JsonValue<uint8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Value = jsonVal->GetUint();
	return true;
}
template <> bool JsonValue<uint16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Value = jsonVal->GetUint();
	return true;
}
template <> bool JsonValue<uint32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Value = jsonVal->GetUint();
	return true;
}
template <> bool JsonValue<uint64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint64()) { return false; }
	Value = jsonVal->GetUint64();
	return true;
}
template <> bool JsonValue<float>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsFloat()) { return false; }
	Value = (float)jsonVal->GetFloat();
	return true;
}
template <> bool JsonValue<double>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsDouble()) { return false; }
	Value = jsonVal->GetDouble();
	return true;
}
template <> bool JsonValue<char *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) { return false; }
	if (!jsonVal->IsString()) {
		if (jsonVal->IsNull()) {
			Value = NULL;
			return true;
		}
		return false;
	}
	Value.DeleteValue();
	size_t len = jsonVal->GetStringLength();
	Value.value = new char[len + 1];
	memcpy(Value.value, (char *)jsonVal->GetString(), len);
	Value.value[len] = 0;
	return true;
}
template <> bool JsonValue<TJsonRawData>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) { return false; }
	if (!jsonVal->IsString()) {
		if (jsonVal->IsNull()) {
			Value = {};
			return true;
		}
		return false;
	}
	TJsonRawData rawData = {(uint8_t *)jsonVal->GetString(), jsonVal->GetStringLength()};
	Value = rawData;
	return true;
}
template <> bool JsonValue<JsonObject *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	return jsonVal != NULL && jsonVal->IsObject() && (/*jsonVal->ObjectEmpty() ||*/ Value->TryParse((TJsonDocument *)jsonVal));
}
template <> bool JsonValue<JsonArrayBase *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	return jsonVal != NULL && jsonVal->IsArray() && Value->TryDocParse((TJsonDocument *)jsonVal);
}
/*


*/
template <> bool JsonValue<bool>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<bool> *)other)->Value; }
template <> bool JsonValue<int8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<int8_t> *)other)->Value; }
template <> bool JsonValue<int16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<int16_t> *)other)->Value; }
template <> bool JsonValue<int32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<int32_t> *)other)->Value; }
template <> bool JsonValue<int64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<int64_t> *)other)->Value; }
template <> bool JsonValue<uint8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<uint8_t> *)other)->Value; }
template <> bool JsonValue<uint16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<uint16_t> *)other)->Value; }
template <> bool JsonValue<uint32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<uint32_t> *)other)->Value; }
template <> bool JsonValue<uint64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<uint64_t> *)other)->Value; }
template <> bool JsonValue<float>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<float> *)other)->Value; }
template <> bool JsonValue<double>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonValue<double> *)other)->Value; }
template <> bool JsonValue<char *>::Equals(JsonValueBase *other) { //
	return JsonValueBase::NamesCompare(Name, other->Name)
		&& (Value == ((JsonValue<char *> *)other)->Value || (Value != NULL && ((JsonValue<char *> *)other)->Value != NULL && strcmp(Value, ((JsonValue<char *> *)other)->Value) == 0));
}
template <> bool JsonValue<TJsonRawData>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name)																  //
		&& ((TJsonRawData)Value).Data == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->Value)).Data //
		&& ((TJsonRawData)Value).Size == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->Value)).Size;
}
template <> bool JsonValue<JsonObject *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)Value->Equals((JsonObject *)((JsonValue<JsonObject *> *)other)->Value);
}
template <> bool JsonValue<JsonArrayBase *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)Value->Equals((JsonArrayBase *)(((JsonValue<JsonArrayBase *> *)other)->Value));
}
/*


*/
template <> void JsonValue<bool>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (bool)Value, doc->GetAllocator()); }
template <> void JsonValue<int8_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (int8_t)Value, doc->GetAllocator()); }
template <> void JsonValue<int16_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (int16_t)Value, doc->GetAllocator()); }
template <> void JsonValue<int32_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (int32_t)Value, doc->GetAllocator()); }
template <> void JsonValue<int64_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (int64_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint8_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (uint8_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint16_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (uint16_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint32_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (uint32_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint64_t>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (uint64_t)Value, doc->GetAllocator()); }
template <> void JsonValue<float>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (float)Value, doc->GetAllocator()); }
template <> void JsonValue<double>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(Name, (double)Value, doc->GetAllocator()); }
template <> void JsonValue<char *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)Value));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	TJsonRawData rawData = Value;
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
	Value->WriteToDoc(&jObject);
	doc->AddMember(Name, jObject, allocator);
}
template <> void JsonValue<JsonArrayBase *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	Value->WriteToDoc(&jArray);
	doc->AddMember(Name, jArray, allocator);
}
/*


*/
template <> void JsonValue<bool>::CloneTo(JsonValueBase *other) { ((JsonValue<bool> *)other)->Value = (bool)this->Value; }
template <> void JsonValue<int8_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int8_t> *)other)->Value = (int8_t)this->Value; }
template <> void JsonValue<int16_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int16_t> *)other)->Value = (int16_t)this->Value; }
template <> void JsonValue<int32_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int32_t> *)other)->Value = (int32_t)this->Value; }
template <> void JsonValue<int64_t>::CloneTo(JsonValueBase *other) { ((JsonValue<int64_t> *)other)->Value = (int64_t)this->Value; }
template <> void JsonValue<uint8_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint8_t> *)other)->Value = (uint8_t)this->Value; }
template <> void JsonValue<uint16_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint16_t> *)other)->Value = (uint16_t)this->Value; }
template <> void JsonValue<uint32_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint32_t> *)other)->Value = (uint32_t)this->Value; }
template <> void JsonValue<uint64_t>::CloneTo(JsonValueBase *other) { ((JsonValue<uint64_t> *)other)->Value = (uint64_t)this->Value; }
template <> void JsonValue<float>::CloneTo(JsonValueBase *other) { ((JsonValue<float> *)other)->Value = (float)this->Value; }
template <> void JsonValue<double>::CloneTo(JsonValueBase *other) { ((JsonValue<double> *)other)->Value = (double)this->Value; }
template <> void JsonValue<char *>::CloneTo(JsonValueBase *other) { ((JsonValue<char *> *)other)->Value = (char *)this->Value; }
template <> void JsonValue<TJsonRawData>::CloneTo(JsonValueBase *other) { ((JsonValue<TJsonRawData> *)other)->Value = (TJsonRawData)this->Value; }
template <> void JsonValue<JsonObject *>::CloneTo(JsonValueBase *other) {
	auto thisObject = ((JsonObject *)Value);
	auto otherObject = ((JsonObject *)((JsonValue<JsonObject *> *)other)->Value);
	thisObject->CloneTo(otherObject);
}
template <> void JsonValue<JsonArrayBase *>::CloneTo(JsonValueBase *other) {
	auto thisArray = ((JsonArrayBase *)Value);
	auto otherArray = ((JsonArrayBase *)((JsonValue<JsonArrayBase *> *)other)->Value);
	thisArray->CloneTo(otherArray);
}
