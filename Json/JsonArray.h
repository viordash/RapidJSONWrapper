#pragma once

#include "LibJson.h"
#include "JsonFieldsContainer.h"

class JsonObject;

class JsonArrayBase {
  public:
	virtual bool TryParse(TJsonDocument *doc) = 0;

	virtual void WriteToDoc(TJsonDocument *doc) = 0;

  protected:
};

template <class TItem> class JsonArray : public JsonArrayBase {
  public:
	std::vector<TItem *> Items;
	TItem *operator[](int index) { return Items[index]; }

	virtual bool TryParse(TJsonDocument *doc) {
		if (!doc->IsArray()) { return false; }

		for (const auto &item : doc->GetArray()) {
			if (!TryParseItem((TJsonDocument *)&item)) { return false; }
		}
		return true;
	}

	bool TryParse(const char *jsonStr, int length = -1)  {
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
		rapidjson::Document::AllocatorType &allocator = doc->GetAllocator();
		doc->SetArray();
		for (const auto item : Items) {
			rapidjson::Document aChildDoc(&allocator);
			item->WriteToDoc(&aChildDoc);
			doc->PushBack(aChildDoc, allocator);
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

	virtual bool Add(TItem *item) {
		if (item == NULL) { return false; }
		if (!Validate(item)) { return false; }
		Items.push_back(item);
		return true;
	}

  protected:
	virtual bool TryParseItem(TJsonDocument *doc) {
		auto newItem = new TItem();
		if (!newItem->TryParse(doc) || !Add(newItem)) {
			delete newItem;
			return false;
		}
		return true;
	}
	virtual bool Validate(TItem *item) = 0;
};
