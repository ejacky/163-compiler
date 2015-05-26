#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
enum kind { ID, IF, NUM, END };
struct token {
	enum kind k;
	char *lexeme;
	int row;
	int column;
};

struct token *nextToken(FILE *file) {
	struct token *token = (struct token*)(malloc(sizeof(*token)));

	char c = getc(file);
	switch (c) {
	case EOF:
		token->row = 0;
		token->column = 0;
		token->k = END;
		token->lexeme = "end";
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		token->lexeme += c;
		c = getc(file);
		token->row += 1;
		int flag = 1;
		while (c != ' ' && c != '\t' && flag) {
			if (c == '\n') {
				flag = 0;
				token->row = 0;
				token->column += 1;
				break;
			}
			if (!isdigit(c)) {
				flag = 0;
				token->lexeme += c;
				token->k = ID;
			}
			token->lexeme += c;
			flag = 1;
			c = getc(file);
			token->row += 1;
		}
		token->k = NUM;
		break;
	case 'i':
		c = getc(file);
		token->row += 1;
		token->lexeme += 'i';
		switch (c)  {
		case 'f':
			c = getc(file);
			token->row += 1;
			if (c == ' ' || c == '\n' || c == '\t') {
				token->k = IF;
				token->lexeme += 'f';
			}
			if (c == '\n') {
				token->row = 0;
				token->column += 1;
			}
		default:
			while (c != ' ' && c != '\t' && flag) {
				if (c == '\n') {
					flag = 0;
					token->row = 0;
					token->column += 1;
					break;
				}
				token->lexeme += c;
				c = getc(file);
				token->row += 1;
			}
		}
	default:
		token->k = ID;
		flag = 1;
		while (c != ' ' || c != '\n' || c != '\t' ) {
			token->lexeme += c;
			c = getc(file);
			token->row += 1;
		}
	};
	return (struct token *)token;
}

int main()
{
	char c;
	FILE *file;
	file = fopen("test.txt", "r");
	struct token *token = nextToken(file);
	while (token->k != EOF ) {
		switch (token->k) {
		case ID:
			printf("ID(%s)  (%d %d)", token->lexeme, token->row, token->column);
		case NUM:
			printf("NUM(%s) (%d %d)", token->lexeme, token->row, token->column);
		case IF:
			printf("IF      (%d %d)", token->row, token->column);
		}
		struct token *token = nextToken(file);
	}

	fclose(file);

	return 0;
}