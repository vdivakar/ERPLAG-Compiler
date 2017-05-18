// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: dfa.c
// //*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"
#include <stdbool.h>
#include "lexerDef.h"
#define NUM_STATES 38

DFA* DFA_initialize()
{
	DFA* dfa = (DFA*)malloc(sizeof(DFA));
	dfa->current_state = -1;
	dfa->start_state = -1 ;
	dfa->num_states = 0;
	// printf("dfa initialized!\n");
	return dfa;
}

void DFA_add_transition(DFA_state* from_state, char input_char, DFA_state* to_state)
{
    int n = from_state->num_transitions;
    from_state->transitions[n].input_char = input_char;
    from_state->transitions[n].dest_state = to_state->state_id;
    from_state->num_transitions ++;
}

void DFA_modify_state(DFA* dfa, int id, char* default_tk, int is_final)
{
    strcpy(dfa->states[id]->comment, default_tk);
    dfa->states[id]->is_final = is_final;
    return;
}

void DFA_construction(DFA* dfa)
{
	int i;
	for(i=0; i<NUM_STATES; i++)
	{
		dfa->states[i] = (DFA_state*) malloc(sizeof(DFA_state));
		dfa->states[i]-> is_final = 0;
		dfa->states[i]->state_id = i;
		dfa->states[i]->num_transitions = 0;
		strcpy(dfa->states[i]->comment, "aa");
		dfa->num_states ++;
	}
	DFA_add_transition(dfa->states[0], '(', dfa->states[1]);
	DFA_add_transition(dfa->states[0], ')', dfa->states[2]);
	DFA_add_transition(dfa->states[0], '[', dfa->states[3]);
	DFA_add_transition(dfa->states[0], ']', dfa->states[4]);
	DFA_add_transition(dfa->states[0], ' ', dfa->states[5]); 
	DFA_add_transition(dfa->states[0], '\t', dfa->states[5]); 
	DFA_add_transition(dfa->states[0], '\n', dfa->states[5]);
	DFA_add_transition(dfa->states[5], ' ', dfa->states[5]);   // sort out for delimeter
	DFA_add_transition(dfa->states[5], '\t', dfa->states[5]);
	DFA_add_transition(dfa->states[5], '\n', dfa->states[5]);
	DFA_add_transition(dfa->states[0], ':', dfa->states[6]);
	DFA_add_transition(dfa->states[6], '=', dfa->states[7]);
	DFA_add_transition(dfa->states[0], '0', dfa->states[8]);	// # -> [0-9]	
	DFA_add_transition(dfa->states[8], '0', dfa->states[8]);	// # -> [0-9]	
	DFA_add_transition(dfa->states[8], '.', dfa->states[9]);
	DFA_add_transition(dfa->states[9], '0', dfa->states[10]);	// # -> [0-9]
	DFA_add_transition(dfa->states[10], '0', dfa->states[10]);	// # -> [0-9]
	DFA_add_transition(dfa->states[9], '.', dfa->states[21]);
	DFA_add_transition(dfa->states[10], 'E', dfa->states[11]);
	DFA_add_transition(dfa->states[10], 'e', dfa->states[11]);
	DFA_add_transition(dfa->states[11], '+', dfa->states[12]);
	DFA_add_transition(dfa->states[11], '-', dfa->states[12]);
	DFA_add_transition(dfa->states[11], '0', dfa->states[13]);	// # -> [0-9]
	DFA_add_transition(dfa->states[12], '0', dfa->states[13]);	// # -> [0-9]
	DFA_add_transition(dfa->states[13], '0', dfa->states[13]);	// # -> [0-9]
	DFA_add_transition(dfa->states[0], '-', dfa->states[20]);
	// DFA_add_transition(dfa->states[20], '0', dfa->states[8]);	// # -> [0-9]
	DFA_add_transition(dfa->states[0],  '*', dfa->states[14]);
	DFA_add_transition(dfa->states[14], '*', dfa->states[15]);	//IGNORE-->>	// sort for comment
	DFA_add_transition(dfa->states[15], '*', dfa->states[16]);
	DFA_add_transition(dfa->states[16], '*', dfa->states[17]);
	DFA_add_transition(dfa->states[0],  '/', dfa->states[18]);
	DFA_add_transition(dfa->states[0],  '+', dfa->states[19]);
	DFA_add_transition(dfa->states[21], '0', dfa->states[22]);
	DFA_add_transition(dfa->states[22], '0', dfa->states[22]);
	DFA_add_transition(dfa->states[0],  '<', dfa->states[23]);
	DFA_add_transition(dfa->states[23], '=', dfa->states[24]);
	DFA_add_transition(dfa->states[23], '<', dfa->states[25]);
	DFA_add_transition(dfa->states[0],  '=', dfa->states[26]);
	DFA_add_transition(dfa->states[26], '=', dfa->states[27]);
	DFA_add_transition(dfa->states[0],  '>', dfa->states[28]);
	DFA_add_transition(dfa->states[28], '=', dfa->states[29]);
	DFA_add_transition(dfa->states[28], '>', dfa->states[30]);
	DFA_add_transition(dfa->states[0],  '!', dfa->states[31]);
	DFA_add_transition(dfa->states[31], '=', dfa->states[32]);
	DFA_add_transition(dfa->states[0],  ';', dfa->states[33]);
	DFA_add_transition(dfa->states[0],  'a', dfa->states[34]);	// sort for alphabets!!!
	DFA_add_transition(dfa->states[34], 'a', dfa->states[34]);	// alphabet to alphaber
	DFA_add_transition(dfa->states[34], '0', dfa->states[34]);	// num to num
	DFA_add_transition(dfa->states[34], '_', dfa->states[34]);
	DFA_add_transition(dfa->states[0],  ',', dfa->states[35]);
	DFA_add_transition(dfa->states[25], '<', dfa->states[36]);
	DFA_add_transition(dfa->states[30],  '>', dfa->states[37]);

	dfa->start_state = dfa->states[0]->state_id;
	dfa->current_state = dfa->start_state;

	DFA_modify_state(dfa, 0, "REPORT_ERROR", 0);
	DFA_modify_state(dfa, 1, "TK_BO", 1);
	DFA_modify_state(dfa, 2, "TK_BC", 1);
	DFA_modify_state(dfa, 3, "TK_SQBO", 1);
	DFA_modify_state(dfa, 4, "TK_SQBC", 1);
	DFA_modify_state(dfa, 5, "TK_DELIM", 1);
    DFA_modify_state(dfa, 6, "TK_COLON", 1);
	DFA_modify_state(dfa, 7, "TK_ASSIGNOP", 1);
	DFA_modify_state(dfa, 8, "TK_NUM", 1);
	DFA_modify_state(dfa, 9, "REPORT_ERROR:NOT-INTEGER/REAL", 0);
	DFA_modify_state(dfa, 10, "TK_RNUM", 1);
    DFA_modify_state(dfa, 11, "REPORT_ERROR:INTEGER/REAL", 0);
	DFA_modify_state(dfa, 12, "REPORT_ERROR:INTEGER/REAL", 0);
	DFA_modify_state(dfa, 13, "TK_RNUM", 1);
	DFA_modify_state(dfa, 14, "TK_MUL", 1);
	DFA_modify_state(dfa, 17, "TK_COMMENT", 1);
	DFA_modify_state(dfa, 18, "TK_DIV", 1);
	DFA_modify_state(dfa, 19, "TK_PLUS", 1);
    DFA_modify_state(dfa, 20, "TK_MINUS", 1);
	DFA_modify_state(dfa, 21,  "REPORT_ERROR:Check RANGEOP", 0);
	DFA_modify_state(dfa, 22, "TK_RANGEOP", 1);
	DFA_modify_state(dfa, 23, "TK_LT", 1);
    DFA_modify_state(dfa, 24, "TK_LE", 1);
	DFA_modify_state(dfa, 25, "TK_DEF", 1);
	DFA_modify_state(dfa, 26, "REPORT_ERROR:EQ operator", 0);
	DFA_modify_state(dfa, 27, "TK_EQ", 1);
    DFA_modify_state(dfa, 28, "TK_GT", 1);
	DFA_modify_state(dfa, 29, "TK_GE", 1);
	DFA_modify_state(dfa, 30, "TK_ENDDEF", 1);
	DFA_modify_state(dfa, 31, "REPORT_ERROR:NE operator", 0);
    DFA_modify_state(dfa, 32, "TK_NE", 1);
	DFA_modify_state(dfa, 33, "TK_SEMICOL", 1);
	DFA_modify_state(dfa, 34, "TK_ID, check for keyword", 1);	// CHECK FOR KEYWORD IN SYMBOL TABLE
	DFA_modify_state(dfa, 35, "TK_COMMA", 1);
	DFA_modify_state(dfa, 36, "TK_DRIVERDEF", 1);
	DFA_modify_state(dfa, 37, "TK_DRIVERENDDEF", 1);

}

void DFA_reset (DFA* dfa)
{
    dfa->current_state = dfa->start_state;
    return;
}
