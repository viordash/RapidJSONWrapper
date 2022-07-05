
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

TEST(JsonFieldTestsGroup, JsonUIntField_SetValue_Test) {
	JsonFieldsContainer container;
	JsonField<unsigned int> testable1(&container, "test");
	JsonField<uint32_t> testable2(&container, "test");
	JsonField<uint16_t> testable3(&container, "test");
	JsonField<uint8_t> testable4(&container, "test");
	testable1.SetValue(0xFFFFFFFF);
	testable2.SetValue(0xFFFFFFFF);
	testable3.SetValue(0xFFFFFFFF);
	testable4.SetValue(0xFFFFFFFF);

	CHECK_EQUAL(testable1.Value, 4294967295);
	CHECK_EQUAL(testable2.Value, 4294967295);
	CHECK_EQUAL(testable3.Value, 65535);
	CHECK_EQUAL(testable4.Value, 255);
	return EXIT_SUCCESS;
}
TEST(JsonFieldTestsGroup, JsonUIntField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonField<unsigned int> testable1(&container, "test");
	JsonField<uint32_t> testable2(&container, "test");
	JsonField<uint16_t> testable3(&container, "test");
	JsonField<uint8_t> testable4(&container, "test");

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

TEST(JsonFieldTestsGroup, JsonUIntField_WriteTo_Test) {
	JsonFieldsContainer container;
	JsonField<unsigned int> testable1(&container, "test");
	JsonField<uint32_t> testable2(&container, "test");
	JsonField<uint16_t> testable3(&container, "test");
	JsonField<uint8_t> testable4(&container, "test");
	testable1.SetValue(19);
	testable2.SetValue(20);
	testable3.SetValue(21);
	testable4.SetValue(22);

	{
		rapidjson::Document doc;
		doc.SetObject();
		testable1.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable2.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable3.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable4.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
	}
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonUIntField_Size_Test) {
	JsonFieldsContainer container;
	JsonField<unsigned int> testable1(&container, "testUInt0");
	CHECK_EQUAL(testable1.GetSize(), 4);
	JsonField<uint32_t> testable2(&container, "testUInt0");
	CHECK_EQUAL(testable2.GetSize(), 4);
	JsonField<uint16_t> testable3(&container, "testUInt0");
	CHECK_EQUAL(testable3.GetSize(), 2);
	JsonField<uint8_t> testable4(&container, "testUInt0");
	CHECK_EQUAL(testable4.GetSize(), 1);
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonUIntField_Equals_Test) {
	JsonFieldsContainer container;
	JsonField<uint32_t> testable1(&container, "test");
	JsonField<uint32_t> testable2(&container, "test");
	testable2.SetValue(1);
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	testable1.SetValue(1);
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	JsonField<unsigned int> testable3(&container, "test");
	CHECK_FALSE(testable1.Equals(&testable3));
	testable3.SetValue(1);
	CHECK_TRUE(testable1.Equals(&testable3));

	JsonField<uint16_t> testable4(&container, "test");
	CHECK_FALSE(testable1.Equals(&testable4));
	testable4.SetValue(1);
	CHECK_FALSE(testable1.Equals(&testable4));
	CHECK_FALSE(testable4.Equals(&testable1));

	JsonField<uint8_t> testable5(&container, "test");
	CHECK_FALSE(testable1.Equals(&testable5));
	testable5.SetValue(1);
	CHECK_FALSE(testable1.Equals(&testable5));

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonIntField_SetValue_Test) {
	JsonFieldsContainer container;
	JsonField<int> testable1(&container, "test");
	JsonField<int32_t> testable2(&container, "test");
	JsonField<int16_t> testable3(&container, "test");
	JsonField<int8_t> testable4(&container, "test");
	testable1.SetValue(0xFFFFFFFF);
	testable2.SetValue(0xFFFFFFFF);
	testable3.SetValue(0xFFFFFFFF);
	testable4.SetValue(0xFFFFFFFF);

	CHECK_EQUAL(testable1.Value, -1);
	CHECK_EQUAL(testable2.Value, -1);
	CHECK_EQUAL(testable3.Value, -1);
	CHECK_EQUAL(testable4.Value, -1);
	return EXIT_SUCCESS;
}
TEST(JsonFieldTestsGroup, JsonIntField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonField<int> testable1(&container, "test");
	JsonField<int32_t> testable2(&container, "test");
	JsonField<int16_t> testable3(&container, "test");
	JsonField<int8_t> testable4(&container, "test");

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

TEST(JsonFieldTestsGroup, JsonIntField_WriteTo_Test) {
	JsonFieldsContainer container;
	JsonField<int> testable1(&container, "test");
	JsonField<int32_t> testable2(&container, "test");
	JsonField<int16_t> testable3(&container, "test");
	JsonField<int8_t> testable4(&container, "test");
	testable1.SetValue(19);
	testable2.SetValue(20);
	testable3.SetValue(21);
	testable4.SetValue(22);

	{
		rapidjson::Document doc;
		doc.SetObject();
		testable1.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":19}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable2.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":20}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable3.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":21}");
	}
	{
		rapidjson::Document doc;
		doc.SetObject();
		testable4.WriteTo(&doc);
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		doc.Accept(writer);
		STRCMP_EQUAL(buffer.GetString(), "{\"test\":22}");
	}
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonIntField_Size_Test) {
	JsonFieldsContainer container;
	JsonField<int> testable1(&container, "testUInt0");
	CHECK_EQUAL(testable1.GetSize(), 4);
	JsonField<int32_t> testable2(&container, "testUInt0");
	CHECK_EQUAL(testable2.GetSize(), 4);
	JsonField<int16_t> testable3(&container, "testUInt0");
	CHECK_EQUAL(testable3.GetSize(), 2);
	JsonField<int8_t> testable4(&container, "testUInt0");
	CHECK_EQUAL(testable4.GetSize(), 1);
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonIntField_Equals_Test) {
	JsonFieldsContainer container;
	JsonField<int32_t> testable1(&container, "test");
	JsonField<int32_t> testable2(&container, "test");
	testable2.SetValue(1);
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	testable1.SetValue(1);
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	JsonField<unsigned int> testable3(&container, "test");
	CHECK_FALSE(testable1.Equals(&testable3));
	testable3.SetValue(1);
	CHECK_TRUE(testable1.Equals(&testable3));

	JsonField<uint16_t> testable4(&container, "test");
	CHECK_FALSE(testable1.Equals(&testable4));
	testable4.SetValue(1);
	CHECK_FALSE(testable1.Equals(&testable4));

	JsonField<uint8_t> testable5(&container, "test");
	CHECK_FALSE(testable1.Equals(&testable5));
	testable5.SetValue(1);
	CHECK_FALSE(testable1.Equals(&testable5));

	return EXIT_SUCCESS;
}

