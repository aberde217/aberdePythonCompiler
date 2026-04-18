/*#include "interpreter.h"

int main() {
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\5_interpreter\\interpreter_test4.txt");
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
    cout << endl;
    Interpreter interpreter(final_asts);
    cout << "Program Output\n-----------------" << endl;
    interpreter.execute();
    cout << endl;
    return 0;
}*/