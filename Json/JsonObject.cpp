
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonObject.h"

JsonObject::JsonObject() {
}

JsonObject::~JsonObject() {
}

JsonStringField *JsonObject::InsertValue(const char *name, const char *value, int size, bool optional) {
	auto field = (JsonStringField *)SeachFieldByName(name);
	if (field != NULL) {
		field->SetValue(value);
	} else {
		field = new JsonStringField(name, value, size, optional);
		fields.push_back(field);
	}
	return field;
}

JsonNumericField<uint32_t> *JsonObject::InsertValue(const char *name, uint32_t value, bool optional) {
	auto field = (JsonNumericField<uint32_t> *)SeachFieldByName(name);
	if (field != NULL) {
		field->Value = value;
	} else {
		field = new JsonNumericField<uint32_t>(name, value, optional);
		fields.push_back(field);
	}
	return field;
}

JsonBaseField *JsonObject::SeachFieldByName(const char *name) {
	for (const auto &field : fields) {
		if (strcmp(field->Name, name) == 0) {
			return field;
		}
	}
	return NULL;
}
