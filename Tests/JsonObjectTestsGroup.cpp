
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

	UserDto(const char *name = {}, const TUserRole role = {})
		: Name(this, "name", name), //
		  Role(this, "role", role){};

	bool Validate() override { return Role.Get() < 1000; }
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

	GoodsDto(const int id = {}, uint32_t created = {}, const char *group = {}, const char *name = {}, const float price = {}, const double quantity = {}, const bool deleted = {},
			 const char *storeName = {})
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

	OrderDto(const char *supplier = {}, const uint32_t dateTime = {}, const char *userName = {}, const TUserRole userRole = {})
		: Supplier(this, "supplier", supplier), //
		  DateTime(this, "dateTime", dateTime), //
		  Goods(this, "goods", &goodsList),		//
		  userDto(userName, userRole),			//
		  User(this, "user", &userDto){};

	~OrderDto() {}
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

	CustomerDto(const uint64_t id = {}, const char *name = {}, const TJsonRawData blob = {})
		: Id(this, "id", id),		//
		  Name(this, "name", name), //
		  Blob(this, "blob", blob), //
		  Orders(this, "orders", &ordersList){};
};

class ValuesWoInstance : public JsonObject {
  public:
	ValuesWoInstance(const uint64_t id = {}, const char *name = {}, const TJsonRawData blob = {}) {
		new JsonValue<uint64_t>(this, "id", id);
		new JsonValue<char *>(this, "name", name);
		new JsonValue<TJsonRawData>(this, "blob", blob);
	};

	~ValuesWoInstance() {
		for (const auto &field : Fields) { delete field; }
	}
};

