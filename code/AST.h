// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: AST.h
// //*

#ifndef AST_H
#define AST_H

#include "lexerDef.h"
#include "symbolTable.h"
#include "lexerDef.h"
#include "parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLAGS 10

typedef Token TERM;

enum ast_action
{
	REPLACE_NULL, TRIM, COLLAPSE_CHAIN  //0,1,2
};

struct _ASTRuleNode
{
    enum ast_action action; // 0: trim, 1: collapse linear chain, -1: replace with NULL
    int num_children;
    int rule_length;
  	int* in_ast;
};
typedef struct _ASTRuleNode ASTRuleNode;

struct _ASTNode
{
    int rule_no;
    char lexeme[MAX_LEXEME_LENGTH];
    int line_num;
    TERM token;
    int num_children;
    // struct _ASTNode* next;
    struct _ASTNode* parent;
    struct _ASTNode** children;
    enum var_type tk_type;
    int is_array;
};
typedef struct _ASTNode ASTNode;

int num_ast_nodes = 0;
int ast_memory = 0;

FILE* fp_ast;

void add_ast_rule(ASTRuleNode* r, enum ast_action action, int rule_length);
ASTNode* initializeASTNode(int rule_no, TERM tk, int line_num, char* lexeme);
ASTRuleNode** createASTRuleList();
ASTNode* createASTfromPT(tree_node* p, ASTRuleNode** ast_rules, ASTNode* parent);
ASTNode* assign_Datatype(varSymbolTable* VST, funcSymbolTable* FST, ASTNode* root );
ASTNode* correct_chain_collapse(tree_node* p, ASTRuleNode** ast_rules, ASTNode* parent);
void displayAST(ASTNode* root);

#endif