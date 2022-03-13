cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)
include_directories(../include test)

add_subdirectory(${PROJECT_SOURCE_DIR}/test/Gtest)

#FILE(GLOB C_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c ${PROJECT_SOURCE_DIR}/include/*.h)
#message( "${C_SOURCES}" "lololololololoolololoolololollol")
set(C_LIB_SOURCES ../src/ctrl.c ../src/domain.c ../src/repo.c ../src/restrict_types.c ../src/validate.c ../src/convert.c ../src/vector.c)

#FILE(GLOB TEST_C_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)
set(TEST_C_SOURCES test.cpp test.c test.h)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

#add_library(lab2_lib STATIC ${C_LIB_SOURCES})

add_executable(run_all_tests ${TEST_C_SOURCES} ${C_LIB_SOURCES} ../src/sort.c ../include/sort.h)
target_link_libraries(run_all_tests GTest::gtest GTest::gtest_main )#gcov)
#target_compile_options(run_all_tests PUBLIC "--coverage")



