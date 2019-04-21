cmake_minimum_required(VERSION 3.8)

project(jit)

set(CMAKE_CXX_STANDARD 11)

add_executable(jit main.cpp runtime_function.hpp)
add_executable(jit_asan main.cpp runtime_function.hpp)

add_compile_options(jit_asan PUBLIC -fsanitize=address)
add_link_options(jit_asan -lasan)
