#include "interpreter.h"
using namespace std;

Interpreter::Interpreter() {}

Interpreter::Interpreter(vector<AST*> finalASTs) {
    astList = finalASTs;
}

void Interpreter::execute() {
    for (int i = 0; i < astList.size(); i++) {
        AST* root = astList[i];
        execute_statement(root);
    }
    cout << "Program ran successfully." << endl;
}

void Interpreter::execute_statement(AST *node) {
    if (node->t.type == TOK_ASSIGNMENT)
        assignments[node->left->t.word] = execute_expression(node->right);
    if (node->t.type == TOK_PRINT)
        cout << execute_expression(node->left) << endl;
    if (node->t.type == TOK_IF) {
        int condition = execute_expression(node->left);
        if (condition == 1) execute_statement(node->right);
        else if (node->third_child != nullptr) execute_statement(node->third_child);
    }
}

int Interpreter::execute_expression(AST *node) {
    //Base Case(s): node is a literal or identifier
    if (node->t.type == TOK_NUM)
        return stoi(node->t.word);
    if (node->t.type == TOK_TRUE)
        return 1;
    if (node->t.type == TOK_FALSE)
        return 0;
    if (node->t.type == TOK_IDENTIFIER)
        return assignments.find(node->t.word)->second;
    // Arithmetic Operators
    if (node->t.type == TOK_MULT)
        return execute_expression(node->left) * execute_expression(node->right);
    if (node->t.type == TOK_DIV)
        return execute_expression(node->left)/execute_expression(node->right);
    if (node->t.type == TOK_PLUS)
        return execute_expression(node->left) + execute_expression(node->right);
    if (node->t.type == TOK_MINUS)
        return execute_expression(node->left) - execute_expression(node->right);
    //Comparison Operators
    if (node->t.type == TOK_EQEQ)
        return execute_expression(node->left) == execute_expression(node->right);
    if (node->t.type == TOK_NEQ)
        return execute_expression(node->left) != execute_expression(node->right);
    if (node->t.type == TOK_LESST)
        return execute_expression(node->left) < execute_expression(node->right);
    if (node->t.type == TOK_LEQ)
        return execute_expression(node->left) <= execute_expression(node->right);
    if (node->t.type == TOK_GREATERT)
        return execute_expression(node->left) > execute_expression(node->right);
    if (node->t.type == TOK_GEQ)
        return execute_expression(node->left) >= execute_expression(node->right);
    //BOOLEAN and, or, not
    if (node->t.type == TOK_AND)
        return execute_expression(node->left) && execute_expression(node->right);
    if (node->t.type == TOK_OR)
        return execute_expression(node->left) || execute_expression(node->right);
    return !execute_expression(node->left); //TOK_NOT
}



