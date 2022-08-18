
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JsonWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(JsonDataValueGroup){void setup(){} void teardown(){}};

TEST(JsonDataValueGroup, JsonDataValue_TryParse_Test) {
	JsonFieldsContainer container;
	JsonValue<TJsonRawData> testable(&container, "testString");

	rapidjson::Document doc;
	doc.Parse("{\"testString\":\"User1\"}");
	CHECK_TRUE(testable.TryParse(&doc));

	MEMCMP_EQUAL(((TJsonRawData)testable.Value).Data, "User1", ((TJsonRawData)testable.Value).Size);

	doc.Parse("{\"testString\":null}");
	CHECK_TRUE(testable.TryParse(&doc));
	CHECK_EQUAL(((TJsonRawData)testable.Value).Data, NULL);
	CHECK_EQUAL(((TJsonRawData)testable.Value).Size, 0);
}

TEST(JsonDataValueGroup, JsonDataValue_WriteTo_Test) {
	uint8_t data[32];
	memset(data, '*', sizeof(data));
	for (size_t i = 0; i < 16; i++) { data[i] = 'A' + (uint8_t)i; }
	data[sizeof(data) - 1] = 0;
	JsonFieldsContainer container;
	JsonValue<TJsonRawData> testable(&container, "testString", {data, 16});

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteToDoc(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();

	STRCMP_EQUAL(jsonStr, "{\"testString\":\"ABCDEFGHIJKLMNOP\"}");
}

TEST(JsonDataValueGroup, JsonDataValue_WriteToJson_Binary_Test) {
	uint8_t data[256];
	for (size_t i = 0; i < sizeof(data); i++) { data[i] = (uint8_t)i; }
	JsonFieldsContainer container;
	JsonValue<TJsonRawData> testable(&container, "testString", {data, sizeof(data)});

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteToDoc(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();

	STRCMP_EQUAL(jsonStr, "{\"testString\":"
						  "\"\\u0000\\u0001\\u0002\\u0003\\u0004\\u0005\\u0006\\u0007\\b\\t\\n\\u000B\\f\\r\\u000E\\u000F\\u0010\\u0011\\u0012\\u0013\\u0014\\u"
						  "0015\\u0016\\u0017\\u0018\\u0019\\u001A\\u001B\\u001C\\u001D\\u001E\\u001F "
						  "!\\\"#$%&'()*+,-./"
						  "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
						  "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F\xA0"
						  "\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF\xC0\xC1"
						  "\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF\xE0\xE1\xE2"
						  "\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF\"}");

	JsonValue<TJsonRawData> readTestable(&container, "testString", {NULL, 0});

	rapidjson::Document readDoc;
	doc.Parse(jsonStr);
	CHECK(readTestable.TryParse(&doc));
	CHECK(((TJsonRawData)readTestable.Value).Data != NULL);
	CHECK_EQUAL(((TJsonRawData)readTestable.Value).Size, sizeof(data));
	MEMCMP_EQUAL(data, ((TJsonRawData)readTestable.Value).Data, ((TJsonRawData)readTestable.Value).Size);
}

TEST(JsonDataValueGroup, JsonDataValue_WriteTo_For_Null_Test) {
	JsonFieldsContainer container;
	JsonValue<TJsonRawData> testable(&container, "testString", {NULL, 0});

	rapidjson::Document doc;
	doc.SetObject();
	testable.WriteToDoc(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();

	STRCMP_EQUAL(jsonStr, "{\"testString\":null}");
}

TEST(JsonDataValueGroup, JsonDataValue_SetValue_Test) {
	JsonFieldsContainer container;
	JsonValue<TJsonRawData> testable(&container, "testString");
	CHECK_EQUAL(((TJsonRawData)testable.Value).Data, NULL);
	CHECK_EQUAL(((TJsonRawData)testable.Value).Size, 0);

	testable.Value = {(uint8_t *)"0123456789", sizeof("0123456789") - 1};
	STRCMP_EQUAL((char *)((TJsonRawData)testable.Value).Data, "0123456789");
	CHECK_EQUAL(((TJsonRawData)testable.Value).Size, sizeof("0123456789") - 1);
}

TEST(JsonDataValueGroup, JsonDataValue_Equals_Test) {
	JsonFieldsContainer container;
	const char *str = "testString";
	JsonValue<TJsonRawData> testable1(&container, "test", {(uint8_t *)str, strlen(str) + 1});
	JsonValue<TJsonRawData> testable01(&container, "test", {(uint8_t *)str, strlen(str) + 1});

	CHECK_TRUE(testable1 == testable01);
	CHECK_FALSE(testable1 != testable01);
	testable01.Value = {(uint8_t *)"otherValue", sizeof("otherValue")};
	CHECK_TRUE(testable1 != testable01);
	CHECK_FALSE(testable1 == testable01);
}

TEST(JsonDataValueGroup, JsonDataValue_CloneTo_Test) {
	JsonFieldsContainer container;
	JsonValue<TJsonRawData> testable1(&container, "test", {(uint8_t *)"0123456789", sizeof("0123456789")});

	JsonValue<TJsonRawData> clone1(&container, "test");

	testable1.CloneTo((JsonValueBase *)&clone1);
	testable1.Value = {(uint8_t *)"check the full data buffer is cloned", sizeof("check the full data buffer is cloned")};
	STRCMP_EQUAL((char *)((TJsonRawData)clone1.Value).Data, "0123456789");
}

TEST(JsonDataValueGroup, JsonDataValue_Common_TryParse_Test) {
	JsonFieldsContainer container;
	JsonCommonValue<TJsonRawData> testable1(&container, "test", {(uint8_t *)"0123456789", sizeof("0123456789")});

	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable1.IsNull());

	rapidjson::Document doc;
	doc.Parse("{\"testOther\":\"01234\"}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_FALSE(testable1.Presented());
	CHECK_FALSE(testable1.IsNull());

	doc.Parse("{\"test\":\"01234\"}");
	CHECK_TRUE(testable1.TryParse(&doc));
	STRCMP_EQUAL((char *)((TJsonRawData)testable1.Value).Data, "01234");
	CHECK_EQUAL(((TJsonRawData)testable1.Value).Size, sizeof("01234") - 1);
	CHECK_TRUE(testable1.Presented());
	CHECK_FALSE(testable1.IsNull());

	doc.Parse("{\"test\":null}");
	CHECK_TRUE(testable1.TryParse(&doc));
	CHECK_TRUE(testable1.Presented());
	CHECK_TRUE(testable1.IsNull());
}