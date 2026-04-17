#ifndef ABERDEPYTHONCOMPILER_ANALYZER_H
#define ABERDEPYTHONCOMPILER_ANALYZER_H
#include "parser.h"
#include <map>

enum varType {
    Integer,
    Boolean
};

class SemanticAnalyzer {
private:
    vector<AST*> astList;
    varType tokToVarType(Token t); // converts token (literal type) to varType
    void analyze_assignments(AST* node); // first-pass, stores all assignments in symbol table
    void analyze_tree(AST *node); // second-pass, checks tree for potential unreferenced identifiers

    void preOrderTraversal(AST *node); // helper function for printing (testing)
public:
    map<string, varType> symbolTable; //simplicity in code generation
    SemanticAnalyzer();
    SemanticAnalyzer(vector<AST*> astList);
    vector<AST*> analyze();
    void print(); // for semantic analyzer testing
};

#endif //ABERDEPYTHONCOMPILER_ANALYZER_H
