cmake_minimum_required(VERSION 3.5)
project(compile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp lex.cpp lex.h Parser.cpp Parser.h semantic.cpp semantic.h symtable.cpp symtable.h)
add_executable(compile ${SOURCE_FILES})