
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

TEST(JsonFieldTestsGroup, JsonField_Equals_Test) {
	JsonStringField testable1("testString", "test");
	JsonStringField testable2("testString", "test");

	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	testable1.Name = "restString";

	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonField_VeryLong_Name_Test) {
	JsonStringField testable(
		"testString0 testString1 testString2 testString3 testString4 testString0 testString1 testString2 testString3 "
		"testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 "
		"testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 testString4g4g4",
		"");

	CHECK_EQUAL(strlen(testable.Name), 355);
	STRCMP_CONTAINS("testString0 testString1 testString2 testString3 testString4 ", testable.Name);
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Test) {
	JsonStringField testable("testString", "1234567");

	rapidjson::Document doc;
	doc.Parse("{\"testString\":\"User1\"}");
	CHECK(testable.ReadFromJson(&doc));
	STRCMP_EQUAL(testable.Value, "User1");
	CHECK_FALSE(testable.IsNull());

	doc.Parse("{\"testString\":null}");
	CHECK(testable.ReadFromJson(&doc));
	CHECK_TRUE(testable.IsNull());
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_WriteToJson_Test) {
	JsonStringField testable("testString", "1234567");

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteToJson(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();

	STRCMP_EQUAL(jsonStr, "{\"testString\":\"1234567\"}");
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_And_VeryLong_Value_Test) {
	JsonStringField testable("testString", "0123456789A 0123456789B 0123456789C 0123456789D 0123456789E 0123456789F 0123456789D 0123456789E "
										   "0123456789D 012345678 0123456789D 0123456789E9E 0123456789D 0123456789E  0123456789D 0123456789E "
										   "0123456789D 0123 0123456789D 012345678 0123456789D 0123456789E9E456789E");
	STRCMP_EQUAL(testable.Value,
				 "0123456789A 0123456789B 0123456789C 0123456789D 0123456789E 0123456789F 0123456789D 0123456789E 0123456789D 012345678 0123456789D "
				 "0123456789E9E 0123456789D 0123456789E  0123456789D 0123456789E 0123456789D 0123 0123456789D 012345678 0123456789D 0123456789E");

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_Size_Test) {
	JsonStringField testable("testString", "1234567890ABCDEF", 8);
	CHECK_EQUAL(testable.GetSize(), 8);
	STRCMP_EQUAL(testable.Value, "1234567");
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_Equals_Test) {
	JsonStringField testable1("testString", NULL);
	JsonStringField testable2("testString", "test");
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	testable1.SetValue("test");
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	JsonStringField testable3("testStringWrong", "test");
	CHECK_FALSE(testable3.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable3));
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Field_Optional_Test) {
	rapidjson::Document doc;
	auto testableFieldMustExists = new JsonStringField("testString", "1234567", 256);
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_FALSE(testableFieldMustExists->ReadFromJson(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonStringField("testString", "1234567", 256, true);
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_TRUE(testableWithOptional->ReadFromJson(&doc));
	CHECK_TRUE(testableWithOptional->IsNull());
	delete testableWithOptional;
	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonFieldTestsGroup, JsonField_Equals_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonField_VeryLong_Name_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_WriteToJson_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_And_VeryLong_Value_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_Size_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_Equals_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Field_Optional_Test);

	return EXIT_SUCCESS;
}