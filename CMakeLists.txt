cmake_minimum_required(VERSION 3.16)
project(cpp_test_zone)
include_directories( include library )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(TEST_SRC_FILES
        tests/main.cpp
        tests/tinyxml2/basic.cpp
        tests/simdjson/basic.cpp )

set(SIMD_JSON_FILES
        library/simdjson/simdjson.cpp
        library/simdjson/simdjson.h)

find_package(tinyxml2 CONFIG REQUIRED)
add_executable( cpp_test_zone ${TEST_SRC_FILES} ${SIMD_JSON_FILES} )

target_link_libraries(cpp_test_zone PRIVATE tinyxml2::tinyxml2)
