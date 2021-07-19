cmake_minimum_required(VERSION 3.15)
project(Pozm_Malding)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pozm_Malding main.cpp main.h libmem/libmem.cpp libmem/libmem.hpp)
target_link_libraries(Pozm_Malding dl)