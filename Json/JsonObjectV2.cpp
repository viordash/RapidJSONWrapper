

#include "JsonObjectV2.h"

template <>
bool JsonObjectV2<bool, true>::TryParseCore(TJsonValue *value) {
	return value->IsBool() && SetValue(value->GetBool());
}
template <>
bool JsonObjectV2<bool, false>::TryParseCore(TJsonValue *value) {
	return value->IsBool() && SetValue(value->GetBool());
}

template <>
bool JsonObjectV2<int8_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsInt() && SetValue(value->GetInt());
}
template <>
bool JsonObjectV2<int8_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsInt() && SetValue(value->GetInt());
}

template <>
bool JsonObjectV2<int16_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsInt() && SetValue(value->GetInt());
}
template <>
bool JsonObjectV2<int16_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsInt() && SetValue(value->GetInt());
}

template <>
bool JsonObjectV2<int32_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsInt() && SetValue(value->GetInt());
}
template <>
bool JsonObjectV2<int32_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsInt() && SetValue(value->GetInt());
}

template <>
bool JsonObjectV2<int64_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsInt64() && SetValue(value->GetInt64());
}
template <>
bool JsonObjectV2<int64_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsInt64() && SetValue(value->GetInt64());
}

template <>
bool JsonObjectV2<uint8_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsUint() && SetValue(value->GetUint());
}
template <>
bool JsonObjectV2<uint8_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsUint() && SetValue(value->GetUint());
}

template <>
bool JsonObjectV2<uint16_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsUint() && SetValue(value->GetUint());
}
template <>
bool JsonObjectV2<uint16_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsUint() && SetValue(value->GetUint());
}

template <>
bool JsonObjectV2<uint32_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsUint() && SetValue(value->GetUint());
}
template <>
bool JsonObjectV2<uint32_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsUint() && SetValue(value->GetUint());
}

template <>
bool JsonObjectV2<uint64_t, true>::TryParseCore(TJsonValue *value) {
	return value->IsUint64() && SetValue(value->GetUint64());
}
template <>
bool JsonObjectV2<uint64_t, false>::TryParseCore(TJsonValue *value) {
	return value->IsUint64() && SetValue(value->GetUint64());
}

/*


*/
template <>
void JsonObjectV2<bool, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (bool)Value, allocator);
}
template <>
void JsonObjectV2<bool, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (bool)Value, allocator);
}

template <>
void JsonObjectV2<int8_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int8_t)Value, allocator);
}
template <>
void JsonObjectV2<int8_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int8_t)Value, allocator);
}

template <>
void JsonObjectV2<int16_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int16_t)Value, allocator);
}
template <>
void JsonObjectV2<int16_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int16_t)Value, allocator);
}

template <>
void JsonObjectV2<int32_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int32_t)Value, allocator);
}
template <>
void JsonObjectV2<int32_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int32_t)Value, allocator);
}

template <>
void JsonObjectV2<int64_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int64_t)Value, allocator);
}
template <>
void JsonObjectV2<int64_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (int64_t)Value, allocator);
}

template <>
void JsonObjectV2<uint8_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint8_t)Value, allocator);
}
template <>
void JsonObjectV2<uint8_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint8_t)Value, allocator);
}

template <>
void JsonObjectV2<uint16_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint16_t)Value, allocator);
}
template <>
void JsonObjectV2<uint16_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint16_t)Value, allocator);
}

template <>
void JsonObjectV2<uint32_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint32_t)Value, allocator);
}
template <>
void JsonObjectV2<uint32_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint32_t)Value, allocator);
}

template <>
void JsonObjectV2<uint64_t, true>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint64_t)Value, allocator);
}
template <>
void JsonObjectV2<uint64_t, false>::WriteToDoc(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	doc->AddMember(rapidjson::StringRef(Name), (uint64_t)Value, allocator);
}