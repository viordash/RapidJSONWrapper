
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

	UserDto(const char *name, TUserRole role)
		: Name(this, "name", name), //
		  Role(this, "role", role){};

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
	JsonField<char *, true> StoreName;

	GoodsDto(int id, uint32_t created, const char *group, const char *name, float price, double quantity, bool deleted = false, const char *storeName = "")
		: Id(this, "Id", id),					//
		  Created(this, "Created", created),	//
		  Group(this, "Group", group),			//
		  Name(this, "Name", name),				//
		  Price(this, "Price", price),			//
		  Quantity(this, "Quantity", quantity), //
		  Deleted(this, "Deleted", deleted),	//
		  StoreName(this, "StoreName", storeName) {
	};

	GoodsDto()
		: Id(this, "Id"),			  //
		  Created(this, "Created"),	  //
		  Group(this, "Group"),		  //
		  Name(this, "Name"),		  //
		  Price(this, "Price"),		  //
		  Quantity(this, "Quantity"), //
		  Deleted(this, "Deleted"),	  //
		  StoreName(this, "StoreName") {
	}
};

TEST(JsonObjectTestsGroup, JsonObject_Parse_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));

	CHECK_EQUAL(goods.Id.Value, 1);
	CHECK_EQUAL(goods.Created.Value, 1657052045);
	STRCMP_EQUAL(goods.Group.Value, "Vegetables");
	STRCMP_EQUAL(goods.Name.Value, "Tomato");
	CHECK_EQUAL(goods.Price.Value, 123.25);
	CHECK_EQUAL(goods.Quantity.Value, 165.052045);
	CHECK_EQUAL(goods.Deleted.Value, false);
	STRCMP_EQUAL(goods.StoreName.Value, "");

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052046,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
							  "\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_EQUAL(goods.Created.Value, 1657052046);

	CHECK_TRUE(goods.TryParse("     \r\n    \t   "
							  "{\"Id\":1,\"Created\":1657052047,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
							  "\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_EQUAL(goods.Created.Value, 1657052047);
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Optionaly_Fields_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryParse(
		"{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,\"Deleted\":true}"));
	CHECK_EQUAL(goods.Id.Value, 1);
	CHECK_EQUAL(goods.Created.Value, 1657052045);
	STRCMP_EQUAL(goods.Group.Value, "Vegetables");
	STRCMP_EQUAL(goods.Name.Value, "Tomato");
	CHECK_EQUAL(goods.Price.Value, 123.25);
	CHECK_EQUAL(goods.Quantity.Value, 165.052045);
	CHECK_EQUAL(goods.Deleted.Value, true);
	STRCMP_EQUAL(goods.StoreName.Value, "");

	CHECK_TRUE(goods.TryParse(
		"{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,\"StoreName\":\"Store #1\"}"));
	CHECK_EQUAL(goods.Deleted.Value, false);
	STRCMP_EQUAL(goods.StoreName.Value, "Store #1");

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
							  "\"Deleted\":true,\"StoreName\":\"Store #2\"}"));
	CHECK_EQUAL(goods.Deleted.Value, true);
	STRCMP_EQUAL(goods.StoreName.Value, "Store #2");

	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_Error_Test) {
	GoodsDto goods;
	CHECK_FALSE(goods.TryParse("{\"Id\":1  \"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryParse("\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045"));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":}"));
	CHECK_FALSE(goods.TryParse("     \r\n some text   \t   "
							   "{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
							   "\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":} some text"));
	CHECK_FALSE(goods.TryParse(NULL, 1));

	CHECK_EQUAL(goods.Id.Value, 0);
	CHECK_EQUAL(goods.Created.Value, 0);
	STRCMP_EQUAL(goods.Group.Value, "");
	STRCMP_EQUAL(goods.Name.Value, "");
	CHECK_EQUAL(goods.Price.Value, 0.0);
	CHECK_EQUAL(goods.Quantity.Value, 0.0);
	CHECK_EQUAL(goods.Deleted.Value, false);
	STRCMP_EQUAL(goods.StoreName.Value, "");
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Reordered_Fields_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryParse("{\"Created\":1657052045,\"Group\":\"Vegetables\",\"Id\":1,\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_EQUAL(goods.Created.Value, 1657052045);
	CHECK_TRUE(goods.TryParse("{\"Created\":1657052046,\"Price\":123.25,\"Group\":\"Vegetables\",\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045}"));
	CHECK_EQUAL(goods.Created.Value, 1657052046);
	CHECK_TRUE(goods.TryParse(
		"{\"Created\":1657052047,\"Price\":123.25,\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045,\"StoreName\":\"Store #1\",\"Group\":\"Vegetables\"}"));
	CHECK_EQUAL(goods.Created.Value, 1657052047);
	CHECK_TRUE(
		goods.TryParse("{\"Deleted\":true, \"Created\":1657052048,\"Price\":123.25,\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045,\"StoreName\":\"Store "
					   "#1\",\"Group\":\"Vegetables\"}"));

	CHECK_EQUAL(goods.Id.Value, 1);
	CHECK_EQUAL(goods.Created.Value, 1657052048);
	STRCMP_EQUAL(goods.Group.Value, "Vegetables");
	STRCMP_EQUAL(goods.Name.Value, "Tomato");
	CHECK_EQUAL(goods.Price.Value, 123.25);
	CHECK_EQUAL(goods.Quantity.Value, 165.052045);
	CHECK_EQUAL(goods.Deleted.Value, true);
	STRCMP_EQUAL(goods.StoreName.Value, "Store #1");
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_And_Length_Defined_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 103));
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 2000));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 102));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 0));

	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Nullable_Values_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":null,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_EQUAL(goods.Created.Value, 0);
	CHECK_EQUAL(goods.Price.Value, 123.25);

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":null,\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	STRCMP_EQUAL(goods.Group.Value, "");
	CHECK_EQUAL(goods.Price.Value, 123.25);

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":null}"));
	CHECK_EQUAL(goods.Quantity.Value, 0);
	CHECK_EQUAL(goods.Price.Value, 123.25);

	CHECK_TRUE(goods.TryParse("{\"Id\":null,\"Created\":null,\"Group\":null,\"Name\":null,\"Price\":null,\"Quantity\":null}"));
	CHECK_EQUAL(goods.Id.Value, 0);
	CHECK_EQUAL(goods.Created.Value, 0);
	STRCMP_EQUAL(goods.Group.Value, "");
	STRCMP_EQUAL(goods.Name.Value, "");
	CHECK_EQUAL(goods.Price.Value, 0.0);
	CHECK_EQUAL(goods.Quantity.Value, 0.0);
	CHECK_EQUAL(goods.Deleted.Value, false);
	STRCMP_EQUAL(goods.StoreName.Value, "");
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Begin_End_Stages_Test) {
	GoodsDto goods;
	auto doc = goods.BeginTryParse("{\"Id\":1,\"Created\":1657052048,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}");

	CHECK(doc != NULL);
	CHECK_EQUAL(goods.Created.Value, 1657052048);
	STRCMP_EQUAL(goods.Group.Value, "Vegetables");
	goods.EndTryParse(doc);
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_WriteTo_Test) {
	char buffer[2048];
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	goods.WriteTo(buffer, sizeof(buffer));

	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"Group\":\"group\",\"Name\":\"name\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,"
						 "\"StoreName\":\"storeName\"}");
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_WriteTo_With_Limited_Buffer_Test) {
	char buffer[32];
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	goods.WriteTo(buffer, sizeof(buffer));

	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"G");
	return EXIT_SUCCESS;
}

