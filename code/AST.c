// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: AST.c
// //*

#include "AST.h"

#define NUM_OF_PRODUCTIONS 96
#define START_OF_TERMINALS 54 //null_val in enum Token/TERM



ASTNode* initializeASTNode(int rule_no, TERM tk, int line_num, char* lexeme)
{
    ASTNode *a = (ASTNode*) malloc(sizeof(ASTNode));
    a->rule_no = rule_no;
    a->num_children = 0;
    strcpy(a->lexeme, lexeme);
    a->token = tk;
    // a->tk.tokenType = tk.tokenType;
    a->line_num = line_num;
    // a->next = NULL;
    a->parent = NULL;
    a->children = NULL;
    return a;
}

void add_ast_rule(ASTRuleNode* r, enum ast_action action, int rule_length)
{

    r->action = action;
    r->rule_length = rule_length;
    int j = 0;
    if(r->action == REPLACE_NULL)
    {
        r->num_children = 0;
        // printf("REPLACE_NULL\n");
        r->in_ast = NULL;
        return;
    }

    r->in_ast = (int*)malloc(r->rule_length*sizeof(int));
    // printf("%d  -> %d ->  ", action, r->rule_length);
    while(j < r->rule_length)
    {
        int flag;
        fscanf(fp_ast, "%d", &flag);
        // printf("%d ", flag);
        if(flag)
        {
            r->num_children++;
            r->in_ast[j] = 1;
        }
        else
        {
            r->in_ast[j] = 0;
        }
        j++;
    }
    // printf("\n");

    return;
}

