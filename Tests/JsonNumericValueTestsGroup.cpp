
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Json.h"
#include "TestsCommon.h"

TEST(JsonNumericValueGroup, JsonUIntField_SetValue_Test) {
	JsonFieldsContainer container;
	JsonValue<unsigned int> testable1(&container, "test");
	JsonValue<uint32_t> testable2(&container, "test");
	JsonValue<uint16_t> testable3(&container, "test");
	JsonValue<uint8_t> testable4(&container, "test");
	testable1.Value = 0xFFFFFFFF;
	testable2.Value = 0xFFFFFFFF;
	testable3.Value = 0xFFFFFFFF;
	testable4.Value = 0xFFFFFFFF;

	CHECK_EQUAL(testable1.Value, 4294967295);
	CHECK_EQUAL(testable1.Value, 4294967295);
	CHECK_EQUAL(testable2.Value, 4294967295);
	CHECK_EQUAL(testable3.Value, 65535);
	CHECK_EQUAL(testable4.Value, 255);

	return EXIT_SUCCESS;
}
TEST(JsonNumericValueGroup, JsonUIntField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonValue<unsigned int> testable1(&container, "test");
	JsonValue<uint32_t> testable2(&container, "test");
	JsonValue<uint16_t> testable3(&container, "test");
	JsonValue<uint8_t> testable4(&container, "test");

	rapidjson::Document doc;
	doc.Parse("{\"test\":153000}");
	CHECK(testable1.TryParse(&doc));
	CHECK(testable2.TryParse(&doc));
	CHECK(testable3.TryParse(&doc));
	CHECK(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 153000);
	CHECK_EQUAL(testable2.Value, 153000);
	CHECK_EQUAL(testable3.Value, 21928);
	CHECK_EQUAL(testable4.Value, 168);

	doc.Parse("{\"test\":null}");
	CHECK(testable1.TryParse(&doc));
	CHECK(testable2.TryParse(&doc));
	CHECK(testable3.TryParse(&doc));
	CHECK(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 0);
	CHECK_EQUAL(testable2.Value, 0);
	CHECK_EQUAL(testable3.Value, 0);
	CHECK_EQUAL(testable4.Value, 0);
	return EXIT_SUCCESS;
}

TEST(JsonNumericValueGroup, JsonUIntField_WriteTo_Test) {
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
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable2.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable3.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable4.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
	}
	return EXIT_SUCCESS;
}

TEST(JsonNumericValueGroup, JsonIntField_SetValue_Test) {
	JsonFieldsContainer container;
	JsonValue<int> testable1(&container, "test");
	JsonValue<int32_t> testable2(&container, "test");
	JsonValue<int16_t> testable3(&container, "test");
	JsonValue<int8_t> testable4(&container, "test");
	testable1.Value = 0xFFFFFFFF;
	testable2.Value = 0xFFFFFFFF;
	testable3.Value = 0xFFFFFFFF;
	testable4.Value = 0xFFFFFFFF;

	CHECK_EQUAL(testable1.Value, -1);
	CHECK_EQUAL(testable2.Value, -1);
	CHECK_EQUAL(testable3.Value, -1);
	CHECK_EQUAL(testable4.Value, -1);
	return EXIT_SUCCESS;
}
TEST(JsonNumericValueGroup, JsonIntField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonValue<int> testable1(&container, "test");
	JsonValue<int32_t> testable2(&container, "test");
	JsonValue<int16_t> testable3(&container, "test");
	JsonValue<int8_t> testable4(&container, "test");

	rapidjson::Document doc;
	doc.Parse("{\"test\":153000}");
	CHECK(testable1.TryParse(&doc));
	CHECK(testable2.TryParse(&doc));
	CHECK(testable3.TryParse(&doc));
	CHECK(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 153000);
	CHECK_EQUAL(testable2.Value, 153000);
	CHECK_EQUAL(testable3.Value, 21928);
	CHECK_EQUAL(testable4.Value, -88);

	doc.Parse("{\"test\":null}");
	CHECK(testable1.TryParse(&doc));
	CHECK(testable2.TryParse(&doc));
	CHECK(testable3.TryParse(&doc));
	CHECK(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 0);
	CHECK_EQUAL(testable2.Value, 0);
	CHECK_EQUAL(testable3.Value, 0);
	CHECK_EQUAL(testable4.Value, 0);
	return EXIT_SUCCESS;
}

