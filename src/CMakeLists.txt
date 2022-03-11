set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 23)
include_directories(../include ../test)

FILE(GLOB C_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

#message("${C_Sources}" "none")
add_executable(main ${C_SOURCES} ../test/test.c)