ASTRuleNode** createASTRuleList()
{
    ASTRuleNode** ast_rules = (ASTRuleNode**) malloc(sizeof(ASTRuleNode*) * NUM_OF_PRODUCTIONS);
    int i;

    for(i=0; i<NUM_OF_PRODUCTIONS; i++)
    {
      ast_rules[i] = (ASTRuleNode*)malloc(sizeof(ASTRuleNode));
    }
  //Grammar index    //astRuleNode    //action  //rule_length
           
   /* 0 */ add_ast_rule(ast_rules[0], TRIM, 4);
   /* 1 */ add_ast_rule(ast_rules[1], TRIM, 2); 
   /* 2 */ add_ast_rule(ast_rules[2], REPLACE_NULL, 0);
   /* 3 */ add_ast_rule(ast_rules[3], TRIM, 4);
   /* 4 */ add_ast_rule(ast_rules[4], TRIM, 2);
   /* 5 */ add_ast_rule(ast_rules[5], REPLACE_NULL, 0);
   /* 6 */ add_ast_rule(ast_rules[6], TRIM, 5);
   /* 7 */ add_ast_rule(ast_rules[7], TRIM, 12);
   /* 8 */ add_ast_rule(ast_rules[8], TRIM, 5);
   /* 9 */ add_ast_rule(ast_rules[9], REPLACE_NULL, 0);
   /* 10 */add_ast_rule(ast_rules[10], TRIM, 4);
   /* 11 */add_ast_rule(ast_rules[11], TRIM, 5);
   /* 12 */add_ast_rule(ast_rules[12], REPLACE_NULL, 0);
   /* 13 */add_ast_rule(ast_rules[13], TRIM, 5);
   /* 14 */add_ast_rule(ast_rules[14], REPLACE_NULL, 0);
   /* 15 */add_ast_rule(ast_rules[15], COLLAPSE_CHAIN, 1);
   /* 16 */add_ast_rule(ast_rules[16], COLLAPSE_CHAIN, 1);
   /* 17 */add_ast_rule(ast_rules[17], COLLAPSE_CHAIN, 1);
   /* 18 */add_ast_rule(ast_rules[18], TRIM, 6);
   /* 19 */add_ast_rule(ast_rules[19], COLLAPSE_CHAIN, 1);
   /* 20 */add_ast_rule(ast_rules[20], COLLAPSE_CHAIN, 1);
   /* 21 */add_ast_rule(ast_rules[21], COLLAPSE_CHAIN, 1);
   /* 22 */add_ast_rule(ast_rules[22], TRIM, 3);
   /* 23 */add_ast_rule(ast_rules[23], TRIM, 2);
   /* 24 */add_ast_rule(ast_rules[24], REPLACE_NULL, 0);
   /* 25 */add_ast_rule(ast_rules[25], COLLAPSE_CHAIN, 1);
   /* 26 */add_ast_rule(ast_rules[26], COLLAPSE_CHAIN, 1);
   /* 27 */add_ast_rule(ast_rules[27], COLLAPSE_CHAIN, 1);
   /* 28 */add_ast_rule(ast_rules[28], COLLAPSE_CHAIN, 1);
   /* 29 */add_ast_rule(ast_rules[29], COLLAPSE_CHAIN, 1);
   /* 30 */add_ast_rule(ast_rules[30], TRIM, 5);
   /* 31 */add_ast_rule(ast_rules[31], TRIM, 5);
   /* 32 */add_ast_rule(ast_rules[32], TRIM, 2);
   /* 33 */add_ast_rule(ast_rules[33], COLLAPSE_CHAIN, 1);
   /* 34 */add_ast_rule(ast_rules[34], COLLAPSE_CHAIN, 1);
   /* 35 */add_ast_rule(ast_rules[35], TRIM, 3);
   /* 36 */add_ast_rule(ast_rules[36], REPLACE_NULL, 0);
   /* 37 */add_ast_rule(ast_rules[37], COLLAPSE_CHAIN, 1);
   /* 38 */add_ast_rule(ast_rules[38], COLLAPSE_CHAIN, 1);
   /* 39 */add_ast_rule(ast_rules[39], TRIM, 2);
   /* 40 */add_ast_rule(ast_rules[40], COLLAPSE_CHAIN, 1);
   /* 41 */add_ast_rule(ast_rules[41], COLLAPSE_CHAIN, 1);
   /* 42 */add_ast_rule(ast_rules[42], TRIM, 3);
   /* 43 */add_ast_rule(ast_rules[43], TRIM, 6);
   /* 44 */add_ast_rule(ast_rules[44], COLLAPSE_CHAIN, 1);
   /* 45 */add_ast_rule(ast_rules[45], COLLAPSE_CHAIN, 1);
   /* 46 */add_ast_rule(ast_rules[46], TRIM, 8);
   /* 47 */add_ast_rule(ast_rules[47], TRIM, 4);
   /* 48 */add_ast_rule(ast_rules[48], REPLACE_NULL, 0);
   /* 49 */add_ast_rule(ast_rules[49], TRIM, 2);
   /* 50 */add_ast_rule(ast_rules[50], TRIM, 3);
   /* 51 */add_ast_rule(ast_rules[51], REPLACE_NULL, 0);
   /* 52 */add_ast_rule(ast_rules[52], TRIM, 2);
   /* 53 */add_ast_rule(ast_rules[53], TRIM, 3);
   /* 54 */add_ast_rule(ast_rules[54], REPLACE_NULL, 0);
   /* 55 */add_ast_rule(ast_rules[55], TRIM, 2);
   /* 56 */add_ast_rule(ast_rules[56], TRIM, 3);
   /* 57 */add_ast_rule(ast_rules[57], REPLACE_NULL, 0);
   /* 58 */add_ast_rule(ast_rules[58], TRIM, 2);
   /* 59 */add_ast_rule(ast_rules[59], TRIM, 3);
   /* 60 */add_ast_rule(ast_rules[60], REPLACE_NULL, 0);
   /* 61 */add_ast_rule(ast_rules[61], TRIM, 2);
   /* 62 */add_ast_rule(ast_rules[62], TRIM, 3);
   /* 63 */add_ast_rule(ast_rules[63], REPLACE_NULL, 0);
   /* 64 */add_ast_rule(ast_rules[64], COLLAPSE_CHAIN, 1);
   /* 65 */add_ast_rule(ast_rules[65], COLLAPSE_CHAIN, 1);
   /* 66 */add_ast_rule(ast_rules[66], COLLAPSE_CHAIN, 1);
   /* 67 */add_ast_rule(ast_rules[67], COLLAPSE_CHAIN, 1);
   /* 68 */add_ast_rule(ast_rules[68], COLLAPSE_CHAIN, 1);
   /* 69 */add_ast_rule(ast_rules[69], COLLAPSE_CHAIN, 1);
   /* 70 */add_ast_rule(ast_rules[70], COLLAPSE_CHAIN, 1);
   /* 71 */add_ast_rule(ast_rules[71], COLLAPSE_CHAIN, 1);
   /* 72 */add_ast_rule(ast_rules[72], COLLAPSE_CHAIN, 1);
   /* 73 */add_ast_rule(ast_rules[73], COLLAPSE_CHAIN, 1);
   /* 74 */add_ast_rule(ast_rules[74], COLLAPSE_CHAIN, 1);
   /* 75 */add_ast_rule(ast_rules[75], COLLAPSE_CHAIN, 1);
   /* 76 */add_ast_rule(ast_rules[76], TRIM, 5);
   /* 77 */add_ast_rule(ast_rules[77], TRIM, 8);
   /* 78 */add_ast_rule(ast_rules[78], TRIM, 7);
   /* 79 */add_ast_rule(ast_rules[79], TRIM, 7);
   /* 80 */add_ast_rule(ast_rules[80], REPLACE_NULL, 0);
   /* 81 */add_ast_rule(ast_rules[81], COLLAPSE_CHAIN, 1);
   /* 82 */add_ast_rule(ast_rules[82], COLLAPSE_CHAIN, 1);
   /* 83 */add_ast_rule(ast_rules[83], COLLAPSE_CHAIN, 1);
   /* 84 */add_ast_rule(ast_rules[84], TRIM, 5);
   /* 85 */add_ast_rule(ast_rules[85], REPLACE_NULL, 0);
   /* 86 */add_ast_rule(ast_rules[86], TRIM, 9);
   /* 87 */add_ast_rule(ast_rules[87], TRIM, 7);
   /* 88 */add_ast_rule(ast_rules[88], TRIM, 4);
   /* 89 */add_ast_rule(ast_rules[89], TRIM, 3);
   /* 90 */add_ast_rule(ast_rules[90], COLLAPSE_CHAIN, 1);
   /* 91 */add_ast_rule(ast_rules[91], TRIM, 4);
   /* 92 */add_ast_rule(ast_rules[92], COLLAPSE_CHAIN, 1);
   // /* 95 */add_ast_rule(ast_rules[95], TRIM, 4);
    // flags for rule 93 : 1 0 1 0
   /* 93 */add_ast_rule(ast_rules[93], TRIM, 2);
   /* 94 */add_ast_rule(ast_rules[94], TRIM, 1);
   /* 95 */add_ast_rule(ast_rules[95], TRIM, 1);

  return ast_rules;
}
int a = 1;

