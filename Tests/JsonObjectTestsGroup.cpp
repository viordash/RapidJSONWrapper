
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
	ObjectC() {
		fields = {
			new JsonStringField("field1", ""),			 //
			new JsonStringField("field2", ""),			 //
			new JsonNumericField<uint32_t>("field3", 0), //
			new JsonNumericField<uint32_t>("field4", 0), //
			new JsonNumericField<int>("field5", 0)		 //
		};
	};

	~ObjectC() {
		printf("~ObjectC()\n");
	}

  protected:
  private:
};

void Test(int count) {
	ObjectC childObject;

	for (auto &field : childObject.fields) {
		std::cout << field->Name << ' ';
	}
	std::cout << count << '\n';
}

int main(const int argc, const char *argv[]) {
	for (size_t i = 0; i < 1000; i++) {
		Test(i);
	}

	ObjectC childObjectC;
	for (auto &field : childObjectC.fields) {
		std::cout << field->Name << ' ';
	}
	std::cout << '\n';

	auto fff = childObjectC.fields;
	fff.push_back(new JsonStringField("field10", ""));

	ObjectC childObjectC1;
	for (auto &field : childObjectC1.fields) {
		std::cout << field->Name << ' ';
	}
	std::cout << '\n';

	return EXIT_SUCCESS;
}