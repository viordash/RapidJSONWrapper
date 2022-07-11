
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

class CarDto : public JsonObject {
  public:
	JsonField<char *> Color;
	JsonField<char *> Fabric;

	CarDto(const char *color, const char *fabric)
		: Color(this, "color", color), //
		  Fabric(this, "fabric", fabric) {
	}

	CarDto()
		: Color(this, "color"), //
		  Fabric(this, "fabric") {
	}
};

class UserCarDto : public JsonObject {
  public:
	JsonField<char *> Name;
	JsonField<uint32_t, true> Role;
	JsonField<JsonObject *> Car;
	CarDto carDto;

	UserCarDto(const char *name, TUserRole role)
		: Name(this, "name"), //
		  Role(this, "role"), //
		  Car(this, "car", &carDto) {
		Name.Value = name;
		Role.Value = role;
	};

	UserCarDto()
		: Name(this, "name"), //
		  Role(this, "role"), //
		  Car(this, "car", &carDto) {
	}
};

class UserDto : public JsonObject {
  public:
	JsonField<char *> Name;
	JsonField<uint32_t, true> Role;

	UserDto(const char *name, TUserRole role)
		: Name(this, "name", name), //
		  Role(this, "role", role) {
	}

	UserDto()
		: Name(this, "name"), //
		  Role(this, "role") {
	}
};

TEST(JsonObjectFieldGroup, JsonObjectField_TryParse_Test) {
	JsonFieldsContainer container;

	UserCarDto userCarDto;
	JsonField<JsonObject *> testable(&container, "user", &userCarDto);

	rapidjson::Document doc;
	doc.Parse("{\"parent1\":\"user1\""
			  ",\"user\":{\"name\":\"Joe Doe\",\"role\":1,\"car\":{\"color\": \"Red\",\"fabric\": \"Lada\"}}}");
	CHECK(testable.TryParse(&doc));

	STRCMP_EQUAL(userCarDto.Name.Value, "Joe Doe");
	STRCMP_EQUAL(userCarDto.carDto.Color.Value, "Red");
	CHECK_EQUAL(userCarDto.Role.Value, TUserRole::uViewer);
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_TryParse_With_Null_Or_Empty_Object_Test) {
	JsonFieldsContainer container;
	UserDto userDto;
	JsonField<JsonObject *> testable(&container, "user", &userDto);

	rapidjson::Document doc;
	doc.Parse("{\"parent1\":\"user1\",\"user\":null}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(userDto.Name.Value, "");
	CHECK_EQUAL(userDto.Role.Value, 0);

	doc.Parse("{\"parent1\":\"user1\",\"user\":{}}");
	CHECK(testable.TryParse(&doc));
	STRCMP_EQUAL(userDto.Name.Value, "");
	CHECK_EQUAL(userDto.Role.Value, 0);
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_TryParse_Field_Optional_Test) {
	rapidjson::Document doc;
	JsonFieldsContainer container;
	UserDto user;
	auto testableFieldMustExists = new JsonField<JsonObject *>(&container, "user", &user);
	doc.Parse("{\"parent1\":\"user1\""
			  ",\"otherField\":{\"name\":\"Joe Doe\",\"role\":1}}");
	CHECK_FALSE(testableFieldMustExists->TryParse(&doc));
	delete testableFieldMustExists;

	auto testableWithOptional = new JsonField<JsonObject *, true>(&container, "user", &user);
	doc.Parse("{\"parent1\":\"user1\""
			  ",\"otherField\":{\"name\":\"Joe Doe\",\"role\":1}}");
	CHECK_TRUE(testableWithOptional->TryParse(&doc));
	STRCMP_EQUAL(user.Name.Value, "");
	delete testableWithOptional;
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_WriteTo_Test) {
	JsonFieldsContainer container;
	UserDto userDto("Joe Doe", TUserRole::uViewer);
	JsonField<JsonObject *> testable(&container, "user", &userDto);

	rapidjson::Document doc;
	doc.SetObject();

	testable.WriteToDoc(&doc);

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
	userDto.Name.Value = "J";
	CHECK_EQUAL(testable.GetSize(), 21);
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_Equals_Test) {
	JsonFieldsContainer container;
	UserDto user1("user1", TUserRole::uViewer);
	UserDto user2("user2", TUserRole::uAdmin);

	JsonField<JsonObject *> testable1(&container, "user", &user1);
	JsonField<JsonObject *> testable2(&container, "user", &user2);
	CHECK_FALSE(testable1.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable1));

	user1.Role.Value = TUserRole::uAdmin;
	user2.Name.Value = "user1";
	CHECK_TRUE(testable1.Equals(&testable2));
	CHECK_TRUE(testable2.Equals(&testable1));

	JsonField<JsonObject *> testable3(&container, "testFieldWrong", &user2);
	CHECK_FALSE(testable3.Equals(&testable2));
	CHECK_FALSE(testable2.Equals(&testable3));
	return EXIT_SUCCESS;
}

TEST(JsonObjectFieldGroup, JsonObjectField_CloneFrom_Test) {
	JsonFieldsContainer container;
	UserDto user1("user1", TUserRole::uViewer);
	UserDto user2("user2", TUserRole::uAdmin);

	JsonField<JsonObject *> testable1(&container, "user", &user1);
	JsonField<JsonObject *> testable2(&container, "user", &user2);
	testable1.CloneFrom(&testable2);
	STRCMP_EQUAL(user1.Name.Value, "user2");
	CHECK_EQUAL(user1.Role.Value, TUserRole::uAdmin);

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_TryParse_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_TryParse_With_Null_Or_Empty_Object_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_TryParse_Field_Optional_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_WriteTo_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_Size_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_Equals_Test);
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_CloneFrom_Test);

	printf("JsonObjectFieldGroup success");
	return EXIT_SUCCESS;
}