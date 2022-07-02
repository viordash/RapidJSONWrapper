
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"

JsonObject::JsonObject() {
	printf("ctor JsonObject()\n");
}

JsonObject::~JsonObject() {
	printf("~JsonObject()\n");
}

JsonField *JsonObject::SeachFieldByName(const char *name) {
	for (const auto &field : Fields) {
		if (strcmp(field->Name, name) == 0) {
			return field;
		}
	}
	return NULL;
}