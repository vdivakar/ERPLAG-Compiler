// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: semanticAnalyzer.c
// //*

#include "semanticAnalyzer.h"
//functions:
//declared but not defined
//recursive call to a function
/*
	case of "for": Re-Definition of a the iterative variable is NOT allowed.


*/

void reportSemanticErrors(linked_list_node* node, varSymbolTable* VST, funcSymbolTable* FST)
{
	// printf("Hi! I am semantic analyzer!\n");
	linked_list_node* current = node;
	linked_list_node* temp;
	while(current!=NULL)
	{
		if(current->data->lexeme_token == TK_MODULE)
		{
			current = current->next; //points to module being called
			int key = computeHashVal(current->data->lexeme);
			funcTableEntry* temp = FST->entries[key];
			while(temp != NULL)
			{
				if(strcmp(temp->name,current->data->lexeme)==0)
					if(temp->scope[1]== -1)
						printf("ERROR: module \"%s\" not defined at line %d\n", temp->name,current->data->line_num);
				temp=temp->next;
			}						
		}
		current = current->next;
	}
	return;	
}

void reportSemanticErrors2(ASTNode* root, varSymbolTable* VST, funcSymbolTable* FST)
{
	if(root == NULL)
		return;

	if(root->token >= START_OF_TERMINALS)  //is a terminal
	{
		return;
	}
	if(root->num_children>0)
		reportSemanticErrors2(root->children[0], VST, FST);
	//for parent
	switch(root->token)
	{
		case conditionalStmt:
		{
			process_switch_stmt(root);
			// printf("######\n");
			break;
		}
		case moduleReuseStmt:
		{
			process_function_call(root, FST);
			break;
		}
		case iterativeStmt:
		{
			if(root->rule_no == 86)
			{
				process_FOR_statement(root->children[0],root->children[2]);
			}
			break;
		}
		case assignmentStmt:
		{
			assign_types(root);	
			break;
		}
		case lvalueARRStmt:
		{
			// printf("%s vvv\n", token_map[root->token]);
			process_array(root);
			break;
		}
		// case module:
		// {
		// 	process_function_return(root);
		// 	break;
		// }
	}
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
		    reportSemanticErrors2(root->children[i], VST, FST);
		    i++;
		    y++;
	  	}
	}
	}
	return;
}

void process_switch_stmt(ASTNode* root)
{
	enum var_type type = root->children[0]->tk_type;
	// printf("#### %s\n",var_map[type]);
	switch(type)
	{
		case _REAL:
		{
			printf("ERROR_T: Identifier \"%s\" in SWITCH cannot be of type real, line number: %d\n",root->children[0]->lexeme ,root->children[0]->line_num);
			break;
		}
		case _NONE:
		{
			printf("ERROR_T: Identifier \"%s\" in SWITCH statement is not valid, line number: %d\n",root->children[0]->lexeme ,root->children[0]->line_num);
			break;
		}
		case _MODULE:
		{
			printf("ERROR_T: Identifier \"%s\" in SWITCH statement is not valid, line number: %d\n",root->children[0]->lexeme ,root->children[0]->line_num);
			break;
		}
		case _INTEGER:
		{
			// printf("Hi %d\n", );
			if((root->num_children <= 2) || (root->children[2] == NULL)) 
				printf("ERROR: There is no DEFAULT statement with an Integer identifier for SWITCH statement at line %d.\n", root->children[0]->line_num);

			ASTNode* case_stmt = root->children[1];

			while(case_stmt!=NULL)
			{
				// printf("checking num of children %d \n",case_stmt->num_children );
				if(case_stmt->children[0]->tk_type != _INTEGER)
				{
					printf("ERROR: Type Mismatch: Expected value for SWITCH CASE must be an Integer at line number %d.\n", case_stmt->children[0]->line_num);
				}
				if(case_stmt->num_children > 2)
					case_stmt = case_stmt->children[2];
				else 
					break;
			}	
			break;	
		}
		case _BOOLEAN:
		{
			// printf("%d %s *****test_switch\n", root->num_children, token_map[root->token]);
			if(root!=NULL && root->num_children > 2 && root->children[2] != NULL && root->children[2]->token == defaultStmt)
			{
				printf("ERROR: There is a DEFAULT statement with a Boolean identifier for SWITCH statemnent at line %d.\n", root->children[0]->line_num);
			}
			ASTNode* case_stmt = root->children[1];
			int case_count = 0;

			while(case_stmt != NULL)
			{
				case_count ++; 
				// printf("%d num_children %d\n", case_count, case_stmt->num_children);

				if(case_stmt->children[0]->tk_type != _BOOLEAN /*check if type of TRUE/FALSE/BOOLEAN*/)
				{
					printf("ERROR: Type Mismatch: Expected value for SWITCH CASE can only be TRUE/FALSE.  (Line number: %d)\n", case_stmt->children[0]->line_num);
				}

				if(case_stmt->num_children > 2)
				{
					// printf("BC!!!!!!!!!!!\n");
					case_stmt = case_stmt->children[2];

				}
				else 
					break;
			}	

			if(case_count>2)
			{
				printf("There can only 2 cases for a SWITCH statement (Line Number: %d) with Boolean identifier.\n", root->children[0]->line_num);
			}

			break;
		}
	}

}

