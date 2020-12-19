cmake_minimum_required(VERSION 3.17)
project(DataBase)

set(CMAKE_CXX_STANDARD 14)

add_executable(DataBase main.cpp TableFunctions.h TableFunctions.cpp IOFunctions.cpp IOFunctions.h)