// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: lexer.h
// //*

#ifndef LEXER_H_
#define LEXER_H_


char* getStream();

int check_transition(DFA* dfa, int from_state, char input_symbol);

Token get_lexeme_token(char* input_lexeme);

TokenInfo* create_token(char* lexeme, char* comment, int line);

void getNextToken (DFA* dfa);

void remove_comments(char* file_name);


#endif