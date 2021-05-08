cmake_minimum_required(VERSION 3.19.2)

project(buflog)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("Debug!!")
    enable_testing()

    include_directories(include)

    add_compile_options(--coverage -g)
    add_subdirectory(src)
    add_subdirectory(tests)
else()
    message("Release!!")
    include_directories(include)
    add_compile_options(-Wall -Wextra -pedantic -Werror)
    add_subdirectory(src)
endif()
