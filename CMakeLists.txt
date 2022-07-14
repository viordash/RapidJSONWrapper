cmake_minimum_required(VERSION 3.8.0)
project(RapidJSONWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

if(WIN32)
  add_definitions("/wd4251")
endif(WIN32)

include(CTest)
include_directories(rapidjson/include Json)

set(SOURCE_FILES     
    # Json/JsonBaseField.cpp
    # Json/JsonField.cpp
    # Json/JsonStringField.cpp
    # Json/JsonObject.cpp
    # Json/JsonBaseArray.cpp
    # Json/JsonObjectsArray.cpp
    # Json/JsonObjectField.cpp
    # Json/JsonArrayField.cpp
    Json/JsonObjectV2.cpp
)

add_executable(RapidJSONWrapper     
    ${SOURCE_FILES}
    main.cpp 
    )

# add_executable(JsonStringFieldTestsGroup    
#     ${SOURCE_FILES}
#     Tests/JsonStringFieldTestsGroup.cpp)

# add_executable(JsonNumericFieldTestsGroup    
#     ${SOURCE_FILES}
#     Tests/JsonNumericFieldTestsGroup.cpp)

# add_executable(JsonObjectFieldTestsGroup    
#     ${SOURCE_FILES}
#     Tests/JsonObjectFieldTestsGroup.cpp)

# add_executable(JsonObjectTestsGroup    
#     ${SOURCE_FILES}
#     Tests/JsonObjectTestsGroup.cpp)

# add_executable(JsonArrayTestsGroup    
#     ${SOURCE_FILES}
#     Tests/JsonArrayTestsGroup.cpp)

# add_executable(JsonArrayFieldTestsGroup    
#     ${SOURCE_FILES}
#     Tests/JsonArrayFieldTestsGroup.cpp)
    


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# enable_testing()

# add_test(JsonStringFieldTestsGroup JsonStringFieldTestsGroup)
# add_test(JsonNumericFieldTestsGroup JsonNumericFieldTestsGroup)
# add_test(JsonObjectFieldTestsGroup JsonObjectFieldTestsGroup)
# add_test(JsonObjectTestsGroup JsonObjectTestsGroup)
# add_test(JsonArrayTestsGroup JsonArrayTestsGroup)
# add_test(JsonArrayFieldTestsGroup JsonArrayFieldTestsGroup)