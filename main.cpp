#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Json.h"

int main(const int argc, const char *argv[]) {
	fprintf(stdout, "json to class object\n");

	JsonObjectV2<int, false> intObj("test", 100);

	auto res = intObj.TryParse("{\"test\":19}");
	fprintf(stdout, "intObj.TryParse res:%d\n", res);

	rapidjson::Document doc;
	doc.SetObject();
	intObj.WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	const char *jsonStr = buffer.GetString();




	// JsonStringField<(const char *)"testName", false, 256> testable1("test");

	// JsonStringField testableString("testName", "test1");
	// JsonNumericField<uint32_t> testableUint("testName", 100);

	// std::cout << testableString.Name << " " << testableString.Value << std::endl;
	// std::cout << testableUint.Name << " " << testableUint.Value << std::endl;
	return EXIT_SUCCESS;
}