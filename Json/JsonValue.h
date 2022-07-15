#pragma once

#include "LibJson.h"

typedef rapidjson::Document TJsonDocument;
typedef rapidjson::Value TJsonValue;

template <class T, bool optional = false> //
class JsonValue {
	class ValueWrapper {
	  public:
		ValueWrapper(JsonValue *owner, const T value) {
			this->owner = owner;
			owner->InitValue(value);
		}

		~ValueWrapper() { owner->DeleteValue(); }

		T operator=(const T right) {
			owner->SetValue(right);
			return owner->value;
		}

		operator T() const { return owner->value; }

	  private:
		JsonValue *owner;
	};

  public:
	const char *Name;
	ValueWrapper Value;

	JsonValue(const char *name, const T value) : Name(name), Value(this, value) {}

	JsonValue(const char *name) : JsonValue(name, T()) {}

	TJsonDocument *BeginTryParse(const char *jsonStr, int length = -1) {
		if (jsonStr == NULL || length == 0) { return NULL; }

		auto doc = new rapidjson::Document();
		if (length < 0) {
			doc->Parse(jsonStr);
		} else {
			doc->Parse(jsonStr, length);
		}
		if (doc->HasParseError() || !TryParse(doc)) {
			delete doc;
			return NULL;
		}
		return doc;
	}

	void EndTryParse(TJsonDocument *doc) { delete doc; }

	bool TryParse(const char *jsonStr, int length = -1) {
		auto doc = BeginTryParse(jsonStr, length);
		if (doc == NULL) { return false; }
		EndTryParse(doc);
		return true;
	}

	bool TryParse(TJsonDocument *doc) {
		rapidjson::Value::MemberIterator member = doc->FindMember(Name);
		if (member == doc->MemberEnd()) {
			this->Reset();
			return optional;
		}

		rapidjson::Value &jsonVal = member->value;
		if (TryParseCore(&jsonVal)) { return true; }
		if (jsonVal.IsNull()) {
			this->Reset();
			return true;
		}
		return false;
	}

	void WriteToDoc(TJsonDocument *doc);

	int WriteToString(char *outBuffer, int outBufferSize) {
		rapidjson::Document doc;
		WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		const char *jsonStr = buffer.GetString();
		int size = buffer.GetSize();
		if (size > outBufferSize - 1) { size = outBufferSize - 1; }
		memcpy(outBuffer, jsonStr, size);
		outBuffer[size] = 0;
		return size;
	}

	typedef void (*TOnCompleted)(void *parent, const char *json, int size);
	int DirectWriteTo(void *parent, TOnCompleted onCompleted) {
		rapidjson::Document doc;
		WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);

		const char *json = buffer.GetString();
		int size = buffer.GetSize();
		onCompleted(parent, json, size);
		return size;
	}

	void Reset() { Value = T(); }

  protected:
  private:
	T value;

	void InitValue(const T value);
	bool SetValue(const T value);

	void DeleteValue();

	bool TryParseCore(TJsonValue *value);
};
