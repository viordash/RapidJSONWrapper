
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <> bool JsonCommonValue<bool>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonCommonValue<bool>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<int8_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<int16_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<int32_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<int64_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<uint8_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<uint16_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<uint32_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<uint64_t>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<float>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
template <> bool JsonCommonValue<double>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonCommonValue<double>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<char *>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<TJsonRawData>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	if (jsonVal->IsDouble()) {
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
	auto jsonVal = JsonCommonValue<JsonObject *>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
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
	auto jsonVal = JsonCommonValue<JsonArrayBase *>::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	if (jsonVal->IsArray()) {
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
