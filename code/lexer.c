// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: lexer.c
// //*

#include <stdio.h>
#define BUFFER_LENGTH 128
#include "dfa.c"
#include "lexer.h"
static FILE * test_file;

char lexeme[MAX_LEXEME_LENGTH];
int lexeme_index=0;
linked_list_node* head;
linked_list_node* current_ptr;
int LINE_NUM = 0;

char* getStream()		//function to read code into the buffer - one line at a time
{
  char *buffer=(char *)malloc(BUFFER_LENGTH*sizeof(char));
  // fgets(buffer, BUFFER_LENGTH, test_file);

  // if (strlen(buffer)==BUFFER_LENGTH)
  if(fgets(buffer, BUFFER_LENGTH, test_file) != NULL)
  {
    int index=0;
    // printf("Check buffer[%d] = %c ", BUFFER_LENGTH-5, buffer[BUFFER_LENGTH-125]);
    while(index!=BUFFER_LENGTH && buffer[index]!='\0')
    {
      if(buffer[index]=='\n')
        LINE_NUM ++ ;
      index++;
    }
  }    
  return buffer;
}

int check_transition(DFA* dfa, int from_state, char input_symbol)
{
	int i =0;		
	if(from_state==10 && (input_symbol =='e' || input_symbol=='E'))			// for cases such as 23.4E-4
		return 11;
	if ((input_symbol>='A'&&input_symbol<='Z')||(input_symbol>='a'&&input_symbol<='z'))
		input_symbol= 'a';
	else if (input_symbol>='0'&& input_symbol<='9')
		input_symbol = '0' ;

	for(i=0; i<dfa->states[from_state]->num_transitions; i++)
	{
		if (dfa->states[from_state]->transitions[i].input_char  == input_symbol)
			return dfa->states[from_state]->transitions[i].dest_state ;
	}
	return -1 ;
}

