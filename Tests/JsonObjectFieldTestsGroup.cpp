
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

	doc.Parse("{\"parent1\":\"user1\",\"user\":null}");
	CHECK(testable.TryParse(&doc));
	// STRCMP_EQUAL(testable.Value, "");
	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonObjectFieldGroup, JsonObjectField_TryParse_Test);

	printf("JsonObjectFieldGroup success");
	return EXIT_SUCCESS;
}