#include "analyzer.h"

SemanticAnalyzer::SemanticAnalyzer() {}

SemanticAnalyzer::SemanticAnalyzer(vector<AST*> astList) {
    this->astList = astList;
}

vector<AST*> SemanticAnalyzer::analyze() {
    for (int i = 0; i < astList.size(); i++) {
        AST *root = astList[i];
        analyze_assignments(root); //add all assignments in code to symbol tree
        analyze_tree(root); //check if any identifiers are accessed while unreferenced
    }
    return astList; // if all is good, return the original AST vector from the parser
}

void SemanticAnalyzer::analyze_tree(AST *node) {
    if (node == nullptr) return;
    if (node->t.type == TOK_IDENTIFIER) {
        if (symbolTable.find(node->t.word) == symbolTable.end()) {
            cout << "NameError on line " << node->t.line_num << ", the name " << node->t.word << " is not defined." << endl;
            exit(1);
        }
    }
    analyze_tree(node->left);
    analyze_tree(node->right);
    analyze_tree(node->third_child);
}

void SemanticAnalyzer::analyze_assignments(AST *node) {
    if (node == nullptr) return;
    if (node->t.type == TOK_ASSIGNMENT)
        symbolTable.insert({node->left->t.word, tokToVarType(node->right->t.type)});
    analyze_assignments(node->left);
    analyze_assignments(node->right);
    analyze_assignments(node->third_child);
}

varType SemanticAnalyzer::tokToVarType(Token t) {
    if (t == TOK_NUM) return Integer;
    return Boolean;
}

void SemanticAnalyzer::print() {
    for (int i = 0; i < astList.size(); i++) {
        preOrderTraversal(astList[i]);
        cout << endl;
    }
}

void SemanticAnalyzer::preOrderTraversal(AST* node) {
    if (node == nullptr) return;
    cout << node->t.word << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
    preOrderTraversal(node->third_child);
}

