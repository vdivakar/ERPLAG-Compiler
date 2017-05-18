// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: grammar.c
// //*

#include <stdlib.h>
#include <stdio.h>
#include "lexerDef.h"
#include "parser.h"

#define MAX_RULES 20
#define NUM_OF_PRODUCTIONS 96

typedef enum TERM TERM;
TERM first_set[20];
TERM follow_set[20] ;

void add_rule(rule* r1, TERM from, TERM to[], int n)
{
    r1->from = from;
    r1->to = (TERM*)malloc((n-1)*sizeof(TERM));
    r1->count = n-1;
    int i=0;
    for(i=0;i<n-1;i++)
    	r1->to[i] = to[i];   	
}

rule** generate_grammar()
{
    rule** Grammar = (rule**)malloc(NUM_OF_PRODUCTIONS*sizeof(rule*));
    int i;
    for (i=0; i<NUM_OF_PRODUCTIONS; i++)
    {
        Grammar[i] = (rule*)malloc(sizeof(rule));
    }

	TERM array_0 [5] = {program, moduleDeclarations, otherModules, driverModule, otherModules};
	add_rule(Grammar[0],array_0[0], &array_0[1], 5);

	TERM array_1 [3] = {moduleDeclarations, moduleDeclaration, moduleDeclarations};
	add_rule(Grammar[1],array_1[0], &array_1[1], 3);

	TERM array_2 [2] = {moduleDeclarations, $};
	add_rule(Grammar[2],array_2[0], &array_2[1], 2);

	TERM array_3 [5] = {moduleDeclaration, TK_DECLARE, TK_MODULE, TK_ID, TK_SEMICOL};
	add_rule(Grammar[3],array_3[0], &array_3[1], 5);

	TERM array_4 [3] = {otherModules, module, otherModules};
	add_rule(Grammar[4],array_4[0], &array_4[1], 3);

	TERM array_5 [2] = {otherModules, $};
	add_rule(Grammar[5],array_5[0], &array_5[1], 2);

	TERM array_6 [6] = {driverModule, TK_DRIVERDEF, TK_DRIVER, TK_PROGRAM, TK_DRIVERENDDEF, moduleDef};
	add_rule(Grammar[6],array_6[0], &array_6[1], 6);

	TERM array_7 [13] = {module, TK_DEF, TK_MODULE, TK_ID, TK_ENDDEF, TK_TAKES, TK_INPUT, TK_SQBO, input_plist, TK_SQBC, TK_SEMICOL, ret, moduleDef};
	add_rule(Grammar[7],array_7[0], &array_7[1], 13);

	TERM array_8 [6] = {ret, TK_RETURNS, TK_SQBO, output_plist, TK_SQBC, TK_SEMICOL};
	add_rule(Grammar[8],array_8[0], &array_8[1], 6);

	TERM array_9 [2] = {ret, $};
	add_rule(Grammar[9],array_9[0], &array_9[1], 2);

	TERM array_10 [5] = {input_plist, TK_ID, TK_COLON, dataType, input_plist_2};
	add_rule(Grammar[10],array_10[0], &array_10[1], 5);

	TERM array_11 [6] = {input_plist_2, TK_COMMA, TK_ID, TK_COLON, dataType, input_plist_2};
	add_rule(Grammar[11],array_11[0], &array_11[1], 6);

	TERM array_12 [2] = {input_plist_2, $};
	add_rule(Grammar[12],array_12[0], &array_12[1], 2);

	TERM array_13 [6] = {output_plist_2, TK_COMMA, TK_ID, TK_COLON, type, output_plist_2};
	add_rule(Grammar[13],array_13[0], &array_13[1], 6);

	TERM array_14 [2] = {output_plist_2, $};
	add_rule(Grammar[14],array_14[0], &array_14[1], 2);

	TERM array_15 [2] = {dataType, TK_INTEGER};
	add_rule(Grammar[15],array_15[0], &array_15[1], 2);

	TERM array_16 [2] = {dataType, TK_REAL};
	add_rule(Grammar[16],array_16[0], &array_16[1], 2);

	TERM array_17 [2] = {dataType, TK_BOOLEAN};
	add_rule(Grammar[17],array_17[0], &array_17[1], 2);

	TERM array_18 [7] = {dataType, TK_ARRAY, TK_SQBO, TK_RANGEOP, TK_SQBC, TK_OF, type};
	add_rule(Grammar[18],array_18[0], &array_18[1], 7);

	TERM array_19 [2] = {type, TK_INTEGER};
	add_rule(Grammar[19],array_19[0], &array_19[1], 2);

	TERM array_20 [2] = {type, TK_REAL};
	add_rule(Grammar[20],array_20[0], &array_20[1], 2);

	TERM array_21 [2] = {type, TK_BOOLEAN};
	add_rule(Grammar[21],array_21[0], &array_21[1], 2);

	TERM array_22 [4] = {moduleDef, TK_START, statements, TK_END};
	add_rule(Grammar[22],array_22[0], &array_22[1], 4);

	TERM array_23 [3] = {statements, statement, statements};
	add_rule(Grammar[23],array_23[0], &array_23[1], 3);

	TERM array_24 [2] = {statements, $};
	add_rule(Grammar[24],array_24[0], &array_24[1], 2);

	TERM array_25 [2] = {statement, ioStmt};
	add_rule(Grammar[25],array_25[0], &array_25[1], 2);

	TERM array_26 [2] = {statement, simpleStmt};
	add_rule(Grammar[26],array_26[0], &array_26[1], 2);

	TERM array_27 [2] = {statement, declareStmt};
	add_rule(Grammar[27],array_27[0], &array_27[1], 2);

	TERM array_28 [2] = {statement, conditionalStmt};
	add_rule(Grammar[28],array_28[0], &array_28[1], 2);

	TERM array_29 [2] = {statement, iterativeStmt};
	add_rule(Grammar[29],array_29[0], &array_29[1], 2);

	TERM array_30 [6] = {ioStmt, TK_GET_VALUE, TK_BO, TK_ID, TK_BC, TK_SEMICOL};
	add_rule(Grammar[30],array_30[0], &array_30[1], 6);

	TERM array_31 [6] = {ioStmt, TK_PRINT, TK_BO, var, TK_BC, TK_SEMICOL};
	add_rule(Grammar[31],array_31[0], &array_31[1], 6);

	TERM array_32 [3] = {var, TK_ID, whichId};
	add_rule(Grammar[32],array_32[0], &array_32[1], 3);

	TERM array_33 [2] = {var, TK_NUM};
	add_rule(Grammar[33],array_33[0], &array_33[1], 2);

	TERM array_34 [2] = {var, TK_RNUM};
	add_rule(Grammar[34],array_34[0], &array_34[1], 2);

	TERM array_35 [4] = {whichId, TK_SQBO, TK_ID, TK_SQBC};
	add_rule(Grammar[35],array_35[0], &array_35[1], 4);

	TERM array_36 [2] = {whichId, $};
	add_rule(Grammar[36],array_36[0], &array_36[1], 2);

	TERM array_37 [2] = {simpleStmt, assignmentStmt};
	add_rule(Grammar[37],array_37[0], &array_37[1], 2);

	TERM array_38 [2] = {simpleStmt, moduleReuseStmt};
	add_rule(Grammar[38],array_38[0], &array_38[1], 2);

	TERM array_39 [3] = {assignmentStmt, TK_ID, whichStmt};
	add_rule(Grammar[39],array_39[0], &array_39[1], 3);

	TERM array_40 [2] = {whichStmt, lvalueIDStmt};
	add_rule(Grammar[40],array_40[0], &array_40[1], 2);

	TERM array_41 [2] = {whichStmt, lvalueARRStmt};
	add_rule(Grammar[41],array_41[0], &array_41[1], 2);

	TERM array_42 [4] = {lvalueIDStmt, TK_ASSIGNOP, expression, TK_SEMICOL};
	add_rule(Grammar[42],array_42[0], &array_42[1], 4);

	TERM array_43 [7] = {lvalueARRStmt, TK_SQBO, Index, TK_SQBC, TK_ASSIGNOP, expression, TK_SEMICOL};
	add_rule(Grammar[43],array_43[0], &array_43[1], 7);

	TERM array_44 [2] = {Index, TK_NUM};
	add_rule(Grammar[44],array_44[0], &array_44[1], 2);

	TERM array_45 [2] = {Index, TK_ID};
	add_rule(Grammar[45],array_45[0], &array_45[1], 2);

	TERM array_46 [9] = {moduleReuseStmt, optional, TK_USE, TK_MODULE, TK_ID, TK_WITH, TK_PARAMETERS, idList, TK_SEMICOL};
	add_rule(Grammar[46],array_46[0], &array_46[1], 9);

	TERM array_47 [5] = {optional, TK_SQBO, idList, TK_SQBC, TK_ASSIGNOP };
	add_rule(Grammar[47],array_47[0], &array_47[1], 5);

	TERM array_48 [2] = {optional, $};
	add_rule(Grammar[48],array_48[0], &array_48[1], 2);

	TERM array_49 [3] = {idList, TK_ID, idList_2};
	add_rule(Grammar[49],array_49[0], &array_49[1], 3);

	TERM array_50 [4] = {idList_2, TK_COMMA, TK_ID, idList_2};
	add_rule(Grammar[50],array_50[0], &array_50[1], 4);

	TERM array_51 [2] = {idList_2, $};
	add_rule(Grammar[51],array_51[0], &array_51[1], 2);

	TERM array_52 [3] = {arithmeticOrBooleanExpr, anyTerm, expr_1};
	add_rule(Grammar[52],array_52[0], &array_52[1], 3);

	TERM array_53 [4] = {expr_1, logicalOp, anyTerm, expr_1};
	add_rule(Grammar[53],array_53[0], &array_53[1], 4);

	TERM array_54 [2] = {expr_1, $};
	add_rule(Grammar[54],array_54[0], &array_54[1], 2);

	TERM array_55 [3] = {anyTerm, arithmeticExpr, expr_2};
	add_rule(Grammar[55],array_55[0], &array_55[1], 3);

	TERM array_56 [4] = {expr_2, relationalOp, arithmeticExpr, expr_2};
	add_rule(Grammar[56],array_56[0], &array_56[1], 4);

	TERM array_57 [2] = {expr_2, $};
	add_rule(Grammar[57],array_57[0], &array_57[1], 2);

	TERM array_58 [3] = {arithmeticExpr, term, expr_3};
	add_rule(Grammar[58],array_58[0], &array_58[1], 3);

	TERM array_59 [4] = {expr_3, op1, term, expr_3};
	add_rule(Grammar[59],array_59[0], &array_59[1], 4);

	TERM array_60 [2] = {expr_3, $};
	add_rule(Grammar[60],array_60[0], &array_60[1], 2);

	TERM array_61 [3] = {term, factor, expr_4};
	add_rule(Grammar[61],array_61[0], &array_61[1], 3);

	TERM array_62 [4] = {expr_4, op2, factor, expr_4};
	add_rule(Grammar[62],array_62[0], &array_62[1], 4);

	TERM array_63 [2] = {expr_4, $};
	add_rule(Grammar[63],array_63[0], &array_63[1], 2);

	TERM array_64 [2] = {op1, TK_PLUS};
	add_rule(Grammar[64],array_64[0], &array_64[1], 2);

	TERM array_65 [2] = {op1, TK_MINUS};
	add_rule(Grammar[65],array_65[0], &array_65[1], 2);

	TERM array_66 [2] = {op2, TK_MUL};
	add_rule(Grammar[66],array_66[0], &array_66[1], 2);

	TERM array_67 [2] = {op2, TK_DIV};
	add_rule(Grammar[67],array_67[0], &array_67[1], 2);

	TERM array_68 [2] = {logicalOp, TK_AND};
	add_rule(Grammar[68],array_68[0], &array_68[1], 2);

	TERM array_69 [2] = {logicalOp, TK_OR};
	add_rule(Grammar[69],array_69[0], &array_69[1], 2);

	TERM array_70 [2] = {relationalOp, TK_LE};
	add_rule(Grammar[70],array_70[0], &array_70[1], 2);

	TERM array_71 [2] = {relationalOp, TK_LT};
	add_rule(Grammar[71],array_71[0], &array_71[1], 2);

	TERM array_72 [2] = {relationalOp, TK_GE};
	add_rule(Grammar[72],array_72[0], &array_72[1], 2);

	TERM array_73 [2] = {relationalOp, TK_GT};
	add_rule(Grammar[73],array_73[0], &array_73[1], 2);

	TERM array_74 [2] = {relationalOp, TK_NE};
	add_rule(Grammar[74],array_74[0], &array_74[1], 2);

	TERM array_75 [2] = {relationalOp, TK_EQ};
	add_rule(Grammar[75],array_75[0], &array_75[1], 2);

	TERM array_76 [6] = {declareStmt, TK_DECLARE, idList, TK_COLON, dataType, TK_SEMICOL};
	add_rule(Grammar[76],array_76[0], &array_76[1], 6);

	TERM array_77 [9] = {conditionalStmt, TK_SWITCH, TK_BO, TK_ID, TK_BC, TK_START, caseStmts, defaultStmt, TK_END};
	add_rule(Grammar[77],array_77[0], &array_77[1], 9);

	TERM array_78 [8] = {caseStmts, TK_CASE, value, TK_COLON, statements, TK_BREAK, TK_SEMICOL, case_stmt};
	add_rule(Grammar[78],array_78[0], &array_78[1], 8);

	TERM array_79 [8] = {case_stmt, TK_CASE, value, TK_COLON, statements, TK_BREAK, TK_SEMICOL, case_stmt};
	add_rule(Grammar[79],array_79[0], &array_79[1], 8);

	TERM array_80 [2] = {case_stmt, $};
	add_rule(Grammar[80],array_80[0], &array_80[1], 2);

	TERM array_81 [2] = {value, TK_NUM};
	add_rule(Grammar[81],array_81[0], &array_81[1], 2);

	TERM array_82 [2] = {value, TK_TRUE};
	add_rule(Grammar[82],array_82[0], &array_82[1], 2);

	TERM array_83 [2] = {value, TK_FALSE};
	add_rule(Grammar[83],array_83[0], &array_83[1], 2);

	TERM array_84 [6] = {defaultStmt, TK_DEFAULT, TK_COLON, statements, TK_BREAK, TK_SEMICOL};
	add_rule(Grammar[84],array_84[0], &array_84[1], 6);

	TERM array_85 [2] = {defaultStmt, $};
	add_rule(Grammar[85],array_85[0], &array_85[1], 2);

	TERM array_86 [10] = {iterativeStmt, TK_FOR, TK_BO, TK_ID, TK_IN, TK_RANGEOP, TK_BC, TK_START, statements, TK_END};
	add_rule(Grammar[86],array_86[0], &array_86[1], 10);

	TERM array_87 [8] = {iterativeStmt, TK_WHILE, TK_BO, expression, TK_BC, TK_START, statements, TK_END};
	add_rule(Grammar[87],array_87[0], &array_87[1], 8);

	TERM array_88 [5] = {expression, TK_PLUS, TK_BO, arithmeticExpr,TK_BC};
	add_rule(Grammar[88],array_88[0], &array_88[1], 5);


	TERM array_89 [4] = {factor, TK_BO, arithmeticOrBooleanExpr,TK_BC};
	add_rule(Grammar[89],array_89[0], &array_89[1], 4);


	TERM array_90 [2] = {factor, var};
	add_rule(Grammar[90],array_90[0], &array_90[1], 2);

	TERM array_91 [5] = {output_plist, TK_ID, TK_COLON, type, output_plist_2};
	add_rule(Grammar[91],array_91[0], &array_91[1], 5);

	TERM array_92 [2] = {expression, arithmeticOrBooleanExpr};
	add_rule(Grammar[92],array_92[0], &array_92[1], 2);


	TERM array_93 [3] = {var, TK_MINUS, t1};
	add_rule(Grammar[93],array_93[0], &array_93[1], 3);

	TERM array_94 [2] = {t1, TK_NUM};
	add_rule(Grammar[94],array_94[0], &array_94[1], 2);

	TERM array_95 [2] = {t1, TK_NUM};
	add_rule(Grammar[95],array_95[0], &array_95[1], 2);

	// TERM array_95 [5] = {expression, TK_MINUS, TK_BO, arithmeticExpr,TK_BC};
	// add_rule(Grammar[95],array_95[0], &array_95[1], 5);
	
	return Grammar;
}

