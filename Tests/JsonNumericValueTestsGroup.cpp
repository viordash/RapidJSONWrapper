
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JsonWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(JsonNumericValueGroup){void setup(){} void teardown(){}};

TEST(JsonNumericValueGroup, JsonField_Equals_By_Name_Test) {
	JsonFieldsContainer container;
	JsonValue<unsigned int> testable1(&container, "test", 100);
	JsonValue<unsigned int> testable01(&container, "test", 100);

	CHECK_TRUE(testable1 == testable01);
	testable01.Value = testable01.Value + 1;
	CHECK_FALSE(testable1 == testable01);
	testable1.Value = testable1.Value + 1;
	CHECK_TRUE(testable1 == testable01);
	testable1.Name = "other";
	CHECK_FALSE(testable1 == testable01);
}

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
}

TEST(JsonNumericValueGroup, JsonUIntField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonValue<unsigned int> testable1(&container, "test");
	JsonValue<uint32_t> testable2(&container, "test");
	JsonValue<uint16_t> testable3(&container, "test");
	JsonValue<uint8_t> testable4(&container, "test");

	rapidjson::Document doc;
	doc.Parse("{\"test\":153000}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 153000);
	CHECK_EQUAL(testable2.Value, 153000);
	CHECK_EQUAL(testable3.Value, 21928);
	CHECK_EQUAL(testable4.Value, 168);

	doc.Parse("{\"testOther\":42}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));

	doc.Parse("{\"test\":null}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));
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
}

TEST(JsonNumericValueGroup, JsonUIntField_Equals_Test) {
	JsonFieldsContainer container;
	JsonValue<unsigned int> testable1(&container, "test", 100);
	JsonValue<unsigned int> testable01(&container, "test", 100);

	JsonValue<uint32_t> testable2(&container, "test", 101);
	JsonValue<uint32_t> testable02(&container, "test", 101);

	JsonValue<uint16_t> testable3(&container, "test", 102);
	JsonValue<uint16_t> testable03(&container, "test", 102);

	JsonValue<uint8_t> testable4(&container, "test", 103);
	JsonValue<uint8_t> testable04(&container, "test", 103);

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	testable01.Value = testable01.Value + 1;
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);

	CHECK_TRUE(testable2 == testable02);
	CHECK_FALSE(testable2 != testable02);
	testable02.Value = testable02.Value + 1;
	CHECK_TRUE(testable2 != testable02);
	CHECK_FALSE(testable2 == testable02);

	CHECK_TRUE(testable3 == testable03);
	CHECK_FALSE(testable3 != testable03);
	testable03.Value = testable03.Value + 1;
	CHECK_TRUE(testable3 != testable03);
	CHECK_FALSE(testable3 == testable03);

	CHECK_TRUE(testable4 == testable04);
	CHECK_FALSE(testable4 != testable04);
	testable04.Value = testable04.Value + 1;
	CHECK_TRUE(testable4 != testable04);
	CHECK_FALSE(testable4 == testable04);
}

TEST(JsonNumericValueGroup, JsonUIntField_CloneTo_Test) {
	JsonFieldsContainer container;
	JsonValue<unsigned int> testable1(&container, "test", 100);
	JsonValue<uint32_t> testable2(&container, "test", 101);
	JsonValue<uint16_t> testable3(&container, "test", 102);
	JsonValue<uint8_t> testable4(&container, "test", 103);

	JsonValue<unsigned int> clone1(&container, "test");
	JsonValue<uint32_t> clone2(&container, "test");
	JsonValue<uint16_t> clone3(&container, "test");
	JsonValue<uint8_t> clone4(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);
	testable2.CloneTo((JsonValueBase *)&clone2);
	testable3.CloneTo((JsonValueBase *)&clone3);
	testable4.CloneTo((JsonValueBase *)&clone4);

	CHECK_EQUAL(clone1.Value, 100);
	CHECK_EQUAL(clone2.Value, 101);
	CHECK_EQUAL(clone3.Value, 102);
	CHECK_EQUAL(clone4.Value, 103);
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

	doc.Parse("{\"testOther\":42}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));

	doc.Parse("{\"test\":null}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));
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
}

TEST(JsonNumericValueGroup, JsonIntField_Equals_Test) {
	JsonFieldsContainer container;
	JsonValue<int> testable1(&container, "test", 100);
	JsonValue<int> testable01(&container, "test", 100);

	JsonValue<int32_t> testable2(&container, "test", 101);
	JsonValue<int32_t> testable02(&container, "test", 101);

	JsonValue<int16_t> testable3(&container, "test", 102);
	JsonValue<int16_t> testable03(&container, "test", 102);

	JsonValue<int8_t> testable4(&container, "test", 103);
	JsonValue<int8_t> testable04(&container, "test", 103);

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	testable01.Value = testable01.Value + 1;
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);

	CHECK_TRUE(testable2 == testable02);
	CHECK_FALSE(testable2 != testable02);
	testable02.Value = testable02.Value + 1;
	CHECK_TRUE(testable2 != testable02);
	CHECK_FALSE(testable2 == testable02);

	CHECK_TRUE(testable3 == testable03);
	CHECK_FALSE(testable3 != testable03);
	testable03.Value = testable03.Value + 1;
	CHECK_TRUE(testable3 != testable03);
	CHECK_FALSE(testable3 == testable03);

	CHECK_TRUE(testable4 == testable04);
	CHECK_FALSE(testable4 != testable04);
	testable04.Value = testable04.Value + 1;
	CHECK_TRUE(testable4 != testable04);
	CHECK_FALSE(testable4 == testable04);
}

TEST(JsonNumericValueGroup, JsonIntField_CloneTo_Test) {
	JsonFieldsContainer container;
	JsonValue<int> testable1(&container, "test", 100);
	JsonValue<int32_t> testable2(&container, "test", 101);
	JsonValue<int16_t> testable3(&container, "test", 102);
	JsonValue<int8_t> testable4(&container, "test", 103);

	JsonValue<int> clone1(&container, "test");
	JsonValue<int32_t> clone2(&container, "test");
	JsonValue<int16_t> clone3(&container, "test");
	JsonValue<int8_t> clone4(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);
	testable2.CloneTo((JsonValueBase *)&clone2);
	testable3.CloneTo((JsonValueBase *)&clone3);
	testable4.CloneTo((JsonValueBase *)&clone4);

	CHECK_EQUAL(clone1.Value, 100);
	CHECK_EQUAL(clone2.Value, 101);
	CHECK_EQUAL(clone3.Value, 102);
	CHECK_EQUAL(clone4.Value, 103);
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
}

TEST(JsonNumericValueGroup, JsonBoolField_TryParse_Test) {
	JsonFieldsContainer container;
	JsonValue<bool> testable1(&container, "test");

	rapidjson::Document doc;
	doc.Parse("{\"test\":true}");
	CHECK(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, true);

	doc.Parse("{\"test\":null}");
	CHECK_FALSE(testable1.TryParse(&doc));
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
}

TEST(JsonNumericValueGroup, JsonBoolField_Equals_Test) {
	JsonFieldsContainer container;
	JsonValue<bool> testable1(&container, "test", true);
	JsonValue<bool> testable01(&container, "test", true);

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	testable01.Value = !testable01.Value;
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
}

TEST(JsonNumericValueGroup, JsonBoolField_CloneTo_Test) {
	JsonFieldsContainer container;
	JsonValue<bool> testable1(&container, "test", true);
	JsonValue<bool> clone1(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);

	CHECK_EQUAL(clone1.Value, true);
}
/*


*/

TEST(JsonNumericValueGroup, JsonUIntField_Optional_TryParse_Test) {
	JsonFieldsContainer container;
	JsonOptionalValue<unsigned int> testable1(&container, "test", 100);
	JsonOptionalValue<uint32_t> testable2(&container, "test", 101);
	JsonOptionalValue<uint16_t> testable3(&container, "test", 102);
	JsonOptionalValue<uint8_t> testable4(&container, "test", 103);

	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable2.Presented());
	CHECK_FALSE(testable3.Presented());
	CHECK_FALSE(testable4.Presented());

	rapidjson::Document doc;
	doc.Parse("{\"testOther\":42}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 0);
	CHECK_EQUAL(testable2.Value, 0);
	CHECK_EQUAL(testable3.Value, 0);
	CHECK_EQUAL(testable4.Value, 0);
	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable2.Presented());
	CHECK_FALSE(testable3.Presented());
	CHECK_FALSE(testable4.Presented());

	doc.Parse("{\"test\":42}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 42);
	CHECK_EQUAL(testable2.Value, 42);
	CHECK_EQUAL(testable3.Value, 42);
	CHECK_EQUAL(testable4.Value, 42);
	CHECK_TRUE(testable1.Presented());
	CHECK_TRUE(testable2.Presented());
	CHECK_TRUE(testable3.Presented());
	CHECK_TRUE(testable4.Presented());

	doc.Parse("{\"test\":null}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));
}

TEST(JsonNumericValueGroup, JsonIntField_Optional_TryParse_Test) {
	JsonFieldsContainer container;
	JsonOptionalValue<int> testable1(&container, "test", 100);
	JsonOptionalValue<int32_t> testable2(&container, "test", 101);
	JsonOptionalValue<int16_t> testable3(&container, "test", 102);
	JsonOptionalValue<int8_t> testable4(&container, "test", 103);

	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable2.Presented());
	CHECK_FALSE(testable3.Presented());
	CHECK_FALSE(testable4.Presented());

	rapidjson::Document doc;
	doc.Parse("{\"testOther\":42}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 0);
	CHECK_EQUAL(testable2.Value, 0);
	CHECK_EQUAL(testable3.Value, 0);
	CHECK_EQUAL(testable4.Value, 0);
	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable2.Presented());
	CHECK_FALSE(testable3.Presented());
	CHECK_FALSE(testable4.Presented());

	doc.Parse("{\"test\":42}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 42);
	CHECK_EQUAL(testable2.Value, 42);
	CHECK_EQUAL(testable3.Value, 42);
	CHECK_EQUAL(testable4.Value, 42);
	CHECK_TRUE(testable1.Presented());
	CHECK_TRUE(testable2.Presented());
	CHECK_TRUE(testable3.Presented());
	CHECK_TRUE(testable4.Presented());

	doc.Parse("{\"test\":null}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));
}

TEST(JsonNumericValueGroup, JsonBoolField_Optional_TryParse_Test) {
	JsonFieldsContainer container;
	JsonOptionalValue<bool> testable1(&container, "test");

	CHECK_FALSE(testable1.Presented());
	rapidjson::Document doc;
	doc.Parse("{\"testOther\":true}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, false);
	CHECK_FALSE(testable1.Presented());

	doc.Parse("{\"test\":true}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, true);
	CHECK_TRUE(testable1.Presented());

	doc.Parse("{\"test\":null}");
	CHECK_FALSE(testable1.TryParse(&doc));
}
/*


*/

TEST(JsonNumericValueGroup, JsonUIntField_Nullable_TryParse_Test) {
	JsonFieldsContainer container;
	JsonNullableValue<unsigned int> testable1(&container, "test", 100);
	JsonNullableValue<uint32_t> testable2(&container, "test", 101);
	JsonNullableValue<uint16_t> testable3(&container, "test", 102);
	JsonNullableValue<uint8_t> testable4(&container, "test", 103);

	CHECK_FALSE(testable1.IsNull());
	CHECK_FALSE(testable2.IsNull());
	CHECK_FALSE(testable3.IsNull());
	CHECK_FALSE(testable4.IsNull());

	rapidjson::Document doc;
	doc.Parse("{\"testOther\":42}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 0);
	CHECK_EQUAL(testable2.Value, 0);
	CHECK_EQUAL(testable3.Value, 0);
	CHECK_EQUAL(testable4.Value, 0);
	CHECK_FALSE(testable1.IsNull());
	CHECK_FALSE(testable2.IsNull());
	CHECK_FALSE(testable3.IsNull());
	CHECK_FALSE(testable4.IsNull());

	doc.Parse("{\"test\":42}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 42);
	CHECK_EQUAL(testable2.Value, 42);
	CHECK_EQUAL(testable3.Value, 42);
	CHECK_EQUAL(testable4.Value, 42);
	CHECK_FALSE(testable1.IsNull());
	CHECK_FALSE(testable2.IsNull());
	CHECK_FALSE(testable3.IsNull());
	CHECK_FALSE(testable4.IsNull());

	doc.Parse("{\"test\":null}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_TRUE(testable1.IsNull());
	CHECK_TRUE(testable2.IsNull());
	CHECK_TRUE(testable3.IsNull());
	CHECK_TRUE(testable4.IsNull());
}

TEST(JsonNumericValueGroup, JsonIntField_Nullable_TryParse_Test) {
	JsonFieldsContainer container;
	JsonNullableValue<int> testable1(&container, "test", 100);
	JsonNullableValue<int32_t> testable2(&container, "test", 101);
	JsonNullableValue<int16_t> testable3(&container, "test", 102);
	JsonNullableValue<int8_t> testable4(&container, "test", 103);

	CHECK_FALSE(testable1.IsNull());
	CHECK_FALSE(testable2.IsNull());
	CHECK_FALSE(testable3.IsNull());
	CHECK_FALSE(testable4.IsNull());

	rapidjson::Document doc;
	doc.Parse("{\"testOther\":42}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_FALSE(testable2.TryParse(&doc));
	CHECK_FALSE(testable3.TryParse(&doc));
	CHECK_FALSE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 0);
	CHECK_EQUAL(testable2.Value, 0);
	CHECK_EQUAL(testable3.Value, 0);
	CHECK_EQUAL(testable4.Value, 0);
	CHECK_FALSE(testable1.IsNull());
	CHECK_FALSE(testable2.IsNull());
	CHECK_FALSE(testable3.IsNull());
	CHECK_FALSE(testable4.IsNull());

	doc.Parse("{\"test\":42}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 42);
	CHECK_EQUAL(testable2.Value, 42);
	CHECK_EQUAL(testable3.Value, 42);
	CHECK_EQUAL(testable4.Value, 42);
	CHECK_FALSE(testable1.IsNull());
	CHECK_FALSE(testable2.IsNull());
	CHECK_FALSE(testable3.IsNull());
	CHECK_FALSE(testable4.IsNull());

	doc.Parse("{\"test\":null}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable2.TryParse(&doc));
	CHECK_TRUE(testable3.TryParse(&doc));
	CHECK_TRUE(testable4.TryParse(&doc));
	CHECK_TRUE(testable1.IsNull());
	CHECK_TRUE(testable2.IsNull());
	CHECK_TRUE(testable3.IsNull());
	CHECK_TRUE(testable4.IsNull());
}

TEST(JsonNumericValueGroup, JsonBoolField_Nullable_TryParse_Test) {
	JsonFieldsContainer container;
	JsonNullableValue<bool> testable1(&container, "test", 100);

	CHECK_FALSE(testable1.IsNull());

	rapidjson::Document doc;
	doc.Parse("{\"testOther\":true}");
	CHECK_FALSE(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, 0);
	CHECK_FALSE(testable1.IsNull());

	doc.Parse("{\"test\":true}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_EQUAL(testable1.Value, true);
	CHECK_FALSE(testable1.IsNull());

	doc.Parse("{\"test\":null}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable1.IsNull());
}