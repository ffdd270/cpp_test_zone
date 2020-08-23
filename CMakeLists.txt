cmake_minimum_required(VERSION 3.16)
project(cpp_test_zone)
include_directories( include )

set(TEST_SRC_FILES
        tests/main.cpp
        tests/tinyxml2/basic.cpp )

find_package(tinyxml2 CONFIG REQUIRED)
add_executable( cpp_test_zone ${TEST_SRC_FILES} )

target_link_libraries(cpp_test_zone PRIVATE tinyxml2::tinyxml2)
