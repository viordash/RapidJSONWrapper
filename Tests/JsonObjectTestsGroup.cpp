
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Json.h"
#include "TestsCommon.h"

typedef enum { uAdmin, uViewer } TUserRole;

class UserDto : public JsonObject {
  public:
	JsonValue<char *> Name;
	JsonValue<uint32_t, true> Role;

	UserDto(char *name, TUserRole role)
		: Name(this, "name", name), //
		  Role(this, "role", role){};

	UserDto()
		: Name(this, "name"), //
		  Role(this, "role") {}
};

class GoodsDto : public JsonObject {
  public:
	JsonValue<int> Id;
	JsonValue<uint32_t> Created;
	JsonValue<char *> Group;
	JsonValue<char *> Name;
	JsonValue<float> Price;
	JsonValue<double> Quantity;
	JsonValue<bool, true> Deleted;
	JsonValue<char *, true> StoreName;

	GoodsDto(int id, uint32_t created, char *group, char *name, float price, double quantity, bool deleted = false, char *storeName = "")
		: Id(this, "Id", id),					//
		  Created(this, "Created", created),	//
		  Group(this, "Group", group),			//
		  Name(this, "Name", name),				//
		  Price(this, "Price", price),			//
		  Quantity(this, "Quantity", quantity), //
		  Deleted(this, "Deleted", deleted),	//
		  StoreName(this, "StoreName", storeName){};

	GoodsDto()
		: Id(this, "Id"),			  //
		  Created(this, "Created"),	  //
		  Group(this, "Group"),		  //
		  Name(this, "Name"),		  //
		  Price(this, "Price"),		  //
		  Quantity(this, "Quantity"), //
		  Deleted(this, "Deleted"),	  //
		  StoreName(this, "StoreName") {}
};

class GoodsList : public JsonArray<GoodsDto *> {
  public:
	bool Validate(GoodsDto *item) { return item->Validate(); }
};

class OrderDto : public JsonObject {
  public:
	JsonValue<char *> Supplier;
	JsonValue<uint32_t, true> DateTime;
	JsonValue<JsonArrayBase *> Goods;
	JsonValue<JsonObject *> User;
	GoodsList goodsList;
	UserDto userDto;

	OrderDto(char *supplier, uint32_t dateTime, char *userName, TUserRole userRole)
		: Supplier(this, "supplier", supplier), //
		  DateTime(this, "dateTime", dateTime), //
		  Goods(this, "goods", &goodsList),		//
		  userDto(userName, userRole),			//
		  User(this, "user", &userDto){};

	OrderDto()
		: Supplier(this, "supplier"),		//
		  DateTime(this, "dateTime"),		//
		  Goods(this, "goods", &goodsList), //
		  User(this, "user", &userDto) {}
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

TEST(JsonObjectTestsGroup, Complex_JsonObject_TryParse_Test) {
	JsonFieldsContainer container;
	OrderDto order;

	CHECK(order.TryParse("{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
						 "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":3,\"Created\":1657054789,\"Group\":\"Keyboards\",\"Name\":\"K3-100\",\"Price\":"
						 "258.25,\"Quantity\":548.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":4,\"Created\":1657055789,\"Group\":\"Keyboards\",\"Name\":\"K4-100\","
						 "\"Price\":358.25,\"Quantity\":648.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_EQUAL(order.goodsList.Items.size(), 3);
	CHECK_EQUAL(order.goodsList.Items[0]->Created.Value, 1657052789);
	STRCMP_EQUAL(order.goodsList.Items[2]->Name.Value, "K4-100");
	STRCMP_EQUAL(order.userDto.Name.Value, "Joe Doe");

	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Optionaly_Fields_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,\"Deleted\":true}"));
	CHECK_EQUAL(goods.Id.Value, 1);
	CHECK_EQUAL(goods.Created.Value, 1657052045);
	STRCMP_EQUAL(goods.Group.Value, "Vegetables");
	STRCMP_EQUAL(goods.Name.Value, "Tomato");
	CHECK_EQUAL(goods.Price.Value, 123.25);
	CHECK_EQUAL(goods.Quantity.Value, 165.052045);
	CHECK_EQUAL(goods.Deleted.Value, true);
	STRCMP_EQUAL(goods.StoreName.Value, "");

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,\"StoreName\":\"Store #1\"}"));
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
	CHECK_TRUE(goods.TryParse("{\"Created\":1657052047,\"Price\":123.25,\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045,\"StoreName\":\"Store #1\",\"Group\":\"Vegetables\"}"));
	CHECK_EQUAL(goods.Created.Value, 1657052047);
	CHECK_TRUE(goods.TryParse("{\"Deleted\":true, \"Created\":1657052048,\"Price\":123.25,\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045,\"StoreName\":\"Store "
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
	CHECK_EQUAL(goods.WriteToString(buffer, sizeof(buffer)), 129);

	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"Group\":\"group\",\"Name\":\"name\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,"
						 "\"StoreName\":\"storeName\"}");
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_WriteTo_With_Limited_Buffer_Test) {
	char buffer[32];
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	CHECK_EQUAL(goods.WriteToString(buffer, sizeof(buffer)), 31);

	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"G");
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

