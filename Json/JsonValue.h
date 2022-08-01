#pragma once

#include "LibJson.h"

template <class T, bool optional> TJsonDocument *JsonValue<T, optional>::BeginTryParse(const char *jsonStr, size_t length) {
	if (jsonStr == NULL) { return NULL; }

	auto doc = new rapidjson::Document();
	if (length == 0) {
		doc->Parse(jsonStr);
	} else {
		doc->Parse(jsonStr, length);
	}
	if (doc->HasParseError() || !TryParse(doc)) {
		delete doc;
		return NULL;
	}
	return doc;
}

template <class T, bool optional> void JsonValue<T, optional>::EndTryParse(TJsonDocument *doc) { delete doc; }

template <class T, bool optional> bool JsonValue<T, optional>::TryParse(const char *jsonStr, size_t length) {
	auto doc = BeginTryParse(jsonStr, length);
	if (doc == NULL) { return false; }
	EndTryParse(doc);
	return true;
}
template <class T, bool optional> bool JsonValue<T, optional>::TryParse(TJsonDocument *doc) {
	rapidjson::Value::MemberIterator member = doc->FindMember(Name);
	if (member == doc->MemberEnd()) {
		this->Reset();
		return optional;
	}

	rapidjson::Value &jsonVal = member->value;
	if (TryParseCore(&jsonVal)) { return true; }
	if (jsonVal.IsNull()) {
		this->Reset();
		return true;
	}
	return false;
}
template <class T, bool optional> size_t JsonValue<T, optional>::WriteToString(char *outBuffer, size_t outBufferSize) {
	rapidjson::Document doc;
	WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	size_t size = buffer.GetSize();
	if (size > outBufferSize - 1) { size = outBufferSize - 1; }
	memcpy(outBuffer, jsonStr, size);
	outBuffer[size] = 0;
	return size;
}
template <class T, bool optional> size_t JsonValue<T, optional>::DirectWriteTo(void *parent, TOnCompleted onCompleted) {
	rapidjson::Document doc;
	WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *json = buffer.GetString();
	int size = buffer.GetSize();
	onCompleted(parent, json, size);
	return size;
}
template <class T, bool optional> void JsonValue<T, optional>::Reset() { Value = T(); }

template <class T, bool optional> bool operator!=(const JsonValue<T, optional> &v1, const JsonValue<T, optional> &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
template <class T, bool optional> bool operator==(const JsonValue<T, optional> &v1, const JsonValue<T, optional> &v2) { return !(v1 != v2); }
/*


*/
template <class T, bool optional> bool JsonValue<T, optional>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<T, true> *)other)->Value; }

template <> bool JsonValue<char *, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && strcmp(Value, ((JsonValue<char *, false> *)other)->Value) == 0; }
template <> bool JsonValue<char *, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && strcmp(Value, ((JsonValue<char *, false> *)other)->Value) == 0; }

template <> bool JsonValue<TRawData, true>::Equals(JsonValueBase *other) {
	return strcmp(Name, other->Name) == 0															 //
		&& ((TRawData)Value).Data == ((TRawData)(((JsonValue<TRawData, false> *)other)->Value)).Data //
		&& ((TRawData)Value).Size == ((TRawData)(((JsonValue<TRawData, false> *)other)->Value)).Size;
}
template <> bool JsonValue<TRawData, false>::Equals(JsonValueBase *other) {
	return strcmp(Name, other->Name) == 0															 //
		&& ((TRawData)Value).Data == ((TRawData)(((JsonValue<TRawData, false> *)other)->Value)).Data //
		&& ((TRawData)Value).Size == ((TRawData)(((JsonValue<TRawData, false> *)other)->Value)).Size;
}

template <> bool JsonValue<JsonObject *, true>::Equals(JsonValueBase *other) {
	return strcmp(Name, other->Name) == 0 && (JsonObject *)Value->Equals((JsonObject *)((JsonValue<JsonObject *, false> *)other)->Value);
}
template <> bool JsonValue<JsonObject *, false>::Equals(JsonValueBase *other) {
	return strcmp(Name, other->Name) == 0 && (JsonObject *)Value->Equals((JsonObject *)(((JsonValue<JsonObject *, false> *)other)->Value));
}

