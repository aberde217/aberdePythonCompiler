#ifndef ABERDEPYTHONCOMPILER_LEXER_H
#define ABERDEPYTHONCOMPILER_LEXER_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

enum Token { //token types
    TOK_NL, //new Line, end of command
    TOK_IDENTIFIER, //identifier
    TOK_NUM, //number literal
    TOK_TRUE, //true literal
    TOK_FALSE, //false literal
    TOK_PRINT, //print keyword
    TOK_IF, //if keyword
    TOK_ELSE, //else keyword
    TOK_LEFTP, // ( operator
    TOK_RIGHTP, // ) operator
    TOK_AND, //and keyword
    TOK_OR, //or keyword
    TOK_ASSIGNMENT, //= assignment operator
    TOK_COLON, //: operator, used in if statement
    TOK_EQEQ, //== operator
    TOK_GEQ, //>= operator
    TOK_LEQ, //<= operator
    TOK_NEQ, //!= operator
    TOK_LESST, //< operator
    TOK_GREATERT, //> operator
    TOK_PLUS, //+ operator
    TOK_MINUS, //- operator
    TOK_MULT, //* operator
    TOK_DIV // / operator
};

struct TokenPair { //
    Token type;
    string word;
};

class Lexer {
private:
    string source_code;
    vector<TokenPair> tokens;
    vector<TokenPair> generateTokens(string source_code);
    bool isSingleCharOperator(char ch); // helper function for generateTokens
    string streq(Token t); // used for lexer testing
public:
    Lexer();
    vector<TokenPair> lex(string file_path);
    void print(); // used for lexer testing
};

#endif //ABERDEPYTHONCOMPILER_LEXER_H