TEST(JsonObjectTestsGroup, JsonObject_Parse_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));

	CHECK_EQUAL(goods.Id.Get(), 1);
	CHECK_EQUAL(goods.Created.Get(), 1657052045);
	STRCMP_EQUAL(goods.Group.Get(), "Vegetables");
	STRCMP_EQUAL(goods.Name.Get(), "Tomato");
	CHECK_EQUAL(goods.Price.Get(), 123.25);
	CHECK_EQUAL(goods.Quantity.Get(), 165.052045);
	CHECK_EQUAL(goods.Deleted.Get(), false);
	STRCMP_EQUAL(goods.StoreName.Get(), NULL);

	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052046,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
									"\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_EQUAL(goods.Created.Get(), 1657052046);

	CHECK_TRUE(goods.TryStringParse("     \r\n    \t   "
									"{\"Id\":1,\"Created\":1657052047,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
									"\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_EQUAL(goods.Created.Get(), 1657052047);
}

TEST(JsonObjectTestsGroup, JsonObject_Complex_TryParse_Test) {
	OrderDto order;

	CHECK(order.TryStringParse("{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
							   "25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":3,\"Created\":1657054789,\"Group\":\"Keyboards\",\"Name\":\"K3-100\",\"Price\":"
							   "258.25,\"Quantity\":548.2,\"Deleted\":false,\"StoreName\":\"\"},{\"Id\":4,\"Created\":1657055789,\"Group\":\"Keyboards\",\"Name\":\"K4-100\","
							   "\"Price\":358.25,\"Quantity\":648.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_EQUAL(order.goodsList.Size(), 3);
	CHECK_EQUAL(order.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1657052789);
	STRCMP_EQUAL(order.goodsList.Item<GoodsDto *>(2)->Name.Get(), "K4-100");
	STRCMP_EQUAL(order.userDto.Name.Get(), "Joe Doe");
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Optionaly_Fields_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,\"Deleted\":true}"));
	CHECK_EQUAL(goods.Id.Get(), 1);
	CHECK_EQUAL(goods.Created.Get(), 1657052045);
	STRCMP_EQUAL(goods.Group.Get(), "Vegetables");
	STRCMP_EQUAL(goods.Name.Get(), "Tomato");
	CHECK_EQUAL(goods.Price.Get(), 123.25);
	CHECK_EQUAL(goods.Quantity.Get(), 165.052045);
	CHECK_EQUAL(goods.Deleted.Presented(), true);
	CHECK_EQUAL(goods.Deleted.Get(), true);
	STRCMP_EQUAL(goods.StoreName.Get(), NULL);

	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,\"StoreName\":\"Store #1\"}"));
	CHECK_EQUAL(goods.Deleted.Presented(), false);
	STRCMP_EQUAL(goods.StoreName.Get(), "Store #1");

	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
									"\"Deleted\":true,\"StoreName\":\"Store #2\"}"));
	CHECK_EQUAL(goods.Deleted.Get(), true);
	STRCMP_EQUAL(goods.StoreName.Get(), "Store #2");
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_Error_Test) {
	GoodsDto goods;
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1  \"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryStringParse("\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045"));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":}"));
	CHECK_FALSE(goods.TryStringParse("     \r\n some text   \t   "
									 "{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045,"
									 "\"StoreName\":\"Store #1\"}               \t  \r\n"));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":} some text"));
	CHECK_FALSE(goods.TryStringParse(NULL, 1));

	CHECK_EQUAL(goods.Id.Get(), 0);
	CHECK_EQUAL(goods.Created.Get(), 0);
	STRCMP_EQUAL(goods.Group.Get(), NULL);
	STRCMP_EQUAL(goods.Name.Get(), NULL);
	CHECK_EQUAL(goods.Price.Get(), 0.0);
	CHECK_EQUAL(goods.Quantity.Get(), 0.0);
	CHECK_EQUAL(goods.Deleted.Get(), false);
	STRCMP_EQUAL(goods.StoreName.Get(), NULL);
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Reordered_Fields_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryStringParse("{\"Created\":1657052045,\"Group\":\"Vegetables\",\"Id\":1,\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_EQUAL(goods.Created.Get(), 1657052045);
	CHECK_TRUE(goods.TryStringParse("{\"Created\":1657052046,\"Price\":123.25,\"Group\":\"Vegetables\",\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045}"));
	CHECK_EQUAL(goods.Created.Get(), 1657052046);
	CHECK_TRUE(goods.TryStringParse("{\"Created\":1657052047,\"Price\":123.25,\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045,\"StoreName\":\"Store #1\",\"Group\":\"Vegetables\"}"));
	CHECK_EQUAL(goods.Created.Get(), 1657052047);
	CHECK_TRUE(goods.TryStringParse("{\"Deleted\":true, \"Created\":1657052048,\"Price\":123.25,\"Id\":1,\"Name\":\"Tomato\",\"Quantity\":165.052045,\"StoreName\":\"Store "
									"#1\",\"Group\":\"Vegetables\"}"));

	CHECK_EQUAL(goods.Id.Get(), 1);
	CHECK_EQUAL(goods.Created.Get(), 1657052048);
	STRCMP_EQUAL(goods.Group.Get(), "Vegetables");
	STRCMP_EQUAL(goods.Name.Get(), "Tomato");
	CHECK_EQUAL(goods.Price.Get(), 123.25);
	CHECK_EQUAL(goods.Quantity.Get(), 165.052045);
	CHECK_EQUAL(goods.Deleted.Get(), true);
	STRCMP_EQUAL(goods.StoreName.Get(), "Store #1");
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_And_Length_Defined_Test) {
	GoodsDto goods;
	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 103));
	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 2000));
	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 0));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 102));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}", 1));
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Nullable_Values_Test) {
	GoodsDto goods;
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,\"Created\":null,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_TRUE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":null,\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}"));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":1,\"Created\":1657052045,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":null}"));
	CHECK_FALSE(goods.TryStringParse("{\"Id\":null,\"Created\":null,\"Group\":null,\"Name\":null,\"Price\":null,\"Quantity\":null}"));

	CustomerDto customerDto;
	CHECK_TRUE(customerDto.TryStringParse(
		"{\"id\":123,\"name\":\"sh\",\"blob\":null,\"orders\":[{\"supplier\":\"Dell1\",\"dateTime\":1657058001,\"goods\":[{\"Id\":1,\"Created\":1657052789,"
		"\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58.25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}]}"));
}

