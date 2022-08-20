
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

template <> void ValueProvider<bool>::DeleteValue() {}
template <> void ValueProvider<int8_t>::DeleteValue() {}
template <> void ValueProvider<int16_t>::DeleteValue() {}
template <> void ValueProvider<int32_t>::DeleteValue() {}
template <> void ValueProvider<int64_t>::DeleteValue() {}
template <> void ValueProvider<uint8_t>::DeleteValue() {}
template <> void ValueProvider<uint16_t>::DeleteValue() {}
template <> void ValueProvider<uint32_t>::DeleteValue() {}
template <> void ValueProvider<uint64_t>::DeleteValue() {}
template <> void ValueProvider<float>::DeleteValue() {}
template <> void ValueProvider<double>::DeleteValue() {}
template <> void ValueProvider<char *>::DeleteValue() { delete[] this->value; }
template <> void ValueProvider<TJsonRawData>::DeleteValue() {}
template <> void ValueProvider<JsonObject *>::DeleteValue() {}
template <> void ValueProvider<JsonArrayBase *>::DeleteValue() {}
/*


*/
template <> void ValueProvider<bool>::InitValue(bool value) { this->value = value; }
template <> void ValueProvider<int8_t>::InitValue(int8_t value) { this->value = value; }
template <> void ValueProvider<int16_t>::InitValue(int16_t value) { this->value = value; }
template <> void ValueProvider<int32_t>::InitValue(int32_t value) { this->value = value; }
template <> void ValueProvider<int64_t>::InitValue(int64_t value) { this->value = value; }
template <> void ValueProvider<uint8_t>::InitValue(uint8_t value) { this->value = value; }
template <> void ValueProvider<uint16_t>::InitValue(uint16_t value) { this->value = value; }
template <> void ValueProvider<uint32_t>::InitValue(uint32_t value) { this->value = value; }
template <> void ValueProvider<uint64_t>::InitValue(uint64_t value) { this->value = value; }
template <> void ValueProvider<float>::InitValue(float value) { this->value = value; }
template <> void ValueProvider<double>::InitValue(double value) { this->value = value; }
template <> void ValueProvider<char *>::InitValue(char *value) {
	if (value == NULL) {
		this->value = NULL;
	} else {
		size_t len = strlen(value);
		this->value = new char[len + 1];
		memcpy(this->value, value, len);
		this->value[len] = 0;
	}
}
template <> void ValueProvider<TJsonRawData>::InitValue(TJsonRawData value) { this->value = value; }
template <> void ValueProvider<JsonObject *>::InitValue(JsonObject *value) { this->value = value; }
template <> void ValueProvider<JsonArrayBase *>::InitValue(JsonArrayBase *value) { this->value = value; }
/*


*/
template <> void ValueProvider<bool>::SetValue(bool value) { this->value = value; }
template <> void ValueProvider<int8_t>::SetValue(int8_t value) { this->value = value; }
template <> void ValueProvider<int16_t>::SetValue(int16_t value) { this->value = value; }
template <> void ValueProvider<int32_t>::SetValue(int32_t value) { this->value = value; }
template <> void ValueProvider<int64_t>::SetValue(int64_t value) { this->value = value; }
template <> void ValueProvider<uint8_t>::SetValue(uint8_t value) { this->value = value; }
template <> void ValueProvider<uint16_t>::SetValue(uint16_t value) { this->value = value; }
template <> void ValueProvider<uint32_t>::SetValue(uint32_t value) { this->value = value; }
template <> void ValueProvider<uint64_t>::SetValue(uint64_t value) { this->value = value; }
template <> void ValueProvider<float>::SetValue(float value) { this->value = value; }
template <> void ValueProvider<double>::SetValue(double value) { this->value = value; }
template <> void ValueProvider<char *>::SetValue(char *value) {
	DeleteValue();
	InitValue(value);
}
template <> void ValueProvider<TJsonRawData>::SetValue(TJsonRawData value) { this->value = value; }
template <> void ValueProvider<JsonObject *>::SetValue(JsonObject *value) { this->value = value; }
template <> void ValueProvider<JsonArrayBase *>::SetValue(JsonArrayBase *value) { this->value = value; }