/*



*/

TEST(JsonFieldTestsGroup, JsonBoolField_SetValue_Test) {
	JsonFieldsContainer container;
	JsonField<bool> testable1(&container, "test");
	testable1.SetValue(0xFFFFFFFF);
	CHECK_EQUAL(testable1.Value, true);
	testable1.SetValue(0);
	CHECK_EQUAL(testable1.Value, false);
	testable1.SetValue(1);
	CHECK_EQUAL(testable1.Value, true);
	testable1.SetValue(false);
	CHECK_EQUAL(testable1.Value, false);
	testable1.SetValue(true);
	CHECK_EQUAL(testable1.Value, true);
	return EXIT_SUCCESS;
}
TEST(JsonFieldTestsGroup, JsonBoolField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonField<bool> testable1(&container, "test");

	rapidjson::Document doc;
	doc.Parse("{\"test\":true}");
	CHECK(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, true);

	doc.Parse("{\"test\":null}");
	CHECK(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, false);
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonBoolField_WriteTo_Test) {
	JsonFieldsContainer container;
	JsonField<bool> testable1(&container, "test");
	testable1.SetValue(true);

	rapidjson::Document doc;
	doc.SetObject();
	testable1.WriteTo(&doc);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	STRCMP_EQUAL(buffer.GetString(), "{\"test\":true}");

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonBoolField_Size_Test) {
	JsonFieldsContainer container;
	JsonField<bool> testable1(&container, "testUInt0");
	CHECK_EQUAL(testable1.GetSize(), 1);
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonBoolField_Equals_Test) {
	JsonFieldsContainer container;
	JsonField<bool> testable1(&container, "test");
	JsonField<bool> testable2(&container, "test");
	testable2.SetValue(true);
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	testable1.SetValue(true);
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, TryParse_Field_Optional_Test) {
	JsonFieldsContainer container;
	rapidjson::Document doc;
	auto testableFieldMustExists = new JsonField<uint32_t>(&container, "testUInt0");
	doc.Parse("{\"otherField\":153}");
	CHECK_FALSE(testableFieldMustExists->TryParse(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonField<uint32_t, true>(&container, "testUInt0");
	testableWithOptional->SetValue(123);
	doc.Parse("{\"otherField\":153}");
	CHECK_TRUE(testableWithOptional->TryParse(&doc));
	CHECK_EQUAL(testableWithOptional->Value, 0);
	delete testableWithOptional;

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_SetValue_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_TryParse_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_WriteTo_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_Size_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_Equals_Test);

	TEST_RUN(JsonFieldTestsGroup, JsonIntField_SetValue_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonIntField_TryParse_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonIntField_WriteTo_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonIntField_Size_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonIntField_Equals_Test);

	TEST_RUN(JsonFieldTestsGroup, JsonBoolField_SetValue_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonBoolField_TryParse_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonBoolField_WriteTo_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonBoolField_Size_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonBoolField_Equals_Test);

	TEST_RUN(JsonFieldTestsGroup, TryParse_Field_Optional_Test);

	return EXIT_SUCCESS;
}