
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JsonWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

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
	CHECK_TRUE(testable.TryParse(&doc));
	STRCMP_EQUAL(testable.Value, "User1");

	doc.Parse("{\"testString\":null}");
	CHECK_TRUE(testable.TryParse(&doc));
	CHECK_EQUAL(testable.Value, NULL);
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

TEST(JsonStringValueGroup, JsonStringValue_SetValue_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable(&container, "testString");
	STRCMP_EQUAL(testable.Value, NULL);

	testable.Value = "0123456789";
	STRCMP_EQUAL(testable.Value, "0123456789");
}

TEST(JsonStringValueGroup, JsonStringValue_Equals_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable1(&container, "test", "testString");
	JsonValue<char *> testable01(&container, "test", "testString");
	JsonValue<char *> testable001(&container, "testOtherField", "testString");

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	CHECK_TRUE(testable1.Equals(&testable01));
	CHECK_TRUE(testable01.Equals(&testable1));	
	testable01.Value = "otherValue";
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
	CHECK_FALSE(testable1.Equals(&testable01));
	CHECK_FALSE(testable01.Equals(&testable1));
	CHECK_FALSE(testable001 == testable1);
	CHECK_FALSE(testable1 == testable001);
	CHECK_FALSE(testable001.Equals(&testable1));
	CHECK_FALSE(testable1.Equals(&testable001));

	JsonValue<char *> testable2(&container, "test");
	JsonValue<char *> testable02(&container, "test", NULL);
	CHECK_TRUE(testable2 == testable02);
	testable2.Value = "123";
	CHECK_FALSE(testable2 == testable02);

	testable2.Value = NULL;
	CHECK_TRUE(testable2 == testable02);
	testable02.Value = "123";
	CHECK_FALSE(testable2 == testable02);
}

TEST(JsonStringValueGroup, JsonStringValue_CloneTo_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testable1(&container, "test", "0123456789");

	JsonValue<char *> clone1(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);
	testable1.Value = "check the full data buffer is cloned";
	STRCMP_EQUAL(clone1.Value, "0123456789");
}

TEST(JsonStringValueGroup, JsonStringValue_Common_TryParse_Test) {
	JsonFieldsContainer container;
	JsonCommonValue<char *> testable1(&container, "test", "0123456789");

	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable1.IsNull());

	rapidjson::Document doc;
	doc.Parse("{\"testOther\":\"01234\"}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable1.IsNull());

	doc.Parse("{\"test\":\"01234\"}");
	CHECK_TRUE(testable1.TryParse(&doc));
	STRCMP_EQUAL(testable1.Value, "01234");
	CHECK_TRUE(testable1.Presented());
	CHECK_FALSE(testable1.IsNull());

	doc.Parse("{\"test\":null}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable1.Presented());
	CHECK_TRUE(testable1.IsNull());
}

TEST(JsonStringValueGroup, JsonStringValue_Null_And_Empty_Value_Test) {
	JsonFieldsContainer container;
	JsonValue<char *> testDefault(&container, "testDefault");
	JsonValue<char *> testNull(&container, "testNull", NULL);
	JsonValue<char *> testEmpty(&container, "testEmpty", "");

	JsonCommonValue<char *> testCommonDefault(&container, "testDefault");
	JsonCommonValue<char *> testCommonNull(&container, "testNull", NULL);
	JsonCommonValue<char *> testCommonEmpty(&container, "testEmpty", "");

	CHECK_EQUAL(testDefault.Value, NULL);
	CHECK_EQUAL(testNull.Value, NULL);
	STRCMP_EQUAL(testEmpty.Value, "");

	CHECK_TRUE(testCommonDefault.IsNull());
	CHECK_TRUE(testCommonNull.IsNull());
	CHECK_FALSE(testCommonEmpty.IsNull());
	CHECK_EQUAL(testCommonDefault.Value, NULL);
	CHECK_EQUAL(testCommonNull.Value, NULL);
	STRCMP_EQUAL(testCommonEmpty.Value, "");

	testDefault.Value = "";
	STRCMP_EQUAL(testDefault.Value, "");

	testEmpty.Value = NULL;
	CHECK_EQUAL(testEmpty.Value, NULL);

	testCommonDefault.Value = "";
	STRCMP_EQUAL(testDefault.Value, "");

	testCommonEmpty.Value = NULL;
	CHECK_EQUAL(testEmpty.Value, NULL);
}