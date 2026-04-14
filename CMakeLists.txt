cmake_minimum_required(VERSION 4.2)
project(aberdePythonCompiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(aberdePythonCompiler
        1_lexer/lexerTest.cpp
        1_lexer/lexer.h
        1_lexer/lexer.cpp
        2_parser/parser.h
        2_parser/parser.cpp
        2_parser/parserTest.cpp
        3_analyzer/analyzer.h
        3_analyzer/analyzer.cpp
        3_analyzer/analyzerTest.cpp)

target_include_directories(aberdePythonCompiler PRIVATE
        1_lexer
        2_parser
        3_analyzer
)
