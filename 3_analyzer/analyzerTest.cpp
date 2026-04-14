#include "analyzer.h"

int main() {
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\analyzer\\analyzer_test2.txt");
    lexer.print();
    Parser parser(tokens);
    vector<AST*> asts = parser.parse();
    cout << "AST(s) Generated:" << endl;
    for (int i = 0; i < asts.size(); i++) {
        parser.printAST(asts[i]);
    }
    cout << endl;
    SemanticAnalyzer analyzer(asts);
    vector<AST*> final_asts = analyzer.analyze();
    cout << "Final AST(s):" << endl;
    analyzer.print();
    return 0;
}