Token get_lexeme_token(char* input_lexeme)
{
	char f = input_lexeme[0] ;
	char f1;

	if(strlen(input_lexeme)>1)
	{
		f1 = input_lexeme[1];
	}	

	if( (f>=40 && f<=47) || (f>=58 && f<=62) || (f>=91 && f<=95) || (f==213) || (f==215) )
	{
		if(strcmp(input_lexeme,"+")==0)
			return TK_PLUS;
		else if(strcmp(input_lexeme,"-")==0)
			return TK_MINUS;
		else if(strcmp(input_lexeme,"*")==0)
			return TK_MUL;
		else if(strcmp(input_lexeme,"/")==0)
			return TK_DIV;
		else if(strcmp(input_lexeme,"(")==0)
			return TK_BO;
		else if(strcmp(input_lexeme,")")==0)
			return TK_BC;
		else if(strcmp(input_lexeme,"[")==0)
			return TK_SQBO;
		else if(strcmp(input_lexeme,"]")==0)
			return TK_SQBC;
		else if(strcmp(input_lexeme,":")==0)
			return TK_COLON;
		else if(strcmp(input_lexeme,";")==0)
			return TK_SEMICOL;	
		else if(strcmp(input_lexeme,",")==0)
			return TK_COMMA;
		else if(strcmp(input_lexeme,":=")==0)
			return TK_ASSIGNOP;
		else if(strcmp(input_lexeme,"<<")==0)
			return TK_DEF;
		else if(strcmp(input_lexeme,">>")==0)
			return TK_ENDDEF;
		else if(strcmp(input_lexeme,"<<<")==0)
			return TK_DRIVERDEF;
		else if(strcmp(input_lexeme,">>>")==0)
			return TK_DRIVERENDDEF;
		else if(strcmp(input_lexeme,"<")==0)
			return TK_LT;
		else if(strcmp(input_lexeme,"<=")==0)
			return TK_LE;
		else if(strcmp(input_lexeme,">")==0)
			return TK_GT;
		else if(strcmp(input_lexeme,">=")==0)
			return TK_GE;
		else if(strcmp(input_lexeme,"!=")==0)
			return TK_NE;
		else if(strcmp(input_lexeme,"==")==0)
			return TK_EQ;
	}

	if((f>=48 && f<=57) || (f == 45 && (f1>=48 && f1<=57)) ) // the 2nd case is for lexemes like -20.3 // 45=="-"
	{
		int k=0 , flag = 0;
		int count = 0;
		for(k=0;k<strlen(input_lexeme);k++)
		{
			if(input_lexeme[k]=='.')
				count++ ;
			if(input_lexeme[k+1] == '.' && input_lexeme[k] == '.')
					flag = 1;
		}

		if(count == 0)
			return TK_NUM;
		else if (count == 1)
			return TK_RNUM;
		else if(count == 2 && flag == 1)
			return TK_RANGEOP;
	}
	else  
	{
		if(strcmp(input_lexeme,"integer")==0)
			return TK_INTEGER;
		else if(strcmp(input_lexeme,"real")==0)
			return TK_REAL;
		else if(strcmp(input_lexeme,"boolean")==0)
			return TK_BOOLEAN;
		else if(strcmp(input_lexeme,"of")==0)
			return TK_OF;
		else if(strcmp(input_lexeme,"array")==0)
			return TK_ARRAY;
		else if(strcmp(input_lexeme,"start")==0)
			return TK_START;
		else if(strcmp(input_lexeme,"end")==0)
			return TK_END;
		else if(strcmp(input_lexeme,"declare")==0)
			return TK_DECLARE;
		else if(strcmp(input_lexeme,"module")==0)
			return TK_MODULE;
		else if(strcmp(input_lexeme,"driver")==0)
			return TK_DRIVER;
		else if(strcmp(input_lexeme,"program")==0)
			return TK_PROGRAM;
		else if(strcmp(input_lexeme,"get_value")==0)
			return TK_GET_VALUE;
		else if(strcmp(input_lexeme,"print")==0)
			return TK_PRINT;
		else if(strcmp(input_lexeme,"use")==0)
			return TK_USE;
		else if(strcmp(input_lexeme,"with")==0)
			return TK_WITH;
		else if(strcmp(input_lexeme,"parameters")==0)
			return TK_PARAMETERS;
		else if(strcmp(input_lexeme,"true")==0)
			return TK_TRUE;
		else if(strcmp(input_lexeme,"false")==0)
			return TK_FALSE;
		else if(strcmp(input_lexeme,"takes")==0)
			return TK_TAKES;
		else if(strcmp(input_lexeme,"input")==0)
			return TK_INPUT;
		else if(strcmp(input_lexeme,"returns")==0)
			return TK_RETURNS;
		else if(strcmp(input_lexeme,"AND")==0)
			return TK_AND;
		else if(strcmp(input_lexeme,"OR")==0)
			return TK_OR;
		else if(strcmp(input_lexeme,"for")==0)
			return TK_FOR;
		else if(strcmp(input_lexeme,"in")==0)
			return TK_IN;
		else if(strcmp(input_lexeme,"switch")==0)
			return TK_SWITCH;
		else if(strcmp(input_lexeme,"case")==0)
			return TK_CASE;
		else if(strcmp(input_lexeme,"break")==0)
			return TK_BREAK;
		else if(strcmp(input_lexeme,"default")==0)
			return TK_DEFAULT;
		else if(strcmp(input_lexeme,"while")==0)
			return TK_WHILE;
		else 
		{
			if(strlen(input_lexeme) > 8)
			{
				num_parsing_errors ++; 
				printf("ERROR_1 : Identifier (%s) at line %d is longer than the prescribed length.\n", lexeme, LINE_NUM);
			}			
			return TK_ID;
		}
	}
}

TokenInfo* create_token(char* lexeme, char* comment, int line)
{
	TokenInfo* tk = (TokenInfo*) malloc (sizeof(TokenInfo)); 
	strcpy(tk->lexeme,lexeme);
	tk->lexeme_token = get_lexeme_token(lexeme);
	Token temp = tk->lexeme_token;
	switch(temp)
	{
		case TK_INTEGER:
		{
			tk->tk_type = _INTEGER;
			break;
		}
		case TK_NUM:
		{
			tk->tk_type = _INTEGER;
			break;
		}
		case TK_REAL:
		{
			tk->tk_type = _REAL;
			break;
		}
		case TK_RNUM:
		{
			tk->tk_type = _REAL;
			break;
		}
		case TK_TRUE:
		{
			tk->tk_type = _BOOLEAN;
			break;
		}
		case TK_FALSE:
		{
			tk->tk_type = _BOOLEAN;
			break;
		}
		case TK_BOOLEAN:
		{
			tk->tk_type = _BOOLEAN;
			break;
		}
		default:
		{
			tk->tk_type = _NONE;
			break;
		}
	}

	tk->line_num = line;
	strcpy(tk->token_name, comment);
	return tk;
}

