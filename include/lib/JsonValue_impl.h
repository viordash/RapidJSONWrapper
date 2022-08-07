#pragma once

#include "LibJson.h"

template <class T> void JsonValue<T>::Reset() { Value = T(); }

template <class T> bool operator!=(const JsonValue<T> &v1, const JsonValue<T> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
template <class T> bool operator==(const JsonValue<T> &v1, const JsonValue<T> &v2) { return !(v1 != v2); }
/*


*/
template <class T> bool JsonValue<T>::Equals(JsonValueBase *other) { return Value == ((JsonValue<T> *)other)->Value; }

template <> bool JsonValue<char *>::Equals(JsonValueBase *other) { return strcmp(Value, ((JsonValue<char *> *)other)->Value) == 0; }

template <> bool JsonValue<TJsonRawData>::Equals(JsonValueBase *other) {
	return ((TJsonRawData)Value).Data == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->Value)).Data //
		&& ((TJsonRawData)Value).Size == ((TJsonRawData)(((JsonValue<TJsonRawData> *)other)->Value)).Size;
}

template <> bool JsonValue<JsonObject *>::Equals(JsonValueBase *other) { return (JsonObject *)Value->Equals((JsonObject *)((JsonValue<JsonObject *> *)other)->Value); }

template <> bool JsonValue<JsonArrayBase *>::Equals(JsonValueBase *other) { return (JsonObject *)Value->Equals((JsonArrayBase *)(((JsonValue<JsonArrayBase *> *)other)->Value)); }
/*


*/
template <class T> bool JsonValue<T>::TryParse(TJsonValue *jValue) {
	if (!jValue->Is<T>()) { return false; }
	Value = jValue->Get<T>();
	return true;
}

template <> bool JsonValue<int8_t>::TryParse(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}

template <> bool JsonValue<int16_t>::TryParse(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}

template <> bool JsonValue<uint8_t>::TryParse(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}

template <> bool JsonValue<uint16_t>::TryParse(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}

template <> bool JsonValue<char *>::TryParse(TJsonValue *jValue) {
	if (!jValue->IsString()) { return false; }
	Value = (char *)jValue->GetString();
	return true;
}

template <> bool JsonValue<TJsonRawData>::TryParse(TJsonValue *jValue) {
	if (!jValue->IsString()) {
		if (jValue->IsNull()) {
			this->Reset();
			return true;
		}
		return false;
	}

	TJsonRawData rawData = {(uint8_t *)jValue->GetString(), jValue->GetStringLength()};
	Value = rawData;
	return true;
}

template <> bool JsonValue<JsonObject *>::TryParse(TJsonValue *jValue) { return jValue->IsObject() && (jValue->ObjectEmpty() || Value->TryParse((TJsonDocument *)jValue)); }

template <> bool JsonValue<JsonArrayBase *>::TryParse(TJsonValue *jValue) { return jValue->IsArray() && Value->TryParse((TJsonDocument *)jValue); }
/*


*/
template <class T> void JsonValue<T>::WriteToDoc(TJsonDocument *doc, TJsonValueName *name) { doc->AddMember(*name, (T)Value, doc->GetAllocator()); }

template <> void JsonValue<char *>::WriteToDoc(TJsonDocument *doc, TJsonValueName *name) { doc->AddMember(*name, rapidjson::StringRef((char *)Value), doc->GetAllocator()); }

template <> void JsonValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc, TJsonValueName *name) {
	rapidjson::Value json_val;
	TJsonRawData rawData = Value;
	if (rawData.Data == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)rawData.Data), (rapidjson::SizeType)rawData.Size);
	}
	doc->AddMember(*name, json_val, doc->GetAllocator());
}

template <> void JsonValue<JsonObject *>::WriteToDoc(TJsonDocument *doc, TJsonValueName *name) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	jObject.SetObject();
	Value->WriteToDoc(&jObject);
	doc->AddMember(*name, jObject, allocator);
}

template <> void JsonValue<JsonArrayBase *>::WriteToDoc(TJsonDocument *doc, TJsonValueName *name) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	Value->WriteToDoc(&jArray);
	doc->AddMember(*name, jArray, allocator);
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
template <class T> void JsonValue<T>::ValueWrapper::InitValue(T value) { this->value = value; }

template <> void JsonValue<char *>::ValueWrapper::InitValue(char *value) {
	if (value != NULL) {
		auto len = strlen(value);
		this->value = new char[len + 1];
		memcpy(this->value, value, len);
		this->value[len] = 0;
	} else {
		this->value = new char[1];
		this->value[0] = 0;
	}
}

template <> void JsonValue<JsonObject *>::ValueWrapper::InitValue(JsonObject *value) { this->value = value; }

template <> void JsonValue<JsonArrayBase *>::ValueWrapper::InitValue(JsonArrayBase *value) { this->value = value; }
/*


*/
template <class T> void JsonValue<T>::ValueWrapper::SetValue(T value) { this->value = value; }

template <> void JsonValue<char *>::ValueWrapper::SetValue(char *value) {
	DeleteValue();
	InitValue(value);
}

template <> void JsonValue<JsonObject *>::ValueWrapper::SetValue(JsonObject *value) { this->value = value; }

template <> void JsonValue<JsonArrayBase *>::ValueWrapper::SetValue(JsonArrayBase *value) { this->value = value; }
/*


*/
template <class T> void JsonValue<T>::CloneTo(JsonValueBase *other) { ((JsonValue<T> *)other)->Value = (T)this->Value; }

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