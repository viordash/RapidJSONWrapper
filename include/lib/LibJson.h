#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <vector>

typedef rapidjson::Document TJsonDocument;
typedef rapidjson::Value::Array TJsonArray;
typedef rapidjson::Value TJsonValue;

class JsonArrayBase {
  public:
	virtual bool TryParse(TJsonDocument *doc) = 0;
	virtual void WriteToDoc(TJsonDocument *doc) = 0;
	virtual bool Equals(JsonArrayBase *other) = 0;
	virtual void CloneTo(JsonArrayBase *other) = 0;
};

class JsonValueBase;

class JsonFieldsContainer {
  public:
	std::vector<const char *> Names;
	std::vector<JsonValueBase *> Fields;
	void Add(const char *name, JsonValueBase *field) {
		Names.push_back(name);
		Fields.push_back(field);
	}
	JsonValueBase *GetField(const char *name);
};

class JsonValueBase {
  public:
	JsonValueBase(JsonValueBase &&) = delete;
	JsonValueBase(const JsonValueBase &) = delete;

	JsonValueBase(JsonFieldsContainer *container, const char *name) { container->Add(name, this); }
	virtual ~JsonValueBase(){};

	virtual bool TryParse(const char *name, TJsonDocument *doc) = 0;
	virtual void WriteToDoc(const char *name, TJsonDocument *doc) = 0;
	virtual bool Equals(JsonValueBase *other) = 0;
	virtual void CloneTo(JsonValueBase *other) = 0;

  protected:
};
