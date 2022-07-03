
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
	JsonField<int> field2;
	JsonField<int> field3;
	JsonField<float> field4;

	ObjectC()
		:								 //
		  field1(this, "field1", false), //
		  field2(this, "field2", false), //
		  field3(this, "field3", false), //
		  field4(this, "field4", false)	 //
	{
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

// template <class T, int size> // size является non-type параметром шаблона
// class StaticArray_Base {
//   protected:
//	// Параметр size отвечает за длину массива
//	T m_array[size];
//
//   public:
//	T *getArray() {
//		return m_array;
//	}
//
//	T &operator[](int index) {
//		return m_array[index];
//	}
//	virtual void print() {
//		for (int i = 0; i < size; i++)
//			std::cout << m_array[i] << ' ';
//		std::cout << "\n";
//	}
// };

// template <class T, int size> // size является non-type параметром шаблона
// class StaticArray : public JsonNumericField<T, size> {
//   public:
//	StaticArray() {
//	}
// };
//
// template <int size> // size является non-type параметром шаблона
// class StaticArray<double, size> : public JsonNumericField<double, size> {
//   public:
//	virtual void print() override {
//		for (int i = 0; i < size; i++)
//			std::cout << std::scientific << this->m_array[i] << " ";
//		// Примечание: Префикс this-> на вышеприведенной строке необходим. Почему? Читайте здесь - https://stackoverflow.com/a/6592617
//		std::cout << "\n";
//	}
// };

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