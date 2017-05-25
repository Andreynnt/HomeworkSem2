cmake_minimum_required(VERSION 3.7)
project(DZ_SEM1)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c menu.h read.h read.c menu.c hash_table.c hash_table.h)
add_executable(DZ_SEM1 ${SOURCE_FILES})