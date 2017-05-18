// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: symbolTable.c
// //*

#include <stdio.h>
#include <stdlib.h>
#include "symbolTable.h"


#define TRACKER_ARRAY_LEN 200
int offset=0; // for setting the offset of variables 
// int size_track_of_arr_variables = 50;
// int index_track_of_arr_variables = 0;
// ASTNode** track_of_arr_variables; //= (varTableEntry*)malloc(sizeof(varTableEntry) * size_track_of_arr_variables );
/////////////////////////////////////////////////////////////////////////////////////////////////

void push2(int stack_data, stack_node2* stack_top)
{
	stack_node2* temp = (stack_node2*)malloc(sizeof(stack_node2));
	if(!temp)
		return;
	temp->stack_data = stack_data;
	temp->next = stack_top->next;
	stack_top->next = temp;
	return;
}

int is_stackEmpty2(stack_node2* top2)
{
	if(top2->next==NULL)
		return 1;
	return 0;
}

int pop2(stack_node2* stack_top)
{
	if(is_stackEmpty2(stack_top))
		return -1;
	int x = stack_top->next->stack_data;
	stack_node2* f = stack_top->next;
	stack_top->next = stack_top->next->next;
	// free(f);
	return x;
}
int top2(stack_node2* stack_top)
{
	if(is_stackEmpty2(stack_top))
	{
		// printf(">>\t\tSTACK EMPTY!! <<\n");
		return -1;
	}
	return stack_top->next->stack_data;
}
stack_node2* create_stack2()
{
	stack_node2* a = (stack_node2*)malloc(sizeof(stack_node2));
	a->next = NULL;
	a->stack_data = 0;
	return a;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

int computeHashVal(char* str)
{
	int k=0;
	int i=0;
	//printf("%d\n",sizeof(ch)/sizeof(char));
	for(i=0;i< sizeof(str)/sizeof(char);i++)
	{   if(str[i]!='\0')
			k+= (int)str[i];
		else
			break;
	}
	return k%PRIME_NUMBER;
}

int find_nesting_level(stack_node2* original_stack)
{
	stack_node2* new_stack = create_stack2();
	int count = 0;
	while(top2( original_stack) != -1)
	{
		push2(pop2(original_stack),new_stack);
		count++;
	}
	while(top2( new_stack) != -1)
	{
		push2( pop2(new_stack),original_stack);
	}
	return count;
}

void insertInVarTable(varSymbolTable* table,char* parent_func, linked_list_node* current, char* type, int top2,int arr_or_var,int start,int end,linked_list_node* a_type_node, int nesting, FILE* fp)
{
	// always check for re-declaration
	// hash the value
	
	int key = computeHashVal(current->data->lexeme);
	varTableEntry* temp = (varTableEntry*)malloc(sizeof(varTableEntry));
	strcpy(temp->name,current->data->lexeme);
	temp->key = key;
	temp->scope[0]= top2;
	temp->scope[1]=-1; 	// end_scope not know yet
	temp->line_num=current->data->line_num;
	temp->next=NULL;
	temp->scope_level = nesting;
	strcpy(temp->parent_func,parent_func);


	enum var_type t;
	if(strcmp(type, "integer")==0)
		t = _INTEGER;
	else if(strcmp(type,"real")==0)
		t = _REAL; 
	else 
		t = _BOOLEAN; // boolean

	temp->is_array = arr_or_var; 			//done -> // *** CAUTION *** to be changed later // ^^^^^^^^^^^^^^^^^^^^^^^
	if(arr_or_var==0)
		temp->arr_or_var.var_type = t;
	else
	{

		if(strcmp(a_type_node->data->lexeme, "integer")==0)
			t= _INTEGER;
		else if(strcmp(a_type_node->data->lexeme, "real")==0)
			t= _REAL;
		else 
			t= _BOOLEAN; // boolean

		temp->arr_or_var.arr.type = t;
		temp->arr_or_var.arr.width[0]=start;
		temp->arr_or_var.arr.width[1]=end;
	}	
	int var_size = end - start + 1;
	int type_size = var_width[t];
	temp->width = var_size*type_size;
	temp->offset = offset;
	offset=offset + temp->width;
	if(table->entries[key]==NULL)
	{
		table->entries[key] = temp;	
	}
	else
	{
		varTableEntry* search = table->entries[key];	// when collision occurs in hashing
		while(search!=NULL)
		{
			if(strcmp(search->name, current->data->lexeme)==0)
			{
				if(search->scope[0]== top2)	
				{
					fprintf(fp, "ERROR: RE-DECLARATION of VARIABLE \"%s\" at line number %d. \n", current->data->lexeme, temp->line_num);
					return;	
				}
			} 
			search=search->next;
		}
		// if it is not found in the list... add in the front of the list
		temp->next = table->entries[key];
		table->entries[key] = temp;
		// printf("\t\t\t>>>>>>adding %s at key %d \n", temp->name,temp->key);

	}
	varTableEntry* temp0 = table->entries[key];
	while( temp0!= NULL)
		// {printf(" >>>>>>>inserting\n%s\t%d",temp0->name, temp0->scope[0]);
		{
			temp0=temp0->next;
		}
}

void insertInFuncTable(funcSymbolTable* table, linked_list_node* current,int is_defined, int top2, FILE* fp)
{
	// always check for re-declaration
	// hash the value
	// **DOUBT** is declaration possible for "driver program"? driver program should be declared only once
	int key = computeHashVal(current->data->lexeme);

	funcTableEntry* temp = (funcTableEntry*)malloc(sizeof(funcTableEntry));
	strcpy(temp->name, current->data->lexeme);
	temp->key = key;
	temp->scope[0]= top2;
	temp->scope[1]=-1; 	// end_scope not know yet
	temp->is_defined=is_defined;
	temp->line_num=current->data->line_num;
	temp->num_input_params = 0;
	temp->num_output_params=0;
	temp->input_plist = NULL;
	temp->output_plist= NULL;
	temp->next=NULL;

	if(table->entries[key]==NULL)
	{
		table->entries[key] = temp;
		// printf("\t\t\t>>>>>>adding %s at key %d \n", temp->name,temp->key);
	}
	else
	{
		funcTableEntry* search = table->entries[key];	// when collision occurs in hashing
		while(search!=NULL)
		{
			if(strcmp(search->name ,current->data->lexeme)==0)
			{
				if(search->is_defined==1)	
					fprintf(fp, "ERROR: RE-DEFINITION of FUNCTION \"%s\" at line number %d. Overloading not allowed.\n",current->data->lexeme, temp->line_num);
				else if (search->is_defined == is_defined)
				{
					fprintf(fp, "ERROR: RE-DECLARATION of FUNCTION \"%s\"  at line number %d.\n",current->data->lexeme, temp->line_num);
				}
				else
				{
					search->scope[1]=top2;// will help to mark the end scope of a declared function.
					search->is_defined = 1; // status changed from declaration to definition
				}
				free(temp);
				return;
			} 
			search=search->next;
		}
		// if it is not found in the list... add in the front of the list
		temp->next = table->entries[key];
		table->entries[key] = temp;
		// printf("\t\t\t>>>>>>adding %s at key %d \n", temp->name,temp->key);

	}
	//take the scope from the stack_top
	//if it is already declared, check is_defined. 
	// 			if is_defined==0, no Error, make is_defined=1; 
}

varSymbolTable* initialize_var_ST()
{
	varSymbolTable* st = (varSymbolTable*)malloc(sizeof(varSymbolTable));
	st->entries = (varTableEntry**)malloc(PRIME_NUMBER*sizeof(varTableEntry*));
	int i;
	for(i=0; i<PRIME_NUMBER; i++)
	{
		st->entries[i] = NULL;//(varTableEntry*)malloc(sizeof(varTableEntry));
	}
	return st;
}

funcSymbolTable* initialize_func_ST()
{
	funcSymbolTable* st = (funcSymbolTable*)malloc(sizeof(funcSymbolTable));
	st->entries = (funcTableEntry**)malloc(PRIME_NUMBER*sizeof(funcTableEntry*));
	int i;
	for(i=0; i<PRIME_NUMBER; i++)
	{
		st->entries[i] = NULL;// (funcTableEntry*)malloc(sizeof(funcTableEntry));
	}
	return st;
}

int addtoTrackerArray(int* array)
{
	int i=0;
	while(array[i]!= -1)
	{
		i++;
	}
	// array[i] = computeHashVal(current->data->lexeme);
	return i;
}
void printArray(int* array)
{
	printf("printing array\n");
	int i=0;
	while(i != 10)
	{
		printf("%d ",array[i] );
		i++;
	}
	printf("\n");
}
void update_func_entry( varSymbolTable* VST, funcSymbolTable* FST, char* parent_func_name, linked_list_node* current, int flag)
{
	int key = computeHashVal(parent_func_name);
	funcTableEntry* temp = FST->entries[key];
	plist* temp2 ;
	plist* new_node = (plist*)malloc(sizeof(plist));
	new_node->v_ptr = VST->entries[computeHashVal(current->data->lexeme)];
	new_node->next = NULL;
	if(flag == 1)
	{
		temp2 = temp->input_plist;
		temp->num_input_params = temp->num_input_params + 1;
	}
	else
	{
		temp2 = temp->output_plist;
		temp->num_output_params = temp->num_output_params + 1;
	}
	// printf("cheeeck %s  %s \n",parent_func_name, temp->name );
	while(temp!=NULL)
	{
		if(strcmp(parent_func_name, temp->name)==0)
		{
			
			// temp2 = temp->input_plist;
			// temp->num_input_params = temp->num_input_params + 1;
			if(temp2 == NULL)
			{
				if(flag ==1)
					temp->input_plist = new_node;	
				else
					temp->output_plist = new_node;
			}
			else
			{
				while(temp2->next != NULL)
					temp2 = temp2->next;
				temp2->next = new_node;
			}
			break;
		}
		temp=temp->next;
	}
}
void populateSymbolTable(linked_list_node* list, varSymbolTable* VST, funcSymbolTable* FST, FILE* fp)
{
	// varSymbolTable* VST = initialize_var_ST(); 
	// funcSymbolTable* FST = initialize_func_ST();
	linked_list_node* current = list;
	stack_node2* scope_stack = create_stack2();
	// push2(1,scope_stack); // the starting line of the code

	int VarTracker_array[TRACKER_ARRAY_LEN];
	int FuncTracker_array[TRACKER_ARRAY_LEN];
	int i=0, index;
	int nesting=-2;
	for(i=0;i<TRACKER_ARRAY_LEN;++i)
		{VarTracker_array[i] = -1;
		 FuncTracker_array[i]= -1;}
	linked_list_node* temp;
	while(current!=NULL)
	{
		if(strcmp(current->data->lexeme, "declare")==0)
		{
			if(strcmp(current->next->data->lexeme,"module")==0)// declaration(not defi.) of a function.
			{
				// printf("Declare Module --\n");
				current=current->next->next; // points to name of function now
				insertInFuncTable(FST, current, 0, current->data->line_num, fp); // 0=> declaration
				index = addtoTrackerArray(FuncTracker_array);
				
				FuncTracker_array[index] = computeHashVal(current->data->lexeme);
				// printArray(FuncTracker_array);
				// current = current->next; // points to ";"
			}
			
			else if(current->next->data->lexeme_token == TK_ID)
			{
				current=current->next;	// points to the variable name
				temp=current->next;		// either points to "," or ":"

				int x=0;
				while(FuncTracker_array[x]!=-1)
					x++;
				x=FuncTracker_array[x-1];
				char parent_func_name[MAX_LEXEME_LENGTH];
				if(x<0)
					strcpy(parent_func_name,"--");
				else
				{

					strcpy(parent_func_name, FST->entries[x]->name);
				}	

				while(strcmp(current->data->lexeme,";")!=0)
				{
					// printf("here3\n");
					while(strcmp(temp->data->lexeme,":")!=0)
						temp=temp->next;
					// printf("c: %s\n",current->data->lexeme );
					// printf("t: %s\n",temp->data->lexeme );

					while(current!=temp)
					{
						//add all the vars before ":" to the table
						// printf("here4\n");
						if(strcmp(current->data->lexeme,",")==0)
						{
							current=current->next;
							continue;
						}

						if(strcmp(temp->next->data->lexeme,"array")==0)
						{
							// current points to var name, temp points to ":"
							//var_name : use "current" node only
							linked_list_node* temp2 = temp->next->next->next; // points to 1..12
							char start_index[5];	// assume max number is of 5 digits
							char end_index[5];
							char string[12];
							for(i=0;i<5;i++)
							{
								start_index[i]='\0';
								end_index[i]='\0';
							}
							// printf("checking the array range: %s\n", temp2->data->lexeme);
							strcpy(string, temp2->data->lexeme);
							int x=0;
							i=0;
							while(string[x]!='.')
							{
								start_index[x] = string[x];
								x++;
							}
							// printf("start index: %s\n", start_index);
							x=x+2;
							int j=0;

							while(string[x]!='\0')
							{
								end_index[j]=string[x];
								x++;j++;
							}
							// printf("end index: %s\n", end_index);

							for(i=0; i<strlen(string); i++)
							{
								string[i] = '\0';
							}	
							int s_index = atoi(start_index);
							int e_index=atoi(end_index);

							linked_list_node* array_type = temp2->next->next->next;
							nesting = find_nesting_level(scope_stack);
							//				table,var_node, 	var_type		, scope  		, is_array,start_in, end_ind, ar_type
							insertInVarTable(VST,parent_func_name,current,temp->next->data->lexeme,top2(scope_stack), 1 ,s_index, e_index ,array_type ,nesting, fp); // temp->data->lexeme gives type:"integer"/ "boolean"/ "real" 
							index = addtoTrackerArray(VarTracker_array);
							int key=computeHashVal(current->data->lexeme);
							VarTracker_array[index] = key;
							if(strcmp(current->next->data->lexeme,",")==0)
								current = current->next;
							else// it points to ":"
							{
								if(strcmp(array_type->next->data->lexeme, ",")==0)
								{
									current = array_type->next->next;	// both point to a new var
									temp = current;
								}
								else // it is ";"
								{

									current = array_type->next;	// both point to ";"
									temp = current;
								}
								
							}


						}
						else
						{	// deal with all other types
							nesting = find_nesting_level(scope_stack);
							insertInVarTable(VST,parent_func_name,current,temp->next->data->lexeme,top2(scope_stack),0,0,0,0, nesting, fp); // temp->data->lexeme gives type:"integer"/ "boolean"/ "real" 
							index = addtoTrackerArray(VarTracker_array);
							VarTracker_array[index] = computeHashVal(current->data->lexeme);
							
							if(strcmp(current->next->data->lexeme,",")==0)
								current = current->next;
							else //if current->next points to ':'
								{current = current->next->next->next;
									temp= current;
								}
						}
					}
				}
				// printf("exiting declare \n");
			}
		}
		else if(strcmp(current->data->lexeme, "module")==0)
		{
			// printf("Module --\n");
			temp =current;
			while(strcmp(temp->data->lexeme,"start")!=0)	// to find the start_scope of variable
				temp=temp->next;
			int line_num = temp->data->line_num;
			push2(line_num,scope_stack);
			// printf("pushed %s at stack@@@@@@@%d\n",current->next->data->lexeme,line_num);
			insertInFuncTable(FST, current->next, 1, top2(scope_stack), fp); // 0=> declaration; 1=>definition
			index = addtoTrackerArray(FuncTracker_array);
			FuncTracker_array[index] = computeHashVal(current->next->data->lexeme);
			// printArray(FuncTracker_array);
			current=current->next->next;

		}
		else if(current->data->lexeme_token==TK_ID)
		{
			// printf("Just ID --\n");
			// scope checking
			/*==>identify "TK_ID" 
   			is variable already?,check line number of the variable(the end_scope might not be yet defined)
   			->is an ":=" operation? then do typechecking only if next token is INT/REAL .. not (a*b+c-34)
						.. what if abc := -(6) ?
			*/

			int key = computeHashVal(current->data->lexeme);
			varTableEntry* check_var = VST->entries[key];
			
			while(check_var != NULL)
			{

				if((strcmp(check_var->name, current->data->lexeme)==0))
				{
					// printf("lexeme:%s stack top %d ; current scope %d to %d; line_num: %d\n",  current->data->lexeme, top2(scope_stack), check_var->scope[0], check_var->scope[1], current->data->line_num);
					if((check_var->scope[0] < current->data->line_num) && (check_var->scope[1] == -1))
					{
						 break;	
					}

					else
					{
						fprintf(fp, "ERROR: Use of Variable \"%s\" out of scope at line number %d.\n", current->data->lexeme, current->data->line_num);
						break;
					}
				}
				check_var = check_var->next;
			}
			if(check_var == NULL)
			{
				fprintf(fp, "ERROR: Use of Variable \"%s\" without DECLARATION at line number %d.\n", current->data->lexeme, current->data->line_num);
			}

		}
		else if(strcmp(current->data->lexeme ,"driver")==0)
		{
			// printf("Driver --\n");
			current=current->next;
			temp=current;
			while(strcmp(temp->data->lexeme,"start")!=0)	// to find the start_scope of variable
				temp=temp->next;
			int line_num = temp->data->line_num;
			push2(line_num,scope_stack);
			insertInFuncTable(FST, current, 1, top2(scope_stack), fp); // 0=> declaration
			index = addtoTrackerArray(FuncTracker_array);
			FuncTracker_array[index] = computeHashVal(current->data->lexeme);
			// printArray(FuncTracker_array);

		}
		else if(strcmp(current->data->lexeme, "use")==0)
		{
			// printf("Use --\n");
			current=current->next->next; // points to the called module(function) (NAME)
			int key = computeHashVal(current->data->lexeme);
			funcTableEntry* check_func = FST->entries[key];
			while(check_func != NULL)
			{
				if((strcmp(check_func->name, current->data->lexeme)==0))
				{
					break;
				}				
				check_func = check_func->next;
			}

			if(check_func == NULL)  //neither declared nor defined // but for now, we are checking declaration only.
			{
				fprintf(fp, "ERROR: Unknown Function \"%s\" at line number %d.\n", current->data->lexeme, current->data->line_num);
			}
			// checking recursive fuction.
			temp = current->next->next->next;
			varTableEntry* check_parameter = VST->entries[computeHashVal(temp->data->lexeme)];
			while (check_parameter!=NULL)
			{
				if(strcmp(check_parameter->name,temp->data->lexeme)==0)
				{
					if(check_parameter->scope[1] == -1) // the parameter variable is of the same function
					{
						if(strcmp(check_parameter->parent_func,current->data->lexeme)==0)
						{
							fprintf(fp, "ERROR: Recursion of the \"%s\" at line %d \n", check_parameter->parent_func,current->data->line_num);
							break;
						}
					}
				}
				check_parameter=check_parameter->next;
			}
				
		}
		else if(strcmp(current->data->lexeme, "start")==0)
		{
			// printf("Start --\n");
			int line_num = current->data->line_num;	// ** DOUBT ** add line_num+1 ??
			if(top2(scope_stack) != line_num)	// avoid double push2ing of "start"; already push2ed in case of: "takes input" [a:boolean...]; "returns" [sum:integer]
				push2(line_num,scope_stack);
		}
		else if(strcmp(current->data->lexeme, "takes")==0) //take input [a:integer, b:real];
		{
			
			current=current->next->next->next;	// points to the variable name
			temp=current->next;		// either points to "," or ":"
			int x=0;
			while(FuncTracker_array[x]!=-1)
				x++;
			x=FuncTracker_array[x-1];
			char parent_func_name[MAX_LEXEME_LENGTH];		
			if(x<0)
				strcpy(parent_func_name,"--");
			else
			{
				// printf("x: %d func:%s check parent name: %s\n",x,current->data->lexeme,FST->entries[x]->name );
				strcpy(parent_func_name, FST->entries[x]->name);
			}	
			
			while(strcmp(current->data->lexeme,"]")!=0)
			{
				while(strcmp(temp->data->lexeme,":")!=0)
					temp=temp->next;
				
				while(current!=temp)
				{
					//add all the vars before ":" to the table
					if(strcmp(current->data->lexeme,",")==0)
					{
						current=current->next;
						continue;
					}
					if(strcmp(temp->next->data->lexeme,"array")==0)
					{
						// current points to var name, temp points to ":"
						//var_name : use "current" node only
						linked_list_node* temp2 = temp->next->next->next; // points to 1..12
						char start_index[5];	// assume max number is of 5 digits
						char end_index[5];
						char string[12];
						for(i=0;i<5;i++)
						{
							start_index[i]='\0';
							end_index[i]='\0';
						}
						strcpy(string, temp2->data->lexeme);
						int x=0;
						i=0;
						while(string[x]!='.')
						{
							start_index[x] = string[x];
							x++;
						}
						x=x+2;
						int j=0;

						while(string[x]!='\0')
						{
							end_index[j]=string[x];
							x++;j++;
						}
						for(i=0; i<strlen(string); i++)
						{
							string[i] = '\0';
						}	
						int s_index = atoi(start_index);
						int e_index=atoi(end_index);

						linked_list_node* array_type = temp2->next->next->next;
						nesting = find_nesting_level(scope_stack);
						//				table,              var_node, 	var_type		, scope  		, is_array,start_in, end_ind, ar_type
						insertInVarTable(VST,parent_func_name,current,temp->next->data->lexeme,top2(scope_stack), 1    ,s_index, e_index ,array_type , nesting, fp); // temp->data->lexeme gives type:"integer"/ "boolean"/ "real" 
						update_func_entry(VST, FST, parent_func_name, current,1); // 1 signifies input_list
						index = addtoTrackerArray(VarTracker_array);
						VarTracker_array[index] = computeHashVal(current->data->lexeme);
						if(strcmp(current->next->data->lexeme,",")==0)
							current = current->next;
						else// it points to ":"
						{
							if(strcmp(array_type->next->data->lexeme, ",")==0)
							{
								current = array_type->next->next;	// both point to a new var
								temp = current;
							}
							else // it is ";"
							{
								current = array_type->next;	// both point to ";"
								temp = current;
							}							
						}
					}
					else
					{	// deal with all other types
						nesting = find_nesting_level(scope_stack);
						insertInVarTable(VST,parent_func_name,current,temp->next->data->lexeme,top2(scope_stack),0,0,0,0,nesting,fp); // temp->data->lexeme gives type:"integer"/ "boolean"/ "real" 
						update_func_entry(VST, FST, parent_func_name, current,1);
						index = addtoTrackerArray(VarTracker_array);
						VarTracker_array[index] = computeHashVal(current->data->lexeme);
						
						if(strcmp(current->next->data->lexeme,",")==0)
							current = current->next;
						else //if current->next points to ':'
							{current = current->next->next->next;
								temp= current;
							}
					}
				}
			}
		}
		else if(strcmp(current->data->lexeme, "returns")==0)
		{
			// printf("Returns --\n");
			current=current->next->next; // points to the variable
			int x=0;
			while(FuncTracker_array[x]!=-1)
				x++;
			x=FuncTracker_array[x-1];
			char parent_func_name[MAX_LEXEME_LENGTH];
			if(x<0)
				strcpy(parent_func_name,"--");
			else
			{
				strcpy(parent_func_name, FST->entries[x]->name);
			}	

			while(strcmp(current->data->lexeme,"]")!=0)
			{
				if(strcmp(current->data->lexeme, ",")==0)
				{
					current=current->next;
					continue;
				}
				nesting = find_nesting_level(scope_stack);
				insertInVarTable(VST, parent_func_name,current, current->next->next->data->lexeme,top2(scope_stack),0,0,0,0,nesting,fp);
				update_func_entry(VST, FST, parent_func_name, current,0); // 0 signifies output list, 1 signifies input_list
				index = addtoTrackerArray(VarTracker_array);
				VarTracker_array[index] = computeHashVal(current->data->lexeme);

				current = current->next->next->next; // "," or "]"
			}
			// current=current->next; // points to ";"
		}
		else if(strcmp(current->data->lexeme, "end")==0)
		{
			// printf("End --\n");
			int end_scope = current->data->line_num;
			int start_scope = top2(scope_stack);
			int i=0;
			// printf("closing scope of %d %d \n", start_scope,end_scope);
			// printf("printing before VarTracker_array\n");
			int t=0;
			// for(t=0;t<TRACKER_ARRAY_LEN/10;t++)
			// 	printf("%d ",VarTracker_array[t] );
			// printf("\n");
			// adding end_scope in VST
			i = 0;
			while(VarTracker_array[i]!=-1)
			{
				i++;
			}
			i = i-1;
			// printf("\niiiiiiiiiiii %d\n",i);
			varTableEntry* new_temp;

			while(i >= 0)
			{
				new_temp = VST->entries[VarTracker_array[i]];
			
				while(new_temp!= NULL)
				{	
					// printf("@@@@ %s scope entry: %d, start_scope: %d  \n",new_temp->name,new_temp->scope[0],start_scope);
					if(new_temp->scope[0] == start_scope && new_temp->scope[1] == -1)
					{

						new_temp->scope[1] = end_scope;
						VarTracker_array[i] = -1;
						// printf("%d (end scope) INSIDE IF!!!!!, %d .... \n", end_scope, i);
						// break;
					}
					new_temp = new_temp->next;
				} 
				i=i-1;
			}
			// printf("printing after VarTracker_array\n");
			// for(t=0;t<TRACKER_ARRAY_LEN/10;t++)
			// 	printf("%d ",VarTracker_array[t] );
			i=0;
			while(FuncTracker_array[i]!=-1)
			{
				if(FST->entries[FuncTracker_array[i]]->scope[1] == start_scope)	// handling a declared function
				{
					FST->entries[FuncTracker_array[i]]->scope[1] = end_scope;
					FuncTracker_array[i] = -1;
					FuncTracker_array[i+1] = -1;
					i++;

				}
				else if(FST->entries[FuncTracker_array[i]]->scope[0] == start_scope)
				{
					FST->entries[FuncTracker_array[i]]->scope[1] = end_scope;
					FuncTracker_array[i] = -1;
				}
				i=i+1;
			}
			pop2(scope_stack);
			if(top2(scope_stack)==-1)
			{
				offset = 0;
			}
		}
		else if(current->data->lexeme_token == TK_FOR)
		{

		}
		else
		{
			// printf("Nothing to do\n");
		}
		current=current->next;
	}
	fclose(fp);
	return;
}

void printSymbolTables(varSymbolTable* VST, funcSymbolTable* FST)
{
	varTableEntry* temp2;
	varTableEntry* travel_ptr;
	int s_no = 1;
	int n = 20, n1 = 6;
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Variable Symbol Table <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
	printf("\nSNo.\t\tLexeme\t\tVarType\t\t\tscope\t\tscope\t\tscope\t\tWidth\t\tOffset\n");
	printf("\t\t\t\t\t\t\t(parent func)\t(line numbers)\t(nesting level)\t\t\n");
	int i;
	for(i=0;i<PRIME_NUMBER;i++)
	{
		travel_ptr=VST->entries[i];
		while(travel_ptr!=NULL)
		{
			temp2 = travel_ptr;
			printf("%*d ", n1, s_no++);
			printf("%*s ", n, temp2->name);
				
			if(temp2->is_array)
			{
				enum var_type arr_type = temp2->arr_or_var.arr.type;
				int start_index = temp2->arr_or_var.arr.width[0];
				int end_index = temp2->arr_or_var.arr.width[1];
				int arr_size = end_index-start_index+1;
				// printf("%d ", start_index);
				// printf("%d ", end_index);
				printf("\t  array(%*s,%d)", 4, var_map[arr_type], arr_size);
				printf("%*s", n, temp2->parent_func);
				printf("%*d to %d", n1, temp2->scope[0], temp2->scope[1]);
				printf("%*d", 10, temp2->scope_level);	
				printf("%*d", n1*3, temp2->width);
				printf("%*d ", n1*2, temp2->offset);

			}	
			else
			{   //print for var type
				enum var_type type = temp2->arr_or_var.var_type;
				printf("%*s", n, var_map[type]);
				printf("%*s", n, temp2->parent_func);
				printf("%*d to %d", n1, temp2->scope[0], temp2->scope[1]);
				printf("%*d", 10, temp2->scope_level);	
				printf("%*d", n1*3, temp2->width);
				printf("%*d", n1*2, temp2->offset);
				//print var_width		
			}		
			travel_ptr=travel_ptr->next;
			printf("\n");	
		}
	}
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Function Symbol Table <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
	plist* in_plist_ptr;
	plist* out_plist_ptr;
	funcTableEntry* f_ptr;
	int sno = 0;
	printf("SNo.\t\tlexeme\t\tscope\tinput_params\toutput_params\n");
	printf("\t\t(func id)\t\t\t\t(line numbers)\n");
	for(i=0;i<PRIME_NUMBER;i++)
	{
		f_ptr= FST->entries[i];
		while(f_ptr!=NULL)
		{
			printf("%*d", n1, sno++);
			printf("%*s %*d to %d", n, f_ptr->name, n1, f_ptr->scope[0], f_ptr->scope[1]);
			in_plist_ptr = f_ptr->input_plist;
			out_plist_ptr= f_ptr->output_plist;
			printf("\t |%d| ",f_ptr->num_input_params);
			while(in_plist_ptr!=NULL)
			{
				printf("%s ", in_plist_ptr->v_ptr->name);
				in_plist_ptr= in_plist_ptr->next;
			}
			printf(" \t|%d| ",f_ptr->num_output_params);
			while(out_plist_ptr!=NULL)
			{
				printf("%s ", out_plist_ptr->v_ptr->name);
				out_plist_ptr= out_plist_ptr->next;
			}
			printf("\n" );
			f_ptr = f_ptr->next;
		}
	}
}

ASTNode* arr_tracker_array[100];
int index_arr_tracker_array = 0;

void add_astnode_to_tracker_array(ASTNode* root,varSymbolTable* VST)
{
	if(index_arr_tracker_array == 99)
		printf("increase the size of arr_tracker_array. symbolTable.c line 907\n");
	arr_tracker_array[index_arr_tracker_array] = root;
	index_arr_tracker_array ++;
}

int find_size(ASTNode* a,varSymbolTable* VST)
{
	int key = computeHashVal(a->lexeme);
	varTableEntry* temp = VST->entries[key];
	while(temp!=NULL)
	{
		if(strcmp(a->lexeme, temp->name)==0 && temp->is_array)
		{
			if(a->line_num >= temp->scope[0] &&  a->line_num <=temp->scope[1]  )
				return (temp->arr_or_var.arr.width[1] - temp->arr_or_var.arr.width[0] );
		}
		temp=temp->next;
	}
	return -1;
}
void check1(ASTNode* root,varSymbolTable* VST)
{
	// printf("inside check1\n");
	int i =0, x,y;
	for(i=0;i<index_arr_tracker_array;i++)
	{
		if(arr_tracker_array[i]->line_num == root->line_num)
		{
			x = find_size(arr_tracker_array[i],VST);
			y = find_size(root,VST);
			if(x==-1 || y ==-1 )
			{
				// printf("size not found of array at line num %d\n", root->line_num);
			}
			if(x!=y)
			{
				printf("ERROR_T: Arrays of different length at line number %d.\n",root->line_num );
			}
		}
	}
}

void check_arr_len_errors(ASTNode* root, varSymbolTable* VST)
{

	if(root == NULL)
    return;

  if(root->token > START_OF_TERMINALS)  //is a terminal
  {
  	if(root->token == TK_ID && root->is_array == 1)
  	{
  		add_astnode_to_tracker_array(root,VST);
  		check1(root, VST);
  	}
   return;
  }
  if(root->num_children>0)
    check_arr_len_errors(root->children[0],VST);
  //for parent
	
  //for right
  if(root->num_children >= 1)
  {
    int i = 1;
    ASTNode* temp = root->children[i];
    if(temp != NULL)
    {
      int y = 0;
      while(y<root->num_children-1)
      {
        // printf("inside while: \n");
        check_arr_len_errors(root->children[i],VST);
        // if(temp->num_children!= 0)
        i++;
        y++;
      }
    }
  }
 
  return;
}
