
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonStringField.h"

#define ReadFromJsonCore_T(value)                                                                                                                              \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		if (jsonValue->IsString()) {                                                                                                                           \
			SetValue(jsonValue->GetString(), jsonValue->GetStringLength());                                                                                    \
			return true;                                                                                                                                       \
		}                                                                                                                                                      \
		return false;                                                                                                                                          \
	}

template <>
bool JsonField<char *, true>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(value);
}
template <>
bool JsonField<char *, false>::ReadFromJsonCore(RapidJsonVal value) {
	ReadFromJsonCore_T(value);
}
/*

*/

#define WriteToJsonCore_T(value)                                                                                                                               \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		jsonValue->SetString(Value, GetSize() - 1);                                                                                                            \
	}

template <>
void JsonField<char *, true>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(value);
}
template <>
void JsonField<char *, false>::WriteToJsonCore(RapidJsonVal value) {
	WriteToJsonCore_T(value);
}

#define SetValue_T(value, len)                                                                                                                                 \
	if (value != NULL) {                                                                                                                                       \
		if (len == 0) {                                                                                                                                        \
			len = strlen(value);                                                                                                                               \
		}                                                                                                                                                      \
	} else {                                                                                                                                                   \
		len = 0;                                                                                                                                               \
	}                                                                                                                                                          \
	if (len >= maxSize) {                                                                                                                                      \
		len = maxSize - 1;                                                                                                                                     \
	}                                                                                                                                                          \
	if (len == size - 1) {                                                                                                                                     \
		if (value != NULL) {                                                                                                                                   \
			memcpy(Value, value, len);                                                                                                                         \
		}                                                                                                                                                      \
		Value[len] = 0;                                                                                                                                        \
		return;                                                                                                                                                \
	}                                                                                                                                                          \
	if (Value != NULL) {                                                                                                                                       \
		char *t = Value;                                                                                                                                       \
		Value = NULL;                                                                                                                                          \
		delete[] t;                                                                                                                                            \
	}                                                                                                                                                          \
	size = len + 1;                                                                                                                                            \
	Value = new char[size];                                                                                                                                    \
	if (value != NULL) {                                                                                                                                       \
		memcpy(Value, value, len);                                                                                                                             \
	}                                                                                                                                                          \
	Value[len] = 0;

template <>
void JsonField<char *, true>::SetValue(const char *value, size_t len) {
	SetValue_T(value, len);
}
template <>
void JsonField<char *, false>::SetValue(const char *value, size_t len) {
	SetValue_T(value, len);
}