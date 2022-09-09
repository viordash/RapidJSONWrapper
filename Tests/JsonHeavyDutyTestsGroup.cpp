
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include "JsonWrapper.h"
#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char **av) { return RUN_ALL_TESTS(ac, av); }

TEST_GROUP(JsonHeavyDutyTestsGroup){void setup(){} void teardown(){}};

static char *strDuplicate(const char *src) {
	if (src == NULL) { return NULL; }
	int len = strlen(src) + 1;
	char *dest = new char[len];
	memcpy(dest, src, len);
	return dest;
}

typedef enum { uAdmin, uViewer } TUserRole;

class UserDto : public JsonObject {
  public:
	JsonValue<char *> Name;
	JsonValue<uint32_t> Role;

	UserDto(const char *name = {}, const TUserRole role = {})
		: Name(this, "name", name), //
		  Role(this, "role", role){};
};

typedef struct {
	char *name;
	TUserRole role;
} TUserDto;

static void SerializeUserDto(rapidjson::Writer<rapidjson::StringBuffer> *writer, const TUserDto *pUserDto) {
	writer->StartObject();
	writer->String("name");
	writer->String(pUserDto->name);
	writer->String("role");
	writer->Uint(pUserDto->role);
	writer->EndObject();
}

static TUserDto *DeserializeUserDto(rapidjson::Value *doc) {
	if (!doc->IsObject()) { return NULL; }

	auto name = doc->FindMember("name");
	auto role = doc->FindMember("role");

	if (name == doc->MemberEnd() || !name->value.IsString()) { return NULL; }
	if (role == doc->MemberEnd() || !role->value.IsUint()) { return NULL; }

	auto userDto = new TUserDto();
	userDto->name = strDuplicate(name->value.GetString());
	userDto->role = (TUserRole)role->value.GetUint();
	return userDto;
}

class GoodsDto : public JsonObject {
  public:
	JsonValue<int> Id;
	JsonValue<uint32_t> Created;
	JsonValue<char *> Group;
	JsonValue<char *> Name;
	JsonValue<float> Price;
	JsonValue<double> Quantity;
	JsonValue<bool> Deleted;
	JsonValue<char *> StoreName;

