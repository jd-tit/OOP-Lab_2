cmake_minimum_required(VERSION 3.16)
project(Lab2 C)
project(Lab2_tests CXX)

set(CMAKE_C_STANDARD 17)

add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(include)

include_directories(include src)
target_include_directories(run_all_tests PUBLIC include src)
