
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

  private:
};

int main(const int argc, const char *argv[]) {

	ObjectC childObjectC;
	for (auto field : childObjectC.fields) {
		std::cout << field->Name << ' ';
	}
	std::cout << '\n';

	return EXIT_SUCCESS;
}