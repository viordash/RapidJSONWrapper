
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonArray.h"
#include "JsonArrayField.h"

#define TryParseInternal_T(value)                                                                                                                              \
	{                                                                                                                                                          \
		rapidjson::Value *jsonValue = (rapidjson::Value *)value;                                                                                               \
		if (!jsonValue->IsArray()) {                                                                                                                           \
			return false;                                                                                                                                      \
		}                                                                                                                                                      \
		if (jsonValue->Size() == 0) {                                                                                                                          \
			return true;                                                                                                                                       \
		}                                                                                                                                                      \
		return array->TryParse((RapidJsonValues)jsonValue);                                                                                                    \
	}

template <>
bool JsonField<JsonBaseArray *, true>::TryParseInternal(RapidJsonValues value) {
	TryParseInternal_T(value);
}
template <>
bool JsonField<JsonBaseArray *, false>::TryParseInternal(RapidJsonValues value) {
	TryParseInternal_T(value);
}
/*

*/

template <>
void JsonField<JsonBaseArray *, true>::WriteToDoc(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	array->WriteToDoc(&jObject);
	jsonDoc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}
template <>
void JsonField<JsonBaseArray *, false>::WriteToDoc(RapidJsonDocument doc) {
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();
	rapidjson::Document jObject(&allocator);
	array->WriteToDoc(&jObject);
	jsonDoc->AddMember(rapidjson::StringRef(Name), jObject, allocator);
}
