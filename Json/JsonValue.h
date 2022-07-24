#pragma once

#include "LibJson.h"

template <class T, bool optional> TJsonDocument *JsonValue<T, optional>::BeginTryParse(const char *jsonStr, int length) {
	if (jsonStr == NULL || length == 0) { return NULL; }

	auto doc = new rapidjson::Document();
	if (length < 0) {
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

template <class T, bool optional> bool JsonValue<T, optional>::TryParse(const char *jsonStr, int length) {
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
template <class T, bool optional> int JsonValue<T, optional>::WriteToString(char *outBuffer, int outBufferSize) {
	rapidjson::Document doc;
	WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	int size = buffer.GetSize();
	if (size > outBufferSize - 1) { size = outBufferSize - 1; }
	memcpy(outBuffer, jsonStr, size);
	outBuffer[size] = 0;
	return size;
}
template <class T, bool optional> int JsonValue<T, optional>::DirectWriteTo(void *parent, TOnCompleted onCompleted) {
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
template <> bool JsonValue<bool, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<bool, true> *)other)->Value; }
template <> bool JsonValue<bool, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<bool, false> *)other)->Value; }

template <> bool JsonValue<int8_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int8_t, true> *)other)->Value; }
template <> bool JsonValue<int8_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int8_t, false> *)other)->Value; }

template <> bool JsonValue<int16_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int16_t, true> *)other)->Value; }
template <> bool JsonValue<int16_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int16_t, false> *)other)->Value; }

template <> bool JsonValue<int32_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int32_t, true> *)other)->Value; }
template <> bool JsonValue<int32_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int32_t, false> *)other)->Value; }

template <> bool JsonValue<int64_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int64_t, true> *)other)->Value; }
template <> bool JsonValue<int64_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<int64_t, false> *)other)->Value; }

template <> bool JsonValue<uint8_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint8_t, true> *)other)->Value; }
template <> bool JsonValue<uint8_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint8_t, false> *)other)->Value; }

template <> bool JsonValue<uint16_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint16_t, true> *)other)->Value; }
template <> bool JsonValue<uint16_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint16_t, false> *)other)->Value; }

template <> bool JsonValue<uint32_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint32_t, true> *)other)->Value; }
template <> bool JsonValue<uint32_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint32_t, false> *)other)->Value; }

template <> bool JsonValue<uint64_t, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint64_t, true> *)other)->Value; }
template <> bool JsonValue<uint64_t, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<uint64_t, false> *)other)->Value; }

template <> bool JsonValue<float, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<float, true> *)other)->Value; }
template <> bool JsonValue<float, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<float, false> *)other)->Value; }

template <> bool JsonValue<double, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<double, true> *)other)->Value; }
template <> bool JsonValue<double, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && Value == ((JsonValue<double, false> *)other)->Value; }

template <> bool JsonValue<char *, true>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && strcmp(Value, ((JsonValue<char *, false> *)other)->Value) == 0; }
template <> bool JsonValue<char *, false>::Equals(JsonValueBase *other) { return strcmp(Name, other->Name) == 0 && strcmp(Value, ((JsonValue<char *, false> *)other)->Value) == 0; }

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
// template <class T, bool optional> bool JsonValue<T, optional>::TryParseCore(TJsonValue *jValue) {
//	if (!jValue->Is<T>()) { return false; }
//	Value = jValue->Get<T>();
//	return true;
//}

template <> bool JsonValue<bool, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsBool()) { return false; }
	Value = jValue->GetBool();
	return true;
}
template <> bool JsonValue<bool, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsBool()) { return false; }
	Value = jValue->GetBool();
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

template <> bool JsonValue<int32_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}
template <> bool JsonValue<int32_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt()) { return false; }
	Value = jValue->GetInt();
	return true;
}

template <> bool JsonValue<int64_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt64()) { return false; }
	Value = jValue->GetInt64();
	return true;
}
template <> bool JsonValue<int64_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsInt64()) { return false; }
	Value = jValue->GetInt64();
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

