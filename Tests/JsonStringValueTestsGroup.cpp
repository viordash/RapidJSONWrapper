
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

TEST(JsonStringValueGroup, JsonField_VeryLong_Name_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable(&container, "testString0 testString1 testString2 testString3 testString4 testString0 testString1 testString2 testString3 "
										   "testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 "
										   "testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 testString4g4g4");

	CHECK_EQUAL(strlen(testable.Name), 355);
	STRCMP_CONTAINS("testString0 testString1 testString2 testString3 testString4 ", testable.Name);
	return EXIT_SUCCESS;
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
	return EXIT_SUCCESS;
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
	return EXIT_SUCCESS;
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
	return EXIT_SUCCESS;
}

TEST(JsonStringValueGroup, JsonStringValue_SetValue_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable(&container, "testString");
	STRCMP_EQUAL(testable.Value, "");

	testable.Value = "0123456789";
	STRCMP_EQUAL(testable.Value, "0123456789");

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonStringValueGroup, JsonField_VeryLong_Name_Test);
	TEST_RUN(JsonStringValueGroup, JsonStringValue_TryParse_Test);
	TEST_RUN(JsonStringValueGroup, JsonStringValue_WriteTo_Test);
	TEST_RUN(JsonStringValueGroup, JsonStringValue_TryParse_Field_Optional_Test);
	TEST_RUN(JsonStringValueGroup, JsonStringValue_SetValue_Test);

	printf("JsonStringValueGroup success");
	return EXIT_SUCCESS;
}