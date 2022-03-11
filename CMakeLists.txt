cmake_minimum_required(VERSION 3.21)
project(Lab2 C)
project(Lab2_tests CXX)
#
#set(CMAKE_C_COMPILER /usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_C_STANDARD 23)

add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(include)

include_directories(include src)
target_include_directories(run_all_tests PUBLIC include src)
#FILE(GLOB C_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)