
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonField.h"

#define ReadFromJsonCore_T(type, value)                                                                                                                        \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		if (jsonValue->Is##type()) {                                                                                                                           \
			SetValue(jsonValue->Get##type());                                                                                                                  \
			return true;                                                                                                                                       \
		}                                                                                                                                                      \
		return false;                                                                                                                                          \
	}

template <>
bool JsonField<bool, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Bool, value);
}
template <>
bool JsonField<bool, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Bool, value);
}

template <>
bool JsonField<int, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int, value);
}
template <>
bool JsonField<int, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int, value);
}

template <>
bool JsonField<int8_t, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int, value);
}
template <>
bool JsonField<int8_t, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int, value);
}

template <>
bool JsonField<int16_t, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int, value);
}
template <>
bool JsonField<int16_t, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int, value);
}

template <>
bool JsonField<int64_t, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int64, value);
}
template <>
bool JsonField<int64_t, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Int64, value);
}

template <>
bool JsonField<unsigned int, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint, value);
}
template <>
bool JsonField<unsigned int, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint, value);
}

template <>
bool JsonField<uint8_t, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint, value);
}
template <>
bool JsonField<uint8_t, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint, value);
}

template <>
bool JsonField<uint16_t, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint, value);
}
template <>
bool JsonField<uint16_t, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint, value);
}

template <>
bool JsonField<uint64_t, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint64, value);
}
template <>
bool JsonField<uint64_t, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Uint64, value);
}

template <>
bool JsonField<float, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Float, value);
}
template <>
bool JsonField<float, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Float, value);
}

template <>
bool JsonField<double, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Double, value);
}
template <>
bool JsonField<double, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(Double, value);
}
/*

*/

#define WriteToJsonCore_T(type, value)                                                                                                                         \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		jsonValue->Set##type(Value);                                                                                                                           \
	}

template <>
void JsonField<bool, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Bool, value);
}
template <>
void JsonField<bool, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Bool, value);
}

template <>
void JsonField<int, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int, value);
}
template <>
void JsonField<int, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int, value);
}

template <>
void JsonField<int8_t, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int, value);
}
template <>
void JsonField<int8_t, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int, value);
}

template <>
void JsonField<int16_t, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int, value);
}
template <>
void JsonField<int16_t, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int, value);
}

template <>
void JsonField<int64_t, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int64, value);
}
template <>
void JsonField<int64_t, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Int64, value);
}

template <>
void JsonField<unsigned int, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint, value);
}
template <>
void JsonField<unsigned int, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint, value);
}

template <>
void JsonField<uint8_t, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint, value);
}
template <>
void JsonField<uint8_t, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint, value);
}

template <>
void JsonField<uint16_t, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint, value);
}
template <>
void JsonField<uint16_t, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint, value);
}

template <>
void JsonField<uint64_t, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint64, value);
}
template <>
void JsonField<uint64_t, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Uint64, value);
}

template <>
void JsonField<float, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Float, value);
}
template <>
void JsonField<float, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Float, value);
}

template <>
void JsonField<double, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Double, value);
}
template <>
void JsonField<double, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(Double, value);
}
