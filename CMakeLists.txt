cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main)

include_directories(include)

add_library(functions STATIC src/functions.cpp)

add_executable(main src/main.cpp)

target_link_libraries(main functions)

#target_link_libraries(main build/src/libfunctions.a)