cmake_minimum_required(VERSION 4.2)
project(aberdePythonCompiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(aberdePythonCompiler
        lexer/lexerTest.cpp
        lexer/lexer.h
        lexer/lexer.cpp
        parser/parser.h
        parser/parser.cpp
        parser/parserTest.cpp
        parser/parser.cpp)

target_include_directories(aberdePythonCompiler PRIVATE
        lexer
        parser
)
