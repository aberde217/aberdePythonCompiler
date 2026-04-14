#include "lexer.h"
using namespace std;

Lexer::Lexer() {
    source_code = "";
    line = 1;
}

vector<TokenPair> Lexer::lex(string file_path) {
    source_code = ""; // clears string in case another file was read previously
    ifstream input_file(file_path);
    if (!input_file.is_open()) {
        cout << "File path is not valid" << endl;
        exit(1);
    }
    string line;
    while (getline(input_file, line)) {
        source_code += line + '\n';
    }
    tokens = generateTokens(source_code);
    return tokens;
}

vector<TokenPair> Lexer::generateTokens(string source_code) {
    vector<TokenPair> tokens;
    string temp = "";
    tokens.clear();
    for (int i = 0; i < source_code.length(); i++) {
        // checking for keywords, literals, and identifiers
        if (isSingleCharOperator(source_code[i])) { // if true, that means temp MAY be a literal, keyword, or identifier
            if (temp == "True")
                tokens.push_back({TOK_TRUE, temp, line});
            else if (temp == "False")
                tokens.push_back({TOK_FALSE, temp, line});
            else if (temp == "print")
                tokens.push_back({TOK_PRINT, temp, line});
            else if (temp == "if")
                tokens.push_back({TOK_IF, temp, line});
            else if (temp == "else")
                tokens.push_back({TOK_ELSE, temp, line});
            else if (temp == "and")
                tokens.push_back({TOK_AND, temp, line});
            else if (temp == "or")
                tokens.push_back({TOK_OR, temp, line});
            else if (temp == "not")
                tokens.push_back({TOK_NOT, temp, line});
            else if (isdigit(temp[0]))
                tokens.push_back({TOK_NUM, temp, line});
            else if (isalpha(temp[0]) || temp[0] == '_')
                tokens.push_back({TOK_IDENTIFIER, temp, line});
            temp = "";
        }
        //checks operators
        if (source_code[i] == '#') { //checks for comments
            i++;
            while (source_code[i] != '\n')
                i++;
            continue;
        }
        if (source_code[i] == ':')
            tokens.push_back({TOK_COLON, string(1, source_code[i]), line});
        else if (source_code[i] == '(')
            tokens.push_back({TOK_LEFTP, string(1, source_code[i]), line});
        else if (source_code[i] == ')')
            tokens.push_back({TOK_RIGHTP, string(1, source_code[i]), line});
        else if (source_code[i] == '+')
            tokens.push_back({TOK_PLUS, string(1, source_code[i]), line});
        else if (source_code[i] == '-')
            tokens.push_back({TOK_MINUS, string(1, source_code[i]), line});
        else if (source_code[i] == '*')
            tokens.push_back({TOK_MULT, string(1, source_code[i]), line});
        else if (source_code[i] == '/')
            tokens.push_back({TOK_DIV, string(1, source_code[i]), line});
        else if (i != source_code.length() - 1) {
            if (source_code[i] == '=' && source_code[i+1] != '=')
                tokens.push_back({TOK_ASSIGNMENT, string(1, source_code[i]), line});
            else if (source_code[i] == '=' && source_code[i+1] == '=') {
                string val = "";
                val += source_code[i];
                val += source_code[i+1];
                i++;
                tokens.push_back({TOK_EQEQ, val, line});
            }
            else if (source_code[i] == '<' && source_code[i+1] != '=')
                tokens.push_back({TOK_LESST, string(1, source_code[i]), line});
            else if (source_code[i] == '<' && source_code[i+1] == '=') {
                string val = "";
                val += source_code[i];
                val += source_code[i+1];
                i++;
                tokens.push_back({TOK_LEQ, val, line});
            }
            else if (source_code[i] == '>' && source_code[i+1] != '=')
                tokens.push_back({TOK_GREATERT, string(1, source_code[i]), line});
            else if (source_code[i] == '>' && source_code[i+1] == '=') {
                string val = "";
                val += source_code[i];
                val += source_code[i+1];
                tokens.push_back({TOK_GEQ, val, line});
                i++;
            }
            else if (source_code[i] == '!' && source_code[i+1] == '=') {
                string val = "";
                val += source_code[i];
                val += source_code[i+1];
                tokens.push_back({TOK_NEQ, val, line});
                i++;
            }
            else if (source_code[i] != ' ' && source_code[i] != '\n' && source_code[i] != '\t') temp += source_code[i];
        }
        // checks end of statement
        if (source_code[i] == '\n') {
            tokens.push_back({TOK_NL, string(1, source_code[i]), line});
            line++;
        }

    }
    tokens.push_back({TOK_EOF, "", line});
    return tokens;
}

bool Lexer::isSingleCharOperator(char ch) { // returns true if ch is a single char operator OR space/tab (or new line, AKA end of statement
    return ch == ' ' || ch == '=' || ch == '(' || ch == ')' || ch == ':' || ch == '<' || ch == '>' || ch == '\n' || ch == '\t' || ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

string Lexer::streq(Token t) { // converts token to string, used for printing the tokens in vector 'tokens' (FOR TESTING)
    if (t == TOK_NL) return "TOK_NL";
    if (t == TOK_IDENTIFIER) return "TOK_IDENTIFIER";
    if (t == TOK_NUM) return "TOK_NUM";
    if (t == TOK_TRUE) return "TOK_TRUE";
    if (t == TOK_FALSE) return "TOK_FALSE";
    if (t == TOK_PRINT) return "TOK_PRINT";
    if (t == TOK_IF) return "TOK_IF";
    if (t == TOK_ELSE) return "TOK_ELSE";
    if (t == TOK_LEFTP) return "TOK_LEFTP";
    if (t == TOK_RIGHTP) return "TOK_RIGHTP";
    if (t == TOK_AND) return "TOK_AND";
    if (t == TOK_OR) return "TOK_OR";
    if (t == TOK_NOT) return "TOK_NOT";
    if (t == TOK_ASSIGNMENT) return "TOK_ASSIGNMENT";
    if (t == TOK_COLON) return "TOK_COLON";
    if (t == TOK_EQEQ) return "TOK_EQEQ";
    if (t == TOK_GEQ) return "TOK_GEQ";
    if (t == TOK_LEQ) return "TOK_LEQ";
    if (t == TOK_NEQ) return "TOK_NEQ";
    if (t == TOK_LESST) return "TOK_LESST";
    if (t == TOK_GREATERT) return "TOK_GREATERT";
    if (t == TOK_PLUS) return "TOK_PLUS";
    if (t == TOK_MINUS) return "TOK_MINUS";
    if (t == TOK_MULT) return "TOK_MULT";
    if (t == TOK_MULT) return "TOK_DIV";
    return "TOK_EOF";
}

void Lexer::print() {
    cout << "Source Code:" << endl;
    cout << source_code << endl;
    cout << "Tokens:" << endl;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].word == "\n")
            cout << "(" << streq(tokens[i].type) << ", \"" << "\\n" << "\", line " << tokens[i].line_num << ")";
        else cout << "(" << streq(tokens[i].type) << ", \"" << tokens[i].word << "\", line " << tokens[i].line_num << ")";
    }
    cout << endl << endl;
}


