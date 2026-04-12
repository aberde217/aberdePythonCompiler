#ifndef ABERDEPYTHONCOMPILER_PARSER_H
#define ABERDEPYTHONCOMPILER_PARSER_H
#include "lexer.h"

struct AST {
    TokenPair t;
    AST *left = nullptr;
    AST *right = nullptr;
    AST *third_child = nullptr; //if statements MAY need three children, (condition, statement for true, statement for else). Default should be nullptr, unless otherwise
};

class Parser {
private:
    vector<TokenPair> tokens;
    int current_index, line_number;

    //Helper functions for parsing statements
    AST* parse_statement();
    AST* parse_if(); // parses if/else statements
    AST* parse_print(); // parses print function calls
    AST* parse_assignment(); // parses assignment statements

    //Helper functions for parsing expressions, from greatest to least precedence
    AST* parse_expression();
    AST* parse_or(); // parser hits an 'or' keyword (boolean or), lowest expression operator in precedence
    AST* parse_and(); // parser hits an 'and' keyword (boolean and), next lowest in precedence
    AST* parse_comparisons(); // parser hits comparison operator (lower precedence): ==, >, <, >=, <=, != (== and != have same precedence as other comparisons in Python)
    AST* parse_terms(); // parser hits + or - operators, lowest arithmetic precedence
    AST* parse_factors(); // parser hits * or / operators, next highest
    AST* parse_primary(); // parser hits identifiers or literals, highest precedence

    void preOrderTraversal(AST *root); // used for printing ASTs
public:
    Parser();
    Parser(vector<TokenPair> tokens);
    vector<AST*> parse();
    void printAST(AST *root);
};

#endif //ABERDEPYTHONCOMPILER_PARSER_H
