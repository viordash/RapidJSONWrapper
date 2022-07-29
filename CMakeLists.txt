cmake_minimum_required(VERSION 3.8.0)
project(RapidJSONWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

include_directories(rapidjson/include Json)

add_subdirectory(Tests)

add_executable(RapidJSONWrapper     
    main.cpp 
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
