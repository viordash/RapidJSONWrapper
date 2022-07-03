
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonField.h"

template <>
bool JsonField<bool>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsBool()) {
		SetValue(jsonValue->GetBool());
		return true;
	}
	return false;
}

template <>
bool JsonField<int>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsInt()) {
		SetValue(jsonValue->GetInt());
		return true;
	}
	return false;
}

template <>
bool JsonField<int8_t>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsInt()) {
		SetValue(jsonValue->GetInt());
		return true;
	}
	return false;
}

template <>
bool JsonField<int16_t>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsInt()) {
		SetValue(jsonValue->GetInt());
		return true;
	}
	return false;
}

template <>
bool JsonField<int64_t>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsInt64()) {
		SetValue(jsonValue->GetInt64());
		return true;
	}
	return false;
}

template <>
bool JsonField<unsigned int>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsUint()) {
		SetValue(jsonValue->GetUint());
		return true;
	}
	return false;
}

template <>
bool JsonField<uint8_t>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsUint()) {
		SetValue(jsonValue->GetUint());
		return true;
	}
	return false;
}

template <>
bool JsonField<uint16_t>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsUint()) {
		SetValue(jsonValue->GetUint());
		return true;
	}
	return false;
}

template <>
bool JsonField<uint64_t>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsUint64()) {
		SetValue(jsonValue->GetUint64());
		return true;
	}
	return false;
}

template <>
bool JsonField<float>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsFloat()) {
		SetValue(jsonValue->GetFloat());
		return true;
	}
	return false;
}

template <>
bool JsonField<double>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsDouble()) {
		SetValue(jsonValue->GetDouble());
		return true;
	}
	return false;
}
/*

*/
template <>
void JsonField<bool>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetBool(Value);
}

template <>
void JsonField<int>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetInt(Value);
}

template <>
void JsonField<int8_t>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetInt(Value);
}

template <>
void JsonField<int16_t>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetInt(Value);
}

template <>
void JsonField<int64_t>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetInt64(Value);
}

template <>
void JsonField<unsigned int>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetUint(Value);
}

template <>
void JsonField<uint8_t>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetUint(Value);
}

template <>
void JsonField<uint16_t>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetUint(Value);
}

template <>
void JsonField<uint64_t>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetUint64(Value);
}

template <>
void JsonField<float>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetFloat(Value);
}

template <>
void JsonField<double>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetDouble(Value);
}