template <> bool JsonValue<uint32_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}
template <> bool JsonValue<uint32_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint()) { return false; }
	Value = jValue->GetUint();
	return true;
}

template <> bool JsonValue<uint64_t, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint64()) { return false; }
	Value = jValue->GetUint64();
	return true;
}
template <> bool JsonValue<uint64_t, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsUint64()) { return false; }
	Value = jValue->GetUint64();
	return true;
}

template <> bool JsonValue<float, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsFloat()) { return false; }
	Value = jValue->GetFloat();
	return true;
}
template <> bool JsonValue<float, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsFloat()) { return false; }
	Value = jValue->GetFloat();
	return true;
}

template <> bool JsonValue<double, true>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsDouble()) { return false; }
	Value = jValue->GetDouble();
	return true;
}
template <> bool JsonValue<double, false>::TryParseCore(TJsonValue *jValue) {
	if (!jValue->IsDouble()) { return false; }
	Value = jValue->GetDouble();
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

template <> bool JsonValue<JsonObject *, true>::TryParseCore(TJsonValue *jValue) { return jValue->IsObject() && (jValue->ObjectEmpty() || Value->TryParse((TJsonDocument *)jValue)); }
template <> bool JsonValue<JsonObject *, false>::TryParseCore(TJsonValue *jValue) { return jValue->IsObject() && (jValue->ObjectEmpty() || Value->TryParse((TJsonDocument *)jValue)); }

template <> bool JsonValue<JsonArrayBase *, true>::TryParseCore(TJsonValue *jValue) { return jValue->IsArray() && Value->TryParse((TJsonDocument *)jValue); }
template <> bool JsonValue<JsonArrayBase *, false>::TryParseCore(TJsonValue *jValue) { return jValue->IsArray() && Value->TryParse((TJsonDocument *)jValue); }
/*


*/
template <> void JsonValue<bool, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (bool)Value, doc->GetAllocator()); }
template <> void JsonValue<bool, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (bool)Value, doc->GetAllocator()); }

template <> void JsonValue<int8_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int8_t)Value, doc->GetAllocator()); }
template <> void JsonValue<int8_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int8_t)Value, doc->GetAllocator()); }

template <> void JsonValue<int16_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int16_t)Value, doc->GetAllocator()); }
template <> void JsonValue<int16_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int16_t)Value, doc->GetAllocator()); }

template <> void JsonValue<int32_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int32_t)Value, doc->GetAllocator()); }
template <> void JsonValue<int32_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int32_t)Value, doc->GetAllocator()); }

template <> void JsonValue<int64_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int64_t)Value, doc->GetAllocator()); }
template <> void JsonValue<int64_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int64_t)Value, doc->GetAllocator()); }

template <> void JsonValue<uint8_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint8_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint8_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint8_t)Value, doc->GetAllocator()); }

template <> void JsonValue<uint16_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint16_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint16_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint16_t)Value, doc->GetAllocator()); }

template <> void JsonValue<uint32_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint32_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint32_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint32_t)Value, doc->GetAllocator()); }

template <> void JsonValue<uint64_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint64_t)Value, doc->GetAllocator()); }
template <> void JsonValue<uint64_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint64_t)Value, doc->GetAllocator()); }

template <> void JsonValue<float, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (float)Value, doc->GetAllocator()); }
template <> void JsonValue<float, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (float)Value, doc->GetAllocator()); }

template <> void JsonValue<double, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (double)Value, doc->GetAllocator()); }
template <> void JsonValue<double, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (double)Value, doc->GetAllocator()); }

template <> void JsonValue<char *, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)Value), doc->GetAllocator()); }
template <> void JsonValue<char *, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)Value), doc->GetAllocator()); }

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
template <> void JsonValue<bool, true>::ValueWrapper::InitValue(bool value) { this->value = value; }
template <> void JsonValue<bool, false>::ValueWrapper::InitValue(bool value) { this->value = value; }

template <> void JsonValue<int8_t, true>::ValueWrapper::InitValue(int8_t value) { this->value = value; }
template <> void JsonValue<int8_t, false>::ValueWrapper::InitValue(int8_t value) { this->value = value; }

