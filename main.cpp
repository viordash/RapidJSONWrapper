#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Json.h"

int main(const int argc, const char *argv[]) {
	fprintf(stdout, "json to class object\n");

	// JsonStringField<(const char *)"testName", false, 256> testable1("test");

	// JsonStringField testableString("testName", "test1");
	// JsonNumericField<uint32_t> testableUint("testName", 100);

	// std::cout << testableString.Name << " " << testableString.Value << std::endl;
	// std::cout << testableUint.Name << " " << testableUint.Value << std::endl;
	return EXIT_SUCCESS;
}