void addToResultSet(TERM* result_set, TERM val)
{
    int k=0;
    while(result_set[k]!= NULL_VAL)
     {
         if(result_set[k]==val)
                return;
         k++;
     }
    result_set[k]=val;
    result_set[k+1]=NULL_VAL;
    return;
}


void first (TERM* result, rule** grammar, TERM symbol)
{

    TERM temp_result[20];
    int is_epsilon;
    int t = 0;
	temp_result[0] = NULL_VAL;
	result[0] = NULL_VAL;

    if(symbol > START_OF_TERMINALS) //it is a terminal
    {
        addToResultSet(result, symbol);
    }
    else
    {
        int i = 0;
        while(i<NUM_OF_PRODUCTIONS)
        {
            if ( grammar[i]->from == symbol )
            {
	            if(grammar[i]->to[0] == $)
	            {
	                 addToResultSet(result, $);
	            }
	            else
	            { 
	                int j = 0;  int k = 0; int y=0;
	                while(j < grammar[i]->count)
	                {
	                    is_epsilon=0;
	                    first(temp_result, grammar, grammar[i]->to[j]);
	                    while(temp_result[k]!= NULL_VAL)
	                    {
	                        if(temp_result[k]==$)
	                        {
	                                is_epsilon=1;
	                                break;
	                        }
	                        k++;
	                    }
	                    if(!is_epsilon)
	                    {
	                    	for(k=0; temp_result[k]!= NULL_VAL; k++)	                    
	                        	{
	                        		addToResultSet(result,temp_result[k]);
	                        	}
	                    	break;
	                    }
	                    else
	                    {
	                    	for(k=0; (temp_result[k]!=$) && (temp_result[k]!= NULL_VAL); k++)	                    
	                        	addToResultSet(result,temp_result[k]);
	                    	j++;
	                    	if(j==grammar[i]->count)
	                    		addToResultSet(result,$);
	                    	temp_result[0] = NULL_VAL;
	                    }
	                }	                
	            }
            }
         	i++;
        }
    }
    return;
}

