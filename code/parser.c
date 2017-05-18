// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: parser.c
// //*

#include <stdio.h>
#include "parserUtils.c"
#include "parser.h"
#include "lexerDef.h"
#define ROOT_LEVEL 0

void push(int stack_data)
{
	stack_node* temp = (stack_node*)malloc(sizeof(stack_node));
	if(!temp)
		return;
	temp->stack_data = stack_data;
	temp->next = stack_top->next;
	stack_top->next = temp;
	return;
}

int is_stackEmpty(stack_node* top)
{
	if(top->next==NULL)
		return 1;
	return 0;
}

int pop()
{
	if(is_stackEmpty(stack_top))
		return -1;
	int x = stack_top->next->stack_data;
	stack_node* f = stack_top->next;
	stack_top->next = stack_top->next->next;
	// free(f);
	return x;
}

stack_node* create_stack()
{
	stack_node* a = (stack_node*)malloc(sizeof(stack_node));
	a->next = NULL;
	a->stack_data = 0;
	return a;
}

queue_node* create_queue()
{
	return NULL;
}
void enqueue( int data)
{
	queue_node* new_node = (queue_node*)malloc(sizeof(queue_node));
	new_node->data = data;
	new_node->next = NULL;
	if(queue_head == NULL && queue_end == NULL)
	{
		queue_head = new_node;
		queue_end = new_node;
	}
	else
		{
			queue_end->next = new_node;
			queue_end = new_node;
	}
}
int dequeue()
{
	if(queue_head == NULL)
		return -1;
	else if(queue_head == queue_end)
	{
		int x = queue_head->data;
		free(queue_head);
		queue_head = NULL;
		queue_end = NULL;
		return x;
	}
	else
	{
		queue_node* temp = queue_head;
		int x = temp->data;
		queue_head = queue_head->next;
		free(temp);
		temp = NULL;
		return x;
	}
}
void token_into_queue(linked_list_node* input_linkedList)
{
	queue_head = NULL; // create_queue();
	queue_end = queue_head;
	linked_list_node* current = input_linkedList;
	while(current!= NULL)
	{
		int a = current->data->lexeme_token;
		enqueue(a);
		current = current->next;
	}
	return;
}

tree_node* create_treeNode()
{
	tree_node* node = (tree_node*)malloc(sizeof(tree_node));
	node->parent = NULL;
	node->children = NULL;
	node->next = NULL;
	node->num_children = 0;
	node->level = 0;
	node->data = NULL_VAL; //call create_token() from lexer.c to initialize
	node->g_index = 0;
	node->line_num = 0;
	node->tk_type = _NONE;
	strcpy(node->lexeme,""); 
	return node;
}

tree_queue* create_treeQueue()
{
	tree_queue* queue = (tree_queue*)malloc(sizeof(tree_queue));
	queue->front = NULL;
	queue->end = NULL;
	return queue;
}

parseTree* create_parseTree()
{
	parseTree* pTree = (parseTree*)malloc(sizeof(parseTree));
	pTree->root = create_treeNode();
	pTree->root->data = program;
	pTree->root->level = ROOT_LEVEL;
	pTree->root->children = create_treeQueue();
	pTree->height = 0;
	pTree->current = pTree->root;
	return pTree;
}

void tree_enQueue(tree_queue* q, tree_node* new_child)
{
	new_child->next = NULL;

	if(q->end)
		q->end->next = new_child;

	q->end = new_child;
	if(q->front == NULL)
		q->front = q->end;

	return;
}

