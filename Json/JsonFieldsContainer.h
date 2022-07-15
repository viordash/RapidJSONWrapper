#pragma once

#include <vector>

class JsonValueBase;
class JsonFieldsContainer {
  public:
	std::vector<JsonValueBase *> Fields;

	void Add(JsonValueBase *field) {
		Fields.push_back(field);
	}
};