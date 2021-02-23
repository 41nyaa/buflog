cmake_minimum_required(VERSION 3.19.2)

project(buflog_unittest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(UNITTEST_SOURCES
    sharedbuffer_test.cpp)

include_directories(../include ../src googletest/googletest/include)
link_directories(googletest/lib)

add_executable(buflog_unittest.out ${UNITTEST_SOURCES})

target_link_libraries(buflog_unittest.out PRIVATE buflog)
target_link_libraries(buflog_unittest.out PUBLIC gtest_main)