void print_InOrder_traversal(tree_node* root, FILE* fp)
{
	int check_leaf = root->num_children;
	int n = 15;
	char *x = "---------";	
	if(root->num_children == 0 || root->children->front ==NULL )
	{
		printf("\n%*s", n, root->lexeme); //print lexeme
		fprintf(fp, "\n%*s",n, root->lexeme);
		printf("%*d ",n, root->line_num);  //print line number
		fprintf(fp,"%*d ",n, root->line_num);
		// printf("( %d)",root->tk_type );
		if(is_terminal(root->data)) //print TOKEN name
		{
			printf("%*s",n, token_map[root->data]);
			fprintf(fp,"%*s",n, token_map[root->data]);

		}
		else
		{
			printf("%*s",n, x);
			fprintf(fp,"%*s",n, x);
		}

		if(root->data == TK_NUM || root->data == TK_RNUM) //value if INT/REAL
		{
			printf("%*s\t ", n, root->lexeme);
			fprintf(fp,"%*s\t ", n, root->lexeme);

		}
		else
		{
			printf("%*s\t ", n, x);
			fprintf(fp,"%*s\t ", n, x);
		}

		if(root->parent!=NULL)  //print parent node 
		{
			printf("%*s", 25, token_map[root->parent->data]);
			fprintf(fp,"%*s", 25, token_map[root->parent->data]);
		}
		else
		{
			printf("\t\tROOT");
			fprintf(fp,"\t\tROOT");
		}

		if(check_leaf != 0)  //print is_leaf 
		{
			printf("\tNo\t ");
			fprintf(fp,"\tNo\t ");
		}
		else
		{
			printf("\tYes\t ");
			fprintf(fp,"\tYes\t ");
		}
		printf("%*s",25, token_map[root->data]);		
		fprintf(fp,"%*s",25, token_map[root->data]);
		return;

	}
	    print_InOrder_traversal(root->children->front, fp);

			printf("\n%*s", n, root->lexeme);
			fprintf(fp, "\n%*s ", n, root->lexeme);

		printf("%*d ",n, root->line_num);
		fprintf(fp, "%*d ",n, root->line_num);
		if(is_terminal(root->data))
		{
			printf("%*s",n, token_map[root->data]);
			fprintf(fp,"%*s",n, token_map[root->data]);
		}
		else
		{
			printf("%*s",n, x);
			fprintf(fp,"%*s",n, x);
		}

		if(root->data == TK_NUM || root->data == TK_RNUM)
		{
			printf("%*s\t ", n, root->lexeme);
			fprintf(fp,"%*s\t ", n, root->lexeme);
		}
		else
		{
			printf("%*s\t ", n, x);
			fprintf(fp,"%*s\t ", n, x);
		}
		if(root->parent!=NULL)
		{
			printf("%*s", 25, token_map[root->parent->data]);
			fprintf(fp,"%*s", 25, token_map[root->parent->data]);
		}
		else
		{
			printf("\t\tROOT");
			fprintf(fp,"\t\tROOT");
		}
		if(check_leaf != 0)
		{
			printf("\tNo\t ");
			fprintf(fp,"\tNo\t ");
		}
		else
		{
			printf("\tYes\t ");
			fprintf(fp,"\tYes\t ");
		}
		printf("%*s",25, token_map[root->data]);		
		fprintf(fp,"%*s",25, token_map[root->data]);

	tree_node* temp = root->children->front->next;
	if(temp != NULL)
	{
		int y = 0;
		while(y<root->num_children-1)
		{
			print_InOrder_traversal(temp, fp);
			if(temp->next != NULL)
			temp = temp->next;
			y++;
		}
	}
	return;
}

TERM tree_deQueue(tree_queue* q)
{
	TERM data;
	tree_node* temp;
	if(q->front == NULL)	// queue is empty
	{
		printf("tree queue is empty");
		return NULL_VAL;
	}
	else{
		temp = q->front;
		data = q->front->data;
		if(q->front == q->end)
		{
			q->front =NULL;
			q->end= NULL;
		}
		else{
			q->front = q->front->next;
		}
		free(temp);
		temp = NULL;
		return data;
	}
}

