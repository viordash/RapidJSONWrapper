
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

typedef enum { uAdmin, uViewer } TUserRole;

class UserDto : public JsonObject {
  public:
	JsonField<char *> Name;
	JsonField<uint32_t, true> Role;

	UserDto(const char *name, TUserRole role) : UserDto() {
		Name.SetValue(name);
		Role.SetValue(role);
	};

	UserDto()
		: Name(this, "name"), //
		  Role(this, "role") {
	}
};

TEST(JsonObjectFieldGroup, JsonObjectField_TryParse_Test) {
	JsonFieldsContainer container;
	UserDto userDto;
	JsonField<JsonObject *> testable(&container, "user", &userDto);

	rapidjson::Document doc;
	doc.Parse("{\"parent1\":\"user1\""
			  ",\"user\":{\"name\":\"Joe Doe\",\"role\":1}}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(((UserDto *)testable.Object)->Name.Value, "Joe Doe");
	CHECK_EQUAL(((UserDto *)testable.Object)->Role.Value, TUserRole::uViewer);
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_TryParse_With_Null_Or_Empty_Object_Test) {
	JsonFieldsContainer container;
	UserDto userDto;
	JsonField<JsonObject *> testable(&container, "user", &userDto);

	rapidjson::Document doc;
	doc.Parse("{\"parent1\":\"user1\",\"user\":null}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(((UserDto *)testable.Object)->Name.Value, "");
	CHECK_EQUAL(((UserDto *)testable.Object)->Role.Value, 0);

	doc.Parse("{\"parent1\":\"user1\",\"user\":{}}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(((UserDto *)testable.Object)->Name.Value, "");
	CHECK_EQUAL(((UserDto *)testable.Object)->Role.Value, 0);
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_WriteTo_Test) {
	JsonFieldsContainer container;
	UserDto userDto("Joe Doe", TUserRole::uViewer);
	JsonField<JsonObject *> testable(&container, "user", &userDto);

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteTo(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	STRCMP_EQUAL(jsonStr, "{\"user\":{\"name\":\"Joe Doe\",\"role\":1}}");
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_Size_Test) {
	JsonFieldsContainer container;
	UserDto userDto("", TUserRole::uViewer);
	JsonField<JsonObject *> testable(&container, "user", &userDto);
	CHECK_EQUAL(testable.GetSize(), 20);
	userDto.Name.SetValue("J");
	CHECK_EQUAL(testable.GetSize(), 21);
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_EqualTo_Test) {
	JsonFieldsContainer container;
	UserDto user1("user1", TUserRole::uViewer);
	UserDto user2("user2", TUserRole::uAdmin);

	JsonField<JsonObject *> testable1(&container, "user", &user1);
	JsonField<JsonObject *> testable2(&container, "user", &user2);
	CHECK_FALSE(testable1.EqualTo(&testable2));
	CHECK_FALSE(testable2.EqualTo(&testable1));

	user1.Role.SetValue(TUserRole::uAdmin);
	user2.Name.SetValue("user1");
	CHECK_TRUE(testable1.EqualTo(&testable2));
	CHECK_TRUE(testable2.EqualTo(&testable1));

	JsonField<JsonObject *> testable3(&container, "testStringWrong", &user2);
	CHECK_FALSE(testable3.EqualTo(&testable2));
	CHECK_FALSE(testable2.EqualTo(&testable3));
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_CloneFrom_Test) {
	JsonFieldsContainer container;
	UserDto user1("user1", TUserRole::uViewer);
	UserDto user2("user2", TUserRole::uAdmin);

	JsonField<JsonObject *> testable1(&container, "user", &user1);
	JsonField<JsonObject *> testable2(&container, "user", &user2);
	testable1.CloneFrom(&testable2);
	STRCMP_EQUAL(((UserDto *)testable1.Object)->Name.Value, "user2");
	CHECK_EQUAL(((UserDto *)testable1.Object)->Role.Value, TUserRole::uAdmin);

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_TryParse_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_TryParse_With_Null_Or_Empty_Object_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_WriteTo_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_Size_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_EqualTo_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_CloneFrom_Test);

	printf("JsonObjectFieldGroup success");
	return EXIT_SUCCESS;
}