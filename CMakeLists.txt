cmake_minimum_required(VERSION 3.12)
project(MEMORY C)

set(CMAKE_C_STANDARD 99)

add_executable(MEMORY main.c function.c headers/function.h)