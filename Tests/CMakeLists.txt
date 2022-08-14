project(RapidJSONWrapperTests)


include(CTest)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -Wno-write-strings -Wno-overflow -Wno-conversion-null")
endif()

if(WIN32)
  add_definitions("/wd4251")
  add_definitions("/wd4305")
  add_definitions("/wd4309")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)

add_subdirectory(cpputest)

set(CPPUTEST_SOURCE_DIRS cpputest/include cpputest/src cpputest/CppUTest)

add_executable(JsonStringValueTestsGroup    
    JsonStringValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonStringValueTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(JsonStringValueTestsGroup CppUTest)
target_include_directories(JsonStringValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonStringValueTestsGroup JsonStringValueTestsGroup)

add_executable(JsonDataValueTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonDataValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonDataValueTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(JsonDataValueTestsGroup CppUTest)
target_include_directories(JsonDataValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonDataValueTestsGroup JsonDataValueTestsGroup)

add_executable(JsonNumericValueTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonNumericValueTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonNumericValueTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(JsonNumericValueTestsGroup CppUTest)
target_include_directories(JsonNumericValueTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonNumericValueTestsGroup JsonNumericValueTestsGroup)

add_executable(JsonObjectTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonObjectTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonObjectTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(JsonObjectTestsGroup CppUTest)
target_include_directories(JsonObjectTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonObjectTestsGroup JsonObjectTestsGroup)

add_executable(JsonArrayTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonArrayTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonArrayTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(JsonArrayTestsGroup CppUTest)
target_include_directories(JsonArrayTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonArrayTestsGroup JsonArrayTestsGroup)

add_executable(JsonHeavyDutyTestsGroup    
	${CPPUTEST_SOURCE_FILES}
    JsonHeavyDutyTestsGroup.cpp)
if(WIN32)
	target_link_libraries(JsonHeavyDutyTestsGroup Winmm.lib)
endif(WIN32)
target_link_libraries(JsonHeavyDutyTestsGroup CppUTest)
target_include_directories(JsonHeavyDutyTestsGroup PRIVATE ${CPPUTEST_SOURCE_DIRS})
add_test(JsonHeavyDutyTestsGroup JsonHeavyDutyTestsGroup)