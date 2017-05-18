// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: semanticAnalyzer.h
// //*

#ifndef SEMANTIC_DEF_H_
#define SEMANTIC_DEF_H_

#include "symbolTable.h"
#include "symbolTableDef.h"
#include "AST.h"

void process_switch_stmt(ASTNode* root);
void process_function_call(ASTNode* root, funcSymbolTable* FST);
void process_FOR_statement(ASTNode* id_node, ASTNode* root)	;
var_type find_type(ASTNode* root);
void process_array(ASTNode* root);
var_type find_type(ASTNode* root);
var_type assign_types(ASTNode* root);
void compare_types(ASTNode* root);

#endif