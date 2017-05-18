// /
// * @Authors:
// * DIVAKAR VERMA (2014A7PS093P)
// * AKANKSHA DARA (2014A7PS104P)
// *
// * @Group - 6
// * @File Name: lexerDef.c
// //*


#ifndef LEXERDEF_H_
#define LEXERDEF_H_

#define NUM_STATES 38
#define MAX_TRANSITIONS 25
#define MAX_LEXEME_LENGTH 30
#define END_MARKER_SYMBOL -2

//extern bool compiler_error;

enum TERM{
    $, anyTerm, arithmeticExpr, arithmeticOrBooleanExpr, assignmentStmt, booleanExpr, case_stmt, caseStmts ,//8
    conditionalStmt, dataType, declareStmt, defaultStmt, driverModule, expr_1, expr_2, expr_3, expr_4,//17
    expression, factor, idList_2, idList, Index, input_plist_2, input_plist, ioStmt, iterativeStmt, // 26
    logicalOp, lvalueARRStmt, lvalueIDStmt, module, moduleDeclaration, moduleDeclarations, moduleDef,//33
    moduleReuseStmt, op1, op2, optional, otherModules, output_plist_2, output_plist, program, range,//42
    relationalOp, ret, simpleStmt, statement, statements, term, type, value, var, whichId, whichStmt, t1, NULL_VAL,//55
   // index 0-50 non terminals
    TK_AND, TK_ARRAY, TK_ASSIGNOP, TK_BC, TK_BO, TK_BOOLEAN, TK_BREAK, TK_CASE,  TK_COLON, TK_COMMA, TK_COMMENT, TK_DECLARE,//63
    TK_DEF, TK_DEFAULT, TK_DELIM, TK_DELIMITER, TK_DIV, TK_DRIVER, TK_DRIVERDEF, TK_DRIVERENDDEF, TK_END,  TK_ENDDEF,  TK_EQ,//80
    TK_FALSE, TK_FOR, TK_GE, TK_GET_VALUE, TK_GT, TK_ID, TK_IN, TK_INPUT, TK_INTEGER,  TK_LE,  TK_LT, TK_MINUS, TK_MODULE, TK_MUL,//106
    TK_NE, TK_NUM,  TK_OF, TK_OR, TK_PARAMETERS, TK_PLUS, TK_PRINT, TK_PROGRAM, TK_RANGEOP, TK_REAL, TK_RETURNS,
    TK_RNUM, TK_START,  TK_SEMICOL, TK_SQBC, TK_SQBO, TK_SWITCH, TK_TAKES, TK_TRUE,  TK_USE, TK_WHILE,  TK_WITH
    //0-2 NON TERMINAL 3-5 TERMINAL
};
typedef enum TERM Token;

char* token_map[116] = {
    "$", "anyTerm", "arithmeticExpr", "arithmeticOrBooleanExpr", "assignmentStmt", "booleanExpr", "case_stmt", "caseStmts" ,
    "conditionalStmt", "dataType", "declareStmt", "defaultStmt", "driverModule", "expr_1", "expr_2", "expr_3", "expr_4",
    "expression", "factor", "idList_2", "idList", "Index", "input_plist_2", "input_plist", "ioStmt", "iterativeStmt",
    "logicalOp", "lvalueARRStmt", "lvalueIDStmt", "module", "moduleDeclaration", "moduleDeclarations", "moduleDef",
    "moduleReuseStmt", "op1", "op2", "optional", "otherModules", "output_plist_2", "output_plist", "program", "range",
    "relationalOp", "ret", "simpleStmt", "statement", "statements", "term", "type", "value", "var", "whichId", "whichStmt","t1", "NULL_VAL",
   // index 0-50 non terminals
    "TK_AND", "TK_ARRAY", "TK_ASSIGNOP", "TK_BC", "TK_BO", "TK_BOOLEAN", "TK_BREAK", "TK_CASE",  "TK_COLON", "TK_COMMA", "TK_COMMENT", 
    "TK_DECLARE", "TK_DEF", "TK_DEFAULT", "TK_DELIM", "TK_DELIMITER", "TK_DIV", "TK_DRIVER", "TK_DRIVERDEF", "TK_DRIVERENDDEF", "TK_END", 
    "TK_ENDDEF", "TK_EQ", "TK_FALSE", "TK_FOR", "TK_GE", "TK_GET_VALUE", "TK_GT", "TK_ID", "TK_IN", "TK_INPUT", "TK_INTEGER",  "TK_LE", 
    "TK_LT", "TK_MINUS","TK_MODULE", "TK_MUL", "TK_NE", "TK_NUM",  "TK_OF", "TK_OR", "TK_PARAMETERS", "TK_PLUS", "TK_PRINT", "TK_PROGRAM", 
    "TK_RANGEOP","TK_REAL", "TK_RETURNS","TK_RNUM", "TK_START",  "TK_SEMICOL", "TK_SQBC", "TK_SQBO", "TK_SWITCH", "TK_TAKES", "TK_TRUE",  
    "TK_USE", "TK_WHILE",  "TK_WITH"
    //0-2 NON TERMINAL 3-5 TERMINAL
};
enum var_type
{
    _NONE, _INTEGER, _REAL, _BOOLEAN , _MODULE
};

int num_parsing_errors = 0;


//structure for storing token information for every lexeme
struct TokenInfo{
    char lexeme[MAX_LEXEME_LENGTH];
    Token lexeme_token;
    int line_num;
    char token_name[30];
    enum var_type tk_type; 
};

typedef struct TokenInfo TokenInfo;

struct node{
	TokenInfo* data;
	struct node *next;
};
typedef struct node linked_list_node;

typedef struct
{
    char input_char;
    int dest_state;
} DFA_transition;
// a**comment
typedef struct {

    int is_final;
    int state_id;
    int num_transitions; //number of outgoing transitions from a state
    DFA_transition transitions[MAX_TRANSITIONS];

    char comment[30] ;

} DFA_state;

typedef struct
{
    int num_states;
    int current_state;
    int start_state;
    DFA_state* states[NUM_STATES];
} DFA;



#endif


