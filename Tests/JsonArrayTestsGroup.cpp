
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

class BoolList : public JsonArray<TBoolArray> {
  public:
	bool Validate(TBoolArray item) override { return Items.size() < maxCount; }
};

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

class DoubleList : public JsonArray<double> {
  public:
	bool Validate(double item) override { return Items.size() < maxCount; }
};
class FloatList : public JsonArray<float> {
  public:
	bool Validate(float item) override { return Items.size() < maxCount; }
};

TEST(JsonArrayTestsGroup, JsonObjectArray_Parse_Test) {
	UsersList list;

	CHECK_TRUE(list.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
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

TEST(JsonArrayTestsGroup, JsonObjectArray_Parse_With_Begin_End_Stages_And_Specified_Length_Test) {
	UsersList list;
	auto doc = list.BeginTryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
								  "\"role\":255}]  some data 0123456                     ",
								  83);

	CHECK(doc != NULL);
	CHECK_EQUAL(list.Items.size(), 3);

	STRCMP_EQUAL(list.Items[2]->Name.Value, "User3");
	CHECK_EQUAL(list.Items[2]->Role.Value, 255);
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

TEST(JsonArrayTestsGroup, JsonObjectArray_Equals_Test) {
	UsersList list1;
	list1.Add(new UserDto("user 1", 0));
	list1.Add(new UserDto("user 2", 10));
	list1.Add(new UserDto("user 3", 100));
	list1.Add(new UserDto("user 4", 999));

	UsersList list2;
	list2.Add(new UserDto("user 1", 0));
	list2.Add(new UserDto("user 2", 10));
	list2.Add(new UserDto("user 3", 100));
	list2.Add(new UserDto("user 4", 999));

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2]->Name.Value = "User3";
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonObjectArray_Find_Test) {
	UsersList list1;
	list1.Add(new UserDto("user 1", 0));
	list1.Add(new UserDto("user 2", 10));
	list1.Add(new UserDto("user 3", 100));
	list1.Add(new UserDto("user 4", 999));

	auto iter = list1.Find(new UserDto("user 3", 100));
	CHECK(iter != list1.Items.end());
	STRCMP_EQUAL((*iter)->Name.Value, "user 3");
	CHECK_EQUAL(list1.Find(new UserDto()), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonStringArray_Parse_Test) {
	StringsList list;

	CHECK_TRUE(list.TryParse("[\"User1\",\"User2\",\"User3\"]"));
	CHECK_EQUAL(list.Items.size(), 3);

	STRCMP_EQUAL((char *)list.Items[0], "User1");
	STRCMP_EQUAL((char *)list.Items[2], "User3");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonStringArray_WriteTo_Test) {
	char buffer[2048];
	StringsList list;
	list.Add("user 1");
	list.Add("user 2");
	list.Add("user 3");
	list.Add("user 4");

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 37);
	STRCMP_EQUAL(buffer, "[\"user 1\",\"user 2\",\"user 3\",\"user 4\"]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonStringArray_Equals_Test) {
	StringsList list1;
	list1.Add("user 1");
	list1.Add("user 2");
	list1.Add("user 3");
	list1.Add("user 4");

	StringsList list2;
	list2.Add("user 1");
	list2.Add("user 2");
	list2.Add("user 3");
	list2.Add("user 4");

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = "User3";
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);
	// list2.Items[2] = "User3";
	// CHECK_TRUE(list1 == list2);
	// list2.Remove("user 2");
	// CHECK_TRUE(list1 != list2);
	// CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonStringArray_Find_Test) {
	StringsList list1;
	list1.Add("user 1");
	list1.Add("user 2");
	list1.Add("user 3");
	list1.Add("user 4");

	CHECK(list1.Find("user 2") != list1.Items.end());
	STRCMP_EQUAL(*(list1.Find("user 2")), "user 2");
	CHECK_EQUAL(list1.Find("error"), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonBoolArray_Parse_Test) {
	BoolList list;

	CHECK_TRUE(list.TryParse("[true,false,true,false]"));
	CHECK_EQUAL(list.Items.size(), 4);

	CHECK_EQUAL(list.Items[0], true);
	CHECK_EQUAL(list.Items[3], false);

	CHECK_FALSE(list.TryParse("[false,1,true,0]"));

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonBoolArray_WriteTo_Test) {
	char buffer[2048];
	BoolList list;
	list.Add(true);
	list.Add(false);
	list.Add(false);
	list.Add(true);
	list.Add(true);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 28);
	STRCMP_EQUAL(buffer, "[true,false,false,true,true]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonBoolArray_Equals_Test) {
	BoolList list1;
	list1.Add(true);
	list1.Add(false);
	list1.Add(false);
	list1.Add(true);

	BoolList list2;
	list2.Add(true);
	list2.Add(false);
	list2.Add(false);
	list2.Add(true);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = true;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonBoolArray_Find_Test) {
	BoolList list1;
	list1.Add(true);

	CHECK(list1.Find(true) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(true)), true);
	CHECK_EQUAL(list1.Find(false), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt64Array_Parse_Test) {
	Int64List list;
	CHECK_TRUE(list.TryParse("[0,1,-5188146770730811392,5188146770730811392]"));
	CHECK_EQUAL(list.Items.size(), 4);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 1);
	CHECK_EQUAL(list.Items[2], -5188146770730811392LL);
	CHECK_EQUAL(list.Items[3], 5188146770730811392LL);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt64Array_WriteTo_Test) {
	char buffer[2048];
	Int64List list;
	list.Add(-5188146770730811392LL);
	list.Add(5188146770730811392LL);
	list.Add(0);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 44);
	STRCMP_EQUAL(buffer, "[-5188146770730811392,5188146770730811392,0]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt64Array_Equals_Test) {
	Int64List list1;
	list1.Add(-5188146770730811392LL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	Int64List list2;
	list2.Add(-5188146770730811392LL);
	list2.Add(5188146770730811392LL);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = -1;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt64Array_Find_Test) {
	Int64List list1;
	list1.Add(-5188146770730811392LL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	CHECK(list1.Find(5188146770730811392LL) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(5188146770730811392LL)), 5188146770730811392LL);
	CHECK_EQUAL(list1.Find(-1), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint64Array_Parse_Test) {
	Uint64List list;
	CHECK_TRUE(list.TryParse("[1,0,10188146770730811392]"));
	CHECK_EQUAL(list.Items.size(), 3);
	CHECK_EQUAL(list.Items[0], 1);
	CHECK_EQUAL(list.Items[1], 0);
	CHECK_EQUAL(list.Items[2], 10188146770730811392LL);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint64Array_WriteTo_Test) {
	char buffer[2048];
	Uint64List list;
	list.Add(0);
	list.Add(10188146770730811392);
	list.Add(1);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 26);
	STRCMP_EQUAL(buffer, "[0,10188146770730811392,1]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint64Array_Equals_Test) {
	Uint64List list1;
	list1.Add(0);
	list1.Add(10188146770730811392);
	list1.Add(1);

	Uint64List list2;
	list2.Add(0);
	list2.Add(10188146770730811392);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 5222;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint64Array_Find_Test) {
	Uint64List list1;
	list1.Add(-5188146770730811392LL);
	list1.Add(5188146770730811392LL);
	list1.Add(0);

	CHECK(list1.Find(5188146770730811392LL) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(5188146770730811392LL)), 5188146770730811392LL);
	CHECK_EQUAL(list1.Find(1), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt32Array_Parse_Test) {
	Int32List list;
	CHECK_TRUE(list.TryParse("[0,-2147483647,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 3);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], -2147483647);
	CHECK_EQUAL(list.Items[2], 2147483647);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt32Array_WriteTo_Test) {
	char buffer[2048];
	Int32List list;
	list.Add(-2147483647);
	list.Add(2147483647);
	list.Add(0);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 26);
	STRCMP_EQUAL(buffer, "[-2147483647,2147483647,0]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt32Array_Equals_Test) {
	Int32List list1;
	list1.Add(-2147483647);
	list1.Add(2147483647);
	list1.Add(0);

	Int32List list2;
	list2.Add(-2147483647);
	list2.Add(2147483647);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 100;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt32Array_Find_Test) {
	Int32List list1;
	list1.Add(-2147483647);
	list1.Add(2147483647);
	list1.Add(0);

	CHECK(list1.Find(-2147483647) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(-2147483647)), -2147483647);
	CHECK_EQUAL(list1.Find(1), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint32Array_Parse_Test) {
	Uint32List list;
	CHECK_TRUE(list.TryParse("[0,4294967295]"));
	CHECK_EQUAL(list.Items.size(), 2);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 4294967295);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint32Array_WriteTo_Test) {
	char buffer[2048];
	Uint32List list;
	list.Add(0);
	list.Add(4294967295);
	list.Add(1);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 16);
	STRCMP_EQUAL(buffer, "[0,4294967295,1]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint32Array_Equals_Test) {
	Uint32List list1;
	list1.Add(147483647);
	list1.Add(2147483647);
	list1.Add(0);

	Uint32List list2;
	list2.Add(147483647);
	list2.Add(2147483647);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 42;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint32Array_Find_Test) {
	Uint32List list1;
	list1.Add(147483647);
	list1.Add(2147483647);
	list1.Add(5);

	CHECK(list1.Find(5) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(5)), 5);
	CHECK_EQUAL(list1.Find(1), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt16Array_Parse_Test) {
	Int16List list;
	CHECK_TRUE(list.TryParse("[0,-32768,32767,-2147483647,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 5);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], -32768);
	CHECK_EQUAL(list.Items[2], 32767);
	CHECK_EQUAL(list.Items[3], 1);
	CHECK_EQUAL(list.Items[4], -1);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt16Array_WriteTo_Test) {
	char buffer[2048];
	Int16List list;
	list.Add(-32768);
	list.Add(32767);
	list.Add(0);
	list.Add(-2147483647);
	list.Add(2147483647);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 21);
	STRCMP_EQUAL(buffer, "[-32768,32767,0,1,-1]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt16Array_Equals_Test) {
	Int16List list1;
	list1.Add(-32768);
	list1.Add(32767);
	list1.Add(0);

	Int16List list2;
	list2.Add(-32768);
	list2.Add(32767);
	list2.Add(0);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 42;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt16Array_Find_Test) {
	Int16List list1;
	list1.Add(-32768);
	list1.Add(32767);
	list1.Add(0);

	CHECK(list1.Find(32767) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(32767)), 32767);
	CHECK_EQUAL(list1.Find(1), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint16Array_Parse_Test) {
	Uint16List list;
	CHECK_TRUE(list.TryParse("[0,65535,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 3);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 65535);
	CHECK_EQUAL(list.Items[2], 65535);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint16Array_WriteTo_Test) {
	char buffer[2048];
	Uint16List list;
	list.Add(0);
	list.Add(65535);
	list.Add(1);
	list.Add(2147483647);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 17);
	STRCMP_EQUAL(buffer, "[0,65535,1,65535]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint16Array_Equals_Test) {
	Int16List list1;
	list1.Add(0);
	list1.Add(65535);
	list1.Add(1);

	Int16List list2;
	list2.Add(0);
	list2.Add(65535);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 42;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint16Array_Find_Test) {
	Uint16List list1;
	list1.Add(0);
	list1.Add(65535);
	list1.Add(1);

	CHECK(list1.Find(65535) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(65535)), 65535);
	CHECK_EQUAL(list1.Find(10), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt8Array_Parse_Test) {
	Int8List list;
	CHECK_TRUE(list.TryParse("[0,-128,127,-2147483647,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 5);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], -128);
	CHECK_EQUAL(list.Items[2], 127);
	CHECK_EQUAL(list.Items[3], 1);
	CHECK_EQUAL(list.Items[4], -1);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt8Array_WriteTo_Test) {
	char buffer[2048];
	Int8List list;
	list.Add(-128);
	list.Add(127);
	list.Add(-32768);
	list.Add(32767);
	list.Add(0);
	list.Add(-2147483647);
	list.Add(2147483647);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 22);
	STRCMP_EQUAL(buffer, "[-128,127,0,-1,0,1,-1]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt8Array_Equals_Test) {
	Int8List list1;
	list1.Add(0);
	list1.Add(-128);
	list1.Add(1);

	Int8List list2;
	list2.Add(0);
	list2.Add(-128);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 42;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonInt8Array_Find_Test) {
	Int8List list1;
	list1.Add(0);
	list1.Add(-128);
	list1.Add(1);

	CHECK(list1.Find(1) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(1)), 1);
	CHECK_EQUAL(list1.Find(2), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint8Array_Parse_Test) {
	Uint8List list;
	CHECK_TRUE(list.TryParse("[0,254,65535,2147483647]"));
	CHECK_EQUAL(list.Items.size(), 4);
	CHECK_EQUAL(list.Items[0], 0);
	CHECK_EQUAL(list.Items[1], 254);
	CHECK_EQUAL(list.Items[2], 255);
	CHECK_EQUAL(list.Items[3], 255);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint8Array_WriteTo_Test) {
	char buffer[2048];
	Uint8List list;
	list.Add(0);
	list.Add(254);
	list.Add(65535);
	list.Add(1);
	list.Add(2147483647);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 17);
	STRCMP_EQUAL(buffer, "[0,254,255,1,255]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint8Array_Equals_Test) {
	Uint8List list1;
	list1.Add(0);
	list1.Add(254);
	list1.Add(1);

	Uint8List list2;
	list2.Add(0);
	list2.Add(254);
	list2.Add(1);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 42;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonUint8Array_Find_Test) {
	Uint8List list1;
	list1.Add(0);
	list1.Add(254);
	list1.Add(1);

	CHECK(list1.Find(1) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(1)), 1);
	CHECK_EQUAL(list1.Find(2), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonDoubleArray_Parse_Test) {
	DoubleList list;
	CHECK_TRUE(list.TryParse("[0.00001,254.123,-65535.523,2147483647.1]"));
	CHECK_EQUAL(list.Items.size(), 4);
	CHECK_EQUAL(list.Items[0], 0.00001);
	CHECK_EQUAL(list.Items[1], 254.123);
	CHECK_EQUAL(list.Items[2], -65535.523);
	CHECK_EQUAL(list.Items[3], 2147483647.1);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonDoubleArray_WriteTo_Test) {
	char buffer[2048];
	DoubleList list;
	list.Add(-0.05);
	list.Add(1.254);
	list.Add(65535.15);
	list.Add(0.1);
	list.Add(2147.483647);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 38);
	STRCMP_EQUAL(buffer, "[-0.05,1.254,65535.15,0.1,2147.483647]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonDoubleArray_Equals_Test) {
	DoubleList list1;
	list1.Add(-0.05);
	list1.Add(1.254);
	list1.Add(65535.15);

	DoubleList list2;
	list2.Add(-0.05);
	list2.Add(1.254);
	list2.Add(65535.15);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 42;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonDoubleArray_Find_Test) {
	DoubleList list1;
	list1.Add(-0.05);
	list1.Add(1.254);
	list1.Add(65535.15);

	CHECK(list1.Find(-0.05) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(-0.05)), -0.05);
	CHECK_EQUAL(list1.Find(2), list1.Items.end());

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonFloatArray_Parse_Test) {
	FloatList list;
	CHECK_TRUE(list.TryParse("[0.1,254.1,-65535.5,214748.1]"));
	CHECK_EQUAL(list.Items.size(), 4);
	CHECK_EQUAL(list.Items[0], 0.1f);
	CHECK_EQUAL(list.Items[1], 254.1f);
	CHECK_EQUAL(list.Items[2], -65535.5f);
	CHECK_EQUAL(list.Items[3], 214748.1f);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonFloatArray_WriteTo_Test) {
	char buffer[2048];
	FloatList list;
	list.Add(-1.5f);
	list.Add(1.25f);
	list.Add(1000.25f);
	list.Add(-100.75f);
	list.Add(214789.5625f);

	CHECK_EQUAL(list.WriteToString(buffer, sizeof(buffer)), 39);
	STRCMP_EQUAL(buffer, "[-1.5,1.25,1000.25,-100.75,214789.5625]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonFloatArray_Equals_Test) {
	FloatList list1;
	list1.Add(-0.05);
	list1.Add(1.254);
	list1.Add(65535.15);

	FloatList list2;
	list2.Add(-0.05);
	list2.Add(1.254);
	list2.Add(65535.15);

	CHECK_TRUE(list1 == list2);
	CHECK_FALSE(list1 != list2);
	list1.Items[2] = 42;
	CHECK_TRUE(list1 != list2);
	CHECK_FALSE(list1 == list2);

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonFloatArray_Find_Test) {
	FloatList list1;
	list1.Add(-0.05);
	list1.Add(1.254);
	list1.Add(65535.15);

	CHECK(list1.Find(-0.05) != list1.Items.end());
	CHECK_EQUAL(*(list1.Find(-0.05)), -0.05f);
	CHECK_EQUAL(list1.Find(2), list1.Items.end());

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Parse_Error_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Parse_With_Begin_End_Stages_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Parse_With_Begin_End_Stages_And_Specified_Length_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_WriteTo_With_Limited_Buffer_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Direct_Write_From_Json_Memory_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonObjectArray_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonStringArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonStringArray_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonStringArray_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonStringArray_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonBoolArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonBoolArray_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonBoolArray_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonBoolArray_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt64Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt64Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt64Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt64Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint64Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint64Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint64Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint64Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt32Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt32Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt32Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt32Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint32Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint32Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint32Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint32Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt16Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt16Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt16Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt16Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint16Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint16Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint16Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint16Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt8Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt8Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt8Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonInt8Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint8Array_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint8Array_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint8Array_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonUint8Array_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonDoubleArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonDoubleArray_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonDoubleArray_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonDoubleArray_Find_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonFloatArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonFloatArray_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonFloatArray_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonFloatArray_Find_Test);

	printf("JsonArrayTestsGroup success");
	return EXIT_SUCCESS;
}