TEST(JsonObjectTestsGroup, JsonObject_Parse_With_Begin_End_Stages_Test) {
	GoodsDto goods;
	auto doc = goods.BeginTryStringParse("{\"Id\":1,\"Created\":1657052048,\"Group\":\"Vegetables\",\"Name\":\"Tomato\",\"Price\":123.25,\"Quantity\":165.052045}");

	CHECK(doc != NULL);
	CHECK_EQUAL(goods.Created.Get(), 1657052048);
	STRCMP_EQUAL(goods.Group.Get(), "Vegetables");
	goods.EndTryStringParse(doc);
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
	orderDto1.DateTime.Set(orderDto1.DateTime.Get() + 1);
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

	STRCMP_EQUAL(orderDto2.Supplier.Get(), "Dell");
	CHECK_EQUAL(orderDto2.DateTime.Get(), 1657058000);
	CHECK_EQUAL(orderDto2.goodsList.Size(), 2);
	CHECK_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1657052789);
	STRCMP_EQUAL(orderDto2.goodsList.Item<GoodsDto *>(1)->Name.Get(), "K2-100");
	STRCMP_EQUAL(orderDto2.userDto.Name.Get(), "Joe Doe");
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

	auto doc = customerDto1->BeginTryStringParse(DirectWriteTestBuffer, size);
	CHECK(doc != NULL);

	CHECK_EQUAL(customerDto1->Id.Get(), 1234567890123456789LL);
	STRCMP_EQUAL(customerDto1->Name.Get(), "Viordash");
	CHECK_EQUAL(customerDto1->ordersList.Size(), 4);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(0)->goodsList.Size(), 3);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(1)->goodsList.Size(), 2);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(2)->goodsList.Size(), 3);
	CHECK_EQUAL(customerDto1->ordersList.Item<OrderDto *>(3)->goodsList.Size(), 2);
	CHECK_EQUAL(((TJsonRawData)customerDto1->Blob.Get()).Size, pictureSize);
	CHECK_FALSE(((TJsonRawData)customerDto1->Blob.Get()).Data == picture);
	for (size_t i = 0; i < pictureSize; i++) { CHECK_EQUAL(((TJsonRawData)customerDto1->Blob.Get()).Data[i], 'A' + (i % 58)); }
	customerDto1->EndTryStringParse(doc);

	delete customerDto1;
	delete[] picture;

	CustomerDto customerDto2;
	doc = customerDto2.BeginTryStringParse(DirectWriteTestBuffer, size);
	CHECK(doc != NULL);

	CHECK_EQUAL(customerDto2.Id.Get(), 1234567890123456789LL);
	STRCMP_EQUAL(customerDto2.Name.Get(), "Viordash");
	CHECK_EQUAL(customerDto2.ordersList.Size(), 2);
	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(0)->goodsList.Size(), 3);
	CHECK_EQUAL(customerDto2.ordersList.Item<OrderDto *>(1)->goodsList.Size(), 2);
	CHECK_EQUAL(((TJsonRawData)customerDto2.Blob.Get()).Size, pictureSize);
	CHECK_FALSE(((TJsonRawData)customerDto2.Blob.Get()).Data == picture);
	for (size_t i = 0; i < pictureSize; i++) { CHECK_EQUAL(((TJsonRawData)customerDto2.Blob.Get()).Data[i], 'A' + (i % 58)); }
	customerDto2.EndTryStringParse(doc);

	delete[] DirectWriteTestBuffer;
}

