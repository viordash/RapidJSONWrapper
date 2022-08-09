#pragma once

#include "LibJson.h"

template <class T> bool JsonNullableValue<T>::TryParse(TJsonDocument *doc) {
	rapidjson::Value::MemberIterator member = doc->FindMember(this->Name);
	if (member == doc->MemberEnd()) {
		this->Reset();
		return false;
	}

	rapidjson::Value &jsonVal = member->value;
	if (this->TryParseCore(&jsonVal)) {
		isNull = false;
		return true;
	}
	if (jsonVal.IsNull()) {
		this->Reset();
		isNull = true;
		return true;
	}
	return false;
}

template <class T> bool JsonNullableValue<T>::IsNull() { return isNull; }