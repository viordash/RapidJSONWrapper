#pragma once

#include "LibJson.h"

template <class T> bool JsonOptionalValue<T>::TryParse(TJsonDocument *doc) {
	rapidjson::Value::MemberIterator member = doc->FindMember(Name);
	if (member == doc->MemberEnd()) {
		this->Reset();
		return true;
	}

	rapidjson::Value &jsonVal = member->value;
	if (TryParseCore(&jsonVal)) { return true; }
	if (jsonVal.IsNull()) {
		this->Reset();
		return true;
	}
	return false;
}