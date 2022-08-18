#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "JsonWrapper.h"

int test(const int argc, const char *argv[]) {
	fprintf(stdout, "json to class object\n");
	JsonFieldsContainer container;
	JsonValue<int> intObj(&container, "test", 100);
	JsonCommonValue<int> intObj1(&container, "test", 100);
	rapidjson::Document doc;
	doc.Parse("{\"test\":153000}");
	intObj.TryParse(&doc);
	intObj1.TryParse(&doc);

	return EXIT_SUCCESS;
}