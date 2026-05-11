#include "4_codegen/codegen.h"
#include "5_interpreter/interpreter.h"

int main() {
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\source_code1.py");

    Parser parser(tokens);
    vector<AST*> astList = parser.parse();

    SemanticAnalyzer analyzer(astList);
    vector<AST*> finalASTs = analyzer.analyze();

    Interpreter interpreter(finalASTs);
    cout << "Program Output:\n--------------------" << endl;
    interpreter.execute(); //runs high-level program
    cout << endl;

    CodeGenerator cg(finalASTs, analyzer.symbolTable);
    cout << "x86 Assembly Code:\n--------------------" << endl;
    cg.generate_x86(); //prints x86 code
    return 0;
}