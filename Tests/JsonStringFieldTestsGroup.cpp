
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

TEST(JsonFieldTestsGroup, JsonField_VeryLong_Name_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(
		&container, "testString0 testString1 testString2 testString3 testString4 testString0 testString1 testString2 testString3 "
					"testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 "
					"testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 testString4g4g4");

	CHECK_EQUAL(strlen(testable.Name), 355);
	STRCMP_CONTAINS("testString0 testString1 testString2 testString3 testString4 ", testable.Name);
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");

	rapidjson::Document doc;
	doc.Parse("{\"testString\":\"User1\"}");
	CHECK(testable.ReadFromJson(&doc));
	STRCMP_EQUAL(testable.Value, "User1");

	doc.Parse("{\"testString\":null}");
	CHECK(testable.ReadFromJson(&doc));
	STRCMP_EQUAL(testable.Value, "");
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_WriteToJson_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");
	testable.SetValue("1234567");

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
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString", 256);

	testable.SetValue("0123456789A 0123456789B 0123456789C 0123456789D 0123456789E 0123456789F 0123456789D 0123456789E "
					  "0123456789D 012345678 0123456789D 0123456789E9E 0123456789D 0123456789E  0123456789D 0123456789E "
					  "0123456789D 0123 0123456789D 012345678 0123456789D 0123456789E9E456789E");
	STRCMP_EQUAL(testable.Value,
				 "0123456789A 0123456789B 0123456789C 0123456789D 0123456789E 0123456789F 0123456789D 0123456789E 0123456789D 012345678 0123456789D "
				 "0123456789E9E 0123456789D 0123456789E  0123456789D 0123456789E 0123456789D 0123 0123456789D 012345678 0123456789D 0123456789E");

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_Size_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");
	testable.SetValue("1234567890ABCDEF", 8);
	CHECK_EQUAL(testable.GetSize(), 8 + 1);
	STRCMP_EQUAL(testable.Value, "12345678");
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_MaxSize_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString", 10);
	testable.SetValue("1234567890ABCDEF1234567890ABCDEF");
	CHECK_EQUAL(testable.GetSize(), 10);
	STRCMP_EQUAL(testable.Value, "123456789");
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_Equals_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable1(&container, "testString");
	JsonField<char *> testable2(&container, "testString");
	testable2.SetValue("test");
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	testable1.SetValue("test");
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	JsonField<char *> testable3(&container, "testStringWrong");
	testable3.SetValue("test");
	CHECK_FALSE(testable3.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable3));
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Field_Optional_Test) {
	rapidjson::Document doc;
	JsonFieldsContainer container;
	auto testableFieldMustExists = new JsonField<char *>(&container, "testString");
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_FALSE(testableFieldMustExists->ReadFromJson(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonField<char *, true>(&container, "testString", 8192);
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_TRUE(testableWithOptional->ReadFromJson(&doc));
	STRCMP_EQUAL(testableWithOptional->Value, "");
	delete testableWithOptional;
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_SetValue_Does_Not_Realloc_Buffer_When_Length_Equals_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");
	STRCMP_EQUAL(testable.Value, "");

	testable.SetValue("0123456789");
	STRCMP_EQUAL(testable.Value, "0123456789");
	CHECK_EQUAL(testable.GetSize(), 11);
	auto buffer = testable.Value;
	testable.SetValue("2345678901");
	STRCMP_EQUAL(testable.Value, "2345678901");
	CHECK_EQUAL(testable.GetSize(), 11);
	CHECK(buffer == testable.Value);

	testable.SetValue("0123456789A");
	STRCMP_EQUAL(testable.Value, "0123456789A");
	CHECK_EQUAL(testable.GetSize(), 12);
	CHECK(buffer != testable.Value);

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonStringField_SetValue_When_Length_Incorrect_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString", 20);
	CHECK_EQUAL(testable.GetSize(), 1);

	testable.SetValue("0123456789", 10000);
	STRCMP_EQUAL(testable.Value, "0123456789");
	CHECK_EQUAL(testable.GetSize(), 20);

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonFieldTestsGroup, JsonField_VeryLong_Name_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_WriteToJson_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_And_VeryLong_Value_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_Size_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_MaxSize_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_Equals_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_ReadFromJson_Field_Optional_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_SetValue_Does_Not_Realloc_Buffer_When_Length_Equals_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonStringField_SetValue_When_Length_Incorrect_Test);

	return EXIT_SUCCESS;
}