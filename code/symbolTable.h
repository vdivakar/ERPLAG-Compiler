// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: symbolTable.h
// //*

#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include "symbolTableDef.h"

void push2(int stack_data, stack_node2* stack_top);
int is_stackEmpty2(stack_node2* top2);
int pop2(stack_node2* stack_top);
int top2(stack_node2* stack_top);
stack_node2* create_stack2();
int computeHashVal(char* str);
void insertInVarTable(varSymbolTable* table,char* parent_func, linked_list_node* current, char* type, int top2,int arr_or_var,int start,int end,linked_list_node* a_type_node, int nesting, FILE* fp);
void insertInFuncTable(funcSymbolTable* table, linked_list_node* current,int is_defined, int top2, FILE* fp);
varSymbolTable* initialize_var_ST();
funcSymbolTable* initialize_func_ST();
int addtoTrackerArray(int* array);
void populateSymbolTable(linked_list_node* list, varSymbolTable* VST, funcSymbolTable* FST, FILE* fp);


#endif

