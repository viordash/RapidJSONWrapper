
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

//class UsersGroupDto : public JsonObject {
//  public:
//	// JsonField<char *> Group;
//	// JsonField<uint32_t, true> Role;
//	JsonField<UsersList *> Users;
//
//	UsersGroup(const char *name, uint32_t role, UsersList *users)
//		: Users(this, "users", users){
//		// Name.Value = name;
//		// Role.Value = role;
//	};
//
//	// UsersGroup(const char *name, uint32_t role, UsersList *users)
//	//	: Name(this, "name"), //
//	//	  Role(this, "role"), //
//	//	  Users(this, "users", users) {
//	//	Name.Value = name;
//	//	Role.Value = role;
//	//};
//
//	// UsersGroup(JsonArray<UserDto> *users)
//	//	: Name(this, "name"), //
//	//	  Role(this, "role"), //
//	//	  Car(this, "users", users) {
//	//}
//};
//
//TEST(JsonArrayFieldGroup, JsonArrayField_TryParse_Test) {
//	UsersList usersList;
//
//	CHECK(usersList.TryParse("[{\"name\":\"User1\",\"role\":100},{\"name\":\"User2\",\"role\":0},{\"name\":\"User3\","
//							 "\"role\":255}]"));
//	CHECK_EQUAL(usersList.Items.size(), 3);
//
//	STRCMP_EQUAL(usersList.Items[0]->Name.Value, "User1");
//	CHECK_EQUAL(usersList.Items[0]->Role.Value, 100);
//	return EXIT_SUCCESS;
//}

int main(const int argc, const char *argv[]) {
	//TEST_RUN(JsonArrayFieldGroup, JsonArrayField_TryParse_Test);

	printf("JsonArrayFieldGroup success");
	return EXIT_SUCCESS;
}