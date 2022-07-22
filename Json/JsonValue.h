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

template <class T, bool optional> bool operator!=(const JsonValue<T, optional> &v1, const JsonValue<T, optional> &v2) {
	if (strcmp(v1.Name, v2.Name) != 0) { return true; }
	return v1.Value != v2.Value;
}
template <class T, bool optional> bool operator==(const JsonValue<T, optional> &v1, const JsonValue<T, optional> &v2) { return !(v1 != v2); }

template <bool optional> bool operator!=(const JsonValue<char *, optional> &v1, const JsonValue<char *, optional> &v2) {
	if (strcmp(v1.Name, v2.Name) != 0) { return true; }
	return strcmp(v1.Value, v2.Value) != 0;
}
template <bool optional> bool operator!=(const JsonValue<JsonObject *, optional> &v1, const JsonValue<JsonObject *, optional> &v2) {
	if (strcmp(v1.Name, v2.Name) != 0) { return true; }
	return *((JsonObject *)v1.Value) != *((JsonObject *)v2.Value);
}
template <bool optional> bool operator!=(const JsonValue<JsonArrayBase *, optional> &v1, const JsonValue<JsonArrayBase *, optional> &v2) {
	if (strcmp(v1.Name, v2.Name) != 0) { return true; }
	return !((JsonArrayBase *)v1.Value)->Equals((JsonArrayBase *)v2.Value);
}

template <class T, bool optional> bool JsonValue<T, optional>::Equals(JsonValueBase *other) { return !(*this != *((JsonValue<T, optional> *)other)); }

bool operator!=(const JsonValueBase &v1, const JsonValueBase &v2) { return !((JsonValueBase *)&v1)->Equals((JsonValueBase *)&v2); }
bool operator==(const JsonValueBase &v1, const JsonValueBase &v2) { return !(v1 != v2); }
/*


*/
template <> bool JsonValue<bool, true>::TryParseCore(TJsonValue *value) { return value->IsBool() && SetValue(value->GetBool()); }
template <> bool JsonValue<bool, false>::TryParseCore(TJsonValue *value) { return value->IsBool() && SetValue(value->GetBool()); }

template <> bool JsonValue<int8_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }
template <> bool JsonValue<int8_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }

template <> bool JsonValue<int16_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }
template <> bool JsonValue<int16_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }

template <> bool JsonValue<int32_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }
template <> bool JsonValue<int32_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }

template <> bool JsonValue<int64_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt64() && SetValue(value->GetInt64()); }
template <> bool JsonValue<int64_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt64() && SetValue(value->GetInt64()); }

template <> bool JsonValue<uint8_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }
template <> bool JsonValue<uint8_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }

template <> bool JsonValue<uint16_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }
template <> bool JsonValue<uint16_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }

template <> bool JsonValue<uint32_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }
template <> bool JsonValue<uint32_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }

template <> bool JsonValue<uint64_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint64() && SetValue(value->GetUint64()); }
template <> bool JsonValue<uint64_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint64() && SetValue(value->GetUint64()); }

template <> bool JsonValue<float, true>::TryParseCore(TJsonValue *value) { return value->IsFloat() && SetValue(value->GetFloat()); }
template <> bool JsonValue<float, false>::TryParseCore(TJsonValue *value) { return value->IsFloat() && SetValue(value->GetFloat()); }

template <> bool JsonValue<double, true>::TryParseCore(TJsonValue *value) { return value->IsDouble() && SetValue(value->GetDouble()); }
template <> bool JsonValue<double, false>::TryParseCore(TJsonValue *value) { return value->IsDouble() && SetValue(value->GetDouble()); }

template <> bool JsonValue<char *, true>::TryParseCore(TJsonValue *value) { return value->IsString() && SetValue((char *)value->GetString()); }
template <> bool JsonValue<char *, false>::TryParseCore(TJsonValue *value) { return value->IsString() && SetValue((char *)value->GetString()); }

template <> bool JsonValue<JsonObject *, true>::TryParseCore(TJsonValue *value) { return value->IsObject() && (value->ObjectEmpty() || this->value->TryParse((TJsonDocument *)value)); }
template <> bool JsonValue<JsonObject *, false>::TryParseCore(TJsonValue *value) { return value->IsObject() && (value->ObjectEmpty() || this->value->TryParse((TJsonDocument *)value)); }

