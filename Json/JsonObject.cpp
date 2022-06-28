
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"

JsonObject::JsonObject() {
	printf("ctor JsonObject()\n");
}

JsonObject::~JsonObject() {
	printf("~JsonObject()\n");
	for (const auto &field : fields) {
		delete field;
	}
}

JsonBaseField *JsonObject::SeachFieldByName(const char *name) {
	for (const auto &field : fields) {
		if (strcmp(field->Name, name) == 0) {
			return field;
		}
	}
	return NULL;
}