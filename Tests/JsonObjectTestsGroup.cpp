
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

class ObjectC : public JsonObject {
  public:
	const static std::vector<JsonBaseField> fields1;

	ObjectC() {
		Fields = fieldsOrg;
	};

	~ObjectC() {
		printf("~ObjectC()\n");
	}

  protected:
  private:
	const static JsonObjectFields fieldsOrg;
};

const JsonObjectFields ObjectC::fieldsOrg = {
	JsonStringField("field1", ""),			 //
	JsonStringField("field2", ""),			 //
	JsonNumericField<uint32_t>("field3", 0), //
	JsonNumericField<uint32_t>("field4", 0), //
	JsonNumericField<int>("field5", 0)		 //
};

void Test(int count) {
	ObjectC childObject;

	for (auto &field : childObject.Fields.Items) {
		std::cout << field.Name << ' ';
	}
	std::cout << count << '\n';
}

int main(const int argc, const char *argv[]) {
	for (size_t i = 0; i < 1000; i++) {
		Test(i);
	}

	ObjectC childObjectC;
	for (auto &field : childObjectC.Fields.Items) {
		std::cout << field.Name << ' ';
	}
	std::cout << '\n';

	auto fff = childObjectC.Fields.Items;
	fff.push_back(JsonStringField("field10", ""));

	ObjectC childObjectC1;
	for (auto &field : childObjectC1.Fields.Items) {
		std::cout << field.Name << ' ';
	}
	std::cout << '\n';

	return EXIT_SUCCESS;
}