cmake_minimum_required(VERSION 3.16)
project(highDiv)

set(CMAKE_CXX_STANDARD 11)

add_executable(highDiv main.cpp LargeInt.cpp LargeInt.h LargeReal.cpp LargeReal.h)