
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include "JsonWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(JsonObjectTestsGroup){void setup(){} void teardown(){}};

typedef enum { uAdmin, uViewer } TUserRole;

class UserDto : public JsonObject {
  public:
	JsonValue<char *> Name;
	JsonCommonValue<uint32_t> Role;

	UserDto(char *name = {}, TUserRole role = {})
		: Name(this, "name", name), //
		  Role(this, "role", role){};
};

class GoodsDto : public JsonObject {
  public:
	JsonValue<int> Id;
	JsonValue<uint32_t> Created;
	JsonValue<char *> Group;
	JsonValue<char *> Name;
	JsonValue<float> Price;
	JsonValue<double> Quantity;
	JsonCommonValue<bool> Deleted;
	JsonCommonValue<char *> StoreName;

	GoodsDto(int id = {}, uint32_t created = {}, char *group = {}, char *name = {}, float price = {}, double quantity = {}, bool deleted = {}, char *storeName = {})
		: Id(this, "Id", id),					//
		  Created(this, "Created", created),	//
		  Group(this, "Group", group),			//
		  Name(this, "Name", name),				//
		  Price(this, "Price", price),			//
		  Quantity(this, "Quantity", quantity), //
		  Deleted(this, "Deleted", deleted),	//
		  StoreName(this, "StoreName", storeName){};
};

class GoodsList : public JsonObjectsArray {
  public:
	bool Validate(JsonObject *item) override { return item->Validate(); }
	JsonObject *CreateItem() override { return new GoodsDto(); }
};

class OrderDto : public JsonObject {
  public:
	JsonValue<char *> Supplier;
	JsonCommonValue<uint32_t> DateTime;
	JsonValue<JsonArrayBase *> Goods;
	JsonValue<JsonObject *> User;
	GoodsList goodsList;
	UserDto userDto;

	OrderDto(char *supplier = {}, uint32_t dateTime = {}, char *userName = {}, TUserRole userRole = {})
		: Supplier(this, "supplier", supplier), //
		  DateTime(this, "dateTime", dateTime), //
		  Goods(this, "goods", &goodsList),		//
		  userDto(userName, userRole),			//
		  User(this, "user", &userDto){};
};

class OrdersList : public JsonObjectsArray {
  public:
	bool Validate(JsonObject *item) override { return item->Validate(); }
	JsonObject *CreateItem() override { return new OrderDto(); }
};

class CustomerDto : public JsonObject {
  public:
	JsonValue<uint64_t> Id;
	JsonValue<char *> Name;
	JsonCommonValue<TJsonRawData> Blob;
	JsonValue<JsonArrayBase *> Orders;
	OrdersList ordersList;

	CustomerDto(uint64_t id = {}, char *name = {}, TJsonRawData blob = {})
		: Id(this, "id", id),		//
		  Name(this, "name", name), //
		  Blob(this, "blob", blob), //
		  Orders(this, "orders", &ordersList){};
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
	STRCMP_EQUAL(goods.StoreName.Value, NULL);

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052046,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
							  "\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_EQUAL(goods.Created.Value, 1657052046);

