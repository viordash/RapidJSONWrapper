#pragma once

#include "LibJson.h"

template <class T> bool JsonCommonValue<T>::TryParse(TJsonDocument *doc) {
	rapidjson::Value::MemberIterator member = doc->MemberBegin();
	while (member != doc->MemberEnd()) {
		auto &memberName = member->name;
		if (strcmp(Name, memberName.GetString()) == 0) break;
		++member;
	}

	if (member == doc->MemberEnd()) {
		this->Reset();
		presented = false;
		return true;
	}
	presented = true;

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

template <class T> bool JsonCommonValue<T>::Presented() { return presented; }
template <class T> bool JsonCommonValue<T>::IsNull() { return isNull; }
template <> bool JsonCommonValue<char *>::IsNull() { return isNull || Value == NULL; }