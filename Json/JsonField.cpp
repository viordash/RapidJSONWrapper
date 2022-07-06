
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

#define WriteToInternal(type, doc)                                                                                                                           \
	{                                                                                                                                                          \
		rapidjson::Value jsonVal;                                                                                                                              \
		rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;                                                                                             \
		rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();                                                                               \
		jsonVal.Set##type(Value);                                                                                                                              \
		jsonDoc->AddMember(rapidjson::StringRef(Name), jsonVal, allocator);                                                                                    \
	}

template <>
void JsonField<bool, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Bool, doc);
}
template <>
void JsonField<bool, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Bool, doc);
}

template <>
void JsonField<int, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int, doc);
}
template <>
void JsonField<int, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int, doc);
}

template <>
void JsonField<int8_t, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int, doc);
}
template <>
void JsonField<int8_t, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int, doc);
}

template <>
void JsonField<int16_t, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int, doc);
}
template <>
void JsonField<int16_t, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int, doc);
}

template <>
void JsonField<int64_t, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int64, doc);
}
template <>
void JsonField<int64_t, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Int64, doc);
}

template <>
void JsonField<unsigned int, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint, doc);
}
template <>
void JsonField<unsigned int, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint, doc);
}

template <>
void JsonField<uint8_t, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint, doc);
}
template <>
void JsonField<uint8_t, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint, doc);
}

template <>
void JsonField<uint16_t, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint, doc);
}
template <>
void JsonField<uint16_t, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint, doc);
}

template <>
void JsonField<uint64_t, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint64, doc);
}
template <>
void JsonField<uint64_t, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Uint64, doc);
}

template <>
void JsonField<float, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Float, doc);
}
template <>
void JsonField<float, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Float, doc);
}

template <>
void JsonField<double, true>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Double, doc);
}
template <>
void JsonField<double, false>::WriteTo(RapidJsonDocument doc) {
	WriteToInternal(Double, doc);
}
