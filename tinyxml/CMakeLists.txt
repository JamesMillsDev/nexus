cmake_minimum_required(VERSION 3.10)

project(tinyxml VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(tinyxml tinyxml2.cpp)