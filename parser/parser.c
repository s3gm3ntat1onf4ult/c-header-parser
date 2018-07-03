#include "parser.h"
#include "str.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

void parse(FILE *h)
{
	char *word = malloc(20);
	int pos = 0;
	char ch;

	int len;
	char *header;

	fseek(h, 0, SEEK_END);
	len = ftell(h) + 1;
	fseek(h, 0, SEEK_SET);

	header = malloc(len + 1);

	fread(header, len, 1, h);
	fclose(h);
	
	// here you can see the tokenizer in action
	w_token tok = find_wtoken(header, 0);
	w_token other = find_wtoken(header, tok.end + 1);
	w_token other2 = find_wtoken(header, other.end + 1);

	printf("Name: %s\nstart: %d\nend: %d\n\n", tok.name, tok.start, tok.end);
	printf("Name: %s\nstart: %d\nend: %d\n\n", other.name, other.start, other.end);
	printf("Name: %s\nstart: %d\nend: %d\n\n", other2.name, other2.start, other2.end);
}

w_token find_wtoken(char *source, int start)
{
	int len = strlen(source);
	
	if (start < 0 || start > len)
		return;
	
	w_token tok;
	char *word = malloc(20);
	memset(word, 0, sizeof word);

	int i;
	for (i = start; i < len; i++)
	{
		char ch = source[i];
		strncat(word, &ch, 1);

		int b = 0;
		while ((b++) < sizeof W_DEL)
		{
			if (ch == W_DEL[b - 1])
			{
				if (strlen(word) - 1 <= 1) // here we skip all the W_DEL chars
				{
					memset(word, 0, sizeof word);
					break;
				}
				// w_token found
				tok.end = i - 1;
				tok.start = i - strlen(word) + 1;
				tok.name = str_slice(source, tok.start, tok.end + 1);

				return tok;
			}
		}
	}
	
	return tok;
}