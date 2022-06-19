cmake_minimum_required(VERSION 3.0.0)
project(RapidJSONWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)



include(CTest)
include_directories(rapidjson/include)

add_executable(RapidJSONWrapper     
    main.cpp 
    Json/templates.cpp
    Json/JsonBaseField.cpp
    Json/JsonStringField.cpp
    Json/JsonNumericField.cpp
    )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")