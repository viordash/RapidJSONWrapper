
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

typedef enum TUserRole { uAdmin, uViewer };

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

class GoodsDto : public JsonObject {
  public:
	JsonField<int> Id;
	JsonField<uint32_t> Created;
	JsonField<char *> Group;
	JsonField<char *> Name;
	JsonField<float> Price;
	JsonField<double> Quantity;
	JsonField<bool, true> Deleted;

	GoodsDto(int id, uint32_t created, const char *group, const char *name, float price, double quantity, bool deleted) : GoodsDto() {
		Id.SetValue(id);
		Created.SetValue(created);
		Group.SetValue(group);
		Name.SetValue(name);
		Price.SetValue(price);
		Quantity.SetValue(quantity);
		Deleted.SetValue(deleted);
	};

	GoodsDto()
		: Id(this, "Id"),			  //
		  Created(this, "Created"),	  //
		  Group(this, "Group"),		  //
		  Name(this, "Name"),		  //
		  Price(this, "Price"),		  //
		  Quantity(this, "Quantity"), //
		  Deleted(this, "Deleted") {
	}
};

TEST(JsonObjectTestsGroup, JsonObject_Parse_Test) {
	GoodsDto goods;

	CHECK(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));

	CHECK_EQUAL(goods.Id.Value, 1);
	CHECK_EQUAL(goods.Created.Value, 1657052045);
	STRCMP_EQUAL(goods.Group.Value, "Vegetables");
	STRCMP_EQUAL(goods.Name.Value, "Tomato");
	CHECK_EQUAL(goods.Price.Value, 123.25);
	CHECK_EQUAL(goods.Quantity.Value, 165.052045);
	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_Test);

	return EXIT_SUCCESS;
}