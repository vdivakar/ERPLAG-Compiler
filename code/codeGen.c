// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: codeGen.c
// //*

#include "codeGenDef.h"

void generateCode(ASTNode* root)
{
	//root points to program
	//program -> driverModule -> moduleDef -> statements ->
	ASTNode* statements_node;
	ASTNode* temp = root->children[0]->children[0];
	if(temp->num_children > 0)
		statements_node = temp->children[0];

	while(statements_node != NULL && statements_node->num_children>0)
	{
		ASTNode* statement = statements_node->children[0];
		switch(statement->token)
		{
			case declareStmt:
			{
				handle_declareStmt(statement);
				break;
			}
			case ioStmt:
			{
				handle_ioStmt(statement);
				break;
			}
			case simpleStmt:
			{
				handle_simpleStmt(statement);
				break;
			}
			case conditionalStmt:
			{
				handle_conditionalStmt(statement);
				break;
			}
			case iterativeStmt:
			{
				handle_iterativeStmt(statement);
				break;
			}
			default:
				break;
		}

		if(statements_node->num_children > 1)
		{
			statements_node = statements_node->children[1];
		}
		else
			break;

	}
	return;
}

void handle_declareStmt(ASTNode* root)
{
	return;
}

void handle_ioStmt(ASTNode* root)
{
	return;
}

void handle_simpleStmt(ASTNode* root)
{
	return;
}

void handle_conditionalStmt(ASTNode* root)
{
	return;
}

void handle_iterativeStmt(ASTNode* root)
{
	return;
}