void process_function_call(ASTNode* root, funcSymbolTable* FST)
{
	// printf("%s check for optional\n", token_map[root->children[0]->token]);
	ASTNode* temp;
	ASTNode* check_params_node;
	ASTNode* idList_node = NULL;  //output list
	funcTableEntry* fst_entry;
	int n;
	int output_params_count, input_params_count;

	if(root->children[0]->token == TK_ID) // the case when the function should not return anything
	{
		output_params_count = 0;
		temp = root->children[0];
		n = temp->line_num;
		check_params_node = root->children[1];
		int key = computeHashVal(temp->lexeme);
		fst_entry = FST->entries[key];
		while(fst_entry!=NULL)
		{
			if(strcmp(fst_entry->name, temp->lexeme) == 0)
			{
				if(fst_entry->num_output_params != 0)
				{
					printf("ERROR_M: Return Mismatch. The value(s) returned by function \"%s\" is not assigned to output list. (Line number: %d). \n", temp->lexeme, temp->line_num);
				}
				break;
			}
			fst_entry = fst_entry->next;
		}
	}
	else if(root->children[0]->token == optional)
	{
		temp = root->children[1];  //temp points to TK_ID (module name)
		n = temp->line_num;
		check_params_node = root->children[2];
		int key = computeHashVal(temp->lexeme);
		fst_entry = FST->entries[key];
		while(fst_entry!=NULL)
		{
			if(strcmp(fst_entry->name, temp->lexeme) == 0)
			{
				if(fst_entry->num_output_params == 0)
				{
					printf("ERROR: Return Mismatch. The void function \"%s\" should not return any value (Line number: %d). \n", temp->lexeme, temp->line_num);
				}
				break;
			}
			fst_entry = fst_entry->next;
		}	

		//check for types of output parameters here...
		idList_node = root->children[0]->children[0];
		output_params_count = 0;
		// printf("check!! %s\n", token_map[idList_node->token]);
		while(idList_node != NULL && idList_node->num_children >= 2)
		{
			output_params_count ++;
			idList_node = idList_node->children[1];
		}	
	}

	input_params_count = 0;
	ASTNode* temp_check_params = check_params_node;

	// checking the number of parameter passed and expected
	while(check_params_node!=NULL && check_params_node->num_children >= 2)
	{
		input_params_count ++;
		check_params_node=check_params_node->children[1];
	}
	if(input_params_count != fst_entry->num_input_params)
	{
		printf("ERROR_M: Expected %d input parameters instead of %d, to the function \"%s\" at Line Number: %d.\n", fst_entry->num_input_params, input_params_count, fst_entry->name, n);
	}

	//checking the "type" of input parameters now... ; temp_check_params points to the top idlist.
	int i;
	enum var_type ret_type, ret_type_2;
	plist* var_entry = fst_entry->input_plist; // linked list of expected input parameters 

	for(i=0;i<fst_entry->num_input_params; i++) // fst_entry points to the name of function being called.
	{
		if(temp_check_params!=NULL && temp_check_params->num_children >= 2) // temp_check_params points to top <idlist> node
		{
			ret_type_2 = temp_check_params->children[0]->tk_type; // the data type of the parameter being passed. 

			if(var_entry->v_ptr->is_array)
				ret_type = var_entry->v_ptr->arr_or_var.arr.type;  // ret_type is the correct/expected data type.
			else
				ret_type = var_entry->v_ptr->arr_or_var.var_type;

			if(ret_type != ret_type_2 && ret_type_2 != _NONE)
			{
				printf("ERROR_T: Type Mismatch. Expected \"%s\" but received \"%s\" for input parameter \"%s\" at line number: %d.\n", var_map[ret_type], var_map[ret_type_2], temp_check_params->children[0]->lexeme, temp_check_params->children[0]->line_num);
			}
			temp_check_params = temp_check_params->children[1];
			var_entry = var_entry->next;
		}
	}

	if(output_params_count != fst_entry->num_output_params)
	{
		printf("ERROR_M: Expected %d output parameters instead of %d, to the function \"%s\" at Line Number: %d.\n", fst_entry->num_output_params, output_params_count, fst_entry->name, n);
	}
	//checking the "type" of "output" parameters now... ; temp_check_params points to the top idlist.

	if(idList_node!=NULL && idList_node->num_children>0 && idList_node->children[0]->num_children>0)
		idList_node = root->children[0]->children[0];

	var_entry = fst_entry->output_plist; // linked list of expected "output" parameters
	for(i=0;  i < fst_entry->num_output_params; i++)
	{
		if(idList_node != NULL && idList_node->num_children >= 2)
		{
			ret_type_2 = idList_node->children[0]->tk_type;	  		// ret_type_2 is the data type of the parameter being passed. 
			// printf("########  %s  %d \n", token_map[idList_node->token], idList_node->rule_no);
			if(idList_node->children[0]->is_array)
			{
				printf("ERROR_T: Return type for output parameter \"%s\" at line number %d cannot be an array .\n", idList_node->children[0]->lexeme, idList_node->children[0]->line_num);
				
				// ret_type = var_entry->v_ptr->arr_or_var.arr.type;  // ret_type is the correct/expected data type.
			}			else
				ret_type = var_entry->v_ptr->arr_or_var.var_type;

			if(ret_type != ret_type_2 && ret_type_2 != _NONE)
			{
				printf("ERROR_T: Type Mismatch. Expected \"%s\" but received \"%s\" for input parameter \"%s\" at line number: %d.\n", var_map[ret_type], var_map[ret_type_2], idList_node->children[0]->lexeme, idList_node->children[0]->line_num);
			}
			idList_node = idList_node->children[1];
			var_entry = var_entry->next;
		}
	}


	return;
}

