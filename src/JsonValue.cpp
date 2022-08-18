
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <class T> TJsonValue *JsonValue<T>::GetMember(TJsonDocument *doc, const char *name) {
	rapidjson::Value::MemberIterator member = doc->MemberBegin();
	while (member != doc->MemberEnd()) {
		auto &memberName = member->name;
		if (strcmp(name, memberName.GetString()) == 0) return &member->value;
		++member;
	}
	return NULL;
}

template <> bool JsonValue<bool>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<bool>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsBool()) { return false; }
	Value = jsonVal->GetBool();
	return true;
}
template <> bool JsonValue<int8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<int8_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Value = jsonVal->GetInt();
	return true;
}
template <> bool JsonValue<int16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<int16_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Value = jsonVal->GetInt();
	return true;
}
template <> bool JsonValue<int32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<int32_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt()) { return false; }
	Value = jsonVal->GetInt();
	return true;
}
template <> bool JsonValue<int64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<int64_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsInt64()) { return false; }
	Value = jsonVal->GetInt64();
	return true;
}
template <> bool JsonValue<uint8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<uint8_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Value = jsonVal->GetUint();
	return true;
}
template <> bool JsonValue<uint16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<uint16_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Value = jsonVal->GetUint();
	return true;
}
template <> bool JsonValue<uint32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<uint32_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint()) { return false; }
	Value = jsonVal->GetUint();
	return true;
}
template <> bool JsonValue<uint64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<uint64_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsUint64()) { return false; }
	Value = jsonVal->GetUint64();
	return true;
}
template <> bool JsonValue<float>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<float>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsDouble()) { return false; }
	Value = (float)jsonVal->GetDouble();
	return true;
}
template <> bool JsonValue<double>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<double>::GetMember(doc, this->Name);
	if (jsonVal == NULL || !jsonVal->IsDouble()) { return false; }
	Value = jsonVal->GetDouble();
	return true;
}
template <> bool JsonValue<char *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<char *>::GetMember(doc, this->Name);
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
	auto jsonVal = JsonValue<TJsonRawData>::GetMember(doc, this->Name);
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
	auto jsonVal = JsonValue<JsonObject *>::GetMember(doc, this->Name);
	return jsonVal != NULL && jsonVal->IsObject() && (/*jsonVal->ObjectEmpty() ||*/ Value->TryParse((TJsonDocument *)jsonVal));
}
template <> bool JsonValue<JsonArrayBase *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValue<JsonArrayBase *>::GetMember(doc, this->Name);
	return jsonVal != NULL && jsonVal->IsArray() && Value->TryParse((TJsonDocument *)jsonVal);
}
/*


*/
bool operator!=(const JsonValue<bool> &v1, const JsonValue<bool> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<bool> &v1, const JsonValue<bool> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<int8_t> &v1, const JsonValue<int8_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<int8_t> &v1, const JsonValue<int8_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<int16_t> &v1, const JsonValue<int16_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<int16_t> &v1, const JsonValue<int16_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<int32_t> &v1, const JsonValue<int32_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<int32_t> &v1, const JsonValue<int32_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<int64_t> &v1, const JsonValue<int64_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<int64_t> &v1, const JsonValue<int64_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<uint8_t> &v1, const JsonValue<uint8_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<uint8_t> &v1, const JsonValue<uint8_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<uint16_t> &v1, const JsonValue<uint16_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<uint16_t> &v1, const JsonValue<uint16_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<uint32_t> &v1, const JsonValue<uint32_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<uint32_t> &v1, const JsonValue<uint32_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<uint64_t> &v1, const JsonValue<uint64_t> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<uint64_t> &v1, const JsonValue<uint64_t> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<float> &v1, const JsonValue<float> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<float> &v1, const JsonValue<float> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<double> &v1, const JsonValue<double> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<double> &v1, const JsonValue<double> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<char *> &v1, const JsonValue<char *> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<char *> &v1, const JsonValue<char *> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<TJsonRawData> &v1, const JsonValue<TJsonRawData> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<TJsonRawData> &v1, const JsonValue<TJsonRawData> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<JsonObject *> &v1, const JsonValue<JsonObject *> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<JsonObject *> &v1, const JsonValue<JsonObject *> &v2) { return !(v1 != v2); }