	CHECK_TRUE(goods.TryParse("     \r\n    \t   "
							  "{\"Id\":1,\"Created\":1657052047,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
							  "\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_EQUAL(goods.Created.Value, 1657052047);
}

TEST(JsonObjectTestsGroup, JsonObject_Complex_TryParse_Test) {
	OrderDto order;

	CHECK(order.TryParse("{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
						 "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":3,\"Created\":1657054789,\"Group\":\"Keyboards\",\"Name\":\"K3-100\",\"Price\":"
						 "258.25,\"Quantity\":548.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":4,\"Created\":1657055789,\"Group\":\"Keyboards\",\"Name\":\"K4-100\","
						 "\"Price\":358.25,\"Quantity\":648.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_EQUAL(order.goodsList.Size(), 3);
	CHECK_EQUAL(order.goodsList.Item<GoodsDto *>(0)->Created.Value, 1657052789);
	STRCMP_EQUAL(order.goodsList.Item<GoodsDto *>(2)->Name.Value, "K4-100");
	STRCMP_EQUAL(order.userDto.Name.Value, "Joe Doe");
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
	CHECK_EQUAL(goods.Deleted.Presented(), true);
	CHECK_EQUAL(goods.Deleted.Value, true);
	STRCMP_EQUAL(goods.StoreName.Value, NULL);

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,\"StoreName\":\"Store #1\"}"));
	CHECK_EQUAL(goods.Deleted.Presented(), false);
	STRCMP_EQUAL(goods.StoreName.Value, "Store #1");

	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
							  "\"Deleted\":true,\"StoreName\":\"Store #2\"}"));
	CHECK_EQUAL(goods.Deleted.Value, true);
	STRCMP_EQUAL(goods.StoreName.Value, "Store #2");
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
	STRCMP_EQUAL(goods.Group.Value, NULL);
	STRCMP_EQUAL(goods.Name.Value, NULL);
	CHECK_EQUAL(goods.Price.Value, 0.0);
	CHECK_EQUAL(goods.Quantity.Value, 0.0);
	CHECK_EQUAL(goods.Deleted.Value, false);
	STRCMP_EQUAL(goods.StoreName.Value, NULL);
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
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_And_Length_Defined_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 103));
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 2000));
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 0));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 102));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 1));
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Nullable_Values_Test) {
	GoodsDto goods;
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":null,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_TRUE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":null,\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":null}"));
	CHECK_FALSE(goods.TryParse("{\"Id\":null,\"Created\":null,\"Group\":null,\"Name\":null,\"Price\":null,\"Quantity\":null}"));

	CustomerDto customerDto;
	CHECK_TRUE(
		customerDto.TryParse("{\"id\":123,\"name\":\"sh\",\"blob\":null,\"orders\":[{\"supplier\":\"Dell1\",\"dateTime\":1657058001,\"goods\":[{\"Id\":1,\"Created\":1657052789,"
							 "\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}]}"));
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Begin_End_Stages_Test) {
	GoodsDto goods;
	auto doc = goods.BeginTryParse("{\"Id\":1,\"Created\":1657052048,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}");

	CHECK(doc != NULL);
	CHECK_EQUAL(goods.Created.Value, 1657052048);
	STRCMP_EQUAL(goods.Group.Value, "Vegetables");
	goods.EndTryParse(doc);
}

TEST(JsonObjectTestsGroup, JsonObject_WriteTo_Test) {
	char buffer[2048];
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	CHECK_EQUAL(goods.WriteToString(buffer, sizeof(buffer)), 129);

	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"Group\":\"group\",\"Name\":\"name\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,"
						 "\"StoreName\":\"storeName\"}");
}

TEST(JsonObjectTestsGroup, JsonObject_WriteTo_With_Limited_Buffer_Test) {
	char buffer[32];
	GoodsDto goods(2, 1657052789, "group", "name", 58.25, 48.2, false, "storeName");
	CHECK_EQUAL(goods.WriteToString(buffer, sizeof(buffer)), 31);

	STRCMP_EQUAL(buffer, "{\"Id\":2,\"Created\":1657052789,\"G");
}

static void *TestParent = NULL;
static char *DirectWriteTestBuffer = NULL;
static void OnReady(void *parent, const char *json, size_t size) {
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
										"\"StoreName\":null}");
	delete[] DirectWriteTestBuffer;
}

TEST(JsonObjectTestsGroup, JsonObject_Complex_WriteTo_Test) {
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
						  "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":null},{\"Id\":2,\"Created\":1657053789,\"Group\":\"Keyboards\",\"Name\":\"K2-100\",\"Price\":158."
						  "25,\"Quantity\":448.2,\"Deleted\":false,\"StoreName\":null},{\"Id\":3,\"Created\":1657054789,\"Group\":\"Keyboards\",\"Name\":\"K3-100\",\"Price\":"
						  "258.25,\"Quantity\":548.2,\"Deleted\":false,\"StoreName\":null},{\"Id\":4,\"Created\":1657055789,\"Group\":\"Keyboards\",\"Name\":\"K4-100\","
						  "\"Price\":358.25,\"Quantity\":648.2,\"Deleted\":false,\"StoreName\":null}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}");
}

TEST(JsonObjectTestsGroup, JsonObject_Equals_Test) {
	OrderDto orderDto1("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto1.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto1.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	OrderDto orderDto2("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto2.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto2.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	CHECK_TRUE(orderDto1 == orderDto2);
	CHECK_FALSE(orderDto1 != orderDto2);
	CHECK_TRUE(orderDto1.Equals(&orderDto2));
	orderDto1.DateTime.Value = orderDto1.DateTime.Value + 1;
	CHECK_TRUE(orderDto1 != orderDto2);
	CHECK_FALSE(orderDto1 == orderDto2);
	CHECK_FALSE(orderDto1.Equals(&orderDto2));
}

TEST(JsonObjectTestsGroup, JsonObject_Clone_Test) {
	auto orderDto1 = new OrderDto("Dell", 1657058000, "Joe Doe", TUserRole::uViewer);
	orderDto1->goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	orderDto1->goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));

	OrderDto orderDto2;

	orderDto1->CloneTo(&orderDto2);
	delete orderDto1;

	STRCMP_EQUAL(orderDto2.Supplier.Value, "Dell");
	CHECK_EQUAL(orderDto2.DateTime.Value, 1657058000);
	CHECK_EQUAL(orderDto2.goodsList.Size(), 2);
	CHECK_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(0)->Created.Value, 1657052789);
	STRCMP_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(1)->Name.Value, "K2-100");
	STRCMP_EQUAL(orderDto2.userDto.Name.Value, "Joe Doe");
}

