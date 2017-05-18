// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: driver.c
// //*

#include "lexer.c"
#include "lexerDef.h"
#include "parser.c"
#include "AST.c"
#include "symbolTable.c"
#include "semanticAnalyzer.c"
#include <stdlib.h>
#include <stdio.h>
#include "codeGen.c"

FILE *fp_tree;
 
void display_file(const char* file_name)
{
  FILE* f = fopen(file_name, "r");
  if(f!=NULL)
  {
    char c;
    while(!feof(f))
    {
      c = fgetc(f);
      if(c!=-1)
        printf("%c", c);
    }
  }
  fclose(f);
  return;
}

void function_0(char* fname)
{
  FILE* file = fopen(fname, "r");
  FILE* f2 = file;
  char buffer[100];
  while(fgets(buffer, sizeof(buffer), file))
  {
     fputs(buffer,stdout); 
  }
  // fclosqe(f2);
  return;
}

void function_1(linked_list_node* current_ptr)
{
    printf("Printing lexems and tokens...\n\n");
    printf("LINE_NO.\t\tLEMEXE\t\t\tTOKEN\n\n");
    while(current_ptr != NULL)
    {
      
       printf("%d\t\t", current_ptr->data->line_num);
       printf("%*s ", 18, current_ptr->data->lexeme);
       printf("%*d ", 18, current_ptr->data->lexeme_token);
       printf("%*s\n",20, token_map[current_ptr->data->lexeme_token]);
       current_ptr= current_ptr->next;
    }
    // printf("token map of tk_minus %s\n", token_map[TK_MINUS]);
    return;
}

void function_2(parseTree* tree, char* filename)
{
      printf("Printing In-Order traversal of the Parse Tree...\n\n");
      printf("Current_Lexeme\t\t");
      printf("LINE_NUM \t");
      printf("Token\t\t");
      printf("value_If_Num\t");
      printf("Parent_Node\t\t");
      printf("Is_Leaf_Node\t");
      printf("Node_Symbol\n\n");

      // printf("file to be opened %s#\n",filename );
      fp_tree = fopen(filename, "w");
      // printf("-----file opened ------\n");
      FILE* fp2 = fp_tree;
      print_InOrder_traversal(tree->root, fp_tree);
      
      return;
}

void function_3(ASTNode* ast)
{ 
  printf("displaying AST\n");
  displayAST(ast);
  return; 
}

void function_4()
{
  pt_memory = sizeof(tree_node)*num_pt_nodes + sizeof(parseTree);
  ast_memory= sizeof(ASTNode)*num_ast_nodes;
  printf("Memory allocation for parse tree and AST:\n");
  printf("Parse Tree\n");
  printf("   |-Number of Nodes  : %d\n" , num_pt_nodes);
  printf("   |-Allocated Memory : %d\n" , pt_memory);
  printf("\n");
  printf("Abstract Syntax Tree\n");
  printf("   |-Number of Nodes  : %d\n" , num_ast_nodes);
  printf("   |-Allocated Memory : %d\n" , ast_memory);
  printf("\n");
  printf("Compression Percentage = %f\n", ((float)((float)pt_memory - (float)ast_memory)/(float)pt_memory)*100);
  return;
}


void function_5(varSymbolTable* VST, funcSymbolTable* FST)
{   
    printf("Displaying Symbol Tables\n"); 
    printSymbolTables(VST, FST);
    printf("\n");
  return;
}

void function_6(linked_list_node* list, ASTNode* ast, varSymbolTable* VST, funcSymbolTable* FST)
{
  printf("Cheching for parsing errors..\n");
  if(num_parsing_errors != 0)
  {
    display_file("parse_errors.txt");
    printf("Parsing error(s) found.\n");
    printf("Semantic Errors will not be printed!\n");
  }  
  else
  {
    printf("Syntax is correct (No parsing errors).\n");
    printf("Reporting Semantic Errors...\n\n");
    display_file("errors.txt");
    reportSemanticErrors(list, VST, FST);
    reportSemanticErrors2(ast, VST, FST);
    compare_types(ast); // compare RHS of ":=" i.e.   a := ((b+c>d) OR (c<b));
    compare_types2(ast); // for comparing LHS and RHS of ":=" ;
    check_arr_len_errors(ast,VST);
  }
  return;
}

void function_7(ASTNode* root)
{
  printf("Assembly code generation..\n");
  generateCode(root);
  printf("Module Incomplete!\nCreated structure for maintaining three address code and implmented one module.\n");
  return;
}


