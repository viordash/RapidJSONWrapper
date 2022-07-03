
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonStringField.h"

bool JsonField<char *>::ReadFromJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	if (jsonValue->IsString()) {
		SetValue((char *)jsonValue->GetString(), jsonValue->GetStringLength());
		return true;
	}
	return false;
}

void JsonField<char *>::WriteToJsonCore(RapidJsonVal value) {
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	jsonValue->SetString(Value, GetSize() - 1);
}

void JsonField<char *>::SetValue(char *value, size_t len) {
	if (value != NULL) {
		if (len == 0) {
			len = strlen(value);
		}
	} else {
		len = 0;
	}
	if (len >= maxSize) {
		len = maxSize - 1;
	}

	if (len == size - 1) {
		if (value != NULL) {
			memcpy(Value, value, len);
		}
		Value[len] = 0;
		return;
	}

	if (Value != NULL) {
		char *t = Value;
		Value = NULL;
		delete[] t;
	}

	size = len + 1;
	Value = new char[size];
	if (value != NULL) {
		memcpy(Value, value, len);
	}
	Value[len] = 0;
}