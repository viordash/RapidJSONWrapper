#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>

typedef rapidjson::Document TJsonDocument;
typedef rapidjson::Value::Array TJsonArray;
typedef rapidjson::Value TJsonValue;
typedef rapidjson::GenericStringRef<char> TJsonValueName;

class JsonArrayBase {
  public:
	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(JsonArrayBase *other) = 0;
	virtual void CloneTo(JsonArrayBase *other) = 0;
};

class JsonValueBase;

class JsonNamesContainer {
  public:
	std::vector<const char *> Names;
};

class JsonValuesContainer {
  public:
	std::vector<JsonValueBase *> Values;
};

class JsonFieldsContainer : public JsonNamesContainer, public JsonValuesContainer {
  public:
	void Add(const char *name, JsonValueBase *value) {
		Names.push_back(name);
		Values.push_back(value);
	}

  protected:
	JsonValueBase *GetField(const char *name) {
		for (size_t i = 0; i < Names.size(); i++) {
			if (strcmp(Names[i], name) == 0) { return Values[i]; }
		}
		return NULL;
	}
};

class JsonValueBase {
  public:
	virtual ~JsonValueBase(){};

	virtual bool TryParse(TJsonValue *value) = 0;
	virtual void WriteToDoc(TJsonDocument *doc, TJsonValueName *name) = 0;
	virtual void Reset() = 0;
	virtual bool Equals(JsonValueBase *other) = 0;
	virtual void CloneTo(JsonValueBase *other) = 0;

	virtual bool TryNotPresented() = 0;

  protected:
};