template <> void JsonValue<int16_t, true>::ValueWrapper::InitValue(int16_t value) { this->value = value; }
template <> void JsonValue<int16_t, false>::ValueWrapper::InitValue(int16_t value) { this->value = value; }

template <> void JsonValue<int32_t, true>::ValueWrapper::InitValue(int32_t value) { this->value = value; }
template <> void JsonValue<int32_t, false>::ValueWrapper::InitValue(int32_t value) { this->value = value; }

template <> void JsonValue<int64_t, true>::ValueWrapper::InitValue(int64_t value) { this->value = value; }
template <> void JsonValue<int64_t, false>::ValueWrapper::InitValue(int64_t value) { this->value = value; }

template <> void JsonValue<uint8_t, true>::ValueWrapper::InitValue(uint8_t value) { this->value = value; }
template <> void JsonValue<uint8_t, false>::ValueWrapper::InitValue(uint8_t value) { this->value = value; }

template <> void JsonValue<uint16_t, true>::ValueWrapper::InitValue(uint16_t value) { this->value = value; }
template <> void JsonValue<uint16_t, false>::ValueWrapper::InitValue(uint16_t value) { this->value = value; }

template <> void JsonValue<uint32_t, true>::ValueWrapper::InitValue(uint32_t value) { this->value = value; }
template <> void JsonValue<uint32_t, false>::ValueWrapper::InitValue(uint32_t value) { this->value = value; }

template <> void JsonValue<uint64_t, true>::ValueWrapper::InitValue(uint64_t value) { this->value = value; }
template <> void JsonValue<uint64_t, false>::ValueWrapper::InitValue(uint64_t value) { this->value = value; }

template <> void JsonValue<float, true>::ValueWrapper::InitValue(float value) { this->value = value; }
template <> void JsonValue<float, false>::ValueWrapper::InitValue(float value) { this->value = value; }

template <> void JsonValue<double, true>::ValueWrapper::InitValue(double value) { this->value = value; }
template <> void JsonValue<double, false>::ValueWrapper::InitValue(double value) { this->value = value; }

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
template <> void JsonValue<bool, true>::ValueWrapper::SetValue(bool value) { this->value = value; }
template <> void JsonValue<bool, false>::ValueWrapper::SetValue(bool value) { this->value = value; }

template <> void JsonValue<int8_t, true>::ValueWrapper::SetValue(int8_t value) { this->value = value; }
template <> void JsonValue<int8_t, false>::ValueWrapper::SetValue(int8_t value) { this->value = value; }

template <> void JsonValue<int16_t, true>::ValueWrapper::SetValue(int16_t value) { this->value = value; }
template <> void JsonValue<int16_t, false>::ValueWrapper::SetValue(int16_t value) { this->value = value; }

template <> void JsonValue<int32_t, true>::ValueWrapper::SetValue(int32_t value) { this->value = value; }
template <> void JsonValue<int32_t, false>::ValueWrapper::SetValue(int32_t value) { this->value = value; }

template <> void JsonValue<int64_t, true>::ValueWrapper::SetValue(int64_t value) { this->value = value; }
template <> void JsonValue<int64_t, false>::ValueWrapper::SetValue(int64_t value) { this->value = value; }

template <> void JsonValue<uint8_t, true>::ValueWrapper::SetValue(uint8_t value) { this->value = value; }
template <> void JsonValue<uint8_t, false>::ValueWrapper::SetValue(uint8_t value) { this->value = value; }

template <> void JsonValue<uint16_t, true>::ValueWrapper::SetValue(uint16_t value) { this->value = value; }
template <> void JsonValue<uint16_t, false>::ValueWrapper::SetValue(uint16_t value) { this->value = value; }

template <> void JsonValue<uint32_t, true>::ValueWrapper::SetValue(uint32_t value) { this->value = value; }
template <> void JsonValue<uint32_t, false>::ValueWrapper::SetValue(uint32_t value) { this->value = value; }

