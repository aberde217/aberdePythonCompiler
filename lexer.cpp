#include "lexer.h"
using namespace std;

Lexer::Lexer() {
    source_code = "";
}

vector<Token> Lexer::lex(string file_path) {
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

vector<Token> Lexer::generateTokens(string source_code) {
    vector<Token> tokens;
    string temp = "";
    tokens.clear();
    for (int i = 0; i < source_code.length(); i++) {
        Token t;
        // checking for keywords, literals, and identifiers
        if (isSingleCharOperator(source_code[i])) { // if true, that means temp MAY be a literal, keyword, or identifier
            if (temp == "True") {
                t = TOK_TRUE;
                tokens.push_back(t);
            }
            else if (temp == "False") {
                t = TOK_FALSE;
                tokens.push_back(t);
            }
            else if (temp == "print") {
                t = TOK_PRINT;
                tokens.push_back(t);
            }
            else if (temp == "if") {
                t = TOK_IF;
                tokens.push_back(t);
            }
            else if (temp == "else") {
                t = TOK_ELSE;
                tokens.push_back(t);
            }
            else if (temp == "and") {
                t = TOK_AND;
                tokens.push_back(t);
            }
            else if (temp == "or") {
                t = TOK_OR;
                tokens.push_back(t);
            }
            else if (isdigit(temp[0])) {
                t = TOK_NUM;
                tokens.push_back(t);
            }
            else if (isalpha(temp[0]) || temp[0] == '_') {
                t = TOK_IDENTIFIER;
                tokens.push_back(t);
            }
            temp = "";
        }
        //checks operators
        if (source_code[i] == ':') {
            t = TOK_COLON;
            tokens.push_back(t);
        }
        else if (source_code[i] == '(') {
            t = TOK_LEFTP;
            tokens.push_back(t);
        }
        else if (source_code[i] == ')') {
            t = TOK_RIGHTP;
            tokens.push_back(t);
        }
        else if (source_code[i] == '+') {
            t = TOK_PLUS;
            tokens.push_back(t);
        }
        else if (source_code[i] == '-') {
            t = TOK_MINUS;
            tokens.push_back(t);
        }
        else if (source_code[i] == '*') {
            t = TOK_MULT;
            tokens.push_back(t);
        }
        else if (source_code[i] == '/') {
            t = TOK_DIV;
            tokens.push_back(t);
        }
        else if (i != source_code.length() - 1) {
            if (source_code[i] == '=' && source_code[i+1] != '=') {
                t = TOK_ASSIGNMENT;
                tokens.push_back(t);
            }
            else if (source_code[i] == ':') {
                t = TOK_COLON;
                tokens.push_back(t);
            }
            else if (source_code[i] == '<' && source_code[i+1] != '=') {
                t = TOK_LESST;
                tokens.push_back(t);
            }
            else if (source_code[i] == '>' && source_code[i+1] != '=') {
                t = TOK_GREATERT;
                tokens.push_back(t);
            }
            else if (source_code[i] == '=' && source_code[i+1] == '=') {
                t = TOK_EQEQ;
                tokens.push_back(t);
                i++;
            }
            else if (source_code[i] == '!' && source_code[i+1] == '=') {
                t = TOK_NEQ;
                tokens.push_back(t);
                i++;
            }
            else if (source_code[i] == '>' && source_code[i+1] == '=') {
                t = TOK_GEQ;
                tokens.push_back(t);
                i++;
            }
            else if (source_code[i] == '<' && source_code[i+1] == '=') {
                t = TOK_LEQ;
                tokens.push_back(t);
                i++;
            }
            else if (source_code[i] != ' ' && source_code[i] != '\n' && source_code[i] != '\t') temp += source_code[i];
        }
        // checks end of statement
        if (source_code[i] == '\n') {
            t = TOK_NL;
            tokens.push_back(t);
        }
    }
    return tokens;
}

bool Lexer::isSingleCharOperator(char ch) { // returns true if ch is a single char operator OR space/tab (or new line, AKA end of statement
    return ch == ' ' || ch == '=' || ch == '(' || ch == ')' || ch == ':' || ch == '<' || ch == '>' || ch == '\n' || ch == '\t' || ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

string Lexer::streq(Token t) { // converts token to string, used for printing the tokens in vector 'tokens' (FOR TESTING
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
    return "TOK_DIV";
}

void Lexer::print() {
    cout << "Source Code:" << endl;
    cout << source_code << endl;
    cout << "Tokens:" << endl;
    for (int i = 0; i < tokens.size(); i++) {
        cout << streq(tokens[i]) << " ";
    }
    cout << endl << endl;
}


