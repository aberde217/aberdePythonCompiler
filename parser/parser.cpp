#include "parser.h"
using namespace std;

Parser::Parser() {
    current_index = 0;
}

Parser::Parser(vector<TokenPair> tokens) {
    current_index = 0;
    this->tokens = tokens;
}

AST *Parser::parse_expression() {
    return parse_or();
}

AST *Parser::parse_or() {
    AST *left_child = parse_and();
    TokenPair op = tokens[current_index];
    if (op.type != TOK_OR)
        return left_child;
    AST *root;
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
    AST *root;
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
    AST *root;
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
        return leaf;
    }
    if (current.type != TOK_IDENTIFIER && current.type != TOK_NUM && current.type != TOK_TRUE && current.type != TOK_FALSE) {
        cout << "SyntaxError: compilation failed." << endl;
        exit(1);
    }
    AST* leaf = new AST(current, nullptr, nullptr);
    current_index++;
    return leaf;
}

void Parser::preOrderTraversal(AST *node) {
    if (node == nullptr) return;
    cout << node->t.word << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void Parser::print(AST *root) {
    preOrderTraversal(root);
}