int follow_counter = 0;
void follow(TERM* result, rule** grammar, TERM symbol, TERM* follow_set)
{
	if(grammar[0]->from == symbol)		// if it is the start symbol
	{
		follow_set[follow_counter] = END_MARKER_SYMBOL;
		follow_counter++;
	}
	else
	{
		int i,j;
		int c;
		for (i = 0; i < NUM_OF_PRODUCTIONS; ++i) 
		{
			for(j=0; j<grammar[i]->count;j++)
			{
				if(grammar[i]->to[j] == symbol)
				{
					if(j+1<=grammar[i]->count-1)	// condition 2 of "follow rules"
						{
							int next = j+1;
							first(result,grammar, grammar[i]->to[next]);	// add condotion for first==$
							for(c=0;c<20;c++)
							{
								if((result[c]!=$) && (result[c]!= NULL_VAL))
									{
										int flag =1 , m;
										for(m=0;m<follow_counter;m++)		// to check if already contains that symbol
										{
											if(follow_set[m]==result[c])
												flag = 0;
										}
										if(flag)
										{
											follow_set[follow_counter] = result[c];
									 		follow_counter++;
									 	}
									}
								else if(result[c]==$ && (next+1<=grammar[i]->count-1))
									{
										first(result,grammar,grammar[i]->to[next+1]);
										next = next + 1 ;
										c=-1;
									}
								else if( (result[c]==$) && (next+1 == grammar[i]->count) && (symbol !=grammar[i]->from) )
									{
										follow(result,grammar,grammar[i]->from,follow_set);	
									}	
								else if (result[c] == NULL_VAL)
									break;
							}
						}
					else if((j>=grammar[i]->count-1) && (symbol!=grammar[i]->from)) // condition 3 of "follow rules"
						{
							follow(result,grammar,grammar[i]->from,follow_set);	
						}
				}
			}
		}
	}
}