template <> bool JsonValue<JsonArrayBase *, true>::TryParseCore(TJsonValue *value) { return value->IsArray() && this->value->TryParse((TJsonDocument *)value); }
template <> bool JsonValue<JsonArrayBase *, false>::TryParseCore(TJsonValue *value) { return value->IsArray() && this->value->TryParse((TJsonDocument *)value); }
/*


*/
template <> void JsonValue<bool, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (bool)value, doc->GetAllocator()); }
template <> void JsonValue<bool, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (bool)value, doc->GetAllocator()); }

template <> void JsonValue<int8_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int8_t)value, doc->GetAllocator()); }
template <> void JsonValue<int8_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int8_t)value, doc->GetAllocator()); }

template <> void JsonValue<int16_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int16_t)value, doc->GetAllocator()); }
template <> void JsonValue<int16_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int16_t)value, doc->GetAllocator()); }

template <> void JsonValue<int32_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int32_t)value, doc->GetAllocator()); }
template <> void JsonValue<int32_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int32_t)value, doc->GetAllocator()); }

template <> void JsonValue<int64_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int64_t)value, doc->GetAllocator()); }
template <> void JsonValue<int64_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int64_t)value, doc->GetAllocator()); }

template <> void JsonValue<uint8_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint8_t)value, doc->GetAllocator()); }
template <> void JsonValue<uint8_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint8_t)value, doc->GetAllocator()); }

template <> void JsonValue<uint16_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint16_t)value, doc->GetAllocator()); }
template <> void JsonValue<uint16_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint16_t)value, doc->GetAllocator()); }

template <> void JsonValue<uint32_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint32_t)value, doc->GetAllocator()); }
template <> void JsonValue<uint32_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint32_t)value, doc->GetAllocator()); }

template <> void JsonValue<uint64_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint64_t)value, doc->GetAllocator()); }
template <> void JsonValue<uint64_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint64_t)value, doc->GetAllocator()); }

template <> void JsonValue<float, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (float)value, doc->GetAllocator()); }
template <> void JsonValue<float, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (float)value, doc->GetAllocator()); }

template <> void JsonValue<double, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (double)value, doc->GetAllocator()); }
template <> void JsonValue<double, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (double)value, doc->GetAllocator()); }

template <> void JsonValue<char *, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)value), doc->GetAllocator()); }
template <> void JsonValue<char *, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)value), doc->GetAllocator()); }

template <> void JsonValue<JsonObject *, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	jObject.SetObject();
	value->WriteToDoc(&jObject);
	doc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}
template <> void JsonValue<JsonObject *, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	jObject.SetObject();
	value->WriteToDoc(&jObject);
	doc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}

template <> void JsonValue<JsonArrayBase *, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	value->WriteToDoc(&jArray);
	doc->AddMember(rapidjson::StringRef(Name), jArray, allocator);
}
template <> void JsonValue<JsonArrayBase *, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	value->WriteToDoc(&jArray);
	doc->AddMember(rapidjson::StringRef(Name), jArray, allocator);
}
/*


*/
template <> void JsonValue<bool, true>::InitValue(bool value) { this->value = value; }
template <> void JsonValue<bool, false>::InitValue(bool value) { this->value = value; }

template <> void JsonValue<int8_t, true>::InitValue(int8_t value) { this->value = value; }
template <> void JsonValue<int8_t, false>::InitValue(int8_t value) { this->value = value; }

template <> void JsonValue<int16_t, true>::InitValue(int16_t value) { this->value = value; }
template <> void JsonValue<int16_t, false>::InitValue(int16_t value) { this->value = value; }

template <> void JsonValue<int32_t, true>::InitValue(int32_t value) { this->value = value; }
template <> void JsonValue<int32_t, false>::InitValue(int32_t value) { this->value = value; }

template <> void JsonValue<int64_t, true>::InitValue(int64_t value) { this->value = value; }
template <> void JsonValue<int64_t, false>::InitValue(int64_t value) { this->value = value; }

template <> void JsonValue<uint8_t, true>::InitValue(uint8_t value) { this->value = value; }
template <> void JsonValue<uint8_t, false>::InitValue(uint8_t value) { this->value = value; }

