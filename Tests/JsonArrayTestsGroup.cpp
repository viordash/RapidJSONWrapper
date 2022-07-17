
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

class UserDto : public JsonObject {
  public:
	JsonValue<char *> Name;
	JsonValue<uint32_t> Role;

	UserDto(char *name, uint32_t role)
		: Name(this, "name", name), //
		  Role(this, "role", role){};

	UserDto()
		: Name(this, "name"), //
		  Role(this, "role") {}

	bool Validate() override { return Role.Value < 1000; }
};

static size_t maxCount = 10;

class UsersList : public JsonArray<UserDto *> {
  public:
	bool Validate(UserDto *item) override { return Items.size() < maxCount && item->Validate(); }
};

class StringsList : public JsonArray<char *> {
  public:
	bool Validate(char *item) override { return Items.size() < maxCount && item != NULL; }
};

// class BoolList : public JsonArray<bool> {
//  public:
//	bool Validate(bool item) override { return Items.size() < maxCount; }
//};

class Int64List : public JsonArray<int64_t> {
  public:
	bool Validate(int64_t item) override { return Items.size() < maxCount && item < 5188146770730811392LL + 1LL; }
};
class Uint64List : public JsonArray<uint64_t> {
  public:
	bool Validate(uint64_t item) override { return Items.size() < maxCount && item < 10188146770730811392LL + 1LL; }
};

class Int32List : public JsonArray<int32_t> {
  public:
	bool Validate(int32_t item) override { return Items.size() < maxCount; }
};
class Uint32List : public JsonArray<uint32_t> {
  public:
	bool Validate(uint32_t item) override { return Items.size() < maxCount; }
};

class Int16List : public JsonArray<int16_t> {
  public:
	bool Validate(int16_t item) override { return Items.size() < maxCount; }
};
class Uint16List : public JsonArray<uint16_t> {
  public:
	bool Validate(uint16_t item) override { return Items.size() < maxCount; }
};

class Int8List : public JsonArray<int8_t> {
  public:
	bool Validate(int8_t item) override { return Items.size() < maxCount; }
};
class Uint8List : public JsonArray<uint8_t> {
  public:
	bool Validate(uint8_t item) override { return Items.size() < maxCount; }
};

TEST(JsonArrayTestsGroup, JsonObjectArray_Parse_Test) {
	UsersList list;

	CHECK(list.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
						"\"role\":255}]"));
	CHECK_EQUAL(list.Items.size(), 3);

	STRCMP_EQUAL(list.Items[0]->Name.Value, "User1");
	CHECK_EQUAL(list.Items[0]->Role.Value, 100);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonObjectArray_Parse_Error_Test) {
	UsersList list;
	CHECK_FALSE(list.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
							  "\"role\":255}"));
	CHECK_FALSE(list.TryParse("{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
							  "\"role\":255}]"));
	CHECK_FALSE(list.TryParse("[\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
							  "\"role\":255}]"));
	CHECK_FALSE(list.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
							  "\"role\":255]"));
	CHECK_FALSE(list.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\"\"User3\","
							  "\"role\":255}]"));
	CHECK_FALSE(list.TryParse("[{\"name\":\"User1\",\"role\":100}{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
							  "\"role\":255}]"));
	CHECK_FALSE(list.TryParse("[{},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\",\"role\":255}]"));
	CHECK_FALSE(list.TryParse(NULL, 1));
	CHECK_EQUAL(list.Items.size(), 0);

	CHECK_FALSE(list.TryParse("[{\"name\":\"User2\",\"role\":0},null]"));
	CHECK_EQUAL(list.Items.size(), 1);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonObjectArray_Parse_With_Begin_End_Stages_Test) {
	UsersList list;
	auto doc = list.BeginTryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
								  "\"role\":255}]");

	CHECK(doc != NULL);
	CHECK_EQUAL(list.Items.size(), 3);

	STRCMP_EQUAL(list.Items[0]->Name.Value, "User1");
	CHECK_EQUAL(list.Items[0]->Role.Value, 100);
	list.EndTryParse(doc);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonObjectArray_WriteTo_Test) {
	char buffer[2048];
	UsersList list;
	list.Add(new UserDto("user 1", 0));
	list.Add(new UserDto("user 2", 10));
	list.Add(new UserDto("user 3", 100));
	list.Add(new UserDto("user 4", 1000));

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 85);
	STRCMP_EQUAL(buffer, "[{\"name\":\"user 1\",\"role\":0},{\"name\":\"user 2\",\"role\":10},{\"name\":\"user 3\",\"role\":100}]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonObjectArray_WriteTo_With_Limited_Buffer_Test) {
	char buffer[100];
	UsersList list;
	list.Add(new UserDto("user 1", 0));
	list.Add(new UserDto("user 2", 10));
	list.Add(new UserDto("user 3", 100));
	list.Add(new UserDto("user 4", 999));

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 99);

	STRCMP_EQUAL(buffer, "[{\"name\":\"user 1\",\"role\":0},{\"name\":\"user 2\",\"role\":10},{\"name\":\"user 3\",\"role\":100},{\"name\":\"user ");
	return EXIT_SUCCESS;
}

