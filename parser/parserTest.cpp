#include "parser.h"

int main() {
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\source3.txt");
    lexer.print();
    Parser parser(tokens);
    vector<AST*> asts = parser.parse();
    cout << "AST(s) Generated:" << endl;
    for (int i = 0; i < asts.size(); i++) {
        parser.printAST(asts[i]);
    }
    return 0;
}

/* Code for testing parse_expression()
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\parser\\parse_expression_test6.txt");
    lexer.print();
    Parser parser(tokens);
    AST* root = parser.parse_expression();
    parser.printAST(root);
    return 0;
 */
