
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

static int maxCount = 10;

class UsersList : public JsonArray<UserDto> {
  public:
	bool Validate(UserDto *item) override {
		return Items.size() < maxCount && item->Validate();
	}
};

TEST(JsonArrayFieldGroup, JsonArrayField_TryParse_Test) {
	JsonFieldsContainer container;
	UsersList usersList;
	JsonField<JsonBaseArray *> testable(&container, "users", &usersList);

	rapidjson::Document doc;
	doc.Parse("{\"users\":[{\"name\":\"user 1\",\"role\":42},{\"name\":\"user "
			  "2\",\"role\":10},{\"name\":\"user 3\",\"role\":100}]}");
	CHECK(testable.TryParse(&doc));

	CHECK_EQUAL(usersList.Items.size(), 3);
	CHECK_EQUAL(usersList.Items[0]->Role.Value, 42);
	STRCMP_EQUAL(usersList.Items[2]->Name.Value, "user 3");

	return EXIT_SUCCESS;
}

TEST(JsonArrayFieldGroup, JsonArrayField_TryParse_With_Null_Or_Empty_Object_Test) {
	rapidjson::Document doc;
	JsonFieldsContainer container;
	UsersList usersList;
	JsonField<JsonBaseArray *> testable(&container, "users", &usersList);

	doc.Parse("{\"users\":null}");
	CHECK(testable.TryParse(&doc));
	CHECK_EQUAL(usersList.Items.size(), 0);

	doc.Parse("{\"users\":[]}");
	CHECK(testable.TryParse(&doc));
	CHECK_EQUAL(usersList.Items.size(), 0);

	return EXIT_SUCCESS;
}

TEST(JsonArrayFieldGroup, JsonArrayField_TryParse_Field_Optional_Test) {
	rapidjson::Document doc;
	JsonFieldsContainer container;
	UsersList usersList;
	auto testableFieldMustExists = new JsonField<JsonBaseArray *>(&container, "users", &usersList);
	doc.Parse("{\"users1\":[{\"name\":\"user 1\",\"role\":42}]}");
	CHECK_FALSE(testableFieldMustExists->TryParse(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonField<JsonBaseArray *, true>(&container, "users", &usersList);
	doc.Parse("{\"users\":[{\"name\":\"user 1\",\"role\":42}]}");
	CHECK_TRUE(testableWithOptional->TryParse(&doc));
	CHECK_EQUAL(usersList.Items.size(), 1);
	delete testableWithOptional;
	return EXIT_SUCCESS;
}

TEST(JsonArrayFieldGroup, JsonArrayField_WriteTo_Test) {
	JsonFieldsContainer container;
	UsersList usersList;
	usersList.Add(new UserDto("user 1", 0));
	usersList.Add(new UserDto("user 2", 10));

	JsonField<JsonBaseArray *> testable(&container, "users", &usersList);

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteToDoc(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	STRCMP_EQUAL(jsonStr, "{\"users\":[{\"name\":\"user 1\",\"role\":0},{\"name\":\"user 2\",\"role\":10}]}");
	return EXIT_SUCCESS;
}

TEST(JsonArrayFieldGroup, JsonArrayField_Size_Test) {
	JsonFieldsContainer container;
	UsersList usersList;
	usersList.Add(new UserDto("user 1", 0));

	JsonField<JsonBaseArray *> testable(&container, "users", &usersList);
	CHECK_EQUAL(testable.GetSize(), 28);
	usersList.Items[0]->Name.Value = "user 12";
	CHECK_EQUAL(testable.GetSize(), 29);
	return EXIT_SUCCESS;
}

TEST(JsonArrayFieldGroup, JsonArrayField_Equals_Test) {
	JsonFieldsContainer container;
	UsersList usersList1;
	usersList1.Add(new UserDto("user 1", 0));
	UsersList usersList2;

	JsonField<JsonBaseArray *> testable1(&container, "user", &usersList1);
	JsonField<JsonBaseArray *> testable2(&container, "user", &usersList2);
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	usersList2.Add(new UserDto("user 1", 0));
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	JsonField<JsonBaseArray *> testable3(&container, "testFieldWrong", &usersList2);
	CHECK_FALSE(testable3.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable3));
	return EXIT_SUCCESS;
}

TEST(JsonArrayFieldGroup, JsonArrayField_CloneFrom_Test) {
	JsonFieldsContainer container;
	UsersList usersList1;
	usersList1.Add(new UserDto("user 1", 0));
	UsersList usersList2;
	usersList2.Add(new UserDto("user 100", 1));
	usersList2.Add(new UserDto("user 101", 2));

	JsonField<JsonBaseArray *> testable1(&container, "user", &usersList1);
	JsonField<JsonBaseArray *> testable2(&container, "user", &usersList2);
	testable1.CloneFrom(&testable2);
	CHECK_EQUAL(usersList1.Items.size(), 2);
	CHECK_EQUAL(usersList1.Items[0]->Role.Value, 1);
	STRCMP_EQUAL(usersList1.Items[1]->Name.Value, "user 101");

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonArrayFieldGroup, JsonArrayField_TryParse_Test);
	TEST_RUN(JsonArrayFieldGroup, JsonArrayField_TryParse_With_Null_Or_Empty_Object_Test);
	TEST_RUN(JsonArrayFieldGroup, JsonArrayField_TryParse_Field_Optional_Test);
	TEST_RUN(JsonArrayFieldGroup, JsonArrayField_WriteTo_Test);
	TEST_RUN(JsonArrayFieldGroup, JsonArrayField_Size_Test);
	TEST_RUN(JsonArrayFieldGroup, JsonArrayField_Equals_Test);
	TEST_RUN(JsonArrayFieldGroup, JsonArrayField_CloneFrom_Test);

	printf("JsonArrayFieldGroup success");
	return EXIT_SUCCESS;
}