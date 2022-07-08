
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonStringField.h"

#define TryParseInternal_T(value)                                                                                                                              \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		if (!jsonValue->IsString()) {                                                                                                                          \
			return false;                                                                                                                                      \
		}                                                                                                                                                      \
		SetCore(jsonValue->GetString(), jsonValue->GetStringLength());                                                                                    \
		return true;                                                                                                                                           \
	}

template <>
bool JsonField<char *, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(value);
}
template <>
bool JsonField<char *, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(value);
}
/*

*/

template <>
void JsonField<char *, true>::WriteTo(RapidJsonDocument doc) {
	rapidjson::Value jsonVal;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	jsonVal.SetString(value, GetSize() - 1);
	jsonDoc->AddMember(rapidjson::StringRef(Name), jsonVal, allocator);
}
template <>
void JsonField<char *, false>::WriteTo(RapidJsonDocument doc) {
	rapidjson::Value jsonVal;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	jsonVal.SetString(value, GetSize() - 1);
	jsonDoc->AddMember(rapidjson::StringRef(Name), jsonVal, allocator);
}

template <bool optional>
void JsonField<char *, optional>::SetCore(const char *value, size_t len) {
	if (value != NULL) {
		if (len == 0) {
			len = strlen(value);
		}
	} else {
		len = 0;
	}
	if (len == size - 1) {
		if (value != NULL) {
			memcpy(this->value, value, len);
		}
		this->value[len] = 0;
		return;
	}
	if (this->value != NULL) {
		char *t = this->value;
		this->value = NULL;
		delete[] t;
	}
	size = len + 1;
	this->value = new char[size];
	if (value != NULL) {
		memcpy(this->value, value, len);
	}
	this->value[len] = 0;
}
