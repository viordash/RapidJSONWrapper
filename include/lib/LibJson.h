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

class JsonFieldsContainer;

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

class JsonValuesContainer {
  public:
	std::vector<JsonValueBase *> Values;
};

class JsonFieldsContainer : public JsonValuesContainer {
  public:
	std::vector<TJsonValueName *> *Names;
	JsonFieldsContainer() {
		cloned = false;
		Names = new std::vector<TJsonValueName *>();
	}

	JsonFieldsContainer(JsonFieldsContainer *container) {
		cloned = true;
		Names = container->Names;
	}

	virtual ~JsonFieldsContainer() {
		if (!cloned) {
			for (const auto &name : *Names) { //
				delete name;
			}
			delete Names;
		}
	};

	void Add(const char *name, size_t nameLen, JsonValueBase *value) {
		bool nameExist = false;
		for (size_t i = 0; i < Names->size(); i++) {
			const char *n = *((*Names)[i]);
			if (n == name || strcmp(n, name) == 0) { //
				nameExist = true;
				break;
			}
		}
		if (!nameExist) { Names->push_back(new TJsonValueName(name, nameLen)); }
		Values.push_back(value);
	}

  protected:
	JsonValueBase *GetField(TJsonValueName *name) {
		for (size_t i = 0; i < Names->size(); i++) {
			const char *n = *((*Names)[i]);
			if (n == *name || strcmp(n, *name) == 0) { return Values[i]; }
		}
		return NULL;
	}

	bool cloned;
};
