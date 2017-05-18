// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: symbolTableDef.h
// //*

#ifndef SYMBOL_TABLE_DEF_H_
#define SYMBOL_TABLE_DEF_H_

#include "lexerDef.h"

#define PRIME_NUMBER 457

typedef struct varTableEntry varTableEntry;
typedef struct varSymbolTable varSymbolTable;
typedef struct funcTableEntry funcTableEntry;
typedef struct funcSymbolTable funcSymbolTable;
typedef struct array array;
typedef enum var_type var_type;
typedef struct plist plist;

char* var_map[5] = {"None","Integer", "Real", "Boolean", "module"};
int var_width[4] = {0,2, 4, 1};

struct plist			// parameters list for the functable entry
{
	varTableEntry* v_ptr;
	struct plist* next;
};

struct funcTableEntry
{
	char name[MAX_LEXEME_LENGTH];  //var name
	int key;
	int scope[2]; //a[0] -> start of scope; a[1] ->end of scope (line  numbers)
	int is_defined;
	int line_num;

	int num_input_params;
	int num_output_params;
	plist* input_plist;
	plist* output_plist;

	struct funcTableEntry* next;
}; 

struct funcSymbolTable
{
	funcTableEntry** entries;
};

struct array
{
	enum var_type type;
	int width[2];  // width[0] => start index , width[1] => end index
	//final-initial+1
	//a[1..10], 1..10 is a single lexeme
};

struct varTableEntry
{
	char name[MAX_LEXEME_LENGTH];  //var name
	int key;
	int scope[2]; //a[0] -> start of scope; a[1] ->end of scope (line  numbers)
	int is_array; //flag
	int line_num;
	union
	{
		enum var_type var_type; 
		struct array arr;
	} arr_or_var;
	struct varTableEntry* next;
	int offset;
	int width;
	char parent_func[MAX_LEXEME_LENGTH];
	int scope_level;
};

struct varSymbolTable
{
	varTableEntry** entries;
};

struct stack_node2
{
	int stack_data;
	struct stack_node2* next;
};
typedef struct stack_node2 stack_node2;

#endif