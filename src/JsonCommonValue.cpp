
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
		Value = jsonVal->GetBool();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetInt();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetInt();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetInt();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetInt64();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetUint();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetUint();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetUint();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetUint();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetFloat();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value = jsonVal->GetDouble();
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value.DeleteValue();
		size_t len = jsonVal->GetStringLength();
		Value.value = new char[len + 1];
		memcpy(Value.value, (char *)jsonVal->GetString(), len);
		Value.value[len] = 0;
		Value.isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		Value = NULL;
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
		Value = rawData;
		return true;
	}
	if (jsonVal->IsNull()) {
		Value = {};
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
		Value->TryParse((TJsonDocument *)jsonVal);
		Value.isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
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
		Value->TryDocParse((TJsonDocument *)jsonVal);
		Value.isNull = false;
		return true;
	}
	if (jsonVal->IsNull()) {
		Value.isNull = true;
		return true;
	}
	return false;
}
/*


*/
template <> bool JsonCommonValue<bool>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<bool> *)other)->Value; }
template <> bool JsonCommonValue<int8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<int8_t> *)other)->Value; }
template <> bool JsonCommonValue<int16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<int16_t> *)other)->Value; }
template <> bool JsonCommonValue<int32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<int32_t> *)other)->Value; }
template <> bool JsonCommonValue<int64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<int64_t> *)other)->Value; }
template <> bool JsonCommonValue<uint8_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<uint8_t> *)other)->Value; }
template <> bool JsonCommonValue<uint16_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<uint16_t> *)other)->Value; }
template <> bool JsonCommonValue<uint32_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<uint32_t> *)other)->Value; }
template <> bool JsonCommonValue<uint64_t>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<uint64_t> *)other)->Value; }
template <> bool JsonCommonValue<float>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<float> *)other)->Value; }
template <> bool JsonCommonValue<double>::Equals(JsonValueBase *other) { return JsonValueBase::NamesCompare(Name, other->Name) && Value == ((JsonCommonValue<double> *)other)->Value; }
template <> bool JsonCommonValue<char *>::Equals(JsonValueBase *other) { //
	return JsonValueBase::NamesCompare(Name, other->Name)
		&& (Value == ((JsonCommonValue<char *> *)other)->Value
			|| (Value != NULL && ((JsonCommonValue<char *> *)other)->Value != NULL && strcmp(Value, ((JsonCommonValue<char *> *)other)->Value) == 0));
}
template <> bool JsonCommonValue<TJsonRawData>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name)														//
		&& ((TJsonRawData)Value).Data == ((TJsonRawData)(((JsonCommonValue<TJsonRawData> *)other)->Value)).Data //
		&& ((TJsonRawData)Value).Size == ((TJsonRawData)(((JsonCommonValue<TJsonRawData> *)other)->Value)).Size;
}
template <> bool JsonCommonValue<JsonObject *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)Value->Equals((JsonObject *)((JsonCommonValue<JsonObject *> *)other)->Value);
}
template <> bool JsonCommonValue<JsonArrayBase *>::Equals(JsonValueBase *other) {
	return JsonValueBase::NamesCompare(Name, other->Name) && (JsonObject *)Value->Equals((JsonArrayBase *)(((JsonCommonValue<JsonArrayBase *> *)other)->Value));
}
/*


*/
template <> void JsonCommonValue<bool>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetBool(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int8_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int16_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int32_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<int64_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetInt64(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint8_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint16_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint32_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<uint64_t>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetUint64(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<float>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetFloat(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<double>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull) {
		json_val.SetNull();
	} else {
		json_val.SetDouble(Value);
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<char *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	if (Value.isNull || Value == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)Value));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<TJsonRawData>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Value json_val;
	TJsonRawData rawData = Value;
	if (Value.isNull || rawData.Data == NULL) {
		json_val.SetNull();
	} else {
		json_val.SetString(rapidjson::StringRef((char *)rawData.Data, (rapidjson::SizeType)rawData.Size));
	}
	doc->AddMember(Name, json_val, doc->GetAllocator());
}
template <> void JsonCommonValue<JsonObject *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	if (Value.isNull || Value == NULL) {
		jObject.SetNull();
	} else {
		Value->WriteToDoc(&jObject);
	}
	doc->AddMember(Name, jObject, allocator);
}
template <> void JsonCommonValue<JsonArrayBase *>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	rapidjson::Document jArray(&allocator);
	if (Value.isNull || Value == NULL) {
		jArray.SetNull();
	} else {
		Value->WriteToDoc(&jArray);
	}
	doc->AddMember(Name, jArray, allocator);
}
/*


*/
template <> void JsonCommonValue<bool>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<bool> *)other)->Value = (bool)this->Value; }
template <> void JsonCommonValue<int8_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int8_t> *)other)->Value = (int8_t)this->Value; }
template <> void JsonCommonValue<int16_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int16_t> *)other)->Value = (int16_t)this->Value; }
template <> void JsonCommonValue<int32_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int32_t> *)other)->Value = (int32_t)this->Value; }
template <> void JsonCommonValue<int64_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<int64_t> *)other)->Value = (int64_t)this->Value; }
template <> void JsonCommonValue<uint8_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint8_t> *)other)->Value = (uint8_t)this->Value; }
template <> void JsonCommonValue<uint16_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint16_t> *)other)->Value = (uint16_t)this->Value; }
template <> void JsonCommonValue<uint32_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint32_t> *)other)->Value = (uint32_t)this->Value; }
template <> void JsonCommonValue<uint64_t>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<uint64_t> *)other)->Value = (uint64_t)this->Value; }
template <> void JsonCommonValue<float>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<float> *)other)->Value = (float)this->Value; }
template <> void JsonCommonValue<double>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<double> *)other)->Value = (double)this->Value; }
template <> void JsonCommonValue<char *>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<char *> *)other)->Value = (char *)this->Value; }
template <> void JsonCommonValue<TJsonRawData>::CloneTo(JsonValueBase *other) { ((JsonCommonValue<TJsonRawData> *)other)->Value = (TJsonRawData)this->Value; }
template <> void JsonCommonValue<JsonObject *>::CloneTo(JsonValueBase *other) {
	auto thisObject = ((JsonObject *)Value);
	auto otherObject = ((JsonObject *)((JsonCommonValue<JsonObject *> *)other)->Value);
	thisObject->CloneTo(otherObject);
}
template <> void JsonCommonValue<JsonArrayBase *>::CloneTo(JsonValueBase *other) {
	auto thisArray = ((JsonArrayBase *)Value);
	auto otherArray = ((JsonArrayBase *)((JsonCommonValue<JsonArrayBase *> *)other)->Value);
	thisArray->CloneTo(otherArray);
}

/*



*/
template <> bool JsonCommonValue<bool>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<int8_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<int16_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<int32_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<int64_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<uint8_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<uint16_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<uint32_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<uint64_t>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<float>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<double>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<char *>::IsNull() { return Value.isNull || (char *)Value == NULL; }
template <> bool JsonCommonValue<TJsonRawData>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<JsonObject *>::IsNull() { return Value.isNull; }
template <> bool JsonCommonValue<JsonArrayBase *>::IsNull() { return Value.isNull; }
/*



*/
template <> void JsonCommonValue<bool>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<int8_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<int16_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<int32_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<int64_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<uint8_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<uint16_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<uint32_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<uint64_t>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<float>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<double>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<char *>::ResetToNull() {
	Value.isNull = true;
	Value = NULL;
}
template <> void JsonCommonValue<TJsonRawData>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<JsonObject *>::ResetToNull() { Value.isNull = true; }
template <> void JsonCommonValue<JsonArrayBase *>::ResetToNull() { Value.isNull = true; }