
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
	JsonField<uint32_t, true> Role;

	UserDto()
		: Name(this, "name"), //
		  Role(this, "role") {
	}
};

static int maxCount = 10;

class UsersList : public JsonArray {
  public:
	UsersList() {
	}

	JsonObject *CreateItem() override {
		return (JsonObject *)(new UserDto());
	}

	bool Validate() override {
		return Items.size() < maxCount;
	}
};

TEST(JsonArrayTestsGroup, JsonArray_Parse_Test) {
	UsersList usersList;

	CHECK(usersList.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
							 "\"role\":255}]"));
	CHECK_EQUAL(usersList.Items.size(), 3);

	auto it = usersList.Items.begin();
	STRCMP_EQUAL(((UserDto *)*it)->Name.Value, "User1");
	CHECK_EQUAL(((UserDto *)*it)->Role.Value, 100);
	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonArrayTestsGroup, JsonArray_Parse_Test);

	printf("JsonArrayTestsGroup success");
	return EXIT_SUCCESS;
}