template <> void JsonValue<uint16_t, true>::InitValue(uint16_t value) { this->value = value; }
template <> void JsonValue<uint16_t, false>::InitValue(uint16_t value) { this->value = value; }

template <> void JsonValue<uint32_t, true>::InitValue(uint32_t value) { this->value = value; }
template <> void JsonValue<uint32_t, false>::InitValue(uint32_t value) { this->value = value; }

template <> void JsonValue<uint64_t, true>::InitValue(uint64_t value) { this->value = value; }
template <> void JsonValue<uint64_t, false>::InitValue(uint64_t value) { this->value = value; }

template <> void JsonValue<float, true>::InitValue(float value) { this->value = value; }
template <> void JsonValue<float, false>::InitValue(float value) { this->value = value; }

template <> void JsonValue<double, true>::InitValue(double value) { this->value = value; }
template <> void JsonValue<double, false>::InitValue(double value) { this->value = value; }

template <> void JsonValue<char *, true>::InitValue(char *value) {
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
template <> void JsonValue<char *, false>::InitValue(char *value) {
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

template <> void JsonValue<JsonObject *, true>::InitValue(JsonObject *value) { this->value = value; }
template <> void JsonValue<JsonObject *, false>::InitValue(JsonObject *value) { this->value = value; }

template <> void JsonValue<JsonArrayBase *, true>::InitValue(JsonArrayBase *value) { this->value = value; }
template <> void JsonValue<JsonArrayBase *, false>::InitValue(JsonArrayBase *value) { this->value = value; }
/*


*/
template <> bool JsonValue<bool, true>::SetValue(bool value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<bool, false>::SetValue(bool value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<int8_t, true>::SetValue(int8_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<int8_t, false>::SetValue(int8_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<int16_t, true>::SetValue(int16_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<int16_t, false>::SetValue(int16_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<int32_t, true>::SetValue(int32_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<int32_t, false>::SetValue(int32_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<int64_t, true>::SetValue(int64_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<int64_t, false>::SetValue(int64_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<uint8_t, true>::SetValue(uint8_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<uint8_t, false>::SetValue(uint8_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<uint16_t, true>::SetValue(uint16_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<uint16_t, false>::SetValue(uint16_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<uint32_t, true>::SetValue(uint32_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<uint32_t, false>::SetValue(uint32_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<uint64_t, true>::SetValue(uint64_t value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<uint64_t, false>::SetValue(uint64_t value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<float, true>::SetValue(float value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<float, false>::SetValue(float value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<double, true>::SetValue(double value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<double, false>::SetValue(double value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<char *, true>::SetValue(char *value) {
	DeleteValue();
	InitValue(value);
	return true;
}
template <> bool JsonValue<char *, false>::SetValue(char *value) {
	DeleteValue();
	InitValue(value);
	return true;
}

template <> bool JsonValue<JsonObject *, true>::SetValue(JsonObject *value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<JsonObject *, false>::SetValue(JsonObject *value) {
	this->value = value;
	return true;
}

template <> bool JsonValue<JsonArrayBase *, true>::SetValue(JsonArrayBase *value) {
	this->value = value;
	return true;
}
template <> bool JsonValue<JsonArrayBase *, false>::SetValue(JsonArrayBase *value) {
	this->value = value;
	return true;
}
/*


*/
template <> void JsonValue<bool, true>::DeleteValue() {}
template <> void JsonValue<bool, false>::DeleteValue() {}

template <> void JsonValue<int8_t, true>::DeleteValue() {}
template <> void JsonValue<int8_t, false>::DeleteValue() {}

template <> void JsonValue<int16_t, true>::DeleteValue() {}
template <> void JsonValue<int16_t, false>::DeleteValue() {}

template <> void JsonValue<int32_t, true>::DeleteValue() {}
template <> void JsonValue<int32_t, false>::DeleteValue() {}

template <> void JsonValue<int64_t, true>::DeleteValue() {}
template <> void JsonValue<int64_t, false>::DeleteValue() {}

template <> void JsonValue<uint8_t, true>::DeleteValue() {}
template <> void JsonValue<uint8_t, false>::DeleteValue() {}

template <> void JsonValue<uint16_t, true>::DeleteValue() {}
template <> void JsonValue<uint16_t, false>::DeleteValue() {}

template <> void JsonValue<uint32_t, true>::DeleteValue() {}
template <> void JsonValue<uint32_t, false>::DeleteValue() {}

template <> void JsonValue<uint64_t, true>::DeleteValue() {}
template <> void JsonValue<uint64_t, false>::DeleteValue() {}

template <> void JsonValue<float, true>::DeleteValue() {}
template <> void JsonValue<float, false>::DeleteValue() {}

template <> void JsonValue<double, true>::DeleteValue() {}
template <> void JsonValue<double, false>::DeleteValue() {}

template <> void JsonValue<char *, true>::DeleteValue() { delete[] this->value; }
template <> void JsonValue<char *, false>::DeleteValue() { delete[] this->value; }

template <> void JsonValue<JsonObject *, true>::DeleteValue() {}
template <> void JsonValue<JsonObject *, false>::DeleteValue() {}

template <> void JsonValue<JsonArrayBase *, true>::DeleteValue() {}
template <> void JsonValue<JsonArrayBase *, false>::DeleteValue() {}
/*


*/
template <> void JsonValue<bool, true>::CloneTo(JsonValueBase *other) { ((JsonValue<bool, true> *)other)->value = this->value; }
template <> void JsonValue<bool, false>::CloneTo(JsonValueBase *other) { ((JsonValue<bool, false> *)other)->value = this->value; }

template <> void JsonValue<int8_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int8_t, true> *)other)->value = this->value; }
template <> void JsonValue<int8_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int8_t, false> *)other)->value = this->value; }

template <> void JsonValue<int16_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int16_t, true> *)other)->value = this->value; }
template <> void JsonValue<int16_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int16_t, false> *)other)->value = this->value; }

template <> void JsonValue<int32_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int32_t, true> *)other)->value = this->value; }
template <> void JsonValue<int32_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int32_t, false> *)other)->value = this->value; }

template <> void JsonValue<int64_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<int64_t, true> *)other)->value = this->value; }
template <> void JsonValue<int64_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<int64_t, false> *)other)->value = this->value; }

template <> void JsonValue<uint8_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint8_t, true> *)other)->value = this->value; }
template <> void JsonValue<uint8_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint8_t, false> *)other)->value = this->value; }

