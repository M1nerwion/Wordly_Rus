cmake_minimum_required(VERSION 3.16) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(wordly_rus)

include_directories(include)

add_library(functions STATIC src/functions.cpp)

add_executable(wordly_rus src/main.cpp)

target_link_libraries(wordly_rus functions)

set(CPACK_PACKAGE_NAME "wordly_rus")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Nikpop228 && M1nerwion")
set(CPACK_GENERATOR DEB RPM)
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Game Wordle on Russian created with CMake")

install(TARGETS wordly_rus DESTINATION /usr/bin)

install(DIRECTORY wordfiles/ DESTINATION /usr/share/wordly_rus/wordfiles)

include(CPack)