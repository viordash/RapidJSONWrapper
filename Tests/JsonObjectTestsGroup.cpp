
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
// class JsonFieldsContainer {
//   public:
// 	std::vector<JsonCField *> Fields;

// 	void Add(JsonCField *field) {
// 		Fields.push_back(field);
// 	}
// };

// class JsonCField {
//   public:
// 	const char *Name;
// 	JsonCField(JsonFieldsContainer *container, const char *name, bool optional) {
// 		Name = name;
// 		this->optional = optional;
// 		printf("JsonCField() name:'%s', optional:%d\n", name, optional);
// 		container->Add(this);
// 	}

//   protected:
// 	bool optional;
// };

// class JsonCIntField : public JsonCField {
//   public:
// 	JsonCIntField(JsonFieldsContainer *container, const char *name, bool optional = false) : JsonCField(container, name, optional) {
// 		Value = 0;
// 	}

//   protected:
// 	int Value;
// };

class ObjectC : public JsonObject {
  public:
	JsonIntField fieldInt1;
	JsonIntField fieldInt2;
	JsonIntField fieldInt3;

	ObjectC()
		: fieldInt1(this, "field1", false), //
		  fieldInt2(this, "field2", false), //
		  fieldInt3(this, "field3", false) {
		printf("ObjectC()\n");
	};

  private:
};

void Test(int count) {
	ObjectC childObject;

	for (auto &field : childObject.Fields) {
		std::cout << field->Name << ' ';
	}
	std::cout << count << '\n';
}

int main(const int argc, const char *argv[]) {
	for (size_t i = 0; i < 1000; i++) {
		Test(i);
	}

	ObjectC childObjectC0;
	for (auto &field : childObjectC0.Fields) {
		std::cout << field->Name << ' ';
	}
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