
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

TEST(JsonFieldTestsGroup, JsonUIntField_ReadFromJson_Test) {
	JsonNumericField<uint32_t> testable("testUInt", 19);

	rapidjson::Document doc;
	doc.Parse("{\"testUInt\":153}");
	CHECK(testable.ReadFromJson(&doc));
	CHECK_EQUAL(testable.Value, 153);
	CHECK_FALSE(testable.IsNull());

	doc.Parse("{\"testUInt\":null}");
	CHECK(testable.ReadFromJson(&doc));
	CHECK_TRUE(testable.IsNull());

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonUIntField_WriteToJson_Test) {
	JsonNumericField<uint32_t> testable("testUInt", 19);

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteToJson(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();

	STRCMP_EQUAL(jsonStr, "{\"testUInt\":19}");
	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonUIntField_Size_Test) {
	JsonNumericField<uint32_t> testable("testUInt0 testUInt1", 0);
	CHECK_EQUAL(testable.GetSize(), 4);
}

TEST(JsonFieldTestsGroup, JsonUIntField_Equals_Test) {
	JsonNumericField<uint32_t> testable1("testUInt", 0);
	JsonNumericField<uint32_t> testable2("testUInt", 1);
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	testable1.SetValue(1);
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	return EXIT_SUCCESS;
}

TEST(JsonFieldTestsGroup, JsonUIntField_ReadFromJson_Field_Optional_Test) {
	rapidjson::Document doc;
	auto testableFieldMustExists = new JsonNumericField<uint32_t>("testUInt0", 0);
	doc.Parse("{\"otherField\":153}");
	CHECK_FALSE(testableFieldMustExists->ReadFromJson(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonNumericField<uint32_t>("testUInt0", 0, true);
	doc.Parse("{\"otherField\":153}");
	CHECK_TRUE(testableWithOptional->ReadFromJson(&doc));
	CHECK_TRUE(testableWithOptional->IsNull());
	delete testableWithOptional;

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_ReadFromJson_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_WriteToJson_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_Size_Test);
	TEST_RUN(JsonFieldTestsGroup, JsonUIntField_ReadFromJson_Field_Optional_Test);

	return EXIT_SUCCESS;
}