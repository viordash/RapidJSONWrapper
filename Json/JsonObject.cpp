
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"

JsonObject::JsonObject() {
}

JsonObject::~JsonObject() {
}

JsonBaseField *JsonObject::SeachFieldByName(const char *name) {
	for (const auto &field : GetFields()) {
		if (strcmp(field->Name, name) == 0) {
			return field;
		}
	}
	return NULL;
}
