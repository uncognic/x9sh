cmake_minimum_required(VERSION 3.28)
project(x9sh C)

set(CMAKE_C_STANDARD 23)

add_executable(x9sh main.c
        builtin/pwd.c
        builtin/pwd.h
        builtin/cd.c
        builtin/cd.h)