TEST(JsonNumericValueGroup, JsonIntField_WriteTo_Test) {
	JsonFieldsContainer container;
	JsonValue<int> testable1(&container, "test", 19);
	JsonValue<int32_t> testable2(&container, "test", 20);
	JsonValue<int16_t> testable3(&container, "test", 21);
	JsonValue<int8_t> testable4(&container, "test", 22);

	{
		rapidjson::Document doc;
		doc.SetObject();
		testable1.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable2.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable3.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable4.WriteToDoc(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
	}
	return EXIT_SUCCESS;
}

/*



*/

TEST(JsonNumericValueGroup, JsonBoolField_SetValue_Test) {
	JsonFieldsContainer container;
	JsonValue<bool> testable1(&container, "test");
	testable1.Value = 0xFFFFFFFF;
	CHECK_EQUAL(testable1.Value, true);
	testable1.Value = 0;
	CHECK_EQUAL(testable1.Value, false);
	testable1.Value = 1;
	CHECK_EQUAL(testable1.Value, true);
	testable1.Value = false;
	CHECK_EQUAL(testable1.Value, false);
	testable1.Value = true;
	CHECK_EQUAL(testable1.Value, true);
	return EXIT_SUCCESS;
}
TEST(JsonNumericValueGroup, JsonBoolField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonValue<bool> testable1(&container, "test");

	rapidjson::Document doc;
	doc.Parse("{\"test\":true}");
	CHECK(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, true);

	doc.Parse("{\"test\":null}");
	CHECK(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, false);
	return EXIT_SUCCESS;
}

TEST(JsonNumericValueGroup, JsonBoolField_WriteTo_Test) {
	JsonFieldsContainer container;
	JsonValue<bool> testable1(&container, "test", true);

	rapidjson::Document doc;
	doc.SetObject();
	testable1.WriteToDoc(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	STRCMP_EQUAL(buffer.GetString(), "{\"test\":true}");

	return EXIT_SUCCESS;
}

TEST(JsonNumericValueGroup, TryParse_Field_Optional_Test) {
	JsonFieldsContainer container;
	rapidjson::Document doc;
	auto testableFieldMustExists = new JsonValue<uint32_t>(&container, "testUInt0");
	doc.Parse("{\"otherField\":153}");
	CHECK_FALSE(testableFieldMustExists->TryParse(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonValue<uint32_t, true>(&container, "testUInt0");
	testableWithOptional->Value = 123;
	doc.Parse("{\"otherField\":153}");
	CHECK_TRUE(testableWithOptional->TryParse(&doc));
	CHECK_EQUAL(testableWithOptional->Value, 0);
	delete testableWithOptional;

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonNumericValueGroup, JsonUIntField_SetValue_Test);
	TEST_RUN(JsonNumericValueGroup, JsonUIntField_TryParse_Test);
	TEST_RUN(JsonNumericValueGroup, JsonUIntField_WriteTo_Test);

	TEST_RUN(JsonNumericValueGroup, JsonIntField_SetValue_Test);
	TEST_RUN(JsonNumericValueGroup, JsonIntField_TryParse_Test);
	TEST_RUN(JsonNumericValueGroup, JsonIntField_WriteTo_Test);

	TEST_RUN(JsonNumericValueGroup, JsonBoolField_SetValue_Test);
	TEST_RUN(JsonNumericValueGroup, JsonBoolField_TryParse_Test);
	TEST_RUN(JsonNumericValueGroup, JsonBoolField_WriteTo_Test);

	TEST_RUN(JsonNumericValueGroup, TryParse_Field_Optional_Test);

	printf("JsonNumericValueGroup success");
	return EXIT_SUCCESS;
}