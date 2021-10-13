# cmake_minimum_required(VERSION <specify CMake version here>)
project(code C)

set(CMAKE_C_STANDARD 11)

add_executable(code main.c)

target_link_libraries(code m)
