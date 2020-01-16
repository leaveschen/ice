cmake_minimum_required(VERSION 3.0)

project(TEST)

set(CMAKE_CXX_STANDARD 14)

enable_testing()
include_directories("../")

add_executable(string algorithm/unittest_string.cc)
add_test(test_string string)

add_executable(traits traits/unittest_traits.cc)
add_test(test_traits traits)

