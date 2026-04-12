#include "parser.h"
using namespace std;

Parser::Parser() {
    current_index = 0;
}

Parser::Parser(vector<TokenPair> tokens) {
    current_index = 0;
    this->tokens = tokens;
}

vector<AST*> Parser::parse() {
    vector<AST*> statement_asts;
    TokenPair current = tokens[current_index];
    while (current.type != TOK_EOF) {
        AST* root = parse_statement();
        if (root == nullptr) break; // EOF is reached
        statement_asts.push_back(root);
        current = tokens[current_index];
    }
    return statement_asts;
}

AST *Parser::parse_statement() {
    TokenPair current = tokens[current_index];
    while (current.type == TOK_NL) { // skips over new-lines (we dont want a new line token parsed)
        current_index++;;
        current = tokens[current_index];
    }
    if (current.type == TOK_IF) return parse_if();
    if (current.type == TOK_PRINT) return parse_print();
    if (current.type == TOK_IDENTIFIER) return parse_assignment();
    if (current.type == TOK_EOF) return nullptr;
    cout << "SyntaxError: compilation failed." << endl;
    exit(1);
}

AST *Parser::parse_if() {
    TokenPair if_keyword = tokens[current_index];
    current_index++;
    AST *node_condition = parse_expression(); // "left child"
    if (tokens[current_index].type != TOK_COLON) {
        cout << "SyntaxError: compilation failed." << endl;
        exit(1);
    }
    current_index++;
    AST *node_if_action = parse_statement(); // "right child"
    AST *node_else_action = nullptr; // "third child"
    while (tokens[current_index].type == TOK_NL) current_index++;
    if (tokens[current_index].type == TOK_ELSE) {
        current_index++;
        if (tokens[current_index].type != TOK_COLON) {
            cout << "SyntaxError: compilation failed." << endl;
            exit(1);
        }
        current_index++;
        node_else_action = parse_statement();
    }
    AST *root = new AST(if_keyword, node_condition, node_if_action, node_else_action);
    return root;
}

AST *Parser::parse_print() {
    TokenPair print = tokens[current_index];
    current_index++;
    if (tokens[current_index].type != TOK_LEFTP) {
        cout << "SyntaxError: compilation failed." << endl;
        exit(1);
    }
    current_index++;
    AST *node_left = parse_expression();
    AST *root = new AST(print, node_left);
    if (tokens[current_index].type != TOK_RIGHTP) {
        cout << "SyntaxError: compilation failed." << endl;
        exit(1);
    }
    current_index++;
    return root;
}

AST *Parser::parse_assignment() {
    AST *node_left = new AST(tokens[current_index], nullptr, nullptr);
    current_index++;
    TokenPair op = tokens[current_index];
    if (op.type != TOK_ASSIGNMENT) {
        cout << "SyntaxError: compilation failed." << endl;
        exit(1);
    }
    current_index++;
    AST *node_right = parse_expression();
    AST *root = new AST(op, node_left, node_right);
    return root;
}

AST *Parser::parse_expression() {
    return parse_or();
}

AST *Parser::parse_or() {
    AST *left_child = parse_and();
    TokenPair op = tokens[current_index];
    if (op.type != TOK_OR)
        return left_child;
    AST *root = nullptr;
    while (op.type == TOK_OR) { // checks for (potential) chain of or
        current_index++;
        AST *right_child = parse_and();
        root = new AST(op, left_child, right_child);
        left_child = root; // left-associative, right subtrees are evaluated first
        op = tokens[current_index];
    }
    return root;
}

AST *Parser::parse_and() {
    AST *left_child = parse_comparisons();
    TokenPair op = tokens[current_index];
    if (op.type != TOK_AND)
        return left_child;
    AST *root = nullptr;
    while (op.type == TOK_AND) { // checks for (potential) chain of and
        current_index++;
        AST *right_child = parse_comparisons();
        root = new AST(op, left_child, right_child);
        left_child = root; // left-associative, right subtrees are evaluated first
        op = tokens[current_index];
    }
    return root;
}

AST *Parser::parse_comparisons() {
    AST* left_child = parse_terms();
    TokenPair op = tokens[current_index];
    if (op.type != TOK_EQEQ && op.type != TOK_NEQ && op.type != TOK_GREATERT && op.type != TOK_GEQ && op.type != TOK_LESST && op.type != TOK_LEQ)
        return left_child;
    AST *root = nullptr;
    while (op.type == TOK_EQEQ || op.type == TOK_NEQ || op.type == TOK_GREATERT || op.type == TOK_GEQ || op.type == TOK_LESST || op.type == TOK_LEQ) { // checks for (potential) chain of comparisons
        current_index++;
        AST *right_child = parse_terms();
        root = new AST(op, left_child, right_child);
        left_child = root; // left-associative, right subtrees are evaluated first
        op = tokens[current_index];
    }
    return root;
}

AST *Parser::parse_terms() {
    AST* left_child = parse_factors();
    TokenPair op = tokens[current_index];
    if (op.type != TOK_PLUS && op.type != TOK_MINUS)
        return left_child;
    AST *root;
    while (op.type == TOK_PLUS || op.type == TOK_MINUS) { // checks for (potential) chain of + or - (ex. (a * b) + c - d)
        current_index++;
        AST *right_child = parse_factors();
        root = new AST(op, left_child, right_child);
        left_child = root; // left-associative, right subtrees are evaluated first
        op = tokens[current_index];
    }
    return root;
}

AST *Parser::parse_factors() {
    AST* left_child = parse_primary();
    TokenPair op = tokens[current_index];
    if (op.type != TOK_MULT && op.type != TOK_DIV)
        return left_child; // the primary itself can be valid, doesn't mean error
    AST *root;
    while (op.type == TOK_MULT || op.type == TOK_DIV) { // checks for (potential) chain of * or / (ex. a * b / c)
        current_index++;
        AST *right_child = parse_primary();
        root = new AST(op, left_child, right_child);
        left_child = root; // left-associative, right subtrees are evaluated first
        op = tokens[current_index];
    }
    return root;
}

AST *Parser::parse_primary() {
    TokenPair current = tokens[current_index];
    if (current.type == TOK_LEFTP) {
        current_index++;
        AST* leaf = parse_expression();
        TokenPair new_current = tokens[current_index];
        if (new_current.type != TOK_RIGHTP) {
            cout << "SyntaxError: compilation failed." << endl;
            exit(1);
        }
        current_index++;
        return leaf;
    }
    if (current.type != TOK_IDENTIFIER && current.type != TOK_NUM && current.type != TOK_TRUE && current.type != TOK_FALSE) {
        cout << "SyntaxError: compilation failed." << endl;
        exit(1);
    }
    AST* leaf = new AST(current);
    current_index++;
    return leaf;
}

void Parser::preOrderTraversal(AST *node) {
    if (node == nullptr) return;
    cout << node->t.word << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
    preOrderTraversal(node->third_child);
}

void Parser::printAST(AST *root) {
    preOrderTraversal(root);
    cout << endl;
}


