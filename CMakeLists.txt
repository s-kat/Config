cmake_minimum_required(VERSION 3.16)

project(Config VERSION 1.0 LANGUAGES CXX)

add_compile_options(

    -Wall
    -Wextra
    -Wpedantic

)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_executable(Config main.cpp)