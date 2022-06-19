
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "JsonNumericField.h"

template <class T>
JsonNumericField<T>::JsonNumericField(const char *name, T value, bool optional) : JsonBaseField(name, optional) {
	this->Value = value;

	static_assert(jsonNumericSupportedTyped<T>, "The function expected a type that matches nodes type");
}

template <class T>
bool JsonNumericField<T>::ReadFromJson(RapidJsonValue value) {
	if (!HasMember(value)) {
		return optional;
	}
	rapidjson::Value *jsonValue = (rapidjson::Value *)value;
	auto &jsonVal = (*jsonValue)[Name];

	if (std::is_same<T, unsigned>::value || std::is_same<T, uint32_t>::value || std::is_same<T, uint16_t>::value || std::is_same<T, uint8_t>::value) {
		if (jsonVal.IsUint()) {
			SetValue(jsonVal.GetUint());
			return true;
		}
	} else if (std::is_same<T, int>::value || std::is_same<T, int32_t>::value || std::is_same<T, int16_t>::value || std::is_same<T, int8_t>::value) {
		if (jsonVal.IsInt()) {
			SetValue(jsonVal.GetInt());
			return true;
		}
	} else if (std::is_same<T, int64_t>::value) {
		if (jsonVal.IsInt64()) {
			SetValue(jsonVal.GetInt64());
			return true;
		}
	} else if (std::is_same<T, uint64_t>::value) {
		if (jsonVal.IsUint64()) {
			SetValue(jsonVal.GetUint64());
			return true;
		}
	} else if (std::is_same<T, double>::value) {
		if (jsonVal.IsDouble()) {
			SetValue(jsonVal.GetDouble());
			return true;
		}
	} else if (std::is_same<T, float>::value) {
		if (jsonVal.IsFloat()) {
			SetValue(jsonVal.GetFloat());
			return true;
		}
	}

	if (jsonVal.IsNull()) {
		hasValue = false;
		return true;
	}
	return false;
}

template <class T>
void JsonNumericField<T>::WriteToJson(RapidJsonDocument doc) {
	rapidjson::Value json_val;
	rapidjson::Document *jsonDoc = (rapidjson::Document *)doc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc->GetAllocator();

	if (std::is_same<T, unsigned>::value || std::is_same<T, uint32_t>::value || std::is_same<T, uint16_t>::value || std::is_same<T, uint8_t>::value) {
		json_val.SetUint(Value);
	} else if (std::is_same<T, int>::value || std::is_same<T, int32_t>::value || std::is_same<T, int16_t>::value || std::is_same<T, int8_t>::value) {
		json_val.SetInt(Value);
	} else if (std::is_same<T, int64_t>::value) {
		json_val.SetInt64(Value);
	} else if (std::is_same<T, uint64_t>::value) {
		json_val.SetUint64(Value);
	} else if (std::is_same<T, double>::value) {
		json_val.SetDouble(Value);
	} else if (std::is_same<T, float>::value) {
		json_val.SetFloat(Value);
	}

	jsonDoc->AddMember(rapidjson::StringRef(Name), json_val, allocator);
}

template <class T>
void JsonNumericField<T>::CloneFrom(JsonBaseField *otherJsonField) {
	Value = ((JsonNumericField *)otherJsonField)->Value;
}

template <class T>
bool JsonNumericField<T>::Equals(JsonBaseField *otherJsonField) {
	return JsonBaseField::Equals(otherJsonField) //
		   && Value == ((JsonNumericField *)otherJsonField)->Value;
}