void process_FOR_statement(ASTNode* id_node, ASTNode* root)		// travel in an IN-ORDER fashion and look for a declarestatement
{
	if(root == NULL)
	return;

	if(root->token >= START_OF_TERMINALS)  //is a terminal
	{
		return;
	}
	if(root->num_children>0)
		process_FOR_statement(id_node, root->children[0]);
	//for parent
	if(root->token == assignmentStmt)
	{
		if(strcmp(root->children[0]->lexeme, id_node->lexeme)==0)
			printf("ERROR: Re-Definition of iterative variable \"%s\" inside a FOR loop at line %d\n", id_node->lexeme, id_node->line_num);
	}
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
		    process_FOR_statement(id_node, root->children[i]);
		    // if(temp->num_children!= 0)
		    i++;
		    y++;
		  }
		}
	}
}

void process_array(ASTNode* root)
{
	ASTNode* temp = root->children[0]; //points to <index>
	// printf("%s, index\n", token_map[temp->token]);
	if(temp->token != TK_ID)
	{
		printf("ERROR: Only idendifier can be used to refer to an array (Line Number: %d).\n", temp->line_num);
	}
	if(temp->tk_type != _INTEGER)
	{
		printf("ERROR: The index of an ARRAY must be an INTEGER (Line Number: %d).\n", temp->line_num);
	}
	return;
}

