
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <> bool JsonCommonValue<bool>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsBool()) {
		Set(jsonVal->GetBool());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt()) {
		Set(jsonVal->GetInt());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt()) {
		Set(jsonVal->GetInt());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt()) {
		Set(jsonVal->GetInt());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<int64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsInt64()) {
		Set(jsonVal->GetInt64());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint8_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Set(jsonVal->GetUint());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint16_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Set(jsonVal->GetUint());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint32_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Set(jsonVal->GetUint());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<uint64_t>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsUint()) {
		Set(jsonVal->GetUint());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<float>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsFloat()) {
		Set(jsonVal->GetFloat());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<double>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsDouble()) {
		Set(jsonVal->GetDouble());
		return true;
	}
	if (jsonVal->IsNull()) {
		isNull = true;
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<char *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsString()) {
		Set((char *)jsonVal->GetString(), jsonVal->GetStringLength());
		return true;
	}
	if (jsonVal->IsNull()) {
		Set(NULL);
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<TJsonRawData>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsString()) {
		TJsonRawData rawData = {(uint8_t *)jsonVal->GetString(), jsonVal->GetStringLength()};
		Set(rawData);
		return true;
	}
	if (jsonVal->IsNull()) {
		Set({});
		return true;
	}
	return false;
}
template <> bool JsonCommonValue<JsonObject *>::TryParse(TJsonDocument *doc) {
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsObject()) {
		value->TryParse((TJsonDocument *)jsonVal);
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
	auto jsonVal = JsonValueBase::GetMember(doc, this->Name);
	if (jsonVal == NULL) {
		presented = false;
		return true;
	}
	presented = true;
	if (jsonVal->IsArray()) {
		value->TryDocParse((TJsonDocument *)jsonVal);
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
template <> bool JsonCommonValue<bool>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<bool> *)other)->value; }
template <> bool JsonCommonValue<int8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<int8_t> *)other)->value; }
template <> bool JsonCommonValue<int16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<int16_t> *)other)->value; }
template <> bool JsonCommonValue<int32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<int32_t> *)other)->value; }
template <> bool JsonCommonValue<int64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<int64_t> *)other)->value; }
template <> bool JsonCommonValue<uint8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<uint8_t> *)other)->value; }
template <> bool JsonCommonValue<uint16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<uint16_t> *)other)->value; }
template <> bool JsonCommonValue<uint32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<uint32_t> *)other)->value; }
template <> bool JsonCommonValue<uint64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<uint64_t> *)other)->value; }
template <> bool JsonCommonValue<float>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<float> *)other)->value; }
template <> bool JsonCommonValue<double>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && value == ((JsonCommonValue<double> *)other)->value; }
template <> bool JsonCommonValue<char *>::Equals(JsonValueBase *other) { //
	return JsonValueBase::NamesCompare(Name, other->Name)
		&& (value == ((JsonCommonValue<char *> *)other)->value
			|| (value != NULL && ((JsonCommonValue<char *> *)other)->value != NULL && strcmp(value, ((JsonCommonValue<char *> *)other)->value) == 0));
}
template <> bool JsonCommonValue<TJsonRawData>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name)														//
		&& ((TJsonRawData)value).Data == ((TJsonRawData)(((JsonCommonValue<TJsonRawData> *)other)->value)).Data //
		&& ((TJsonRawData)value).Size == ((TJsonRawData)(((JsonCommonValue<TJsonRawData> *)other)->value)).Size;
}
template <> bool JsonCommonValue<JsonObject *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)value->Equals((JsonObject *)((JsonCommonValue<JsonObject *> *)other)->value);
}
template <> bool JsonCommonValue<JsonArrayBase *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)value->Equals((JsonArrayBase *)(((JsonCommonValue<JsonArrayBase *> *)other)->value));
}
/*


*/
template <> void JsonCommonValue<bool>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetBool(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int8_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int16_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int32_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int64_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt64(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint8_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint16_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint32_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint64_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint64(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<float>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetFloat(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<double>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull) {
		json_val.SetNull();
	} else {
		json_val.SetDouble(value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<char *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (isNull || value == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)value));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	TJsonRawData rawData = value;
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
	if (isNull || value == NULL) {
		jObject.SetNull();
	} else {
		value->WriteToDoc(&jObject);
	}
	doc->AddMember(Name, jObject, allocator);
}
template <> void JsonCommonValue<JsonArrayBase *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	if (isNull || value == NULL) {
		jArray.SetNull();
	} else {
		value->WriteToDoc(&jArray);
	}
	doc->AddMember(Name, jArray, allocator);
}
/*


*/
template <> void JsonCommonValue<bool>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<bool> *)other)->Set((bool)this->value); }
template <> void JsonCommonValue<int8_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int8_t> *)other)->Set((int8_t)this->value); }
template <> void JsonCommonValue<int16_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int16_t> *)other)->Set((int16_t)this->value); }
template <> void JsonCommonValue<int32_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int32_t> *)other)->Set((int32_t)this->value); }
template <> void JsonCommonValue<int64_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int64_t> *)other)->Set((int64_t)this->value); }
template <> void JsonCommonValue<uint8_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint8_t> *)other)->Set((uint8_t)this->value); }
template <> void JsonCommonValue<uint16_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint16_t> *)other)->Set((uint16_t)this->value); }
template <> void JsonCommonValue<uint32_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint32_t> *)other)->Set((uint32_t)this->value); }
template <> void JsonCommonValue<uint64_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint64_t> *)other)->Set((uint64_t)this->value); }
template <> void JsonCommonValue<float>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<float> *)other)->Set((float)this->value); }
template <> void JsonCommonValue<double>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<double> *)other)->Set((double)this->value); }
template <> void JsonCommonValue<char *>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<char *> *)other)->Set((char *)this->value); }
template <> void JsonCommonValue<TJsonRawData>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<TJsonRawData> *)other)->Set((TJsonRawData)this->value); }
template <> void JsonCommonValue<JsonObject *>::CloneTo(JsonValueBase *other) {
	auto thisObject = ((JsonObject *)value);
	auto otherObject = ((JsonObject *)((JsonCommonValue<JsonObject *> *)other)->value);
	thisObject->CloneTo(otherObject);
}
template <> void JsonCommonValue<JsonArrayBase *>::CloneTo(JsonValueBase *other) {
	auto thisArray = ((JsonArrayBase *)value);
	auto otherArray = ((JsonArrayBase *)((JsonCommonValue<JsonArrayBase *> *)other)->value);
	thisArray->CloneTo(otherArray);
}
/*


*/
template <> void JsonCommonValue<bool>::DeleteValue() {}
template <> void JsonCommonValue<int8_t>::DeleteValue() {}
template <> void JsonCommonValue<int16_t>::DeleteValue() {}
template <> void JsonCommonValue<int32_t>::DeleteValue() {}
template <> void JsonCommonValue<int64_t>::DeleteValue() {}
template <> void JsonCommonValue<uint8_t>::DeleteValue() {}
template <> void JsonCommonValue<uint16_t>::DeleteValue() {}
template <> void JsonCommonValue<uint32_t>::DeleteValue() {}
template <> void JsonCommonValue<uint64_t>::DeleteValue() {}
template <> void JsonCommonValue<float>::DeleteValue() {}
template <> void JsonCommonValue<double>::DeleteValue() {}
template <> void JsonCommonValue<char *>::DeleteValue() { delete[] this->value; }
template <> void JsonCommonValue<TJsonRawData>::DeleteValue() {}
template <> void JsonCommonValue<JsonObject *>::DeleteValue() {}
template <> void JsonCommonValue<JsonArrayBase *>::DeleteValue() {}
/*


*/
template <> void JsonCommonValue<bool>::InitValue(bool value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<int8_t>::InitValue(int8_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<int16_t>::InitValue(int16_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<int32_t>::InitValue(int32_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<int64_t>::InitValue(int64_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<uint8_t>::InitValue(uint8_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<uint16_t>::InitValue(uint16_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<uint32_t>::InitValue(uint32_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<uint64_t>::InitValue(uint64_t value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<float>::InitValue(float value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<double>::InitValue(double value, size_t valueLen) {
	this->value = value;
	this->isNull = false;
}
template <> void JsonCommonValue<char *>::InitValue(char *value, size_t valueLen) {
	if (value == NULL) {
		this->value = NULL;
	} else {
		size_t len = valueLen != size_t() //
					   ? valueLen		  //
					   : strlen(value);
		this->value = new char[len + 1];
		memcpy(this->value, value, len);
		this->value[len] = 0;
	}
	this->isNull = this->value == NULL;
}
template <> void JsonCommonValue<TJsonRawData>::InitValue(TJsonRawData value, size_t valueLen) {
	this->value = value;
	this->isNull = this->value.Data == NULL;
}
template <> void JsonCommonValue<JsonObject *>::InitValue(JsonObject *value, size_t valueLen) {
	this->value = value;
	this->isNull = this->value == NULL;
}
template <> void JsonCommonValue<JsonArrayBase *>::InitValue(JsonArrayBase *value, size_t valueLen) {
	this->value = value;
	this->isNull = this->value == NULL;
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
template <> bool JsonCommonValue<char *>::IsNull() { return isNull || (char *)value == NULL; }
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
template <> void JsonCommonValue<char *>::ResetToNull() { Set(NULL); }
template <> void JsonCommonValue<TJsonRawData>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<JsonObject *>::ResetToNull() { isNull = true; }
template <> void JsonCommonValue<JsonArrayBase *>::ResetToNull() { isNull = true; }
