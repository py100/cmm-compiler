#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED

const int KEYWORD_NUM = 18, BUFFER_SIZE = 4096;

typedef enum {
	T_BREAK = 0, T_CHAR, T_CONTINUE, T_DOUBLE,
	T_ELSE, T_FLOAT, T_FOR, T_IF, T_INT, T_LONG,
	T_RETURN, T_SHORT, T_SIGNED, T_TYPEDEF, T_UNSIGNED,
	T_VOID, T_WHILE, T_INCLUDE,

	T_IDENTIFER,

	INT_VAL, CHAR_VAL, FLOAT_VAL, STRING_VAL, 

	OP_MUL, OP_DIV, OP_MOD, OP_ADD, OP_SUB,
	OP_LT, OP_GT, OP_ASS, OP_SADD, OP_SSUB,
	OP_LE, OP_GE, OP_NE, OP_AND, OP_OR, OP_EQ, OP_NOT,
	OP_OTHERS,
	
	CONST_STR,

	LEFT_BRA, RIGHT_BRA,
	LEFT_INDEX, RIGHT_INDEX,
	L_BOUNDER, R_BOUNDER,

	SQ, DQ,

	F_CON, F_SEMIC, F_COMMA,

	F_EOF

}TokenType;


static const char* keywordList[] = {
	"break", "char", "continue", "double",
	"else", "float", "for", "if", "int", "long",
	"return", "short", "signed", "typedef", "unsigned",
	"void", "while", "include"
};


#endif
