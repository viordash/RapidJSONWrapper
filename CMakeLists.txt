cmake_minimum_required(VERSION 3.8.0)
project(RapidJSONWrapper VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)

if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)


set(CPP_SOURCE_FILES 
src/ValueProvider.cpp
src/JsonValueBase.cpp
src/JsonValue.cpp
src/JsonCommonValue.cpp
src/JsonObject.cpp
src/JsonArrayBase.cpp
src/JsonArray.cpp
src/JsonObjectsArray.cpp
)

add_executable(RapidJSONWrapper     
    main.cpp 
	test.cpp 
	${CPP_SOURCE_FILES}
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


enable_testing()
add_subdirectory(Tests)