TEST(JsonObjectTestsGroup, JsonObject_Optional_Values_Presented_Test) {
	OrderDto order;

	CHECK_FALSE(order.DateTime.Presented());

	CHECK(order.TryStringParse("{\"supplier\":\"Dell\",\"dateTime\":1657058000,\"goods\":[],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(order.DateTime.Presented());

	CHECK(order.TryStringParse("{\"supplier\":\"Dell\",\"goods\":[],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
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

	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":null,\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_TRUE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":null}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_TRUE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goodsOther\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"user\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_FALSE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_TRUE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());

	CHECK_TRUE(optionalObjectDto.TryStringParse("{\"id\":1,\"goods\":[{\"Id\":1,\"Created\":1657052789,\"Group\":\"Keyboards\",\"Name\":\"K1-100\",\"Price\":58."
												"25,\"Quantity\":48.2,\"Deleted\":false,\"StoreName\":\"\"}],\"userOther\":{\"name\":\"Joe Doe\",\"role\":1}}"));
	CHECK_TRUE(optionalObjectDto.Goods.Presented());
	CHECK_FALSE(optionalObjectDto.Goods.IsNull());
	CHECK_FALSE(optionalObjectDto.User.Presented());
	CHECK_FALSE(optionalObjectDto.User.IsNull());
}

TEST(JsonObjectTestsGroup, JsonObject_Values_Without_Instance_Parse_Test) {
	ValuesWoInstance valuesWoInstance;

	auto doc = valuesWoInstance.BeginTryStringParse("{\"id\":123,\"name\":\"Tomato\",\"blob\":\"ABCDEFGHIJKLMNOPQR\"}");
	CHECK(doc != NULL);

	auto id = (JsonValue<uint64_t> *)valuesWoInstance.GetField("id");
	CHECK_FALSE(id == NULL);
	CHECK_EQUAL(id->Get(), 123);

	auto name = (JsonValue<char *> *)valuesWoInstance.GetField("name");
	CHECK_FALSE(name == NULL);
	STRCMP_EQUAL(name->Get(), "Tomato");

	auto blob = (JsonValue<TJsonRawData> *)valuesWoInstance.GetField("blob");
	CHECK_FALSE(blob == NULL);
	STRCMP_EQUAL((char *)((TJsonRawData)(blob->Get())).Data, "ABCDEFGHIJKLMNOPQR");

	auto notExistsValue = (JsonValue<uint32_t> *)valuesWoInstance.GetField("notExistsValue");
	CHECK_TRUE(notExistsValue == NULL);
	valuesWoInstance.EndTryStringParse(doc);
}

TEST(JsonObjectTestsGroup, JsonObject_Values_Without_Instance_WriteTo_Test) {
	char buffer[2048];
	ValuesWoInstance valuesWoInstance(1657052789, "Tomato", {(uint8_t *)"ABCDEFGHIJKLMNOPQR", strlen("ABCDEFGHIJKLMNOPQR")});
	valuesWoInstance.WriteToString(buffer, sizeof(buffer));

	STRCMP_EQUAL(buffer, "{\"id\":1657052789,\"name\":\"Tomato\",\"blob\":\"ABCDEFGHIJKLMNOPQR\"}");
}

TEST(JsonObjectTestsGroup, JsonObject_Validate_Test) {
	auto userDto = new UserDto();
	CHECK_TRUE(userDto->Validate());
	userDto->Role.Set(1000);
	CHECK_FALSE(userDto->Validate());
	CHECK_TRUE(userDto->TryStringParse("{\"name\":\"Joe Doe\",\"role\":999}"));
	CHECK_FALSE(userDto->TryStringParse("{\"name\":\"Joe Doe\",\"role\":1000}"));
	delete userDto;
}

class SetValueObjectDto : public JsonObject {
  public:
	JsonValue<int> Id;
	JsonCommonValue<JsonArrayBase *> Goods;
	JsonCommonValue<JsonObject *> User;
	GoodsList goodsList;
	UserDto userDto;

	SetValueObjectDto(int id = {}, char *userName = {}, TUserRole userRole = {})
		: Id(this, "id", id),				//
		  Goods(this, "goods", &goodsList), //
		  userDto(userName, userRole),		//
		  User(this, "user", &userDto){};
};

TEST(JsonObjectTestsGroup, JsonObject_Update_ArrayValue_Test) {
	SetValueObjectDto testDto(1657058000, "Joe Doe", TUserRole::uViewer);
	testDto.goodsList.Add(new GoodsDto(1, 1657052789, "Keyboards", "K1-100", 58.25, 48.2));
	testDto.goodsList.Add(new GoodsDto(2, 1657053789, "Keyboards", "K2-100", 158.25, 448.2));
	testDto.goodsList.Add(new GoodsDto(3, 1657054789, "Keyboards", "K3-100", 258.25, 548.2));
	testDto.goodsList.Add(new GoodsDto(4, 1657055789, "Keyboards", "K4-100", 358.25, 648.2));
	CHECK_EQUAL(testDto.goodsList.Size(), 4);

	GoodsList newGoodsList;
	newGoodsList.Add(new GoodsDto(100, 1111, "Keyboards-111", "K111-100", 1158.25, 1148.2));
	newGoodsList.Add(new GoodsDto(200, 2222, "Keyboards-222", "K222-100", 22158.25, 22448.2));

	testDto.Goods.Set(&newGoodsList);

	CHECK_EQUAL(testDto.goodsList.Size(), 2);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Id.Get(), 100);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Created.Get(), 1111);
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Group.Get(), "Keyboards-111");
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Name.Get(), "K111-100");
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Price.Get(), 1158.25);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(0)->Quantity.Get(), 1148.2);

	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Id.Get(), 200);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Created.Get(), 2222);
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Group.Get(), "Keyboards-222");
	STRCMP_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Name.Get(), "K222-100");
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Price.Get(), 22158.25);
	CHECK_EQUAL(testDto.goodsList.Item<GoodsDto *>(1)->Quantity.Get(), 22448.2);
}