template <> void JsonValue<uint64_t, true>::ValueWrapper::SetValue(uint64_t value) { this->value = value; }
template <> void JsonValue<uint64_t, false>::ValueWrapper::SetValue(uint64_t value) { this->value = value; }

template <> void JsonValue<float, true>::ValueWrapper::SetValue(float value) { this->value = value; }
template <> void JsonValue<float, false>::ValueWrapper::SetValue(float value) { this->value = value; }

template <> void JsonValue<double, true>::ValueWrapper::SetValue(double value) { this->value = value; }
template <> void JsonValue<double, false>::ValueWrapper::SetValue(double value) { this->value = value; }

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

template <> void JsonValue<JsonObject *, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<JsonObject *, false>::ValueWrapper::DeleteValue() {}

template <> void JsonValue<JsonArrayBase *, true>::ValueWrapper::DeleteValue() {}
template <> void JsonValue<JsonArrayBase *, false>::ValueWrapper::DeleteValue() {}
/*


*/
template <> void JsonValue<bool, true>::CloneTo(JsonValueBase *other) { ((JsonValue<bool, true> *)other)->Value = (bool)this->Value; }
template <> void JsonValue<bool, false>::CloneTo(JsonValueBase *other) { ((JsonValue<bool, false> *)other)->Value = (bool)this->Value; }

template <> void JsonValue<int8_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int8_t, true> *)other)->Value = (int8_t)this->Value; }
template <> void JsonValue<int8_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int8_t, false> *)other)->Value = (int8_t)this->Value; }

template <> void JsonValue<int16_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int16_t, true> *)other)->Value = (int16_t)this->Value; }
template <> void JsonValue<int16_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int16_t, false> *)other)->Value = (int16_t)this->Value; }

template <> void JsonValue<int32_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int32_t, true> *)other)->Value = (int32_t)this->Value; }
template <> void JsonValue<int32_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int32_t, false> *)other)->Value = (int32_t)this->Value; }

template <> void JsonValue<int64_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int64_t, true> *)other)->Value = (int64_t)this->Value; }
template <> void JsonValue<int64_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int64_t, false> *)other)->Value = (int64_t)this->Value; }

template <> void JsonValue<uint8_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint8_t, true> *)other)->Value = (uint8_t)this->Value; }
template <> void JsonValue<uint8_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint8_t, false> *)other)->Value = (uint8_t)this->Value; }

template <> void JsonValue<uint16_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint16_t, true> *)other)->Value = (uint16_t)this->Value; }
template <> void JsonValue<uint16_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint16_t, false> *)other)->Value = (uint16_t)this->Value; }

template <> void JsonValue<uint32_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint32_t, true> *)other)->Value = (uint32_t)this->Value; }
template <> void JsonValue<uint32_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint32_t, false> *)other)->Value = (uint32_t)this->Value; }

template <> void JsonValue<uint64_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint64_t, true> *)other)->Value = (uint64_t)this->Value; }
template <> void JsonValue<uint64_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint64_t, false> *)other)->Value = (uint64_t)this->Value; }

template <> void JsonValue<float, true>::CloneTo(JsonValueBase *other) { ((JsonValue<float, true> *)other)->Value = (float)this->Value; }
template <> void JsonValue<float, false>::CloneTo(JsonValueBase *other) { ((JsonValue<float, false> *)other)->Value = (float)this->Value; }

template <> void JsonValue<double, true>::CloneTo(JsonValueBase *other) { ((JsonValue<double, true> *)other)->Value = (double)this->Value; }
template <> void JsonValue<double, false>::CloneTo(JsonValueBase *other) { ((JsonValue<double, false> *)other)->Value = (double)this->Value; }

template <> void JsonValue<char *, true>::CloneTo(JsonValueBase *other) { ((JsonValue<char *, true> *)other)->Value = (char *)this->Value; }
template <> void JsonValue<char *, false>::CloneTo(JsonValueBase *other) { ((JsonValue<char *, false> *)other)->Value = (char *)this->Value; }

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