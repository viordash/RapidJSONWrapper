

#include "JsonValue.h"

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
