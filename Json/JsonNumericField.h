#pragma once

#include "JsonBaseField.h"

template <typename T>
constexpr bool jsonNumericSupportedTyped = std::is_same<T, int>::value			 //
										   || std::is_same<T, int64_t>::value	 //
										   || std::is_same<T, int32_t>::value	 //
										   || std::is_same<T, int16_t>::value	 //
										   || std::is_same<T, unsigned>::value //
										   || std::is_same<T, uint64_t>::value	 //
										   || std::is_same<T, uint32_t>::value	 //
										   || std::is_same<T, uint16_t>::value	 //
										   || std::is_same<T, double>::value	 //
										   || std::is_same<T, float>::value;

template <class T>
class JsonNumericField : public JsonBaseField {
  public:
	JsonNumericField(const char *name, T value, bool optional = false);
	T Value;

	int GetSize() {
		return sizeof(Value);
	}

	bool ReadFromJson(RapidJsonValue value);
	void WriteToJson(RapidJsonDocument doc);
	void CloneFrom(JsonBaseField *otherJsonField);
	void SetValue(T value) {
		Value = value;
	}
	bool Equals(JsonBaseField *otherJsonField);
};