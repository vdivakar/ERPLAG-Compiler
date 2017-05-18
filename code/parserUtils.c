// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: parserUtils.c
// //*

#include "parser.h"
#include "grammar.c"


int is_terminal(int t)
{
    if(t>53)
        return 1;
    else
        return 0;
}

int** createParseTable()
{
    int** table = (int**)malloc(NUM_ROWS * sizeof(int*));
    int i, j;
    for(i=0; i<NUM_ROWS; i++)
    {
        table[i] = (int*)malloc(NUM_COLUMNS *sizeof(int));
    }
    for(i = 0; i<NUM_ROWS; i++)
    {
        for(j=0; j<NUM_COLUMNS ; j++)
        {
           table[i][j] = -1;                                   //by default -1 in parse table to report error
        }
    }
   return table;
}

void print_a_table(int** table)
{
    int i, j;
    for(i =0; i<NUM_ROWS; i++)
    {
        printf("%s:-> ",token_map[i]);
        for(j=0; j<NUM_COLUMNS; j++)
        {
           
            if(table[i][j] != -1)
                printf("(%s, %d) ",token_map[j+53], table[i][j]);
        }
       printf("\n");
    }
}

void populateParseTable(rule** grammar, int** table, int first_table[NUM_TERMS][MAX_RHS], int** follow_table)
{
    int i,k,j;
    for(i = 0; i<NUM_OF_PRODUCTIONS ; i++)
    {
        TERM alpha = grammar[i]->to[0];      
        int A = grammar[i]->from;

        if (alpha == $)
        {
            for(j=0; j<MAX_RHS && follow_table[A][j]!=NULL_VAL; j++)
                {
                    int b = follow_table[A][j];
                    if( b == $) //check
                    {
                        table[A][$] = i;
                    }
                    else if(b == NULL_VAL)
                    {
                        printf("encountered NULL_VAL\n");
                    }
                    else
                        table[A][b-START_OF_TERMINALS] = i;
                }
        }

        for(k=0; k<MAX_RHS && first_table[alpha][k]!=54; k++)
        {
            int a = first_table[alpha][k];
            if(is_terminal(a) == 1)
            {
                table[A][a - START_OF_TERMINALS] = i;        //rule number is index of Grammar  //NULL_TERM in enum structure(NULL_VAL)
            }
            if(a == $)
            {

                for(j=0; j<MAX_RHS && follow_table[alpha][j]!=54; j++)
                {
                    int b = follow_table[alpha][j];
                    if( b == $) //check
                    {
                        table[A][$] = i;
                    }
                    else if(b == NULL_VAL)
                    {
                        // printf("encountered NULL_VAL\n");
                    }
                    else
                        table[A][b-START_OF_TERMINALS] = i;
                }
            }
        }
    }

}
void reset_array(TERM* array)
{
    int k;
    for(k=0;k<20;k++)
	{
		array[k] = NULL_VAL;
	}
}

void generate_first_table(int first_table[NUM_TERMS][MAX_RHS], rule** grammar)
{
    reset_array((TERM*)first_table[0]);
    first_table[0][0] = 0;
    int y=1;
	while( y<NUM_TERMS)
	{
	    reset_array((TERM*)first_set);
	    reset_array((TERM*)first_table[y]);
	    int i=0;

        first(first_set, grammar, y);
        while(first_set[i]!= NULL_VAL)
        {
            first_table[y][i] = first_set[i];
            i++;
        }
        y++;
	}
	return;
}

int** generate_follow_table(rule** grammar)  //int (*follow_table)[MAX_RHS] ,
{
    int** follow_table = (int**)malloc(NUM_NON_TERMINALS* sizeof(int*));
    int i, j;
    for(i=0; i<NUM_NON_TERMINALS; i++)
    {
        follow_table[i] = (int*)malloc(MAX_RHS *sizeof(int));
    }
    reset_array((TERM*)follow_table[0]);
    int y=1;
    while( y<NUM_NON_TERMINALS)
    {
        reset_array((TERM*)follow_set);
        reset_array((TERM*)first_set);
        reset_array((TERM*)follow_table[y]);
        follow_counter = 0;
        int i=0;
        follow(first_set, grammar, y, follow_set);
        while(i<20 && follow_set[i]!= NULL_VAL)
        {
            follow_table[y][i] = follow_set[i];
            i++;
        }
        y++;
    }
	return follow_table;
}
