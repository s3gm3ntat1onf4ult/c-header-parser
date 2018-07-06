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
	
	printf("%d bytes read\n%d\n", len, header[len]);
	
	// here you can see the tokenizer in action
	int end = 0;
	w_token token = find_wtoken(header, end);
	while (memcmp(&token, &EMPTY, sizeof token) != 0)
	{
		end = token.end + 1;
		printf("Name: %s\nstart: %d\nend: %d\n", token.name, token.start, token.end);
		if (end != len - 1) // prevent infinite loop
			token = find_wtoken(header, end);
		else
			break;
	}
}

w_token find_wtoken(char *source, int start)
{
	int len = strlen(source);
	
	if (start < 0 || start >= len - 1)
		return;
	
	w_token tok = {0};
	char *word = malloc(20);
	memset(word, 0, sizeof word);

	int i;
	for (i = start; i < len; i++)
	{
		char ch = source[i];
		strncat(word, &ch, 1);
		
		if (ch == '/' && strlen(word) == 1)
			if (source[i + 1] == '/')  // comment found
			{
				i++;
				while (source[++i] != '\n');
				memset(word, 0, sizeof word);
			}
			else if (source[i + 1] == '*') // comment found
			{
				++i;
				
				while (source[++i] != 0)
					if (source[i] == '*' && source[i + 1] == '/')
						break;
						
				i += 2;
				memset(word, 0, sizeof word);
			}

		if (i == len - 1)
		{
			tok.end = i;
			tok.start = i - strlen(word) + 1;
			tok.name = str_slice(source, tok.start, tok.end + 1);

			return tok;
		}
		
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