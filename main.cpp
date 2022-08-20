#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

void JsonUIntField_WriteTo_Test() {
	JsonFieldsContainer container;
	JsonValue<unsigned int> testable1(&container, "test", 19);
	JsonValue<uint32_t> testable2(&container, "test", 20);
	JsonValue<uint16_t> testable3(&container, "test", 21);
	JsonValue<uint8_t> testable4(&container, "test", 22);

	{
		rapidjson::Document doc;
		doc.SetObject();
		testable1.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":19}") == 0) { printf("111\n"); }
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable2.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":20}") == 0) { printf("222\n"); }
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable3.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":21}") == 0) { printf("333\n"); }
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable4.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":22}") == 0) { printf("444\n"); }
	}
}

void JsonUIntCommonField_WriteTo_Test() {
	JsonFieldsContainer container;
	JsonCommonValue<unsigned int> testable1(&container, "test", 19);
	JsonCommonValue<uint32_t> testable2(&container, "test", 20);
	JsonCommonValue<uint16_t> testable3(&container, "test", 21);
	JsonCommonValue<uint8_t> testable4(&container, "test", 22);

	{
		rapidjson::Document doc;
		doc.SetObject();
		testable1.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":19}") == 0) { printf("111\n"); }
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable2.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":20}") == 0) { printf("222\n"); }
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable3.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":21}") == 0) { printf("333\n"); }
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable4.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		if (strcmp(buffer.GetString(), "{\"test\":22}") == 0) { printf("444\n"); }
	}
}

void JsonFloatField_Equals_Test() {
	JsonFieldsContainer container;
	JsonValue<float> testable1(&container, "test", 100.5);
	JsonValue<float> testable01(&container, "test", 100.5);

	JsonValue<double> testable2(&container, "test", 101.75);
	JsonValue<double> testable02(&container, "test", 101.75);

	if (testable1.Equals(&testable01)) { printf("111\n"); }
	if (testable1 == testable01) { printf("111\n"); }
	if (!(testable1 != testable01)) { printf("222\n"); }
	testable01.Value = testable01.Value + 1;
	if (testable1 != testable01) { printf("333\n"); }
	if (!(testable1 == testable01)) { printf("444\n"); }

	if (testable2 == testable02) { printf("555\n"); }
	if (!(testable2 != testable02)) { printf("777\n"); }
	testable02.Value = testable02.Value + 1;
	if (testable2 != testable02) { printf("888\n"); }
	if (!(testable2 == testable02)) { printf("999\n"); }
}

void JsonFloatCommonField_Equals_Test() {
	JsonFieldsContainer container;
	JsonCommonValue<float> testable1(&container, "test", 100.5);
	JsonCommonValue<float> testable01(&container, "test", 100.5);

	JsonCommonValue<double> testable2(&container, "test", 101.75);
	JsonCommonValue<double> testable02(&container, "test", 101.75);

	if (testable1.Equals(&testable01)) { printf("111\n"); }
	if (testable1 == testable01) { printf("111\n"); }
	if (!(testable1 != testable01)) { printf("222\n"); }
	testable01.Value = testable01.Value + 1;
	if (testable1 != testable01) { printf("333\n"); }
	if (!(testable1 == testable01)) { printf("444\n"); }

	if (testable2 == testable02) { printf("555\n"); }
	if (!(testable2 != testable02)) { printf("777\n"); }
	testable02.Value = testable02.Value + 1;
	if (testable2 != testable02) { printf("888\n"); }
	if (!(testable2 == testable02)) { printf("999\n"); }
}

void JsonStringValue_CloneTo_Test() {
	JsonFieldsContainer container;
	JsonValue<char *> testable1(&container, "test", (char *)"0123456789");

	JsonValue<char *> clone1(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);
	testable1.Value = (char *)"check the full data buffer is cloned";
	if (clone1.Value == (char *)"0123456789") { printf("1000\n"); }
}

void JsonStringCommonValue_CloneTo_Test() {
	JsonFieldsContainer container;
	JsonCommonValue<char *> testable1(&container, "test", (char *)"0123456789");

	JsonCommonValue<char *> clone1(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);
	testable1.Value = (char *)"check the full data buffer is cloned";
	if (clone1.Value == (char *)"0123456789") { printf("1000\n"); }
}

int main(const int argc, const char *argv[]) {
	fprintf(stdout, "json to class object\n");

	// {
	JsonFieldsContainer container;
	JsonValue<int> intObj(&container, "test", 100);
	JsonCommonValue<int> intObj1(&container, "test", 100);
	rapidjson::Document doc;
	doc.Parse("{\"test\":153000}");
	intObj.TryParse(&doc);
	intObj1.TryParse(&doc);

	JsonValue<int8_t> int8Obj(&container, "test", 100);
	JsonCommonValue<int8_t> int8Obj1(&container, "test", 100);
	rapidjson::Document doc8;
	doc8.Parse("{\"test\":153000}");
	int8Obj.TryParse(&doc8);
	int8Obj1.TryParse(&doc8);

	JsonValue<uint8_t> uint8Obj(&container, "test", 100);
	JsonCommonValue<uint8_t> uint8Obj1(&container, "test", 100);
	rapidjson::Document docu8;
	docu8.Parse("{\"test\":153000}");
	uint8Obj.TryParse(&doc8);
	uint8Obj1.TryParse(&doc8);

	JsonUIntField_WriteTo_Test();
	JsonUIntCommonField_WriteTo_Test();
	JsonFloatField_Equals_Test();
	JsonFloatCommonField_Equals_Test();
	JsonStringValue_CloneTo_Test();
	JsonStringCommonValue_CloneTo_Test();

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