static void *TestParent = NULL;
static char *TestAsyncBuffer = NULL;
static void OnReady(void *parent, const char *json, int size) {
	TestParent = parent;
	TestAsyncBuffer = new char[size + 1];
	memcpy(TestAsyncBuffer, json, size);
	TestAsyncBuffer[size] = 0;
}

TEST(JsonObjectTestsGroup, JsonObject_WriteTo_Async_Test) {
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2);
	goods.WriteToAsync((void *)987654321, OnReady);

	CHECK_EQUAL(TestParent, (void *)987654321);
	STRCMP_EQUAL(TestAsyncBuffer, "{\"Id\":2,\"Created\":1657052789,\"Group\":\"group\",\"Name\":\"name\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,"
								  "\"StoreName\":\"\"}");
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Equals_Test) {
	GoodsDto goods1(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	GoodsDto goods2(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	CHECK_TRUE(goods1.Equals(&goods2));
	CHECK_TRUE(goods2.Equals(&goods1));

	goods2.Created.Value = goods2.Created.Value + 1;
	CHECK_FALSE(goods1.Equals(&goods2));
	CHECK_FALSE(goods2.Equals(&goods1));

	UserDto user("name", TUserRole::uViewer);
	CHECK_FALSE(user.Equals(&goods1));
	CHECK_FALSE(goods1.Equals(&user));
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_GetSize_Test) {
	GoodsDto goods;
	CHECK_EQUAL(goods.GetSize(), 99);
	goods.Group.Value = "1";
	CHECK_EQUAL(goods.GetSize(), 100);
	goods.Id.Value = 1;
	CHECK_EQUAL(goods.GetSize(), 100);
	goods.Id.Value = 10;
	CHECK_EQUAL(goods.GetSize(), 101);
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Reset_Test) {
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2);
	goods.Reset();
	CHECK_EQUAL(goods.Id.Value, 0);
	CHECK_EQUAL(goods.Created.Value, 0);
	STRCMP_EQUAL(goods.Group.Value, "");
	STRCMP_EQUAL(goods.Name.Value, "");
	CHECK_EQUAL(goods.Price.Value, 0.0);
	CHECK_EQUAL(goods.Quantity.Value, 0.0);
	CHECK_EQUAL(goods.Deleted.Value, false);
	STRCMP_EQUAL(goods.StoreName.Value, "");

	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_CloneFrom_Test) {
	GoodsDto goods1(2, 1657052100, "group0", "name0", 580.25, 480.2, false, "storeName0");
	GoodsDto goods2(100, 1657052800, "group1", "name1", 58.25, 48.2, true, "storeName1");
	goods1.CloneFrom(&goods2);

	CHECK_EQUAL(goods1.Id.Value, 100);
	CHECK_EQUAL(goods1.Created.Value, 1657052800);
	STRCMP_EQUAL(goods1.Group.Value, "group1");
	STRCMP_EQUAL(goods1.Name.Value, "name1");
	CHECK_EQUAL(goods1.Price.Value, 58.25);
	CHECK_EQUAL(goods1.Quantity.Value, 48.2);
	CHECK_EQUAL(goods1.Deleted.Value, true);
	STRCMP_EQUAL(goods1.StoreName.Value, "storeName1");

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Optionaly_Fields_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_Error_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Reordered_Fields_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_And_Length_Defined_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Nullable_Values_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Begin_End_Stages_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_WriteTo_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_WriteTo_With_Limited_Buffer_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_WriteTo_Async_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Equals_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_GetSize_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Reset_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_CloneFrom_Test);

	printf("JsonObjectTestsGroup success");
	return EXIT_SUCCESS;
}