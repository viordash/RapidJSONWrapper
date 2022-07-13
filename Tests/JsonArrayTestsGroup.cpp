
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
	JsonField<char *> Name;
	JsonField<uint32_t> Role;

	UserDto(const char *name, uint32_t role)
		: Name(this, "name", name), //
		  Role(this, "role", role){};

	UserDto()
		: Name(this, "name"), //
		  Role(this, "role") {
	}
};

static size_t maxCount = 10;

class UsersList : public JsonArray<UserDto> {
  public:
	bool Validate(UserDto *item) override {
		return Items.size() < maxCount && item->Validate();
	}
};

TEST(JsonArrayTestsGroup, JsonArray_Parse_Test) {
	UsersList usersList;

	CHECK(usersList.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
							 "\"role\":255}]"));
	CHECK_EQUAL(usersList.Items.size(), 3);

	STRCMP_EQUAL(usersList.Items[0]->Name.Value, "User1");
	CHECK_EQUAL(usersList.Items[0]->Role.Value, 100);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_Parse_Error_Test) {
	UsersList usersList;
	CHECK_FALSE(usersList.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
								   "\"role\":255}"));
	CHECK_FALSE(usersList.TryParse("{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
								   "\"role\":255}]"));
	CHECK_FALSE(usersList.TryParse("[\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
								   "\"role\":255}]"));
	CHECK_FALSE(usersList.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
								   "\"role\":255]"));
	CHECK_FALSE(usersList.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\"\"User3\","
								   "\"role\":255}]"));
	CHECK_FALSE(usersList.TryParse("[{\"name\":\"User1\",\"role\":100}{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
								   "\"role\":255}]"));
	CHECK_FALSE(usersList.TryParse("[{},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\",\"role\":255}]"));
	CHECK_FALSE(usersList.TryParse(NULL, 1));
	CHECK_EQUAL(usersList.Items.size(), 0);

	CHECK_FALSE(usersList.TryParse("[{\"name\":\"User2\",\"role\":0},null]"));
	CHECK_EQUAL(usersList.Items.size(), 1);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_Parse_With_Begin_End_Stages_Test) {
	UsersList usersList;
	auto doc = usersList.BeginTryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
									   "\"role\":255}]");

	CHECK(doc != NULL);
	CHECK_EQUAL(usersList.Items.size(), 3);

	STRCMP_EQUAL(usersList.Items[0]->Name.Value, "User1");
	CHECK_EQUAL(usersList.Items[0]->Role.Value, 100);
	usersList.EndTryParse(doc);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_WriteTo_Test) {
	char buffer[2048];
	UsersList usersList;
	usersList.Add(new UserDto("user 1", 0));
	usersList.Add(new UserDto("user 2", 10));
	usersList.Add(new UserDto("user 3", 100));
	usersList.Add(new UserDto("user 4", 1000));

	CHECK_EQUAL(usersList.WriteToString(buffer, sizeof(buffer)), 115);
	STRCMP_EQUAL(buffer,
				 "[{\"name\":\"user 1\",\"role\":0},{\"name\":\"user 2\",\"role\":10},{\"name\":\"user 3\",\"role\":100},{\"name\":\"user 4\",\"role\":1000}]");
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_WriteTo_With_Limited_Buffer_Test) {
	char buffer[100];
	UsersList usersList;
	usersList.Add(new UserDto("user 1", 0));
	usersList.Add(new UserDto("user 2", 10));
	usersList.Add(new UserDto("user 3", 100));
	usersList.Add(new UserDto("user 4", 1000));

	CHECK_EQUAL(usersList.WriteToString(buffer, sizeof(buffer)), 99);

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

TEST(JsonArrayTestsGroup, JsonArray_Direct_Write_From_Json_Memory_Test) {
	UsersList usersList;
	usersList.Add(new UserDto("user 1", 0));
	usersList.Add(new UserDto("user 2", 10));
	usersList.Add(new UserDto("user 3", 100));
	usersList.Add(new UserDto("user 4", 1000));

	usersList.DirectWriteTo((void *)987654321, OnReady);
	CHECK_EQUAL(TestParent, (void *)987654321);
	STRCMP_EQUAL(DirectWriteTestBuffer,
				 "[{\"name\":\"user 1\",\"role\":0},{\"name\":\"user 2\",\"role\":10},{\"name\":\"user 3\",\"role\":100},{\"name\":\"user 4\",\"role\":1000}]");
	delete[] DirectWriteTestBuffer;
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_Equals_Test) {
	UsersList usersList1;
	usersList1.Add(new UserDto("user 1", 0));
	usersList1.Add(new UserDto("user 2", 10));

	UsersList usersList2;
	usersList2.Add(new UserDto("user 1", 0));
	usersList2.Add(new UserDto("user 2", 10));

	CHECK_TRUE(usersList1.Equals(&usersList2));
	CHECK_TRUE(usersList2.Equals(&usersList1));

	usersList2[0]->Role.Value = usersList2[0]->Role.Value + 1;
	CHECK_FALSE(usersList1.Equals(&usersList2));
	CHECK_FALSE(usersList2.Equals(&usersList1));

	usersList1[0]->Role.Value = usersList1[0]->Role.Value + 1;
	CHECK_TRUE(usersList1.Equals(&usersList2));
	CHECK_TRUE(usersList2.Equals(&usersList1));

	usersList2.Add(new UserDto("user 2", 10));
	CHECK_FALSE(usersList1.Equals(&usersList2));
	CHECK_FALSE(usersList2.Equals(&usersList1));

	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_GetSize_Test) {
	UsersList usersList;
	usersList.Add(new UserDto("user 1", 0));
	usersList.Add(new UserDto("user 2", 10));
	usersList.Add(new UserDto("user 3", 100));
	usersList.Add(new UserDto("user 4", 1000));
	CHECK_EQUAL(usersList.GetSize(), 115);

	usersList[0]->Name.Value = "user 1_1";
	CHECK_EQUAL(usersList.GetSize(), 117);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_Reset_Test) {
	UsersList usersList;
	usersList.Add(new UserDto("user 1", 0));
	usersList.Add(new UserDto("user 2", 10));
	usersList.Add(new UserDto("user 3", 100));
	usersList.Add(new UserDto("user 4", 1000));

	usersList.Reset();
	CHECK_EQUAL(usersList.Items.size(), 0);
	return EXIT_SUCCESS;
}

TEST(JsonArrayTestsGroup, JsonArray_CloneFrom_Test) {
	UsersList usersList1;
	usersList1.Add(new UserDto("user 1", 0));
	usersList1.Add(new UserDto("user 2", 10));

	UsersList usersList2;
	usersList2.Add(new UserDto("user 100", 200));
	usersList2.Add(new UserDto("user 200", 2010));
	usersList2.Add(new UserDto("user 300", 3010));

	usersList1.CloneFrom(&usersList2);

	CHECK_EQUAL(usersList1.Items.size(), 3);

	STRCMP_EQUAL(usersList1.Items[0]->Name.Value, "user 100");
	CHECK_EQUAL(usersList1.Items[0]->Role.Value, 200);

	STRCMP_EQUAL(usersList1.Items[1]->Name.Value, "user 200");
	CHECK_EQUAL(usersList1.Items[1]->Role.Value, 2010);

	STRCMP_EQUAL(usersList1.Items[2]->Name.Value, "user 300");
	CHECK_EQUAL(usersList1.Items[2]->Role.Value, 3010);

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonArrayTestsGroup, JsonArray_Parse_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_Parse_Error_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_Parse_With_Begin_End_Stages_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_WriteTo_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_WriteTo_With_Limited_Buffer_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_Direct_Write_From_Json_Memory_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_Equals_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_GetSize_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_Reset_Test);
	TEST_RUN(JsonArrayTestsGroup, JsonArray_CloneFrom_Test);

	printf("JsonArrayTestsGroup success");
	return EXIT_SUCCESS;
}