void add_pnode_to_tree(parseTree* tree,tree_node* parent, TERM data,int g_index)
{
	num_pt_nodes ++; 
	// printf("add pnode %d\n", num_pt_nodes);
	tree_node* newNode = create_treeNode();
	newNode->parent = parent;
	newNode->data = data;
	newNode->g_index = g_index;
	newNode->children = create_treeQueue();
	tree_enQueue(parent->children, newNode);
	parent->num_children ++;
	newNode->level = parent->level + 1;
}

parseTree* parse(linked_list_node* input_linkedList)
{
	rule** grammar = generate_grammar();
    int**parseTable = createParseTable();
    int first_table[NUM_TERMS][MAX_RHS] ;
    generate_first_table(first_table, grammar);
    int** follow_table = generate_follow_table(grammar);
    populateParseTable(grammar, parseTable, first_table, follow_table);
	stack_top = create_stack(); //initialize stack
	push(END_MARKER_SYMBOL);	
	push(program); 			//start symbol

	parseTree* tree = create_parseTree(); 	
	token_into_queue(input_linkedList); //initialize queue
	int a = dequeue() - START_OF_TERMINALS;

	int X;  //read and put X back to stack
	int g;  // grammar index
	int num=0;
	while(1)
	{
		int flag = 0;
		X = pop();	
		if(X == -1)
		{
			printf("STACK is EMPTY\n");
			break;
		}
		push(X);
		if(X>START_OF_TERMINALS)
		{	
			flag = 1;	// this means X is a terminal
			X = X-START_OF_TERMINALS;
		}
		else
			g = parseTable[X][a];	// g is the grammar index	
	
		if((flag == 1 && X==a) || X==$) 
		{
			X = pop();			
			if(X!= $)	// update information in the leaf node / current node of the tree
			{
				tree->current->line_num = input_linkedList->data->line_num;
				strcpy(tree->current->lexeme, input_linkedList->data->lexeme);
				tree->current->tk_type = input_linkedList->data->tk_type;

			}
			if(X!= $)
			{
				a = dequeue()-START_OF_TERMINALS;
				linked_list_node* temp = input_linkedList;			//dequeue from second list or fix it
				if(temp == NULL)
				{
					printf("input_linkedList is now empty\n");
				}
				else
				{
					input_linkedList = input_linkedList->next;
				}
			}

			tree_node* old_current = tree->current;				// setting tree->current ....
			if( old_current->next== NULL)
			{
				while(tree->current != tree->root && tree->current->parent->next == NULL )
					tree->current = tree->current->parent;

				if(tree->current != tree->root)
				{
					tree->current = tree->current->parent->next; 
					old_current->next= tree->current;	// important modification!
				}
			}
			else
				tree->current = tree->current->next;
		}
		else if(X!=0 && flag==1)	// when X is a terminal
		{
			printf("ERROR: The token \"%s\" for lexeme \"%s\" does not match at line \"%d\". ", token_map[a+START_OF_TERMINALS], input_linkedList->data->lexeme, input_linkedList->data->line_num);
			printf("The expected token here is \"%s\".\n", token_map[X=pop()]);
			num_parsing_errors ++;
			push(X);
			return tree;
		}
		else if(g == -1 && X!=0)	// when X is a non-terminal
		{	
			if(a>=0)
			{
				num_parsing_errors++;
				printf("ERROR: The token \"%s\" for lexeme \"%s\" does not match at line \"%d\".\n", token_map[a+START_OF_TERMINALS], input_linkedList->data->lexeme, input_linkedList->data->line_num);
			}
			return tree;
		}
		else
		{
			X = pop();
			int n= grammar[g]->count - 1, i=0;
			for(i=n; i>=0; i--)
			{
				int z = grammar[g]->to[i];
					push(z);	// let the $ also push
			}
			for(i=0; i<=n; i++)
			{
				int z = grammar[g]->to[i];
				num = num +1;
				// printf("here %d %d\n",num,i);
					add_pnode_to_tree(tree, tree->current, z, g);	// let $ also push
			}			
			tree->current = tree->current->children->front; 	// update current of tree
		}
	}
	return tree;
}
