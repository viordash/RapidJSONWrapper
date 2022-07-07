
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"
#include "JsonObjectField.h"

#define TryParseInternal_T(value)                                                                                                                              \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		if (!jsonValue->IsObject()) {                                                                                                                          \
			return false;                                                                                                                                      \
		}                                                                                                                                                      \
		if (jsonValue->ObjectEmpty()) {                                                                                                                        \
			return true;                                                                                                                                       \
		}                                                                                                                                                      \
		return object->TryParse((RapidJsonValues)jsonValue);                                                                                                   \
	}

template <>
bool JsonField<JsonObject *, true>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(value);
}
template <>
bool JsonField<JsonObject *, false>::TryParseInternal(RapidJsonVal value) {
	TryParseInternal_T(value);
}
/*

*/

template <>
void JsonField<JsonObject *, true>::WriteTo(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	jObject.SetObject();
	object->WriteTo(&jObject);
	jsonDoc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}
template <>
void JsonField<JsonObject *, false>::WriteTo(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	jObject.SetObject();
	object->WriteTo(&jObject);
	jsonDoc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}
