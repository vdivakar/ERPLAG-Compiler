// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: codeGen.h
// //*
#ifndef CODEGEN_DEF_H_
#define CODEGEN_DEF_H_

struct triple
{
	char op[50];
	int arg1;
	int arg2;
};

typedef struct triple triple;

int* indirect_tuple;
int tuple_length;
/*
	initially make an appropriate array. it is about to get filled, re-alloc the size

*/
void generateCode(ASTNode* root);
void handle_declareStmt(ASTNode* root);
void handle_ioStmt(ASTNode* root);
void handle_simpleStmt(ASTNode* root);
void handle_conditionalStmt(ASTNode* root);
void handle_iterativeStmt(ASTNode* root);

#endif
