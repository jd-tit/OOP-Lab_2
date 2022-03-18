set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_C_STANDARD 23)
include_directories(../include ../test)

FILE(GLOB C_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)
#set(C_SOURCES ../src/ctrl.c ../src/domain.c ../src/repo.c ../src/restrict_types.c ../src/validate.c ../src/convert.c
#        ../src/user_interface.c)

message( "${PROJECT_SOURCE_DIR}" "${C_SOURCES}" "none")
add_executable(main ${C_SOURCES} ../test/test.c ../include/convert.h sort.c ../include/sort.h vector.c util.c ../include/util.h)
