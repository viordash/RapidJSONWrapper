
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

TJsonValue *JsonValueBase::GetMember(TJsonDocument *doc, const char *name) {
	rapidjson::Value::MemberIterator member = doc->MemberBegin();
	while (member != doc->MemberEnd()) {
		auto &memberName = member->name;
		if (strcmp(name, memberName.GetString()) == 0) return &member->value;
		++member;
	}
	return NULL;
}


bool JsonValueBase::NamesCompare(const char *name1, const char *name2) { return name1 == name2 || strcmp(name1, name2) == 0; };