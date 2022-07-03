#pragma once

#include <vector>

class JsonBaseField;
class JsonFieldsContainer {
  public:
	std::vector<JsonBaseField *> Fields;

	void Add(JsonBaseField *field) {
		Fields.push_back(field);
	}
};