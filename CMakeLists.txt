cmake_minimum_required(VERSION 3.28)
project(lb2)

set(CMAKE_CXX_STANDARD 17)

add_library(lb2rsa SHARED lb2rsa.cpp)
target_include_directories(lb2rsa PUBLIC ./)

add_executable(lb2main main.cpp)
target_link_libraries(lb2main lb2rsa)
target_include_directories(lb2main PUBLIC ./)