var_type find_type(ASTNode* root)
{
	// if(root==NULL)
	// 	return _NONE;
	// if(root->token == TK_GE||root->token == TK_GT ||root->token == TK_LE ||root->token == TK_LT ||root->token == TK_EQ ||root->token == TK_NE ||root->token == TK_OR || root->token == TK_AND)
	// {
	// 	return _BOOLEAN;
	// }
	if(root->tk_type == _INTEGER)
		return _INTEGER;
	else if (root->tk_type == _REAL)
		return _REAL;
	else if (root->tk_type == _BOOLEAN)
		return _BOOLEAN;
	else
	{
		int i;
		var_type* t_arr = (var_type *)malloc(root->num_children * sizeof(var_type));
		var_type v_flag = _NONE;
		for (i = 0; i < root->num_children; ++i)
		{
			if(root->children[i]==NULL)
				t_arr[i] = _NONE;
			// else if(root->children[i]->token == TK_GE||root->children[i]->token == TK_GT ||root->children[i]->token == TK_LE ||root->children[i]->token == TK_LT ||root->children[i]->token == TK_EQ ||root->children[i]->token == TK_NE ||root->children[i]->token == TK_OR || root->children[i]->token == TK_AND)
			// {
			// 	printf("hereww %s \n", token_map[root->children[i]->token]);
			// 	t_arr[i] = _BOOLEAN;
			// }
			else
			{
				t_arr[i] = find_type(root->children[i]);
				if(root->children[i]->token == TK_GE||root->children[i]->token == TK_GT ||root->children[i]->token == TK_LE ||root->children[i]->token == TK_LT ||root->children[i]->token == TK_EQ ||root->children[i]->token == TK_NE ||root->children[i]->token == TK_OR || root->children[i]->token == TK_AND)
					t_arr[i] = _BOOLEAN;
			}
		}
		i=0;
		int flag=0;
		int flag2=0;
		while(i<root->num_children)
		{
			printf("%s,, ", var_map[t_arr[i]]);
			i++;
		}
		printf("###\n");
		i=0;
		while(i<root->num_children)
		{
			if(t_arr[i] != _NONE)
			{
				if(v_flag == _NONE && t_arr[i]!=_BOOLEAN)
					v_flag = t_arr[i];
				else
				{
					// if (t_arr[i]== TK_GE||t_arr[i]== TK_GT ||t_arr[i] == TK_LE ||t_arr[i]== TK_LT ||t_arr[i]== TK_EQ ||t_arr[i] == TK_NE ||t_arr[i]== TK_OR || t_arr[i]== TK_AND)
					if(t_arr[i] == _BOOLEAN)
					{
						flag2 = 1;
					}
					else if(v_flag != t_arr[i])
					{
						flag = 1;
						printf("Type Mismatch at line num %d \n",root->children[i]->line_num);
						break;
						// return _NONE;
					}
				}
			}
			i++;
		}
		if(flag)
			return root->tk_type;
		else if (flag2)
		{
			printf("returning BOOOlean\n");
			root->tk_type = _BOOLEAN;
			return _BOOLEAN;
		}
		else if (root->token == TK_GE||root->token == TK_GT ||root->token == TK_LE ||root->token == TK_LT ||root->token == TK_EQ ||root->token == TK_NE ||root->token == TK_OR || root->token == TK_AND)
		{
			printf("setting the type of %s to %s \n", token_map[root->token], var_map[_BOOLEAN]);
			root->tk_type = _BOOLEAN;
			return _BOOLEAN;
		}
		else
		{
			printf("setting the type of %s to %s \n", token_map[root->token], var_map[v_flag]);
			root->tk_type = v_flag;
			return v_flag;
		}	
		// return v_flag;
	}

}