template <> bool JsonValue<JsonArrayBase *, true>::Equals(JsonValueBase *other) {
	return strcmp(Name, other->Name) == 0 && (JsonObject *)Value->Equals((JsonArrayBase *)(((JsonValue<JsonArrayBase *, false> *)other)->Value));
}
template <> bool JsonValue<JsonArrayBase *, false>::Equals(JsonValueBase *other) {
	return strcmp(Name, other->Name) == 0 && (JsonObject *)Value->Equals((JsonArrayBase *)(((JsonValue<JsonArrayBase *, false> *)other)->Value));
}
/*


*/
template <class T, bool optional> bool JsonValue<T, optional>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->Is<T>()) { return false; }
	Value = jValue->Get<T>();
	return true;
}

template <> bool JsonValue<int8_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}
template <> bool JsonValue<int8_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}

template <> bool JsonValue<int16_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}
template <> bool JsonValue<int16_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}

template <> bool JsonValue<uint8_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}
template <> bool JsonValue<uint8_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}

template <> bool JsonValue<uint16_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}
template <> bool JsonValue<uint16_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}

template <> bool JsonValue<char *, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsString()) { return false; }
	Value = (char *)jValue->GetString();
	return true;
}
template <> bool JsonValue<char *, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsString()) { return false; }
	Value = (char *)jValue->GetString();
	return true;
}

template <> bool JsonValue<TRawData, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsString()) { return false; }
	TRawData rawData = {(uint8_t *)jValue->GetString(), jValue->GetStringLength()};
	Value = rawData;
	return true;
}
template <> bool JsonValue<TRawData, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsString()) { return false; }
	Value = {(uint8_t *)jValue->GetString(), jValue->GetStringLength()};
	return true;
}

template <> bool JsonValue<JsonObject *, true>::TryParseCore(TJsonValue *jValue) { return jValue->IsObject() && (jValue->ObjectEmpty() || Value->TryParse((TJsonDocument *)jValue)); }
template <> bool JsonValue<JsonObject *, false>::TryParseCore(TJsonValue *jValue) { return jValue->IsObject() && (jValue->ObjectEmpty() || Value->TryParse((TJsonDocument *)jValue)); }

template <> bool JsonValue<JsonArrayBase *, true>::TryParseCore(TJsonValue *jValue) { return jValue->IsArray() && Value->TryParse((TJsonDocument *)jValue); }
template <> bool JsonValue<JsonArrayBase *, false>::TryParseCore(TJsonValue *jValue) { return jValue->IsArray() && Value->TryParse((TJsonDocument *)jValue); }
/*


*/
template <class T, bool optional> void JsonValue<T, optional>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (T)Value, doc->GetAllocator()); }

template <> void JsonValue<char *, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)Value), doc->GetAllocator()); }
template <> void JsonValue<char *, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)Value), doc->GetAllocator()); }

template <> void JsonValue<TRawData, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	TRawData rawData = Value;
	if (rawData.Data == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)rawData.Data), (rapidjson::SizeType)rawData.Size);
	}
	doc->AddMember(rapidjson::StringRef(Name), json_val, doc->GetAllocator());
}
template <> void JsonValue<TRawData, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	TRawData rawData = Value;
	if (rawData.Data == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)rawData.Data), (rapidjson::SizeType)rawData.Size);
	}
	doc->AddMember(rapidjson::StringRef(Name), json_val, doc->GetAllocator());
}

template <> void JsonValue<JsonObject *, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	jObject.SetObject();
	Value->WriteToDoc(&jObject);
	doc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}
template <> void JsonValue<JsonObject *, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	jObject.SetObject();
	Value->WriteToDoc(&jObject);
	doc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}

