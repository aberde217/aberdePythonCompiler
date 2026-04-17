#include "codegen.h"

int main() {
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\4_codegen\\codegen_test7.txt");
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
    CodeGenerator cg(final_asts, analyzer.symbolTable);
    cout << "Assembly Code:\n--------------------------" << endl;
    cg.generate_x86();
}