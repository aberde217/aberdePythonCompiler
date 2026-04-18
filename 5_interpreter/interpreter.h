#ifndef ABERDEPYTHONCOMPILER_INTERPRETER_H
#define ABERDEPYTHONCOMPILER_INTERPRETER_H
#include "analyzer.h"

class Interpreter {
private:
    vector<AST*> astList;
    map<string, int> assignments;
    void execute_statement(AST *node);
    int execute_expression(AST *node);
public:
    Interpreter();
    Interpreter(vector<AST*> finalASTs);
    void execute();
};

#endif //ABERDEPYTHONCOMPILER_INTERPRETER_H
