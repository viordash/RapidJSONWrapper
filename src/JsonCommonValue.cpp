
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

static TJsonValue *GetMember(TJsonDocument *doc, const char *name) {
	rapidjson::Value::MemberIterator member = doc->MemberBegin();
	while (member != doc->MemberEnd()) {
		auto &memberName = member->name;
		if (strcmp(name, memberName.GetString()) == 0) return &member->value;
		++member;
	}
	return NULL;
}

template <> bool JsonCommonValue<bool>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsBool()) {
		Value = jsonVal->GetBool();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt()) {
		Value = jsonVal->GetInt();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt()) {
		Value = jsonVal->GetInt();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt()) {
		Value = jsonVal->GetInt();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt64()) {
		Value = jsonVal->GetInt64();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Value = jsonVal->GetUint();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Value = jsonVal->GetUint();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Value = jsonVal->GetUint();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Value = jsonVal->GetUint();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<float>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsFloat()) {
		Value = jsonVal->GetFloat();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<double>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsDouble()) {
		Value = jsonVal->GetDouble();
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<char *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsString()) {
		Value.DeleteValue();
		size_t len = jsonVal->GetStringLength();
		Value.value = new char[len + 1];
		memcpy(Value.value, (char *)jsonVal->GetString(), len);
		Value.value[len] = 0;
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		Value = NULL;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<TJsonRawData>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsString()) {
		TJsonRawData rawData = {(uint8_t *)jsonVal->GetString(), jsonVal->GetStringLength()};
		Value = rawData;
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		Value = {};
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<JsonObject *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsObject()) {
		Value->TryParse((TJsonDocument *)jsonVal);
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<JsonArrayBase *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsArray()) {
		Value->TryDocParse((TJsonDocument *)jsonVal);
		isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
/*



*/
template <> bool JsonCommonValue<bool>::IsNull() { return isNull; }
template <> bool JsonCommonValue<int8_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<int16_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<int32_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<int64_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<uint8_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<uint16_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<uint32_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<uint64_t>::IsNull() { return isNull; }
template <> bool JsonCommonValue<float>::IsNull() { return isNull; }
template <> bool JsonCommonValue<double>::IsNull() { return isNull; }
template <> bool JsonCommonValue<char *>::IsNull() { return isNull || (char *)Value == NULL; }
template <> bool JsonCommonValue<TJsonRawData>::IsNull() { return isNull; }
template <> bool JsonCommonValue<JsonObject *>::IsNull() { return isNull; }
template <> bool JsonCommonValue<JsonArrayBase *>::IsNull() { return isNull; }