ASTNode* createASTfromPT(tree_node* p, ASTRuleNode** ast_rules, ASTNode* parent)
{
    // printf("%d, p->root: %s \n", a++, token_map[p->data]);

    if(p == NULL)
    {
      // printf("p == NULL\n");
        return NULL;
    }
    int rule;
    if(p->num_children==0)
    {
      rule=-1;
    }
    else if(p->children->front == $)
    {
      rule = -2;
    }
    // int rule = p->g_index; //rule number
    else
    {
      rule = p->children->front->g_index;
    }
    // printf("token: %s rule: %d \n", token_map[p->data], rule);
    // printf("%s%*s\n", getIDStr(p->nodeid), 50, p->tk.lexeme);
    if(rule == -1)   // Is a terminal
    {
        // printf("Terminal: Leaf Node -> %s\n", token_map[p->data]);
        ASTNode *a = (ASTNode*) malloc(sizeof(ASTNode));
        a->rule_no = p->g_index;
        a->num_children = 0;
        strcpy(a->lexeme, p->lexeme);
        a->token = p->data;
        a->tk_type = p->tk_type;
       // a->tk.tokenType = tk.tokenType;
        a->line_num = p->line_num;
        // a->next = NULL;
        a->parent = parent;
        a->children = NULL;
        num_ast_nodes ++;
        return a;
    }
    else if(rule == -2)
    {
      return NULL;
    }

    enum ast_action action = ast_rules[rule]->action;

    switch(action)
    {
        case(REPLACE_NULL):
        {
          int count = 0; 
          ASTNode* temp = parent;
          // parent->num_children --;
          return NULL;
          break;
        }

        case(TRIM):
        {
          // printf("------------ ");
          //trim the parse tree
          // printf("TRIM: %s", token_map[p->data]);
          int i = 0, j = 0;
          ASTNode *a = (ASTNode*) malloc(sizeof(ASTNode));
          a->rule_no = p->children->front->g_index;
          strcpy(a->lexeme, p->lexeme);
          a->token = p->data;
         // a->tk.tokenType = tk.tokenType;
          a->line_num = p->line_num;
          // a->next = NULL;
          // a->parent = NULL;
          a->num_children = ast_rules[rule]->num_children;
          // printf(" rule:%d  num_children:%d \n",a->rule_no, a->num_children);
          a->children = (ASTNode**) malloc(sizeof(ASTNode*) * a->num_children);
          while(i < p->num_children)
          {
              if(ast_rules[rule]->in_ast[i] == 1)
              {
                // printf("calling from while of TRIM\n");
                ASTNode* temp = createASTfromPT(p->children->front, ast_rules, a);
                if(temp!=NULL)
                {
                  // temp->parent = (ASTNode*)malloc(sizeof(ASTNode));
                  temp->parent = a;
                  a->children[j] = temp;
                  j++;
                }
                //p->children->front = p->children->front->next;
              } 
              p->children->front = p->children->front->next;
              i++;
          }
          num_ast_nodes++;
          return a;
         break;
        }

     };  
        // collapsing linear chains
    // printf("-------- Chain Copllapse: %s\n", p->lexeme);
    int i;
    for (i = 0; i < p->num_children; i++)
    {
        if(ast_rules[rule]->in_ast[i] == 1)
            break;
        p->children->front = p->children->front->next;
    }
    // printf("calling after COLLAPSE_CHAIN\n");
    return createASTfromPT(p->children->front, ast_rules, NULL);
        
}