template <> void JsonValue<uint16_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint16_t, true> *)other)->value = this->value; }
template <> void JsonValue<uint16_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint16_t, false> *)other)->value = this->value; }

template <> void JsonValue<uint32_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint32_t, true> *)other)->value = this->value; }
template <> void JsonValue<uint32_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint32_t, false> *)other)->value = this->value; }

template <> void JsonValue<uint64_t, true>::CloneTo(JsonValueBase *other) { ((JsonValue<uint64_t, true> *)other)->value = this->value; }
template <> void JsonValue<uint64_t, false>::CloneTo(JsonValueBase *other) { ((JsonValue<uint64_t, false> *)other)->value = this->value; }

template <> void JsonValue<float, true>::CloneTo(JsonValueBase *other) { ((JsonValue<float, true> *)other)->value = this->value; }
template <> void JsonValue<float, false>::CloneTo(JsonValueBase *other) { ((JsonValue<float, false> *)other)->value = this->value; }

template <> void JsonValue<double, true>::CloneTo(JsonValueBase *other) { ((JsonValue<double, true> *)other)->value = this->value; }
template <> void JsonValue<double, false>::CloneTo(JsonValueBase *other) { ((JsonValue<double, false> *)other)->value = this->value; }

template <> void JsonValue<char *, true>::CloneTo(JsonValueBase *other) { ((JsonValue<char *, true> *)other)->SetValue(this->value); }
template <> void JsonValue<char *, false>::CloneTo(JsonValueBase *other) { ((JsonValue<char *, false> *)other)->SetValue(this->value); }

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
	auto otherArray = ((JsonArrayBase *)((JsonValue<JsonArrayBase *, false> *)other)->Value);
	// for (const auto &item : Items) { delete item; }
	// Items.clear();

	// for (const auto &item : otherJsonArray->Items) {
	//	auto newItem = CreateItem();
	//	newItem->CloneFrom(item);
	//	if (!Add(newItem)) {
	//		delete newItem;
	//		return;
	//	}
	//}
}
template <> void JsonValue<JsonArrayBase *, false>::CloneTo(JsonValueBase *other) { ((JsonValue<JsonArrayBase *, false> *)other)->value; }