TEST(JsonObjectTestsGroup, JsonObject_WriteTo_Async_Test) {
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2);
	goods.DirectWriteTo((void *)987654321, OnReady);

	CHECK_EQUAL(TestParent, (void *)987654321);
	STRCMP_EQUAL(DirectWriteTestBuffer, "{\"Id\":2,\"Created\":1657052789,\"Group\":\"group\",\"Name\":\"name\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,"
										"\"StoreName\":\"\"}");
	delete[] DirectWriteTestBuffer;
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, Complex_JsonObject_WriteTo_Test) {
	JsonFieldsContainer container;

	OrderDto orderDto("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));
	orderDto.goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2));
	orderDto.goodsList.Add(new GoodsDto(4, 1657055789, "Keyboards", "K4-100", 358.25, 648.2));

	rapidjson::Document doc;
	doc.SetObject();

	orderDto.WriteToDoc(&doc);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	const char *jsonStr = buffer.GetString();
	STRCMP_EQUAL(jsonStr, "{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
						  "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":2,\"Created\":1657053789,\"Group\":\"Keyboards\",\"Name\":\"K2-100\",\"Price\":158."
						  "25,\"Quantity\":448.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":3,\"Created\":1657054789,\"Group\":\"Keyboards\",\"Name\":\"K3-100\",\"Price\":"
						  "258.25,\"Quantity\":548.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":4,\"Created\":1657055789,\"Group\":\"Keyboards\",\"Name\":\"K4-100\","
						  "\"Price\":358.25,\"Quantity\":648.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}");
	return EXIT_SUCCESS;
}

TEST(JsonObjectTestsGroup, JsonObject_Equals_Test) {
	JsonFieldsContainer container;

	OrderDto orderDto1("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto1.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto1.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	OrderDto orderDto2("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto2.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto2.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	CHECK_TRUE(orderDto1 == orderDto2);
	CHECK_FALSE(orderDto1 != orderDto2);

	return EXIT_SUCCESS;
}

int main(const int argc, const char *argv[]) {
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_Test);
	TEST_RUN(JsonObjectTestsGroup, Complex_JsonObject_TryParse_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Optionaly_Fields_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_Error_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Reordered_Fields_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_And_Length_Defined_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Nullable_Values_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Parse_With_Begin_End_Stages_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_WriteTo_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_WriteTo_With_Limited_Buffer_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_WriteTo_Async_Test);
	TEST_RUN(JsonObjectTestsGroup, Complex_JsonObject_WriteTo_Test);
	TEST_RUN(JsonObjectTestsGroup, JsonObject_Equals_Test);

	printf("JsonObjectTestsGroup success");
	return EXIT_SUCCESS;
}