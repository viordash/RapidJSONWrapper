
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
	const TFields &GetFields() const override {
		return fields;
	}

  protected:
  private:
	static const TFields fields;
};

const JsonObject::TFields ObjectC ::fields({
	new JsonStringField("field1", ""),			 //
	new JsonStringField("field2", ""),			 //
	new JsonNumericField<uint32_t>("field3", 0), //
	new JsonNumericField<uint32_t>("field4", 0), //
	new JsonNumericField<int>("field5", 0)		 //
});

int main(const int argc, const char *argv[]) {

	ObjectC childObjectC;
	for (auto field : childObjectC.GetFields()) {
		std::cout << field->Name << ' ';
	}
	std::cout << '\n';

	auto fff = childObjectC.GetFields();
	fff.push_back(new JsonStringField("field10", ""));

	return EXIT_SUCCESS;
}