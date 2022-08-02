#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

int main(const int argc, const char *argv[]) {
	fprintf(stdout, "json to class object\n");

	// {
	// 	JsonFieldsContainer container;
	// 	JsonValue<int, false> intObj(&container, "test", 100);

	// 	auto res = intObj.TryParse("{\"test\":19}");
	// 	printf("intObj.TryParse res:%d, val:%d\n", res, (int)intObj.Value);

	// 	rapidjson::Document doc;
	// 	doc.SetObject();
	// 	intObj.WriteToDoc(&doc);
	// 	rapidjson::StringBuffer buffer;
	// 	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	// 	doc.Accept(writer);
	// 	const char *jsonStr = buffer.GetString();
	// }

	// {
	// 	JsonFieldsContainer container;
	// 	JsonValue<char *, false> strObj(&container, "testStr", "hello json");
	// 	auto res = strObj.TryParse("{\"testStr\":\"0123456 abcdef\"}");
	// 	printf("strObj.TryParse res:%d, val:%s\n", res, (char *)strObj.Value);

	// 	rapidjson::Document doc;
	// 	doc.SetObject();
	// 	strObj.WriteToDoc(&doc);
	// 	rapidjson::StringBuffer buffer;
	// 	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	// 	doc.Accept(writer);
	// 	const char *jsonStr = buffer.GetString();
	// }

	// JsonStringField<(const char *)"testName", false, 256> testable1("test");

	// JsonStringField testableString("testName", "test1");
	// JsonNumericField<uint32_t> testableUint("testName", 100);

	// std::cout << testableString.Name << " " << testableString.Value << std::endl;
	// std::cout << testableUint.Name << " " << testableUint.Value << std::endl;
	return EXIT_SUCCESS;
}