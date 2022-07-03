
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "Json.h"
#include "TestsCommon.h"

// class JsonCField;
// class JsonCFieldsContainer {
//   public:
//	std::vector<JsonCField *> Fields;
//
//	void Add(JsonCField *field) {
//		Fields.push_back(field);
//	}
// };
//
// class JsonCField {
//   public:
//	const char *Name;
//	JsonCField(JsonCFieldsContainer *container, const char *name, bool optional) {
//		Name = name;
//		this->optional = optional;
//		printf("JsonCField() name:'%s', optional:%d\n", name, optional);
//		container->Add(this);
//	}
//
//   protected:
//	bool optional;
// };
//
// template <class T>
// class JsonCIntField : public JsonCField {
//   public:
//	JsonCIntField(JsonCFieldsContainer *container, const char *name, bool optional = false) : JsonCField(container, name, optional) {
//		Value = 0;
//	}
//
//   protected:
//	T Value;
// };

class ObjectC : public JsonFieldsContainer {
  public:
	JsonField<int> field1;
	JsonField<int8_t> field2;
	JsonField<int16_t> field3;
	JsonField<int32_t> field4;
	JsonField<uint8_t> field5;
	JsonField<uint16_t> field6;
	JsonField<uint32_t> field7;
	JsonField<float> field8;
	JsonField<double> field9;
	JsonField<char *> field10;

	ObjectC()
		:						  //
		  field1(this, "field1"), //
		  field2(this, "field2"), //
		  field3(this, "field3"), //
		  field4(this, "field4"), //
		  field5(this, "field5"), //
		  field6(this, "field6"), //
		  field7(this, "field7"), //
		  field8(this, "field8"), //
		  field9(this, "field9"), //
		  field10(this, "field10") {
		printf("ObjectC()\n");
		field1.SetValue(12);
		field7.SetValue(54);
		field8.SetValue(78.25);
		field9.SetValue(278.25);

		char buffer[256];
		sprintf(buffer, "www 111 fff rrrr 64333333 time: %u", (uint32_t)time(NULL));
		field10.SetValue(buffer);
	};

  private:
};

void Test(int count) {
	ObjectC childObject;

	for (auto &field : childObject.Fields) {
		std::cout << field->Name << ' ';
	}
	std::cout << childObject.field10.Value << ' ';
	std::cout << count << '\n';
}

int main(const int argc, const char *argv[]) {
	for (size_t i = 0; i < 10000; i++) {
		Test(i);
	}

	ObjectC childObjectC0;
	for (auto &field : childObjectC0.Fields) {
		std::cout << field->Name << ' ';
	}
	std::cout << childObjectC0.field10.Value << ' ';
	std::cout << '\n';

	// ObjectC1 childObjectC1;
	// for (auto &field : childObjectC1.Fields.Items) {
	//	std::cout << field.Name << ' ';
	//}
	// std::cout << '\n';

	// auto fff = childObjectC.Fields.Items;
	// fff.push_back(JsonStringField("field10", ""));

	// ObjectC childObjectC1;
	// for (auto &field : childObjectC1.Fields.Items) {
	//	std::cout << field.Name << ' ';
	//}
	std::cout << '\n';

	return EXIT_SUCCESS;
}