cmake_minimum_required(VERSION 3.0.0)
project(RapidJSONWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

include(CTest)
include_directories(rapidjson/include Json)

set(SOURCE_FILES     
    Json/templates.cpp
    Json/JsonBaseField.cpp
    Json/JsonStringField.cpp
    Json/JsonNumericField.cpp
)

add_executable(RapidJSONWrapper     
    ${SOURCE_FILES}
    main.cpp 
    )

add_executable(JsonStringFieldTestsGroup    
    ${SOURCE_FILES}
    Tests/JsonStringFieldTestsGroup.cpp)
    


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

enable_testing()

add_test(JsonStringFieldTestsGroup JsonStringFieldTestsGroup)