static void *TestParent = NULL;
static char *DirectWriteTestBuffer = NULL;
static void OnReady(void *parent, const char *json, int size) {
	TestParent = parent;
	DirectWriteTestBuffer = new char[size + 1];
	memcpy(DirectWriteTestBuffer, json, size);
	DirectWriteTestBuffer[size] = 0;
}

TEST(JsonArrayTestsGroup, JsonObjectArray_Direct_Write_From_Json_Memory_Test) {
	UsersList list;
	list.Add(new UserDto("user 1", 0));
	list.Add(new UserDto("user 2", 10));
	list.Add(new UserDto("user 3", 100));
	list.Add(new UserDto("user 4", 999));

	list.DirectWriteTo((void *)987654321, OnReady);
	CHECK_EQUAL(TestParent, (void *)987654321);
	STRCMP_EQUAL(DirectWriteTestBuffer, "[{\"name\":\"user 1\",\"role\":0},{\"name\":\"user 2\",\"role\":10},{\"name\":\"user 3\",\"role\":100},{\"name\":\"user 4\",\"role\":999}]");
	delete[] DirectWriteTestBuffer;
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonStringArray_Parse_Test) {
	StringsList list;

	CHECK(list.TryParse("[\"User1\",\"User2\",\"User3\"]"));
	CHECK_EQUAL(list.Items.size(), 3);

	STRCMP_EQUAL((char *)list.Items[0], "User1");
	STRCMP_EQUAL((char *)list.Items[2], "User3");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonBoolArray_Parse_Test) {
	// BoolList list;

	// CHECK(list.TryParse("[true,false,true,false]"));
	// CHECK_EQUAL(list.Items.size(), 4);

	// CHECK_EQUAL(list.Items[0], true);
	// CHECK_EQUAL(list.Items[3], false);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt64Array_Parse_Test) {
	Int64List list;
	CHECK(list.TryParse("[0,1,-5188146770730811392,5188146770730811392]"));
	CHECK_EQUAL(list.Items.size(), 4);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 1);
	CHECK_EQUAL(list.Items[2], -5188146770730811392LL);
	CHECK_EQUAL(list.Items[3], 5188146770730811392LL);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint64Array_Parse_Test) {
	Uint64List list;
	CHECK(list.TryParse("[1,0,10188146770730811392]"));
	CHECK_EQUAL(list.Items.size(), 3);
	CHECK_EQUAL(list.Items[0], 1);
	CHECK_EQUAL(list.Items[1], 0);
	CHECK_EQUAL(list.Items[2], 10188146770730811392LL);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt32Array_Parse_Test) {
	Int32List list;
	CHECK(list.TryParse("[0,-2147483647,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 3);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], -2147483647);
	CHECK_EQUAL(list.Items[2], 2147483647);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint32Array_Parse_Test) {
	Uint32List list;
	CHECK(list.TryParse("[0,4294967295]"));
	CHECK_EQUAL(list.Items.size(), 2);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 4294967295);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt16Array_Parse_Test) {
	Int16List list;
	CHECK(list.TryParse("[0,-32768,32767,-2147483647,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 5);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], -32768);
	CHECK_EQUAL(list.Items[2], 32767);
	CHECK_EQUAL(list.Items[3], 1);
	CHECK_EQUAL(list.Items[4], -1);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint16Array_Parse_Test) {
	Uint16List list;
	CHECK(list.TryParse("[0,65535,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 3);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 65535);
	CHECK_EQUAL(list.Items[2], 65535);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt8Array_Parse_Test) {
	Int8List list;
	CHECK(list.TryParse("[0,-128,127,-2147483647,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 5);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], -128);
	CHECK_EQUAL(list.Items[2], 127);
	CHECK_EQUAL(list.Items[3], 1);
	CHECK_EQUAL(list.Items[4], -1);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint8Array_Parse_Test) {
	Uint8List list;
	CHECK(list.TryParse("[0,255,65535,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 4);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 255);
	CHECK_EQUAL(list.Items[2], 255);
	CHECK_EQUAL(list.Items[3], 255);
	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Parse_Error_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Parse_With_Begin_End_Stages_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_WriteTo_With_Limited_Buffer_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Direct_Write_From_Json_Memory_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonStringArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonBoolArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt64Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint64Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt32Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint32Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt16Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint16Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt8Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint8Array_Parse_Test);

	printf("JsonArrayTestsGroup success");
	return EXIT_SUCCESS;
}
