
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
template <> void JsonCommonValue<bool>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetBool(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int8_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int16_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int32_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int64_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt64(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint8_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint16_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint32_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint64_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint64(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<float>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetFloat(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<double>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetDouble(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<char *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull || Value == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)Value));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	TJsonRawData rawData = Value;
	if (isNull || rawData.Data == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)rawData.Data, (rapidjson::SizeType)rawData.Size));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<JsonObject *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	if (isNull || Value == NULL) {
		jObject.SetNull();
	} else {
		Value->WriteToDoc(&jObject);
	}
	doc->AddMember(Name, jObject, allocator);
}
template <> void JsonCommonValue<JsonArrayBase *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	if (isNull || Value == NULL) {
		jArray.SetNull();
	} else {
		Value->WriteToDoc(&jArray);
	}
	doc->AddMember(Name, jArray, allocator);
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
/*



*/
template <> void JsonCommonValue<bool>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<int8_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<int16_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<int32_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<int64_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<uint8_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<uint16_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<uint32_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<uint64_t>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<float>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<double>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<char *>::ResetToNull() {
	isNull = true;
	Value = NULL;
}
template <> void JsonCommonValue<TJsonRawData>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<JsonObject *>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<JsonArrayBase *>::ResetToNull() { isNull = true; }