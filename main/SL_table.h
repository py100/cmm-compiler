#ifndef SL_TABLE_H_INCLUDE
#define SL_TABLE_H_INCLUDE

#define NUM_LABLE 4
#define _ERROR(_str) printf("ERROR : %s\n", _str)

static const char *label_list[] {
	"nonterminal",
	"terminal",
	"start",
	"production"
};

#endif
