project(RapidJSONWrapperTests)


include(CTest)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -Wno-write-strings -Wno-overflow -Wno-conversion-null")
endif()

if(WIN32)
  add_definitions("/wd4251")
endif(WIN32)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)


set(CPPUTEST_SOURCE_FILES     
	../cpputest/src/CppUTest/CommandLineArguments.cpp
	../cpputest/src/CppUTest/CommandLineTestRunner.cpp
	../cpputest/src/CppUTest/JUnitTestOutput.cpp
	../cpputest/src/CppUTest/MemoryLeakDetector.cpp
	../cpputest/src/CppUTest/MemoryLeakWarningPlugin.cpp
	../cpputest/src/CppUTest/SimpleMutex.cpp
	../cpputest/src/CppUTest/SimpleString.cpp
	../cpputest/src/CppUTest/SimpleStringInternalCache.cpp
	../cpputest/src/CppUTest/TeamCityTestOutput.cpp
	../cpputest/src/CppUTest/TestFailure.cpp
	../cpputest/src/CppUTest/TestFilter.cpp
	../cpputest/src/CppUTest/TestHarness_c.cpp
	../cpputest/src/CppUTest/TestMemoryAllocator.cpp
	../cpputest/src/CppUTest/TestOutput.cpp
	../cpputest/src/CppUTest/TestPlugin.cpp
	../cpputest/src/CppUTest/TestRegistry.cpp
	../cpputest/src/CppUTest/TestResult.cpp
	../cpputest/src/CppUTest/TestTestingFixture.cpp
	../cpputest/src/CppUTest/Utest.cpp

	../cpputest/src/CppUTestExt/CodeMemoryReportFormatter.cpp
	../cpputest/src/CppUTestExt/GTest.cpp
	../cpputest/src/CppUTestExt/IEEE754ExceptionsPlugin.cpp
	../cpputest/src/CppUTestExt/MemoryReportAllocator.cpp
	../cpputest/src/CppUTestExt/MemoryReporterPlugin.cpp
	../cpputest/src/CppUTestExt/MemoryReportFormatter.cpp
	../cpputest/src/CppUTestExt/MockActualCall.cpp
	../cpputest/src/CppUTestExt/MockExpectedCall.cpp
	../cpputest/src/CppUTestExt/MockExpectedCallsList.cpp
	../cpputest/src/CppUTestExt/MockFailure.cpp
	../cpputest/src/CppUTestExt/MockNamedValue.cpp
	../cpputest/src/CppUTestExt/MockSupport_c.cpp
	../cpputest/src/CppUTestExt/MockSupport.cpp
	../cpputest/src/CppUTestExt/MockSupportPlugin.cpp
	../cpputest/src/CppUTestExt/OrderedTest.cpp
)

if(WIN32)
set(CPPUTEST_SOURCE_FILES ${CPPUTEST_SOURCE_FILES} ../cpputest/src/Platforms/VisualCpp/UtestPlatform.cpp)
endif(WIN32)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
set(CPPUTEST_SOURCE_FILES ${CPPUTEST_SOURCE_FILES} ../cpputest/src/Platforms/Gcc/UtestPlatform.cpp)
endif()

set(CPPUTEST_SOURCE_DIRS ../cpputest/include ../cpputest/src cpputest/CppUTest)

add_executable(JsonStringValueTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonStringValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonStringValueTestsGroup Winmm.lib)
endif(WIN32)
target_include_directories(JsonStringValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonStringValueTestsGroup JsonStringValueTestsGroup)

add_executable(JsonDataValueTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonDataValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonDataValueTestsGroup Winmm.lib)
endif(WIN32)
target_include_directories(JsonDataValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonDataValueTestsGroup JsonDataValueTestsGroup)

add_executable(JsonNumericValueTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonNumericValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonNumericValueTestsGroup Winmm.lib)
endif(WIN32)
target_include_directories(JsonNumericValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonNumericValueTestsGroup JsonNumericValueTestsGroup)

add_executable(JsonObjectTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonObjectTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonObjectTestsGroup Winmm.lib)
endif(WIN32)
target_include_directories(JsonObjectTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonObjectTestsGroup JsonObjectTestsGroup)

add_executable(JsonArrayTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonArrayTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonArrayTestsGroup Winmm.lib)
endif(WIN32)
target_include_directories(JsonArrayTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonArrayTestsGroup JsonArrayTestsGroup)