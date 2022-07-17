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

		if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
			return TryParseJsonObject(doc);
		} else if (std::is_same<TItem, char *>::value) {
			return TryParseString(doc);
		} else if (std::is_same<TItem, TBoolArray>::value) {
			return TryParseBool(doc);
		} else if (std::is_same<TItem, int64_t>::value) {
			return TryParseInt64(doc);
		} else if (std::is_same<TItem, uint64_t>::value) {
			return TryParseUint64(doc);
		} else if (std::is_signed<TItem>::value) {
			return TryParseInt(doc);
		} else if (std::is_unsigned<TItem>::value) {
			return TryParseUint(doc);
		} else {
			return false;
		}
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

		if (std::is_base_of<JsonObject, TNewObjectItem>::value) {
			WriteJsonObjectToDoc(doc);
		} else if (std::is_same<TItem, char *>::value) {
			WriteJsonStringToDoc(doc);
		} else if (std::is_same<TItem, TBoolArray>::value) {
			WriteJsonBoolToDoc(doc);
		} else if (std::is_same<TItem, int64_t>::value) {
			WriteJsonInt64ToDoc(doc);
		} else if (std::is_same<TItem, uint64_t>::value) {
			WriteJsonUint64ToDoc(doc);
		} else if (std::is_signed<TItem>::value) {
			WriteJsonIntToDoc(doc);
		} else if (std::is_unsigned<TItem>::value) {
			WriteJsonUintToDoc(doc);
		}
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

		if (std::is_same<TItem, char *>::value) {
			auto len = strlen((char *)item);
			auto newItem = new char[len + 1];
			memcpy(newItem, (char *)item, len);
			newItem[len] = 0;
			Items.push_back((TItem)newItem);
		} else {
			Items.push_back(item);
		}

		return true;
	}

  protected:
	virtual bool Validate(TItem item) = 0;

  private:
	bool TryParseJsonObject(TJsonDocument *doc) {
		for (const auto &jItem : doc->GetArray()) {
			auto newItem = new TNewObjectItem();
			if (!((JsonObject *)newItem)->TryParse((TJsonDocument *)&jItem) || !Add((TItem)newItem)) {
				delete newItem;
				return false;
			}
		}
		return true;
	}

	bool TryParseString(TJsonDocument *doc) {
		for (const auto &jItem : doc->GetArray()) {
			if (!jItem.IsString() || !Add((TItem)jItem.GetString())) { return false; }
		}
		return true;
	}

	bool TryParseInt(TJsonDocument *doc) {
		for (const auto &jItem : doc->GetArray()) {
			if (!jItem.IsInt() || !Add((TItem)jItem.GetInt())) { return false; }
		}
		return true;
	}

	bool TryParseUint(TJsonDocument *doc) {
		for (const auto &jItem : doc->GetArray()) {
			if (!jItem.IsUint() || !Add((TItem)jItem.GetUint())) { return false; }
		}
		return true;
	}

	bool TryParseInt64(TJsonDocument *doc) {
		for (const auto &jItem : doc->GetArray()) {
			if (!jItem.IsInt64() || !Add((TItem)jItem.GetInt64())) { return false; }
		}
		return true;
	}

	bool TryParseUint64(TJsonDocument *doc) {
		for (const auto &jItem : doc->GetArray()) {
			if (!jItem.IsUint64() || !Add((TItem)jItem.GetUint64())) { return false; }
		}
		return true;
	}

	bool TryParseBool(TJsonDocument *doc) {
		for (const auto &jItem : doc->GetArray()) {
			if (!jItem.IsBool() || !Add((TItem)jItem.GetBool())) { return false; }
		}
		return true;
	}

	void WriteJsonObjectToDoc(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		for (const auto &item : Items) {
			rapidjson::Document childDoc(&allocator);
			JsonObject *jObject = (JsonObject *)item;
			jObject->WriteToDoc(&childDoc);
			doc->PushBack(childDoc, allocator);
		}
	}
	void WriteJsonStringToDoc(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		for (const auto &item : Items) {
			rapidjson::Value temp;
			temp.SetString(rapidjson::StringRef((char *)item));
			doc->PushBack(temp, allocator);
		}
	}
	void WriteJsonIntToDoc(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		for (const auto &item : Items) {
			rapidjson::Value temp;
			temp.SetInt((signed int)item);
			doc->PushBack(temp, allocator);
		}
	}
	void WriteJsonUintToDoc(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		for (const auto &item : Items) {
			rapidjson::Value temp;
			temp.SetUint((unsigned int)item);
			doc->PushBack(temp, allocator);
		}
	}
	void WriteJsonInt64ToDoc(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		for (const auto &item : Items) {
			rapidjson::Value temp;
			temp.SetInt64((int64_t)item);
			doc->PushBack(temp, allocator);
		}
	}
	void WriteJsonUint64ToDoc(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		for (const auto &item : Items) {
			rapidjson::Value temp;
			temp.SetUint64((uint64_t)item);
			doc->PushBack(temp, allocator);
		}
	}
	void WriteJsonBoolToDoc(TJsonDocument *doc) {
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		for (const auto &item : Items) {
			rapidjson::Value temp;
			temp.SetBool(item);
			doc->PushBack(temp, allocator);
		}
	}
};
