cmake_minimum_required(VERSION 3.20)

project(DataStructureLab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

enable_testing()

add_executable(ds_tests tests/test_bootstrap.cpp )
target_include_directories(ds_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME ds_tests COMMAND ds_tests)

add_executable(test_array_list tests/test_array_list.cpp)
target_include_directories(test_array_list PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME test_array_list COMMAND test_array_list)