cmake_minimum_required(VERSION 4.1)
project(laba_1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


set(SOURCES
        main.c
        vector.c
        int_type.c
        double_type.c
        tests.c
)
set(HEADERS
        vector.h
        type_info.h
        int_type.h
        double_type.h
        tests.h
)


add_executable(laba_1 ${SOURCES} ${HEADERS})

message(STATUS "=== Лабораторная работа №1 готова к сборке ===")
