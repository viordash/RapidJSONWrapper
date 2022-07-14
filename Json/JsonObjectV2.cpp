

#include "JsonObjectV2.h"

template <> bool JsonObjectV2<bool, true>::TryParseCore(TJsonValue *value) { return value->IsBool() && SetValue(value->GetBool()); }
template <> bool JsonObjectV2<bool, false>::TryParseCore(TJsonValue *value) { return value->IsBool() && SetValue(value->GetBool()); }

template <> bool JsonObjectV2<int8_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }
template <> bool JsonObjectV2<int8_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }

template <> bool JsonObjectV2<int16_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }
template <> bool JsonObjectV2<int16_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }

template <> bool JsonObjectV2<int32_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }
template <> bool JsonObjectV2<int32_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt() && SetValue(value->GetInt()); }

template <> bool JsonObjectV2<int64_t, true>::TryParseCore(TJsonValue *value) { return value->IsInt64() && SetValue(value->GetInt64()); }
template <> bool JsonObjectV2<int64_t, false>::TryParseCore(TJsonValue *value) { return value->IsInt64() && SetValue(value->GetInt64()); }

template <> bool JsonObjectV2<uint8_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }
template <> bool JsonObjectV2<uint8_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }

template <> bool JsonObjectV2<uint16_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }
template <> bool JsonObjectV2<uint16_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }

template <> bool JsonObjectV2<uint32_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }
template <> bool JsonObjectV2<uint32_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint() && SetValue(value->GetUint()); }

template <> bool JsonObjectV2<uint64_t, true>::TryParseCore(TJsonValue *value) { return value->IsUint64() && SetValue(value->GetUint64()); }
template <> bool JsonObjectV2<uint64_t, false>::TryParseCore(TJsonValue *value) { return value->IsUint64() && SetValue(value->GetUint64()); }

template <> bool JsonObjectV2<char *, true>::TryParseCore(TJsonValue *value) { return value->IsString() && SetValue((char *)value->GetString()); }
template <> bool JsonObjectV2<char *, false>::TryParseCore(TJsonValue *value) { return value->IsString() && SetValue((char *)value->GetString()); }
/*


*/
template <> void JsonObjectV2<bool, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (bool)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<bool, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (bool)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<int8_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int8_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<int8_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int8_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<int16_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int16_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<int16_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int16_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<int32_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int32_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<int32_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int32_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<int64_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int64_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<int64_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (int64_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<uint8_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint8_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<uint8_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint8_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<uint16_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint16_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<uint16_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint16_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<uint32_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint32_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<uint32_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint32_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<uint64_t, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint64_t)Value, doc->GetAllocator()); }
template <> void JsonObjectV2<uint64_t, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), (uint64_t)Value, doc->GetAllocator()); }

template <> void JsonObjectV2<char *, true>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)Value), doc->GetAllocator()); }
template <> void JsonObjectV2<char *, false>::WriteToDoc(TJsonDocument *doc) { doc->AddMember(rapidjson::StringRef(Name), rapidjson::StringRef((char *)Value), doc->GetAllocator()); }
/*


*/
template <> void JsonObjectV2<bool, true>::InitValue(bool value) { this->value = value; }
template <> void JsonObjectV2<bool, false>::InitValue(bool value) { this->value = value; }

template <> void JsonObjectV2<int8_t, true>::InitValue(int8_t value) { this->value = value; }
template <> void JsonObjectV2<int8_t, false>::InitValue(int8_t value) { this->value = value; }

template <> void JsonObjectV2<int16_t, true>::InitValue(int16_t value) { this->value = value; }
template <> void JsonObjectV2<int16_t, false>::InitValue(int16_t value) { this->value = value; }

template <> void JsonObjectV2<int32_t, true>::InitValue(int32_t value) { this->value = value; }
template <> void JsonObjectV2<int32_t, false>::InitValue(int32_t value) { this->value = value; }

template <> void JsonObjectV2<int64_t, true>::InitValue(int64_t value) { this->value = value; }
template <> void JsonObjectV2<int64_t, false>::InitValue(int64_t value) { this->value = value; }

template <> void JsonObjectV2<uint8_t, true>::InitValue(uint8_t value) { this->value = value; }
template <> void JsonObjectV2<uint8_t, false>::InitValue(uint8_t value) { this->value = value; }

