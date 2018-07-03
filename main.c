#include <stdio.h>
#include "parser/parser.h"
#include <string.h>

int main()
{
	parse(fopen("/home/headerparser/test.txt", "r"));

	return 0;
}