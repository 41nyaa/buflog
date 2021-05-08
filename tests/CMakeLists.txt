set(UNITTEST_SOURCES
    buflog_test.cpp
    ipcsharedbuffer_test.cpp)

include(GoogleTest)
find_package(Threads REQUIRED)

include_directories(../include ../src googletest/googletest/include)
link_directories(googletest/lib)
link_directories(../lib)

add_executable(buflog_unittest.out ${UNITTEST_SOURCES})

target_link_libraries(buflog_unittest.out PRIVATE buflog)
target_link_libraries(buflog_unittest.out PUBLIC gtest_main)
target_link_libraries(buflog_unittest.out PUBLIC gtest)
target_link_libraries(buflog_unittest.out PUBLIC Threads::Threads)
target_link_libraries(buflog_unittest.out PUBLIC -fprofile-arcs)

gtest_discover_tests(buflog_unittest.out)
