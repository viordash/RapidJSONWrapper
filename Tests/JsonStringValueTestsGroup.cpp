
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Json.h"
// #include "TestsCommon.h"

#include "CppUTest/CommandLineTestRunner.h"

TEST_GROUP(JsonStringValueGroup){void setup(){} void teardown(){}};

TEST(JsonStringValueGroup, JsonField_VeryLong_Name_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable(&container, "testString0 testString1 testString2 testString3 testString4 testString0 testString1 testString2 testString3 "
										   "testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 "
										   "testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 testString4g4g4");

	CHECK_EQUAL(strlen(testable.Name), 355);
	STRCMP_CONTAINS("testString0 testString1 testString2 testString3 testString4 ", testable.Name);
}

TEST(JsonStringValueGroup, JsonStringValue_TryParse_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable(&container, "testString");

	rapidjson::Document doc;
	doc.Parse("{\"testString\":\"User1\"}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(testable.Value, "User1");

	doc.Parse("{\"testString\":null}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(testable.Value, "");
}

TEST(JsonStringValueGroup, JsonStringValue_WriteTo_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable(&container, "testString", "1234567");

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteToDoc(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();

	STRCMP_EQUAL(jsonStr, "{\"testString\":\"1234567\"}");
}

TEST(JsonStringValueGroup, JsonStringValue_TryParse_Field_Optional_Test) {
	rapidjson::Document doc;
	JsonFieldsContainer container;
	auto testableFieldMustExists = new JsonValue<char *>(&container, "testString");
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_FALSE(testableFieldMustExists->TryParse(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonValue<char *, true>(&container, "testString");
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_TRUE(testableWithOptional->TryParse(&doc));
	STRCMP_EQUAL(testableWithOptional->Value, "");
	delete testableWithOptional;
}

TEST(JsonStringValueGroup, JsonStringValue_SetValue_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable(&container, "testString");
	STRCMP_EQUAL(testable.Value, "");

	testable.Value = "0123456789";
	STRCMP_EQUAL(testable.Value, "0123456789");
}

TEST(JsonStringValueGroup, JsonStringValue_Equals_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable1(&container, "test", "testString");
	JsonValue<char *> testable01(&container, "test", "testString");

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	testable01.Value = "otherValue";
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);

	JsonValue<char *, true> optional1(&container, "test", "testString");
	JsonValue<char *, true> optional01(&container, "test", "testString");

	CHECK_TRUE(optional1 == optional01);
	CHECK_FALSE(optional1 != optional01);
	optional01.Value = "otherValue";
	CHECK_TRUE(optional1 != optional01);
	CHECK_FALSE(optional1 == optional01);
}

TEST(JsonStringValueGroup, JsonStringValue_CloneTo_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable1(&container, "test", "0123456789");

	JsonValue<char *> clone1(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);
	testable1.Value = "check the full data buffer is cloned";
	STRCMP_EQUAL(clone1.Value, "0123456789");
}

int main(int ac, char **av) {
	//
	return RUN_ALL_TESTS(ac, av);
}

// int main(const int argc, const char *argv[]) {
// 	TEST_RUN(JsonStringValueGroup, JsonField_VeryLong_Name_Test);
// 	TEST_RUN(JsonStringValueGroup, JsonStringValue_TryParse_Test);
// 	TEST_RUN(JsonStringValueGroup, JsonStringValue_WriteTo_Test);
// 	TEST_RUN(JsonStringValueGroup, JsonStringValue_TryParse_Field_Optional_Test);
// 	TEST_RUN(JsonStringValueGroup, JsonStringValue_SetValue_Test);
// 	TEST_RUN(JsonStringValueGroup, JsonStringValue_Equals_Test);
// 	TEST_RUN(JsonStringValueGroup, JsonStringValue_CloneTo_Test);

// 	printf("JsonStringValueGroup success");
// 	return EXIT_SUCCESS;
// }