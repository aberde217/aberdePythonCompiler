#include "codegen.h"
#include <string>
using namespace std;

CodeGenerator::CodeGenerator() {}

CodeGenerator::CodeGenerator(vector<AST*> ast, map<string, varType> symbolTable) {
    finalASTs = ast;
    this->symbolTable = symbolTable;
}

void CodeGenerator::generate_x86() {
    generate_data_segment();
    cout << endl;
    generate_code_segment();
}

void CodeGenerator::generate_data_segment() {
    cout << ".data" << endl;
    for (pair p : symbolTable) {
        cout << p.first << " DD 0" << endl;
    }
}

void CodeGenerator::generate_code_segment() {
    cout << ".code\nmain proc" << endl;
    for (int i = 0; i < finalASTs.size(); i++) {
        generate_statement_code(finalASTs[i]);
    }
    cout << "end main" << endl;
}

void CodeGenerator::generate_statement_code(AST *node) {
    if (node->t.type == TOK_ASSIGNMENT) {
        generate_expression_code(node->right);
        cout << "mov " << node->left->t.word << ", eax" << endl;
    }
}

void CodeGenerator::generate_expression_code(AST* node) {
    if (node == nullptr) return;
    //checks for literals or identifiers, and moves them into EAX register
    if (node->t.type == TOK_NUM)
        cout << "mov eax, " << node->t.word << endl;
    else if (node->t.type == TOK_TRUE)
        cout << "mov eax, 1" << endl;
    else if (node->t.type == TOK_FALSE)
        cout << "mov eax, 0" << endl;
    else if (node->t.type == TOK_IDENTIFIER) {
        cout << "mov eax, " << node->t.word << endl;
    }

    // checks for generate operators: +, -, *, /
    else if (node->t.type == TOK_PLUS) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "add eax, ebx" << endl;
    }
    else if (node->t.type == TOK_MINUS) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "sub ebx, eax" << endl;
        cout << "mov eax, ebx" << endl;
    }
    else if (node->t.type == TOK_MULT) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "imul eax, ebx" << endl; // one operand mul places upper 32 bits into EDX. only imul supports two operand instruction
    }
    else if (node->t.type == TOK_DIV) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "xchg eax, ebx" << endl; //swaps register eax and ebx, as we want ebx value to be the dividend
        cout << "idiv ebx" << endl; //div/idiv doesn't support multi-operand instructions. We'll assume quotient is small enough to fit completely in EAX, where EDX is just 0s.
    }

    // checks for generate comparison operators: <, <=, >, >=, ==
    else if (node->t.type == TOK_LESST) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "cmp ebx, eax" << endl;
        cout << "setl al" << endl;
        cout << "movzx eax, al" << endl;
    }
    else if (node->t.type == TOK_GREATERT) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "cmp ebx, eax" << endl;
        cout << "setg al" << endl;
        cout << "movzx eax, al" << endl;
    }
    else if (node->t.type == TOK_LEQ) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "cmp ebx, eax" << endl;
        cout << "setle al" << endl;
        cout << "movzx eax, al" << endl;
    }
    else if (node->t.type == TOK_GEQ) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "cmp ebx, eax" << endl;
        cout << "setge al" << endl;
        cout << "movzx eax, al" << endl;
    }
    else if (node->t.type == TOK_EQEQ) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "cmp ebx, eax" << endl;
        cout << "sete al" << endl;
        cout << "movzx eax, al" << endl;
    }
    else if (node->t.type == TOK_NEQ) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "cmp ebx, eax" << endl;
        cout << "setne al" << endl;
        cout << "movzx eax, al" << endl;
    }

    //checks for operators 'and', 'or', and 'not'
    else if (node->t.type == TOK_AND) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "and eax, ebx" << endl; // bitwise AND equivalent to logical AND
    }
    else if (node->t.type == TOK_OR) {
        generate_expression_code(node->left);
        cout << "push eax" << endl;
        generate_expression_code(node->right);
        cout << "pop ebx" << endl;
        cout << "or eax, ebx" << endl; // bitwise OR equivalent to logical OR
    }
    else if (node->t.type == TOK_NOT) {
        generate_expression_code(node->left);
        cout << "cmp eax, 0" << endl; // checks if value is FALSE (0)
        cout << "sete al" << endl;
        cout << "movzx eax, al" << endl;
    }
}