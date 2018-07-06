#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

typedef struct
{
	int start, end;
	char *name;

}w_token; // word token

static const w_token EMPTY = {0};
static const char W_DEL[] = {' ', '\t', '\n'}; // word delimeters

void parse(FILE*);
w_token find_wtoken(char*, int);

#endif