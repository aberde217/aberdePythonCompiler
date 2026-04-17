#ifndef ABERDEPYTHONCOMPILER_CODEGEN_H
#define ABERDEPYTHONCOMPILER_CODEGEN_H
#include "analyzer.h"

class CodeGenerator { //generate x86 code for 32-bit processor
private:
    vector<AST*> finalASTs;
    map<string, varType> symbolTable;
    void generate_data_segment(); // generates .data section of x86 program
    void generate_code_segment(); // generates .code section of x86 program

    // Helper functions for generating .code x86 code
    void generate_statement_code(AST* node);
    void generate_expression_code(AST* node);
public:
    CodeGenerator();
    CodeGenerator(vector<AST*> ast, map<string, varType> symbolTable);
    void generate_x86();
};

#endif //ABERDEPYTHONCOMPILER_CODEGEN_H