template <> void JsonValue<JsonArrayBase *, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	Value->WriteToDoc(&jArray);
	doc->AddMember(rapidjson::StringRef(Name), jArray, allocator);
}
template <> void JsonValue<JsonArrayBase *, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	Value->WriteToDoc(&jArray);
	doc->AddMember(rapidjson::StringRef(Name), jArray, allocator);
}
/*


*/
template <> void JsonValue<bool, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<bool, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<int8_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int8_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<int16_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int16_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<int32_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int32_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<int64_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<int64_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<uint8_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint8_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<uint16_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint16_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<uint32_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint32_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<uint64_t, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<uint64_t, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<float, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<float, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<double, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<double, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<char *, true>::ValueWrapper::DeleteValue() { delete[] this->value; }
template <> void JsonValue<char *, false>::ValueWrapper::DeleteValue() { delete[] this->value; }

template <> void JsonValue<TRawData, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<TRawData, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<JsonObject *, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<JsonObject *, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<JsonArrayBase *, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<JsonArrayBase *, false>::ValueWrapper::DeleteValue() {}
/*


*/
template <class T, bool optional> void JsonValue<T, optional>::ValueWrapper::InitValue(T value) { this->value = value; }

template <> void JsonValue<char *, true>::ValueWrapper::InitValue(char *value) {
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
template <> void JsonValue<char *, false>::ValueWrapper::InitValue(char *value) {
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

template <> void JsonValue<JsonObject *, true>::ValueWrapper::InitValue(JsonObject *value) { this->value = value; }
template <> void JsonValue<JsonObject *, false>::ValueWrapper::InitValue(JsonObject *value) { this->value = value; }

template <> void JsonValue<JsonArrayBase *, true>::ValueWrapper::InitValue(JsonArrayBase *value) { this->value = value; }
template <> void JsonValue<JsonArrayBase *, false>::ValueWrapper::InitValue(JsonArrayBase *value) { this->value = value; }
/*


*/
template <class T, bool optional> void JsonValue<T, optional>::ValueWrapper::SetValue(T value) { this->value = value; }

template <> void JsonValue<char *, true>::ValueWrapper::SetValue(char *value) {
	DeleteValue();
	InitValue(value);
}
template <> void JsonValue<char *, false>::ValueWrapper::SetValue(char *value) {
	DeleteValue();
	InitValue(value);
}

template <> void JsonValue<JsonObject *, true>::ValueWrapper::SetValue(JsonObject *value) { this->value = value; }
template <> void JsonValue<JsonObject *, false>::ValueWrapper::SetValue(JsonObject *value) { this->value = value; }

template <> void JsonValue<JsonArrayBase *, true>::ValueWrapper::SetValue(JsonArrayBase *value) { this->value = value; }
template <> void JsonValue<JsonArrayBase *, false>::ValueWrapper::SetValue(JsonArrayBase *value) { this->value = value; }
/*


*/
template <class T, bool optional> void JsonValue<T, optional>::CloneTo(JsonValueBase *other) { ((JsonValue<T, optional> *)other)->Value = (T)this->Value; }

template <> void JsonValue<JsonObject *, true>::CloneTo(JsonValueBase *other) {
	auto thisObject = ((JsonObject *)Value);
	auto otherObject = ((JsonObject *)((JsonValue<JsonObject *, true> *)other)->Value);
	thisObject->CloneTo(otherObject);
}
template <> void JsonValue<JsonObject *, false>::CloneTo(JsonValueBase *other) {
	auto thisObject = ((JsonObject *)Value);
	auto otherObject = ((JsonObject *)((JsonValue<JsonObject *, false> *)other)->Value);
	thisObject->CloneTo(otherObject);
}

template <> void JsonValue<JsonArrayBase *, true>::CloneTo(JsonValueBase *other) {
	auto thisArray = ((JsonArrayBase *)Value);
	auto otherArray = ((JsonArrayBase *)((JsonValue<JsonArrayBase *, true> *)other)->Value);
	thisArray->CloneTo(otherArray);
}
template <> void JsonValue<JsonArrayBase *, false>::CloneTo(JsonValueBase *other) {
	auto thisArray = ((JsonArrayBase *)Value);
	auto otherArray = ((JsonArrayBase *)((JsonValue<JsonArrayBase *, false> *)other)->Value);
	thisArray->CloneTo(otherArray);
}