template <> void JsonObjectV2<uint16_t, true>::InitValue(uint16_t value) { this->value = value; }
template <> void JsonObjectV2<uint16_t, false>::InitValue(uint16_t value) { this->value = value; }

template <> void JsonObjectV2<uint32_t, true>::InitValue(uint32_t value) { this->value = value; }
template <> void JsonObjectV2<uint32_t, false>::InitValue(uint32_t value) { this->value = value; }

template <> void JsonObjectV2<uint64_t, true>::InitValue(uint64_t value) { this->value = value; }
template <> void JsonObjectV2<uint64_t, false>::InitValue(uint64_t value) { this->value = value; }

template <> void JsonObjectV2<char *, true>::InitValue(char *value) {
	auto len = strlen(value);
	this->value = new char[len + 1];
	if (value != NULL) { memcpy(this->value, value, len); }
	this->value[len] = 0;
}
template <> void JsonObjectV2<char *, false>::InitValue(char *value) {
	auto len = strlen(value);
	this->value = new char[len + 1];
	if (value != NULL) { memcpy(this->value, value, len); }
	this->value[len] = 0;
}
/*


*/
template <> bool JsonObjectV2<bool, true>::SetValue(bool value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<bool, false>::SetValue(bool value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<int8_t, true>::SetValue(int8_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<int8_t, false>::SetValue(int8_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<int16_t, true>::SetValue(int16_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<int16_t, false>::SetValue(int16_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<int32_t, true>::SetValue(int32_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<int32_t, false>::SetValue(int32_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<int64_t, true>::SetValue(int64_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<int64_t, false>::SetValue(int64_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<uint8_t, true>::SetValue(uint8_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<uint8_t, false>::SetValue(uint8_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<uint16_t, true>::SetValue(uint16_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<uint16_t, false>::SetValue(uint16_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<uint32_t, true>::SetValue(uint32_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<uint32_t, false>::SetValue(uint32_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<uint64_t, true>::SetValue(uint64_t value) {
	this->value = value;
	return true;
}
template <> bool JsonObjectV2<uint64_t, false>::SetValue(uint64_t value) {
	this->value = value;
	return true;
}

template <> bool JsonObjectV2<char *, true>::SetValue(char *value) {
	DeleteValue();
	auto len = strlen(value);
	this->value = new char[len + 1];
	if (value != NULL) { memcpy(this->value, value, len); }
	this->value[len] = 0;
	return true;
}
template <> bool JsonObjectV2<char *, false>::SetValue(char *value) {
	DeleteValue();
	auto len = strlen(value);
	this->value = new char[len + 1];
	if (value != NULL) { memcpy(this->value, value, len); }
	this->value[len] = 0;
	return true;
}
/*


*/
template <> void JsonObjectV2<bool, true>::DeleteValue() {}
template <> void JsonObjectV2<bool, false>::DeleteValue() {}

template <> void JsonObjectV2<int8_t, true>::DeleteValue() {}
template <> void JsonObjectV2<int8_t, false>::DeleteValue() {}

template <> void JsonObjectV2<int16_t, true>::DeleteValue() {}
template <> void JsonObjectV2<int16_t, false>::DeleteValue() {}

template <> void JsonObjectV2<int32_t, true>::DeleteValue() {}
template <> void JsonObjectV2<int32_t, false>::DeleteValue() {}

template <> void JsonObjectV2<int64_t, true>::DeleteValue() {}
template <> void JsonObjectV2<int64_t, false>::DeleteValue() {}

template <> void JsonObjectV2<uint8_t, true>::DeleteValue() {}
template <> void JsonObjectV2<uint8_t, false>::DeleteValue() {}

template <> void JsonObjectV2<uint16_t, true>::DeleteValue() {}
template <> void JsonObjectV2<uint16_t, false>::DeleteValue() {}

template <> void JsonObjectV2<uint32_t, true>::DeleteValue() {}
template <> void JsonObjectV2<uint32_t, false>::DeleteValue() {}

template <> void JsonObjectV2<uint64_t, true>::DeleteValue() {}
template <> void JsonObjectV2<uint64_t, false>::DeleteValue() {}

template <> void JsonObjectV2<char *, true>::DeleteValue() { delete[] this->value; }
template <> void JsonObjectV2<char *, false>::DeleteValue() { delete[] this->value; }