TEST(JsonObjectTestsGroup, JsonObject_Update_ObjectValue_Test) {
	SetValueObjectDto testDto(1657058000, "Joe Doe", TUserRole::uViewer);

	UserDto userDto("User 1", TUserRole::uAdmin);

	testDto.User.Set(&userDto);
	STRCMP_EQUAL(testDto.userDto.Name.Get(), "User 1");
	CHECK_EQUAL(testDto.userDto.Role.Get(), TUserRole::uAdmin);
}

class NullValueObjectDto : public JsonObject {
  public:
	JsonValue<int> Id;
	JsonCommonValue<JsonArrayBase *> Goods;
	JsonCommonValue<JsonObject *> User;

	NullValueObjectDto(int id = {})
		: Id(this, "id", id),	//
		  Goods(this, "goods"), //
		  User(this, "user"){};
};

TEST(JsonObjectTestsGroup, JsonObject_Update_Nulled_ArrayValue_Test) {
	NullValueObjectDto testDto(1657058000);

	GoodsList newGoodsList;
	newGoodsList.Add(new GoodsDto(100, 1111, "Keyboards-111", "K111-100", 1158.25, 1148.2));
	newGoodsList.Add(new GoodsDto(200, 2222, "Keyboards-222", "K222-100", 22158.25, 22448.2));

	testDto.Goods.Set(&newGoodsList);

	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Size(), 2);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Id.Get(), 100);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Created.Get(), 1111);
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Group.Get(), "Keyboards-111");
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Name.Get(), "K111-100");
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Price.Get(), 1158.25);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(0)->Quantity.Get(), 1148.2);

	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Id.Get(), 200);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Created.Get(), 2222);
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Group.Get(), "Keyboards-222");
	STRCMP_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Name.Get(), "K222-100");
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Price.Get(), 22158.25);
	CHECK_EQUAL(((GoodsList *)testDto.Goods.Get())->Item<GoodsDto *>(1)->Quantity.Get(), 22448.2);
}

TEST(JsonObjectTestsGroup, JsonObject_Update_Nulled_ObjectValue_Test) {
	NullValueObjectDto testDto(1657058000);

	UserDto userDto("User 1", TUserRole::uAdmin);

	testDto.User.Set(&userDto);
	STRCMP_EQUAL(((UserDto *)testDto.User.Get())->Name.Get(), "User 1");
	CHECK_EQUAL(((UserDto *)testDto.User.Get())->Role.Get(), TUserRole::uAdmin);
}