
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

TEST(JsonStringFieldGroup, JsonField_VeryLong_Name_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(
		&container, "testString0 testString1 testString2 testString3 testString4 testString0 testString1 testString2 testString3 "
					"testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 "
					"testStrintestString0 testString1 testString2 testString3 testString4testString0 testString1 testString2 testString3 testString4g4g4");

	CHECK_EQUAL(strlen(testable.Name), 355);
	STRCMP_CONTAINS("testString0 testString1 testString2 testString3 testString4 ", testable.Name);
	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");

	rapidjson::Document doc;
	doc.Parse("{\"testString\":\"User1\"}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(testable.Value, "User1");

	doc.Parse("{\"testString\":null}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(testable.Value, "");
	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_WriteTo_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString", "1234567");

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteTo(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();

	STRCMP_EQUAL(jsonStr, "{\"testString\":\"1234567\"}");
	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_Size_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");
	testable.Value.Set("1234567890ABCDEF", 8);
	CHECK_EQUAL(testable.GetSize(), 8 + 1);
	STRCMP_EQUAL(testable.Value, "12345678");

	JsonField<char *> testableSizeInCtor(&container, "testString", "1234567890ABCDEF", 10);
	CHECK_EQUAL(testableSizeInCtor.GetSize(), 10 + 1);
	STRCMP_EQUAL(testableSizeInCtor.Value, "1234567890");

	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_Equals_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable1(&container, "testString");
	JsonField<char *> testable2(&container, "testString", "test");
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	testable1.Value = "test";
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	JsonField<char *> testable3(&container, "testStringWrong");
	testable3.Value = "test";
	CHECK_FALSE(testable3.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable3));
	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_TryParse_Field_Optional_Test) {
	rapidjson::Document doc;
	JsonFieldsContainer container;
	auto testableFieldMustExists = new JsonField<char *>(&container, "testString");
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_FALSE(testableFieldMustExists->TryParse(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonField<char *, true>(&container, "testString");
	doc.Parse("{\"otherField\":\"User1\"}");
	CHECK_TRUE(testableWithOptional->TryParse(&doc));
	STRCMP_EQUAL(testableWithOptional->Value, "");
	delete testableWithOptional;
	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_SetValue_Does_Not_Realloc_Buffer_When_Length_Equals_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");
	STRCMP_EQUAL(testable.Value, "");

	testable.Value = "0123456789";
	STRCMP_EQUAL(testable.Value, "0123456789");
	CHECK_EQUAL(testable.GetSize(), 11);
	auto buffer = (char *)testable.Value;
	testable.Value = "2345678901";
	STRCMP_EQUAL(testable.Value, "2345678901");
	CHECK_EQUAL(testable.GetSize(), 11);
	CHECK(buffer == testable.Value);

	testable.Value = "0123456789A";
	STRCMP_EQUAL(testable.Value, "0123456789A");
	CHECK_EQUAL(testable.GetSize(), 12);
	CHECK(buffer != testable.Value);

	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_SetValue_With_Too_Larger_Size_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable(&container, "testString");
	CHECK_EQUAL(testable.GetSize(), 1);

	testable.Value.Set("0123456789", 10000);
	STRCMP_EQUAL(testable.Value, "0123456789");
	CHECK_EQUAL(testable.GetSize(), 10001);

	return EXIT_SUCCESS;
}

TEST(JsonStringFieldGroup, JsonStringField_CloneFrom_Test) {
	JsonFieldsContainer container;
	JsonField<char *> testable1(&container, "testString");
	JsonField<char *> testable2(&container, "testString", "test");
	testable1.CloneFrom(&testable2);
	STRCMP_EQUAL(testable1.Value, "test");
	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonStringFieldGroup, JsonField_VeryLong_Name_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_TryParse_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_WriteTo_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_Size_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_Equals_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_TryParse_Field_Optional_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_SetValue_Does_Not_Realloc_Buffer_When_Length_Equals_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_SetValue_With_Too_Larger_Size_Test);
	TEST_RUN(JsonStringFieldGroup, JsonStringField_CloneFrom_Test);

	printf("JsonStringFieldGroup success");
	return EXIT_SUCCESS;
}