void getNextToken(DFA* dfa)
{
	char *buffer=(char *)malloc(BUFFER_LENGTH*sizeof(char)); 
	buffer  = getStream();		
	char lookahead;
	int val_check_transition, i;
	int current_state = dfa->current_state;		// current state of DFA
	for (i=0;i<BUFFER_LENGTH ; i++)
	{
		current_state = dfa->current_state;
		lookahead = buffer[i];
		if (feof(test_file) != 0)
		{
			break;
		}
		else if(lookahead == '\0')
		{ 
			return;
		}

		char temp[MAX_LEXEME_LENGTH];
		strcpy(temp, lexeme);

		val_check_transition = check_transition(dfa, current_state, lookahead);		// returns -1 if no possible tran. else return ID of "toState"

		if(val_check_transition == -1)					// no transition made
		{
			if(dfa->states[current_state]->is_final)	// check if that is the final state
			{
				if(!(current_state == 5))
				{ 	
					TokenInfo* t = create_token(lexeme, dfa->states[current_state]->comment, LINE_NUM);
					linked_list_node* newnode = (linked_list_node*)malloc(sizeof(linked_list_node));
					newnode->data = t;
					newnode->next = NULL;
					current_ptr->next = newnode;
					current_ptr = newnode;
				}
				
				lexeme_index = 0 ;
				memset(lexeme, 0, sizeof(lexeme));
				i--;									// keep the lookahead
				dfa->current_state = dfa->start_state;	// go to the start state of DFA and check according to the lookahead.
			}	
			else										// if it is not a final state,
			{
				if(lookahead == '\0')
					printf("NULL lookahead  ");
				int l = (int)lookahead;
				if((l>=34 && l <=39) || (l==63) || (l==64) || (l>=92 && l<=96) || (l>=123 && l<=126))
					{
						num_parsing_errors ++;
						printf("ERROR_2 : Unknown Symbol %c at line %d.\n", lookahead, LINE_NUM);	// report error corresponding to the current state
						FILE* fp = fopen("errorfile.txt", "a");
						FILE* fp2 = fp;
						fprintf(fp, "ERROR_2 : Unknown Symbol %c at line %d.\n", lookahead, LINE_NUM );
						fclose(fp2);
					}
				if(lookahead == '\n' && dfa->current_state != 0)
					{
						num_parsing_errors ++;
						printf("ERROR_3 : Unknown pattern %c\'\\n\' at line %d.\n", buffer[i-1],  LINE_NUM);
						FILE* fp3 = fopen("errorfile.txt", "a");
						FILE* fp4 = fp3;
						fprintf(fp3, "ERROR_3 : Unknown pattern %c\'\\n\' at line %d.\n", buffer[i-1],  LINE_NUM );
						fclose(fp4);
					}
				else if(dfa->current_state != 0)
				{
					num_parsing_errors++;
					printf("ERROR_3 : Unknown pattern %c%c at line %d.\n", buffer[i-1], lookahead, LINE_NUM);
					FILE* fp5 = fopen("errorfile.txt", "a");
					FILE* fp6 = fp5;
					fprintf(fp5,"ERROR_3 : Unknown pattern %c%c at line %d.\n", buffer[i-1], lookahead, LINE_NUM);
					fclose(fp6);
				}
				
				lexeme_index = 0 ;
				memset(lexeme, 0, sizeof(lexeme));
				dfa->current_state = 0;
			}
		}
		else											// transition is made
		{
			if(!(current_state==5))  //corresponds to TK_DELIM state
				lexeme[lexeme_index++] = lookahead;		// take action for the transition
			dfa->current_state = val_check_transition;	// update the current state
		}
	}	
}

void remove_comments(char* file_name)
{
	// printf("in remove comments, file: %s\n", file_name);
	
    char input_test_file[50], cleaned_test_file[50];
    strcpy(cleaned_test_file, "cleaned_");
    strcat(cleaned_test_file, file_name);
    // printf("name of cleaned file %s", cleaned_test_file);

    FILE* input_file = fopen(file_name, "r");
    FILE* input_file2 = input_file;
    FILE* clean_file = fopen(cleaned_test_file, "w");
    FILE* clean_file2 = clean_file;

    if (input_file == NULL || clean_file == NULL)
   {
        printf("Error opening file");
        return;
   }
  char ch, nextc;
  nextc = fgetc (input_file);
  while (nextc != EOF)
    {
      ch = nextc;
      nextc = fgetc (input_file);

      if ((ch == '*') && (nextc == '*'))
        {
          nextc = fgetc (input_file);
          while ((ch != '*') || (nextc != '*')) /* unroll until the end of comment*/
            {
            	if(ch == '\n')
            		fprintf(clean_file, "%c", ch);
            	else
            		fprintf(clean_file, "%c", ' ');
              ch = nextc;
              nextc = fgetc (input_file);
            }
          ch = fgetc (input_file);
          nextc = fgetc (input_file);
        }
      fprintf(clean_file, "%c", ch);
    }
    fprintf(clean_file, "\n");
  fclose (input_file2);
  fclose (clean_file2);
  return;
}