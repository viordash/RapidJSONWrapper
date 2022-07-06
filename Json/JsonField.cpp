
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonField.h"

#define TryParseInternal_T(type, value)                                                                                                                        \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		if (!jsonValue->Is##type()) {                                                                                                                          \
			return false;                                                                                                                                      \
		}                                                                                                                                                      \
		SetValue(jsonValue->Get##type());                                                                                                                      \
		return true;                                                                                                                                           \
	}

template <>
bool JsonField<bool, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Bool, value);
}
template <>
bool JsonField<bool, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Bool, value);
}

template <>
bool JsonField<int, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int, value);
}
template <>
bool JsonField<int, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int, value);
}

template <>
bool JsonField<int8_t, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int, value);
}
template <>
bool JsonField<int8_t, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int, value);
}

template <>
bool JsonField<int16_t, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int, value);
}
template <>
bool JsonField<int16_t, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int, value);
}

template <>
bool JsonField<int64_t, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int64, value);
}
template <>
bool JsonField<int64_t, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Int64, value);
}

template <>
bool JsonField<unsigned int, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint, value);
}
template <>
bool JsonField<unsigned int, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint, value);
}

template <>
bool JsonField<uint8_t, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint, value);
}
template <>
bool JsonField<uint8_t, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint, value);
}

template <>
bool JsonField<uint16_t, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint, value);
}
template <>
bool JsonField<uint16_t, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint, value);
}

template <>
bool JsonField<uint64_t, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint64, value);
}
template <>
bool JsonField<uint64_t, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Uint64, value);
}

template <>
bool JsonField<float, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Float, value);
}
template <>
bool JsonField<float, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Float, value);
}

template <>
bool JsonField<double, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Double, value);
}
template <>
bool JsonField<double, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(Double, value);
}
/*

*/

#define WriteToInternal_T(type, value)                                                                                                                         \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		jsonValue->Set##type(Value);                                                                                                                           \
	}

template <>
void JsonField<bool, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Bool, value);
}
template <>
void JsonField<bool, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Bool, value);
}

template <>
void JsonField<int, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int, value);
}
template <>
void JsonField<int, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int, value);
}

template <>
void JsonField<int8_t, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int, value);
}
template <>
void JsonField<int8_t, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int, value);
}

template <>
void JsonField<int16_t, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int, value);
}
template <>
void JsonField<int16_t, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int, value);
}

template <>
void JsonField<int64_t, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int64, value);
}
template <>
void JsonField<int64_t, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Int64, value);
}

template <>
void JsonField<unsigned int, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint, value);
}
template <>
void JsonField<unsigned int, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint, value);
}

template <>
void JsonField<uint8_t, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint, value);
}
template <>
void JsonField<uint8_t, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint, value);
}

template <>
void JsonField<uint16_t, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint, value);
}
template <>
void JsonField<uint16_t, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint, value);
}

template <>
void JsonField<uint64_t, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint64, value);
}
template <>
void JsonField<uint64_t, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Uint64, value);
}

template <>
void JsonField<float, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Float, value);
}
template <>
void JsonField<float, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Float, value);
}

template <>
void JsonField<double, true>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Double, value);
}
template <>
void JsonField<double, false>::WriteToInternal(RapidJsonVal value) {
	WriteToInternal_T(Double, value);
}