	GoodsDto(const int id = {}, const uint32_t created = {}, const char *group = {}, const char *name = {}, const float price = {}, const double quantity = {}, const bool deleted = {},
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

typedef struct {
	int id;
	uint32_t created;
	char *group;
	char *name;
	float price;
	double quantity;
	bool deleted;
	char *storeName;
} TGoodsDto;

static void SerializeGoodsDto(rapidjson::Writer<rapidjson::StringBuffer> *writer, const TGoodsDto *pGoodsDto) {
	writer->StartObject();
	writer->String("Id");
	writer->Int(pGoodsDto->id);
	writer->String("Created");
	writer->Uint(pGoodsDto->created);
	writer->String("Group");
	writer->String(pGoodsDto->group);
	writer->String("Name");
	writer->String(pGoodsDto->name);
	writer->String("Price");
	writer->Double(pGoodsDto->price);
	writer->String("Quantity");
	writer->Double(pGoodsDto->quantity);
	writer->String("Deleted");
	writer->Bool(pGoodsDto->deleted);
	writer->String("StoreName");
	writer->String(pGoodsDto->storeName);

	writer->EndObject();
}

static TGoodsDto *DeserializeGoodsDto(rapidjson::Value *doc) {
	if (!doc->IsObject()) { return NULL; }

	auto id = doc->FindMember("Id");
	auto created = doc->FindMember("Created");
	auto group = doc->FindMember("Group");
	auto name = doc->FindMember("Name");
	auto price = doc->FindMember("Price");
	auto quantity = doc->FindMember("Quantity");
	auto deleted = doc->FindMember("Deleted");
	auto storeName = doc->FindMember("StoreName");

	if (id == doc->MemberEnd() || !id->value.IsInt()) { return NULL; }
	if (created == doc->MemberEnd() || !created->value.IsUint()) { return NULL; }
	if (group == doc->MemberEnd() || !group->value.IsString()) { return NULL; }
	if (name == doc->MemberEnd() || !name->value.IsString()) { return NULL; }
	if (price == doc->MemberEnd() || !price->value.IsDouble()) { return NULL; }
	if (quantity == doc->MemberEnd() || !quantity->value.IsDouble()) { return NULL; }
	if (deleted == doc->MemberEnd() || !deleted->value.IsBool()) { return NULL; }

	auto goodsDto = new TGoodsDto();
	goodsDto->id = id->value.GetInt();
	goodsDto->created = id->value.GetUint();
	goodsDto->group = strDuplicate(group->value.GetString());
	goodsDto->name = strDuplicate(name->value.GetString());
	goodsDto->price = price->value.GetDouble();
	goodsDto->quantity = quantity->value.GetDouble();
	goodsDto->deleted = deleted->value.GetBool();
	goodsDto->storeName = strDuplicate(storeName->value.GetString());
	return goodsDto;
}

class GoodsList : public JsonObjectsArray {
  public:
	bool Validate(JsonObject *item) override { return item->Validate(); }
	JsonObject *CreateItem() override { return new GoodsDto(); }
};

static void SerializeGoodsList(rapidjson::Writer<rapidjson::StringBuffer> *writer, std::vector<TGoodsDto *> *goods) {
	writer->StartArray();
	for (const auto &item : *goods) { //
		SerializeGoodsDto(writer, item);
	}
	writer->EndArray();
}

static std::vector<TGoodsDto *> *DeserializeGoodsList(rapidjson::Value *doc) {
	if (!doc->IsArray()) { return NULL; }
	auto jArray = doc->GetArray();

	auto goodsList = new std::vector<TGoodsDto *>();
	for (const auto &jItem : jArray) {
		auto goods = DeserializeGoodsDto((rapidjson::Value *)&jItem);
		if (goods == NULL) {
			for (const auto item : *goodsList) { delete item; }
			delete goodsList;
			return NULL;
		}
		goodsList->push_back(goods);
	}
	return goodsList;
}

class OrderDto : public JsonObject {
  public:
	JsonValue<char *> Supplier;
	JsonValue<uint32_t> DateTime;
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
};

typedef struct {
	char *supplier;
	uint32_t dateTime;
	std::vector<TGoodsDto *> *goods;
	TUserDto *user;
} TOrderDto;

static void SerializeOrderDto(rapidjson::Writer<rapidjson::StringBuffer> *writer, const TOrderDto *pOrderDto) {
	writer->StartObject();
	writer->String("supplier");
	writer->String(pOrderDto->supplier);
	writer->String("dateTime");
	writer->Uint(pOrderDto->dateTime);

	writer->String("user");
	SerializeUserDto(writer, pOrderDto->user);

	writer->String("goods");
	SerializeGoodsList(writer, pOrderDto->goods);
	writer->EndObject();
}

static TOrderDto *DeserializeOrderDto(rapidjson::Value *doc) {
	if (!doc->IsObject()) { return NULL; }

	auto supplier = doc->FindMember("supplier");
	auto dateTime = doc->FindMember("dateTime");
	auto user = doc->FindMember("user");
	auto goods = doc->FindMember("goods");

	if (supplier == doc->MemberEnd() || !supplier->value.IsString()) { return NULL; }
	if (dateTime == doc->MemberEnd() || !dateTime->value.IsUint()) { return NULL; }
	if (user == doc->MemberEnd() || !user->value.IsObject()) { return NULL; }
	if (goods == doc->MemberEnd() || !goods->value.IsArray()) { return NULL; }

	auto orderDto = new TOrderDto();
	orderDto->supplier = strDuplicate(supplier->value.GetString());
	orderDto->dateTime = dateTime->value.GetUint();
	orderDto->user = DeserializeUserDto((rapidjson::Value *)&user->value);
	orderDto->goods = DeserializeGoodsList((rapidjson::Value *)&goods->value);
	return orderDto;
}

class OrdersList : public JsonObjectsArray {
  public:
	bool Validate(JsonObject *item) override { return item->Validate(); }
	JsonObject *CreateItem() override { return new OrderDto(); }
};

static void SerializeOrdersList(rapidjson::Writer<rapidjson::StringBuffer> *writer, std::vector<TOrderDto *> *orders) {
	writer->StartArray();
	for (const auto &item : *orders) { //
		SerializeOrderDto(writer, item);
	}
	writer->EndArray();
}

static std::vector<TOrderDto *> *DeserializeOrdersList(rapidjson::Value *doc) {
	if (!doc->IsArray()) { return NULL; }
	auto jArray = doc->GetArray();

	auto ordersList = new std::vector<TOrderDto *>();
	for (const auto &jItem : jArray) {
		auto goods = DeserializeOrderDto((rapidjson::Value *)&jItem);
		if (goods == NULL) {
			for (const auto item : *ordersList) { delete item; }
			delete ordersList;
			return NULL;
		}
		ordersList->push_back(goods);
	}
	return ordersList;
}

class CustomerDto : public JsonObject {
  public:
	JsonValue<uint64_t> Id;
	JsonValue<char *> Name;
	JsonValue<TJsonRawData> Blob;
	JsonValue<JsonArrayBase *> Orders;
	OrdersList ordersList;

	CustomerDto(const uint64_t id = {}, const char *name = {}, const TJsonRawData blob = {})
		: Id(this, "id", id),		//
		  Name(this, "name", name), //
		  Blob(this, "blob", blob), //
		  Orders(this, "orders", &ordersList){};
};

typedef struct {
	uint64_t id;
	char *name;
	TJsonRawData blob;
	std::vector<TOrderDto *> *orders;
} TCustomerDto;

static void SerializeCustomerDto(rapidjson::Writer<rapidjson::StringBuffer> *writer, const TCustomerDto *customerDto) {
	writer->StartObject();
	writer->String("id");
	writer->Uint64(customerDto->id);
	writer->String("name");
	writer->String(customerDto->name);
	writer->String("blob");
	writer->String((char *)customerDto->blob.Data, (rapidjson::SizeType)customerDto->blob.Size);

	writer->String("orders");
	SerializeOrdersList(writer, customerDto->orders);
	writer->EndObject();
}

static TCustomerDto *DeserializeCustomerDto(rapidjson::Value *doc) {
	if (!doc->IsObject()) { return NULL; }

	auto id = doc->FindMember("id");
	auto name = doc->FindMember("name");
	auto blob = doc->FindMember("blob");
	auto orders = doc->FindMember("orders");

	if (id == doc->MemberEnd() || !id->value.IsUint64()) { return NULL; }
	if (name == doc->MemberEnd() || !name->value.IsString()) { return NULL; }
	if (blob == doc->MemberEnd() || !blob->value.IsString()) { return NULL; }
	if (orders == doc->MemberEnd() || !orders->value.IsArray()) { return NULL; }

	auto customerDto = new TCustomerDto();
	customerDto->id = id->value.GetUint64();
	customerDto->name = strDuplicate(name->value.GetString());
	customerDto->blob = {(uint8_t *)blob->value.GetString(), blob->value.GetStringLength()};
	customerDto->orders = DeserializeOrdersList((rapidjson::Value *)&orders->value);
	return customerDto;
}

class CustomerList : public JsonObjectsArray {
  public:
	bool Validate(JsonObject *item) override { return item->Validate(); }
	JsonObject *CreateItem() override { return new CustomerDto(); }
};

static void SerializeCustomerList(rapidjson::Writer<rapidjson::StringBuffer> *writer, std::vector<TCustomerDto *> *customers) {
	writer->StartArray();
	for (const auto &item : *customers) { //
		SerializeCustomerDto(writer, item);
	}
	writer->EndArray();
}

static std::vector<TCustomerDto *> *DeserializeCustomerList(rapidjson::Value *doc) {
	if (!doc->IsArray()) { return NULL; }
	auto jArray = doc->GetArray();

	auto customerList = new std::vector<TCustomerDto *>();
	for (const auto &jItem : jArray) {
		auto customer = DeserializeCustomerDto((rapidjson::Value *)&jItem);
		if (customer == NULL) {
			for (const auto item : *customerList) { delete item; }
			delete customerList;
			return NULL;
		}
		customerList->push_back(customer);
	}
	return customerList;
}

static void *TestParent = NULL;
static char *DirectWriteTestBuffer = NULL;
static void OnReady(void *parent, const char *json, size_t size) {
	TestParent = parent;
	DirectWriteTestBuffer = new char[size + 1];
	memcpy(DirectWriteTestBuffer, json, size);
	DirectWriteTestBuffer[size] = 0;
}

const int perfTestItemsCount = 1'000;
int picture[] = {0x66, 0x00, 0x67, 0x67, 0x67, 0x00, 0x68, 0x68, 0x68, 0x00, 0x69, 0x69, 0x69, 0x00, 0x6A, 0x6A};

static uint64_t testFillArray(CustomerList *customerList) {
	auto start = std::chrono::high_resolution_clock::now();
	customerList->Reserve(perfTestItemsCount);
	for (size_t i = 0; i < perfTestItemsCount; i++) {
		picture[0] = i;
		customerList->Add(new CustomerDto(12345678901100LL + i, "Viordash", {(uint8_t *)picture, sizeof(picture)}));
		auto customerDto = customerList->Item<CustomerDto *>(i);
		for (size_t k = 0; k < (perfTestItemsCount / 100) + 1; k++) {
			customerDto->ordersList.Add(new OrderDto("Dell1", 165700 + i + k, "Joe Doe", TUserRole::uViewer));

			auto orderDto = customerDto->ordersList.Item<OrderDto *>(k);
			for (size_t m = 0; m < (perfTestItemsCount / 1000) + 1; m++) { //
				orderDto->goodsList.Add(
					new GoodsDto(1, 16570 + i + k + m, "Keyboards", "K1-100", k * 2.5, k * 0.1, m % 2 == 0, "Chargoggagoggmanchauggagoggchaubunagungamaugg 0123456789012345678901234567890123456789"));
			}
		}
	}
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static uint64_t testArrayWriteTo(CustomerList *customerList, size_t *size) {
	auto start = std::chrono::high_resolution_clock::now();
	*size = customerList->DirectWriteTo(0, OnReady);
	CHECK(*size > 0);
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static uint64_t testArrayTryParse(CustomerList *customerList, const char *jsonStr, size_t size) {
	auto start = std::chrono::high_resolution_clock::now();
	CHECK(customerList->TryStringParse(jsonStr, size));
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static void DeleteCustomerList(std::vector<TCustomerDto *> *customerList) {
	for (const auto customer : *customerList) {
		delete[] customer->name;
		for (const auto order : *customer->orders) {
			delete[] order->supplier;
			delete[] order->user->name;
			delete order->user;
			for (const auto goods : *order->goods) {
				delete[] goods->group;
				delete[] goods->name;
				delete[] goods->storeName;
				delete goods;
			}
			delete order->goods;
			delete order;
		}
		delete customer->orders;
		delete customer;
	}
	delete customerList;
}

static uint64_t testFillRapidArray(std::vector<TCustomerDto *> *customerList) {
	auto start = std::chrono::high_resolution_clock::now();
	customerList->reserve(perfTestItemsCount);
	for (size_t i = 0; i < perfTestItemsCount; i++) {
		picture[0] = i;
		auto customer = new TCustomerDto();
		customer->id = 52345678901100LL + i;
		customer->name = strDuplicate("Viordash");
		customer->blob = {(uint8_t *)picture, sizeof(picture)};
		customer->orders = new std::vector<TOrderDto *>();
		customerList->push_back(customer);

		auto customerDto = (*customerList)[i];
		for (size_t k = 0; k < (perfTestItemsCount / 100) + 1; k++) {
			auto order = new TOrderDto();
			order->supplier = strDuplicate("Dell1");
			order->dateTime = 165700 + i + k;
			order->user = new TUserDto();
			order->user->name = strDuplicate("Joe Doe");
			order->user->role = TUserRole::uViewer;

			order->goods = new std::vector<TGoodsDto *>();
			customerDto->orders->push_back(order);

			auto orderDto = (*customerDto->orders)[k];
			for (size_t m = 0; m < (perfTestItemsCount / 1000) + 1; m++) { //
				auto goods = new TGoodsDto();
				goods->id = 1;
				goods->created = 16570 + i + k + m;
				goods->group = strDuplicate("Keyboards");
				goods->name = strDuplicate("K1-100");
				goods->price = k * 2.5;
				goods->quantity = k * 0.1;
				goods->deleted = m % 2 == 0;
				goods->storeName = strDuplicate("Chargoggagoggmanchauggagoggchaubunagungamaugg 0123456789012345678901234567890123456789");
				orderDto->goods->push_back(goods);
			}
		}
	}
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static char *RapidWriteTestBuffer = NULL;
static uint64_t testRapidArrayWriteTo(std::vector<TCustomerDto *> *customerList, size_t *size) {
	auto start = std::chrono::high_resolution_clock::now();
	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	SerializeCustomerList(&writer, customerList);

	*size = s.GetSize();
	CHECK(*size > 0);
	RapidWriteTestBuffer = new char[s.GetSize() + 1];
	memcpy(RapidWriteTestBuffer, s.GetString(), s.GetSize());
	RapidWriteTestBuffer[s.GetSize()] = 0;
	auto finish = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

static uint64_t testRapidArrayTryParse(const char *jsonStr, size_t size) {
	auto start = std::chrono::high_resolution_clock::now();
	rapidjson::Document document;
	CHECK_FALSE(document.Parse(jsonStr, size).HasParseError());
	auto customerList = DeserializeCustomerList(&document);
	CHECK(customerList != NULL);
	auto finish = std::chrono::high_resolution_clock::now();
	DeleteCustomerList(customerList);
	return std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
}

TEST(JsonHeavyDutyTestsGroup, JsonObject_Perfomance_Test) {
	uint64_t durationAdd = 0;
	uint64_t durationDirectWriteTo = 0;
	uint64_t durationTryParse = 0;

	uint64_t rapidDurationAdd = 0;
	uint64_t rapidDurationDirectWriteTo = 0;
	uint64_t rapidDurationTryParse = 0;

	size_t size = 0;
	size_t rapidSize = 0;

	const int avgCount = 10;
	for (size_t a = 0; a < avgCount; a++) {

		auto customerList = new CustomerList();
		auto rapidCustomerList = new std::vector<TCustomerDto *>();

		durationAdd += testFillArray(customerList);
		rapidDurationAdd += testFillRapidArray(rapidCustomerList);

		DirectWriteTestBuffer = NULL;
		RapidWriteTestBuffer = NULL;
		durationDirectWriteTo += testArrayWriteTo(customerList, &size);
		rapidDurationDirectWriteTo += testRapidArrayWriteTo(rapidCustomerList, &rapidSize);

		DeleteCustomerList(rapidCustomerList);
		delete customerList;

		customerList = new CustomerList();
		durationTryParse += testArrayTryParse(customerList, DirectWriteTestBuffer, size);
		rapidDurationTryParse += testRapidArrayTryParse(RapidWriteTestBuffer, rapidSize);
		delete customerList;

		delete[] RapidWriteTestBuffer;
		delete[] DirectWriteTestBuffer;
	}
	char text[512];
	sprintf(text, "wrapper 'Add' dur(mean %u): %.02f us", avgCount, durationAdd / avgCount / 1000.0);
	UT_PRINT(text);
	sprintf(text, "rapid   'Add' dur(mean %u): %.02f us", avgCount, rapidDurationAdd / avgCount / 1000.0);
	UT_PRINT(text);

	sprintf(text, "wrapper 'WriteTo' size: %lu, dur(mean %u): %.02f us", size, avgCount, durationDirectWriteTo / avgCount / 1000.0);
	UT_PRINT(text);
	sprintf(text, "rapid   'WriteTo' size: %lu, dur(mean %u): %.02f us", rapidSize, avgCount, rapidDurationDirectWriteTo / avgCount / 1000.0);
	UT_PRINT(text);

	sprintf(text, "wrapper TryParse dur(mean %u): %.02f us", avgCount, durationTryParse / avgCount / 1000.0);
	UT_PRINT(text);
	sprintf(text, "rapid   TryParse dur(mean %u): %.02f us", avgCount, rapidDurationTryParse / avgCount / 1000.0);
	UT_PRINT(text);

	sprintf(text, "wrapper to rapid ratio 'Add':%.03f, 'WriteTo':%.03f, 'TryParse':%.03f", (double)durationAdd / (double)rapidDurationAdd,
			(double)durationDirectWriteTo / (double)rapidDurationDirectWriteTo, (double)durationTryParse / (double)rapidDurationTryParse);
	UT_PRINT(text);

	CHECK_EQUAL(size, rapidSize);
	CHECK_FALSE(durationAdd > rapidDurationAdd * 3);
	CHECK_FALSE(durationDirectWriteTo > rapidDurationDirectWriteTo * 3);
	CHECK_FALSE(durationTryParse > rapidDurationTryParse * 3);
}