bool operator!=(const JsonValue<JsonArrayBase *> &v1, const JsonValue<JsonArrayBase *> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValue<JsonArrayBase *> &v1, const JsonValue<JsonArrayBase *> &v2) { return !(v1 != v2); }
/*


*/
static bool NamesCompare(const char *name1, const char *name2) { return name1 == name2 || strcmp(name1, name1) == 0; };
template <> bool JsonValue<bool>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<bool> *)other)->Value; }
template <> bool JsonValue<int8_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<int8_t> *)other)->Value; }
template <> bool JsonValue<int16_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<int16_t> *)other)->Value; }
template <> bool JsonValue<int32_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<int32_t> *)other)->Value; }
template <> bool JsonValue<int64_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<int64_t> *)other)->Value; }
template <> bool JsonValue<uint8_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<uint8_t> *)other)->Value; }
template <> bool JsonValue<uint16_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<uint16_t> *)other)->Value; }
template <> bool JsonValue<uint32_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<uint32_t> *)other)->Value; }
template <> bool JsonValue<uint64_t>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<uint64_t> *)other)->Value; }
template <> bool JsonValue<float>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<float> *)other)->Value; }
template <> bool JsonValue<double>::Equals(JsonValueBase *other) { return NamesCompare(Name, other->Name) && Value == ((JsonValue<double> *)other)->Value; }
template <> bool JsonValue<char *>::Equals(JsonValueBase *other) { //
	return NamesCompare(Name, other->Name)
		&& (Value == ((JsonValue<char *> *)other)->Value || (Value != NULL && ((JsonValue<char *> *)other)->Value != NULL && strcmp(Value, ((JsonValue<char *> *)other)->Value) == 0));
}
template <> bool JsonValue<TJsonRawData>::Equals(JsonValueBase *other) {
	return NamesCompare(Name, other->Name)																  //
		&& ((TJsonRawData)Value).Data == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->Value)).Data //
		&& ((TJsonRawData)Value).Size == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->Value)).Size;
}
template <> bool JsonValue<JsonObject *>::Equals(JsonValueBase *other) {
	return NamesCompare(Name, other->Name) && (JsonObject *)Value->Equals((JsonObject *)((JsonValue<JsonObject *> *)other)->Value);
}
template <> bool JsonValue<JsonArrayBase *>::Equals(JsonValueBase *other) {
	return NamesCompare(Name, other->Name) && (JsonObject *)Value->Equals((JsonArrayBase *)(((JsonValue<JsonArrayBase *> *)other)->Value));
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
	jObject.SetObject();
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
template <> void JsonValue<bool>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int8_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int16_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int32_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int64_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint8_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint16_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint32_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint64_t>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<float>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<double>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<char *>::ValueWrapper::DeleteValue() { delete[] this->value; }
template <> void JsonValue<TJsonRawData>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<JsonObject *>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<JsonArrayBase *>::ValueWrapper::DeleteValue() {}
/*


*/
template <> void JsonValue<bool>::ValueWrapper::InitValue(bool value) { this->value = value; }
template <> void JsonValue<int8_t>::ValueWrapper::InitValue(int8_t value) { this->value = value; }
template <> void JsonValue<int16_t>::ValueWrapper::InitValue(int16_t value) { this->value = value; }
template <> void JsonValue<int32_t>::ValueWrapper::InitValue(int32_t value) { this->value = value; }
template <> void JsonValue<int64_t>::ValueWrapper::InitValue(int64_t value) { this->value = value; }
template <> void JsonValue<uint8_t>::ValueWrapper::InitValue(uint8_t value) { this->value = value; }
template <> void JsonValue<uint16_t>::ValueWrapper::InitValue(uint16_t value) { this->value = value; }
template <> void JsonValue<uint32_t>::ValueWrapper::InitValue(uint32_t value) { this->value = value; }
template <> void JsonValue<uint64_t>::ValueWrapper::InitValue(uint64_t value) { this->value = value; }
template <> void JsonValue<float>::ValueWrapper::InitValue(float value) { this->value = value; }
template <> void JsonValue<double>::ValueWrapper::InitValue(double value) { this->value = value; }
template <> void JsonValue<char *>::ValueWrapper::InitValue(char *value) {
	if (value == NULL) {
		this->value = NULL;
	} else {
		size_t len = strlen(value);
		this->value = new char[len + 1];
		memcpy(this->value, value, len);
		this->value[len] = 0;
	}
}
template <> void JsonValue<TJsonRawData>::ValueWrapper::InitValue(TJsonRawData value) { this->value = value; }
template <> void JsonValue<JsonObject *>::ValueWrapper::InitValue(JsonObject *value) { this->value = value; }
template <> void JsonValue<JsonArrayBase *>::ValueWrapper::InitValue(JsonArrayBase *value) { this->value = value; }
/*


*/
template <> void JsonValue<bool>::ValueWrapper::SetValue(bool value) { this->value = value; }
template <> void JsonValue<int8_t>::ValueWrapper::SetValue(int8_t value) { this->value = value; }
template <> void JsonValue<int16_t>::ValueWrapper::SetValue(int16_t value) { this->value = value; }
template <> void JsonValue<int32_t>::ValueWrapper::SetValue(int32_t value) { this->value = value; }
template <> void JsonValue<int64_t>::ValueWrapper::SetValue(int64_t value) { this->value = value; }
template <> void JsonValue<uint8_t>::ValueWrapper::SetValue(uint8_t value) { this->value = value; }
template <> void JsonValue<uint16_t>::ValueWrapper::SetValue(uint16_t value) { this->value = value; }
template <> void JsonValue<uint32_t>::ValueWrapper::SetValue(uint32_t value) { this->value = value; }
template <> void JsonValue<uint64_t>::ValueWrapper::SetValue(uint64_t value) { this->value = value; }
template <> void JsonValue<float>::ValueWrapper::SetValue(float value) { this->value = value; }
template <> void JsonValue<double>::ValueWrapper::SetValue(double value) { this->value = value; }
template <> void JsonValue<char *>::ValueWrapper::SetValue(char *value) {
	DeleteValue();
	InitValue(value);
}
template <> void JsonValue<TJsonRawData>::ValueWrapper::SetValue(TJsonRawData value) { this->value = value; }
template <> void JsonValue<JsonObject *>::ValueWrapper::SetValue(JsonObject *value) { this->value = value; }
template <> void JsonValue<JsonArrayBase *>::ValueWrapper::SetValue(JsonArrayBase *value) { this->value = value; }
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
