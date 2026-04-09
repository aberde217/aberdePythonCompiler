cmake_minimum_required(VERSION 4.2)
project(aberdePythonCompiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(aberdePythonCompiler lexerTest.cpp
        lexer.h
        lexer.cpp)