void compare_types(ASTNode* root)		// this functions compare types in RHS of ":=" i.e.   a := ((b+c>d) OR (c<b));
{
	
	if(root == NULL)
    return;

  if(root->token > START_OF_TERMINALS)  //is a terminal
  {
	if(root->token == TK_GE||root->token == TK_GT ||root->token == TK_LE ||root->token == TK_LT ||root->token == TK_EQ ||root->token == TK_NE )
	{
		var_type LHS, middle, RHS;
		ASTNode* top = root->parent->parent;
		LHS = top->children[0]->tk_type;
		RHS = root->parent->children[1]->tk_type;
		// printf("LHS: %s  ... RHS: %s \n", var_map[LHS], var_map[RHS]);
		if(LHS!= RHS)
			printf("ERROR: Type Mismatch at line number %d.\n", root->line_num);
		// printf("asdf\n");
	} 
	else if(root->token == TK_OR || root->token == TK_AND )
	{
		var_type LHS, RHS;
		ASTNode* top = root->parent->parent;
		LHS = top->children[0]->tk_type;
		RHS = root->parent->children[1]->tk_type;
		// printf("LHS: %s  ... RHS: %s \n", var_map[LHS], var_map[RHS]);
		if(LHS!= _BOOLEAN || RHS != _BOOLEAN)
			printf("ERROR: Type Mismatch at line number %d.\n", root->line_num);
			// printf(">>> error type checking in %s \n", token_map[root->token]);
		// printf("inside AND or OR\n");
	}
   return;
  }
  if(root->num_children>0)
    compare_types(root->children[0]);
  //for parent
	// printf("hsahf>>>\n");
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
        compare_types(root->children[i]);
        // if(temp->num_children!= 0)
        i++;
        y++;
      }
    }
  }
 
  return;
}

void compare_types2(ASTNode* root)		// this functions compare types in RHS of ":=" i.e.   a := ((b+c>d) OR (c<b));
{
	
	if(root == NULL)
    return;

  if(root->token > START_OF_TERMINALS)  //is a terminal
  {
   return;
  }
  if(root->num_children>0)
    compare_types2(root->children[0]);
  //for parent
	if(root->token == assignmentStmt)
	{
		var_type LHS = root->children[0]->tk_type;
		var_type RHS = root->children[1]->tk_type;

		// printf("~~~LHS: %s  ...(%s) RHS: %s \n", var_map[LHS], token_map[root->children[1]->token],var_map[RHS]);
		if(LHS != RHS)
		{
			printf("ERROR: Type Mismatch at line number %d.\n",root->line_num);
		}
	}
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
        compare_types2(root->children[i]);
        // if(temp->num_children!= 0)
        i++;
        y++;
      }
    }
  }
 
  return;
}

var_type assign_types(ASTNode* root)
{

	if(root->tk_type == _INTEGER)
		return _INTEGER;
	else if (root->tk_type == _REAL)
		return _REAL;
	else if (root->tk_type == _BOOLEAN)
		return _BOOLEAN;
	else if(root->token == TK_ID)
	{
		return root->tk_type;
	}
	else
	{
		int i;
		for (i = 0; i < root->num_children; ++i)
		{
			// printf("current root %d\n",root->children[i]->token );
			if(root->children[i]!=NULL)
			{
				// printf("root %s has child %d  null \n", token_map[root->token], i);
				root->children[i]->tk_type = assign_types(root->children[i]);
				// printf("root %s has child %s type assigned: %d \n", token_map[root->token],token_map[root->children[i]->token], root->children[i]->tk_type);
			}
		}
		if(root->token == TK_GE||root->token == TK_OR ||root->token == TK_GT ||root->token == TK_LE ||root->token == TK_LT ||root->token == TK_EQ ||root->token == TK_NE || root->token == TK_AND)
			root->tk_type= _BOOLEAN;
		int flag = 0;
		for(i=0;i<root->num_children;++i)
		{
			if(root->children[i] == NULL)
				continue;
			else if(root->children[i]->tk_type == _BOOLEAN)
			{
				root->tk_type = _BOOLEAN;
				flag = 1;
				break;
			}
			else if(root->token == lvalueARRStmt)
			{
				root->tk_type = root->children[1]->tk_type ;
				flag = 1;
				break;
			}
		}
		if(flag == 0)
		{
			for(i=0;i<root->num_children;++i)
			{
				if(root->children[i] == NULL)
					continue;
				else
					root->tk_type = root->children[i]->tk_type;
				break;
			}
		}
		// printf("over here %s->tk_type= %d \n",token_map[root->token] ,root->tk_type);
		// for(i=0;i<root->num_children;i++)
		// {
		// 	if(root->children[i] == NULL)
		// 		printf(" X ");
		// 	else
		// 		printf(" %s ",token_map[root->children[i]->token] );
		// }
		// printf("\nchildren of %s printed above \n",token_map[root->token] );
		return root->tk_type;
	}
}

//modify FST 
//FST entry shoud have number of input an d output parameters