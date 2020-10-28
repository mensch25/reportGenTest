cmake_minimum_required(VERSION 3.17)
project(pa_c_0 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_COMPILER "/etc/alternatives/mpi")
add_executable(pa_c_0 main.c)