int main(int argc, char* argv[])
{
  printf("\nLEVEL 4: Symbol Table/ AST/ Semantic Rules modules work.\n\n");
  printf("FIRST and FOLLOW sets automated.\n");   // -------------------------//code according to the driver specifications mentioned--------
  printf("Both lexical and syntax analysis modules implemented.\n");
  printf("DFA initialized.\n");

  linked_list_node* head =(linked_list_node*) malloc(sizeof(linked_list_node));
  head->next = NULL;
  current_ptr = head;
  DFA* dfa = DFA_initialize();
  DFA_construction(dfa);
  remove_comments(argv[1]);   // removing comments
  char cleaned_file[30];
  strcpy(cleaned_file, "cleaned_");
  strcat(cleaned_file, argv[1]);
  test_file = fopen(cleaned_file, "r");
  FILE* test_file2 = test_file;
  char input_test_file[50];

  char* tree_filename = argv[2];
  // printf("1st argument %s\n",argv[1] );
  // linked_list_node* current_ptr2 = head;
  while(feof(test_file) == 0)
    getNextToken(dfa);
  // free(dfa);
  // fclose(test_file2);
  
  current_ptr= head->next;
  parseTree* parse_tree = NULL;  
  parse_tree = parse(head->next);  
  parseTree* parse_tree_copy = parse_tree;
  // printf("%d, !!!!", num_parsing_errors);
  printf("Parse tree created.\n");

   // print the errors on the screen
  // printf("chececk start: %s\n", token_map[head->next->data->lexeme_token]);

  varSymbolTable* VST; 
  funcSymbolTable* FST;
  ASTNode* ast_copy;
  ASTNode* ast;

  FILE * fp_errors = fopen("errors.txt", "w");
  fp_ast = fopen("ast_flags.txt", "r");
  linked_list_node* input_node = head->next;
  VST = initialize_var_ST(); 
  FST = initialize_func_ST();
  populateSymbolTable(input_node, VST, FST, fp_errors);

  if(num_parsing_errors == 0)
  {
      
      printf("Symbol table created.\n");

      
      // printf("Creating AST rule list...\n");
      ASTRuleNode** ast_rules = createASTRuleList();
      // printf("Creating AST from Parse Tree...\n");
      ast = createASTfromPT(parse_tree->root, ast_rules, NULL);
      ast = assign_Datatype(VST, FST, ast); 
      printf("AST created.\n");  
      ast_copy = ast;
  }
  fclose(fp_ast);

  while(1)
    {    

      printf("----------------------------------------------------------------------------------------\n");
      printf("0 - Print the comment free code.\n");
      printf("1 - Print the token list and lexemes generated from LEXER.\n"); 
      printf("2 - Parse a test file to verify its syntactic correctness and display errors. Print the Parse Tree\n");
      printf("3 - Print the Abstract Syntax Tree (In-Order Traversal).\n");
      printf("4 - Memory allocation and compression ration.\n");
      printf("5 - Print the Symbol Table in appropriate format.\n");
      printf("6 - Compiling to verify the syntactic and semantic correctness of the input source code.\n");
      printf("7 - For producing assembly code.\n");
      printf("Press any other key to exit\n");
      printf("----------------------------------------------------------------------------------------\n");    
      // printf("---------------------------------------------------------------\n");
      printf("Enter your choice:  INTEGRAL VALUES ONLY!\n");
      printf("\n");
      
      int choice;
      scanf("%d", &choice);

      if(choice >= 0 && choice <= 7)
      {
        switch(choice)
        {
          case(0): 
          {
            function_0(cleaned_file);
            break;
          }
          case(1):
          {
            function_1(head->next);
            break;
          }
          case(2):
          {
              // printf("chechk..... %s\n", token_map[parse_tree->root->data]);
              printf("Printing In-Order traversal of the Parse Tree...\n\n");
              parse_tree = parse(head->next); 
              function_2(parse_tree, tree_filename);
              printf("\nParse tree written in file...\n");
  
              break;
          }
          case(3):    // AST
          {
            if(num_parsing_errors==0)
                function_3(ast_copy);
            else
                printf("Incorrect Syntax: AST will not be created.\n");

            break;
          }
          case(4):   //memory used
          {
              if(num_parsing_errors==0)
                function_4();
              else
                printf("Incorrect Syntax: AST will not be created.\n");

              break;
          }     
          case(5):  // print symbol table
          {
            function_5(VST, FST);
            // printf("SymbolTable.txt generated.");
            break;
          }  
          case(6):  //report semantic errors
          {
            if(num_parsing_errors==0)
                function_6(head->next, ast, VST, FST);
            else
                printf("Incorrect Syntax: AST will not be created -> Semantic analysis not possible\n");
            break;
          }
          case(7):
          {
            if(num_parsing_errors==0)
                function_7(ast);
            else
                printf("Incorrect Syntax: AST will not be created -> Assembly code generation not possible\n");
            break;
          }
          default:
          {
            break;
          }  
        }
      }
      else
        break;
    }
    remove("errors.txt");
    remove("errorfile.txt");
    remove(cleaned_file);
    return 0;        
}
