#include "parser.h"

int main() {
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\parser\\parse_expression_test3.txt");
    lexer.print();
    Parser parser(tokens);
    AST* root = parser.parse_expression();
    parser.print(root);
    return 0;
}