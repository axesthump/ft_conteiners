cmake_minimum_required(VERSION 3.17)
project(ft_container)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_container main.cpp list.hpp ft.hpp vector.hpp stack.hpp queue.hpp map.hpp)

add_library(testlib INTERFACE)
add_subdirectory(unit_tests)