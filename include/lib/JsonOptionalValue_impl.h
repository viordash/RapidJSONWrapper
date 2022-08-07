#pragma once

#include "LibJson.h"

template <class T> bool JsonOptionalValue<T>::TryParse(TJsonDocument *doc) {
	rapidjson::Value::MemberIterator member = doc->FindMember(this->Name->s);
	if (member == doc->MemberEnd()) {
		this->Reset();
		presented = false;
		return true;
	}
	presented = true;

	rapidjson::Value &jsonVal = member->value;
	if (this->TryParseCore(&jsonVal)) { return true; }
	if (jsonVal.IsNull()) {
		this->Reset();
		return true;
	}
	return false;
}

template <class T> bool JsonOptionalValue<T>::Presented() { return presented; }