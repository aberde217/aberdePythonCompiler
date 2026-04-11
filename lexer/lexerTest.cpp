#include "lexer.h"
#include <vector>
using namespace std;

int main() {
    Lexer lexer;
    vector<TokenPair> tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\source2.txt");
    lexer.print();
    tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\source1.txt");
    lexer.print();
    tokens = lexer.lex("C:\\Users\\anayf\\CLionProjects\\aberdePythonCompiler\\source3.txt");
    lexer.print();
    return 0;
}
