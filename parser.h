#ifndef ABERDEPYTHONCOMPILER_PARSER_H
#define ABERDEPYTHONCOMPILER_PARSER_H
#include "lexer.h"

struct AST {
    TokenPair t;
    AST *left, *right;
};

class Parser {
private:
    vector<TokenPair> tokens;
    int current_index;

    //Helper functions for recursive descent parsing algorithm
    AST* parse_or(); // parser hits an 'or' keyword (boolean or), lowest expression operator in precedence
    AST* parse_and(); // parser hits an 'and' keyword (boolean and), next lowest in precedence
    AST* parse_comparisons(); // parser hits comparison operator (lower precedence): ==, >, <, >=, <=, != (== and != have same precedence as other comparisons in Python)
    AST* parse_terms(); // parser hits + or - operators, lowest arithmetic precedence
    AST* parse_factors(); // parser hits * or / operators, next highest
    AST* parse_primary(); // parser hits identifiers or literals, highest precedence

    void preOrderTraversal(AST *root);
public:
    Parser();
    Parser(vector<TokenPair> tokens);
    AST* parse_expression();
    void print(AST *root);
};

#endif //ABERDEPYTHONCOMPILER_PARSER_H
