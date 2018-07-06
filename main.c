#include <stdio.h>
#include "parser/parser.h"
#include <string.h>
#include <time.h>

int main()
{
	clock_t begin = clock();
	parse(fopen("/home/headerparser/test.txt", "r"));
	clock_t end = clock();
	
	double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	printf("\nProgram time execution: %.4f seconds\n", time_spent);

	return 0;
}