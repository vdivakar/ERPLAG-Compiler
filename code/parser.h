// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: parser.h
// //*

#include "lexerDef.h"
#include<stdlib.h>
#include<stdio.h>
#define NUM_NON_TERMINALS 53
#define NUM_TERMINALS 59
#define NUM_TERMS 113
#define NUM_ROWS 54
#define NUM_COLUMNS 60
#define MAX_RHS 30
#define START_OF_TERMINALS 54 //null_val in enum Token/TERM
#define END_MARKER_SYMBOL -2


#ifndef PARSERDEF_H_
#define PARSERDEF_H_
typedef enum TERM TERM;
struct stack_node
{
	int stack_data;
	struct stack_node* next;
};
typedef struct stack_node stack_node;


struct queue_node
{
	int data;
	struct queue_node* next;
};
typedef struct queue_node queue_node;

stack_node* stack_top;
queue_node* queue_head;
queue_node* queue_end;

struct tree_queue
{
	struct tree_node* front;
	struct tree_node* end;
};
typedef struct tree_queue tree_queue;

struct tree_node
{
	struct tree_node * parent;
	struct tree_queue* children;
	struct tree_node* next;
	int num_children;		// if num_children == 0   => it is a Terminal / Leaf node.
	int level;
	enum TERM data;
	int g_index;	// grammar index
	int line_num;
	char lexeme[MAX_LEXEME_LENGTH];
    enum var_type tk_type; 
};
typedef struct tree_node tree_node;

struct parseTree
{
	struct tree_node* root;
	struct tree_node* current;
	int height;
};
typedef struct parseTree parseTree;

//DECLARATIONS FOR grammar.c

struct Grammar_Rule{
    TERM from;
    TERM* to;
    int count;
};
typedef struct Grammar_Rule rule;

int num_pt_nodes = 0;
int pt_memory = 1;

//////////////////////////////////////////////////////////////////////

void add_rule(rule* r1, TERM from, TERM to[], int n);

rule** generate_grammar();

void addToResultSet(TERM* result_set, TERM val);

void first (TERM* result, rule** grammar, TERM symbol);

void follow(TERM* result, rule** grammar, TERM symbol, TERM* follow_set);

//declarations for parser.c

void push(int stack_data);

int is_stackEmpty(stack_node* top);

int pop();

stack_node* create_stack();

queue_node* create_queue();

void enqueue( int data);

int dequeue();

void token_into_queue(linked_list_node* input_linkedList);

tree_node* create_treeNode();

tree_queue* create_treeQueue();

parseTree* create_parseTree();

void tree_enQueue(tree_queue* q, tree_node* new_child);

void print_InOrder_traversal(tree_node* root, FILE* fp);

TERM tree_deQueue(tree_queue* q);

void add_pnode_to_tree(parseTree* tree,tree_node* parent, TERM data,int g_index);

parseTree* parse(linked_list_node* input_linkedList);

//declarations from parserUtils.c
int is_terminal(int t);
int** createParseTable();
void print_a_table(int** table);
void populateParseTable(rule** grammar, int** table, int first_table[NUM_TERMS][MAX_RHS], int** follow_table);
void reset_array(TERM* array);
void generate_first_table(int first_table[NUM_TERMS][MAX_RHS], rule** grammar);
int** generate_follow_table(rule** grammar);
#endif


