cmake_minimum_required(VERSION 3.8)

project(image_processor)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(util)

add_subdirectory(src)