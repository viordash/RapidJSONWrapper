#pragma once

#include "LibJson.h"
#include "JsonFieldsContainer.h"

typedef char TBoolArray;

class JsonObject;

class JsonArrayBase {
  public:
	virtual bool TryParse(TJsonDocument *doc) = 0;

	virtual void WriteToDoc(TJsonDocument *doc) = 0;

  protected:
};

template <class TItem> class JsonArray : public JsonArrayBase {
	typedef typename std::remove_pointer<TItem>::type TNewObjectItem;

  public:
	std::vector<TItem> Items;
	TItem operator[](int index) { return Items[index]; }

	virtual bool TryParse(TJsonDocument *doc) {
		if (!doc->IsArray()) { return false; }
		auto jArray = doc->GetArray();
		Items.reserve(jArray.Size());
		if (TryParseInternal(&jArray)) { return true; }
		Items.shrink_to_fit();
		return false;
	}

	bool TryParse(const char *jsonStr, int length = -1) {
		auto doc = BeginTryParse(jsonStr, length);
		if (doc == NULL) { return false; }
		EndTryParse(doc);
		return true;
	}

	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1) {
		if (jsonStr == NULL || length == 0) { return NULL; }

		rapidjson::Document *doc = new rapidjson::Document();
		if (length < 0) {
			doc->Parse(jsonStr);
		} else {
			doc->Parse(jsonStr, length);
		}
		if (doc->HasParseError() || !this->TryParse(doc)) {
			delete doc;
			return NULL;
		}
		return doc;
	}

	void EndTryParse(TJsonDocument *doc) { delete doc; }

	virtual void WriteToDoc(TJsonDocument *doc) {
		doc->SetArray();
		WriteToDocInternal(doc);
	}

	int WriteToString(char *outBuffer, int outBufferSize) {
		rapidjson::Document doc;
		this->WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		const char *jsonStr = buffer.GetString();
		int size = buffer.GetSize();
		if (size > outBufferSize - 1) { size = outBufferSize - 1; }
		strncpy(outBuffer, jsonStr, size);
		outBuffer[size] = 0;
		return size;
	}

	typedef void (*TOnReady)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnReady onReady) {
		rapidjson::Document doc;
		this->WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		const char *json = buffer.GetString();
		int size = buffer.GetSize();
		onReady(parent, json, size);
		return size;
	}

	virtual bool Add(TItem item) {
		if (!Validate(item)) { return false; }
		AddInternal(item);
		return true;
	}

  protected:
	virtual bool Validate(TItem item) = 0;

  private:
	bool TryParseInternal(TJsonArray *jArray) {
		if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
			for (const auto &jItem : *jArray) {
				auto newItem = new TNewObjectItem();
				if (!((JsonObject *)newItem)->TryParse((TJsonDocument *)&jItem) || !Add((TItem)newItem)) {
					delete newItem;
					return false;
				}
			}
			return true;
		}
	}

	void WriteToDocInternal(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
			for (const auto &item : Items) {
				rapidjson::Document childDoc(&allocator);
				JsonObject *jObject = (JsonObject *)item;
				jObject->WriteToDoc(&childDoc);
				doc->PushBack(childDoc, allocator);
			}
		}
	}

	void AddInternal(TItem item) { Items.push_back(item); }
};

template <> bool JsonArray<char *>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsString() || !Add((char *)jItem.GetString())) { return false; }
	}
	return true;
}
template <> bool JsonArray<TBoolArray>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsBool() || !Add((TBoolArray)jItem.GetBool())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int64_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt64() || !Add((int64_t)jItem.GetInt64())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint64_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint64() || !Add((uint64_t)jItem.GetUint64())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int32_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt() || !Add((int32_t)jItem.GetInt())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint32_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((uint32_t)jItem.GetUint())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int16_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt() || !Add((int16_t)jItem.GetInt())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint16_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((uint16_t)jItem.GetUint())) { return false; }
	}
	return true;
}
template <> bool JsonArray<int8_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsInt() || !Add((int8_t)jItem.GetInt())) { return false; }
	}
	return true;
}
template <> bool JsonArray<uint8_t>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((uint8_t)jItem.GetUint())) { return false; }
	}
	return true;
}
template <> bool JsonArray<double>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((double)jItem.GetFloat())) { return false; }
	}
	return true;
}
template <> bool JsonArray<float>::TryParseInternal(TJsonArray *jArray) {
	for (const auto &jItem : *jArray) {
		if (!jItem.IsUint() || !Add((float)jItem.GetFloat())) { return false; }
	}
	return true;
}
/*


*/
template <> void JsonArray<char *>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(rapidjson::StringRef((char *)item));
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<TBoolArray>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp((bool)item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int64_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint64_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int32_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint32_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int16_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint16_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<int8_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<uint8_t>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<double>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
template <> void JsonArray<float>::WriteToDocInternal(TJsonDocument *doc) {
	rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
	for (const auto &item : Items) {
		rapidjson::Value temp(item);
		doc->PushBack(temp, allocator);
	}
}
/*


*/
template <> void JsonArray<char *>::AddInternal(char *item) {
	auto len = strlen((char *)item);
	auto newItem = new char[len + 1];
	memcpy(newItem, (char *)item, len);
	newItem[len] = 0;
	Items.push_back(newItem);
}