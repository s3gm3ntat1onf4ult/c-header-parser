#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

typedef struct
{
	int start, end;
	char *name;

}w_token; // word token

static const char W_DEL[] = {' ', '\t'}; // word delimeters

void parse(FILE*);
w_token find_wtoken(char*, int);

#endif