#pragma once

#define TEST(testGroup, testName) int TEST_##testGroup##_##testName()

#define TEST_RUN(testGroup, testName)                                                                                                                          \
	{                                                                                                                                                          \
		if (TEST_##testGroup##_##testName() != EXIT_SUCCESS) {                                                                                                 \
			return EXIT_FAILURE;                                                                                                                               \
		}                                                                                                                                                      \
	}

#define CHECK_TRUE(condition)                                                                                                                                  \
	{                                                                                                                                                          \
		if (!(condition)) {                                                                                                                                    \
			return EXIT_FAILURE;                                                                                                                               \
		}                                                                                                                                                      \
	}

#define CHECK(condition) CHECK_TRUE(condition)

#define CHECK_FALSE(condition)                                                                                                                                 \
	{                                                                                                                                                          \
		if ((condition)) {                                                                                                                                     \
			return EXIT_FAILURE;                                                                                                                               \
		}                                                                                                                                                      \
	}

#define CHECK_EQUAL(expected, actual)                                                                                                                          \
	{                                                                                                                                                          \
		if ((expected) != (actual)) {                                                                                                                          \
			return EXIT_FAILURE;                                                                                                                               \
		}                                                                                                                                                      \
	}

#define STRCMP_EQUAL(expected, actual)                                                                                                                         \
	{                                                                                                                                                          \
		if (strcmp((expected), (actual)) != 0) {                                                                                                               \
			return EXIT_FAILURE;                                                                                                                               \
		}                                                                                                                                                      \
	}

#define STRCMP_CONTAINS(expected, actual)                                                                                                                      \
	{                                                                                                                                                          \
		if (strstr((actual), (expected)) == NULL) {                                                                                                            \
			return EXIT_FAILURE;                                                                                                                               \
		}                                                                                                                                                      \
	}