TEST(JsonObjectTestsGroup, JsonObject_With_Blob_Field_Test) {
	const int pictureSize = 1'000'0000;
	uint8_t *picture = new uint8_t[pictureSize];
	for (size_t i = 0; i < pictureSize; i++) { picture[i] = 'A' + (i % 58); }

	auto customerDto1 = new CustomerDto(1234567890123456789LL, "Viordash", {picture, pictureSize});
	CHECK(customerDto1->ordersList.Add(new OrderDto("Dell1", 1657058001, "Joe Doe", TUserRole::uViewer)));
	CHECK(customerDto1->ordersList.Add(new OrderDto("Dell2", 1657058002, "Joe Doe", TUserRole::uViewer)));
	auto orderDto1 = customerDto1->ordersList.Item<OrderDto *>(0);
	CHECK(orderDto1->goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2)));
	CHECK(orderDto1->goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2)));
	CHECK(orderDto1->goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2)));
	auto orderDto2 = customerDto1->ordersList.Item<OrderDto *>(1);
	CHECK(orderDto2->goodsList.Add(new GoodsDto(100, 1007052789, "Mouse", "M1-100", 8.25, 18.2)));
	CHECK(orderDto2->goodsList.Add(new GoodsDto(200, 2007053789, "Mouse", "M2-100", 48.25, 28.2)));

	auto size = customerDto1->DirectWriteTo(0, OnReady);
	CHECK_EQUAL(size, 10173299);
	delete customerDto1;
	delete[] picture;

	CustomerDto customerDto2;
	auto doc = customerDto2.BeginTryParse(DirectWriteTestBuffer, size);
	CHECK(doc != NULL);

	CHECK_EQUAL(customerDto2.Id.Value, 1234567890123456789LL);
	STRCMP_EQUAL(customerDto2.Name.Value, "Viordash");
	CHECK_EQUAL(customerDto2.ordersList.Size(), 2);
	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(0)->goodsList.Size(), 3);
	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(1)->goodsList.Size(), 2);
	CHECK_EQUAL(((TJsonRawData)customerDto2.Blob.Value).Size, pictureSize);
	CHECK_FALSE(((TJsonRawData)customerDto2.Blob.Value).Data == picture);
	for (size_t i = 0; i < pictureSize; i++) { CHECK_EQUAL(((TJsonRawData)customerDto2.Blob.Value).Data[i], 'A' + (i % 58)); }
	customerDto2.EndTryParse(doc);

	delete[] DirectWriteTestBuffer;
}

TEST(JsonObjectTestsGroup, JsonObject_Optional_Values_Presented_Test) {
	OrderDto order;

	CHECK_FALSE(order.DateTime.Presented());

	CHECK(order.TryParse("{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(order.DateTime.Presented());

	CHECK(order.TryParse("{\"supplier\":\"Dell\",\"goods\":[],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_FALSE(order.DateTime.Presented());
}

class OptionalObjectDto : public JsonObject {
  public:
	JsonValue<int> Id;
	JsonCommonValue<JsonArrayBase *> Goods;
	JsonCommonValue<JsonObject *> User;
	GoodsList goodsList;
	UserDto userDto;

	OptionalObjectDto(int id = {}, char *userName = {}, TUserRole userRole = {})
		: Id(this, "id", id),				//
		  Goods(this, "goods", &goodsList), //
		  userDto(userName, userRole),		//
		  User(this, "user", &userDto){};
};

TEST(JsonObjectTestsGroup, JsonObject_Optional_TryParse_Test) {
	OptionalObjectDto optionalObjectDto;

	CHECK_TRUE(optionalObjectDto.TryParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
										  "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryParse("{\"id\":1,\"goods\":null,\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_TRUE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
										  "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":null}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_TRUE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryParse("{\"id\":1,\"goodsOther\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
										  "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_FALSE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
										  "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"userOther\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_FALSE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());
}