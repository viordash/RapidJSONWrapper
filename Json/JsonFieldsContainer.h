#pragma once

#include <vector>

class JsonField;
class JsonFieldsContainer {
  public:
	std::vector<JsonField *> Fields;

	void Add(JsonField *field) {
		Fields.push_back(field);
	}
};