/*
if found in VST
        {
          find the hashValue
          travel the linked list in VST entry
          1. if the line no. is between the start and end scope
          2. else if (line no. + 2 ) is the start scope (i.e. "returns" also exists) .... handling takes parameter
          3. else if (line no. + 1 ) is the start scope .... handling returns parameter
        }
        else find in FST
        {
  
        }
        if not found
          assign type = NONE; 
*/
ASTNode* assign_Datatype(varSymbolTable* VST, funcSymbolTable* FST, ASTNode* root )
{
  if(root == NULL)
  {
    // printf("culprit!!\n");
    return root ;
  }
  // printf("Hi");

  if(root->token > START_OF_TERMINALS)  //is a terminal
  {    
    if (root->token == TK_ID)
    {
      // printf("%s %s check\n", root->lexeme, token_map[TK_ID] );
      int key = computeHashVal(root->lexeme);
      if(root->parent->token == module || root->parent->token == moduleDeclaration || root->parent->token == moduleDeclarations)  /* parent is mD or mDs || module  */
      {
        // printf("Hi %s  func\n", root->lexeme);
        funcTableEntry* temp = FST->entries[key];
        while(temp!= NULL)
        {
          // printf("%s %s check\n", temp->name, root->lexeme);
          if(strcmp(root->lexeme, temp->name)==0)
          {
            // printf("assigning _MODULE to %s", root->lexeme);
            root->tk_type = _MODULE ;
            return root;
          }
          temp=temp->next;
        }
      }
      else
      {
        int line = -1;
        varTableEntry* temp =  VST->entries[key];
        while(temp != NULL)   // handling the normal variables
        {
          if(strcmp(temp->name, root->lexeme)==0)
          {
            // printf("here?\n");
            line = root->line_num;
            if(line >= temp->scope[0] && line <= temp->scope[1])
            {
                if(temp->is_array == 1)
              {
                  root->tk_type = temp->arr_or_var.arr.type;
                  root->is_array = 1;
              }    
              else
              {
                  root->tk_type = temp->arr_or_var.var_type; 
                  root->is_array = 0;
              }
              return root;             
            }
          }
          temp = temp->next;
        }
        temp =  VST->entries[key];
        while(temp!=NULL)  // handling the case of "takes" and "returns"
        {
          if(strcmp(temp->name, root->lexeme)==0)
          {
            // printf("here?2\n");

            line = root->line_num + 2;
            if(line >= temp->scope[0] && line <= temp->scope[1])
            {
              if(temp->is_array == 1)
              {
                  root->tk_type = temp->arr_or_var.arr.type;
                  root->is_array = 1;
              }    
              else
              {
                  root->tk_type = temp->arr_or_var.var_type; 
                  root->is_array = 0;
              } 
              return root;             
            }
          }
          temp = temp->next;
        }
      }
    }
    return root;
  }
  if(root!=NULL && root->num_children>0)
  {
    // printf("entering this..\n");
    root->children[0] = assign_Datatype(VST, FST, root->children[0]);
    if(root->children[0] != NULL)
      root->line_num = root->children[0]->line_num;
  }
  //for parent
  // printf("%s\n", token_map[root->token]);
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
        root->children[i] = assign_Datatype(VST, FST, root->children[i]);
        // if(temp->num_children!= 0)
        i++;
        y++;
      }
    }
  }
 
  return root ;
}

ASTNode* correct_chain_collapse(tree_node* p, ASTRuleNode** ast_rules, ASTNode* parent)
{
  //send the left child
  // deal with parent
  // send the right child
  printf(">>> inside correct_chain_collapse >>> PENDING FUNCTION\n");
  return parent;
}

void displayAST(ASTNode* root)
{ 
  if(root == NULL)
    return;

  if(root->token > START_OF_TERMINALS)  //is a terminal
  {
    printf("%*s %*s %*s %*d\n", 10, root->lexeme, 25, token_map[root->token], 25, var_map[root->tk_type], 5, root->line_num);
    return;
  }
  if(root->num_children>0)
    displayAST(root->children[0]);
  //for parent
  printf("%*s %*s %*s %*d\n", 10, root->lexeme, 25, token_map[root->token], 25, var_map[root->tk_type], 5, root->line_num);
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
        displayAST(root->children[i]);
        // if(temp->num_children!= 0)
        i++;
        y++;
      }
    }
  }
 
  return;
}

// int main()
// {
//   ASTRuleNode** ast_rules = createASTRuleList();
//   return 0;
// }
