#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum kind {ID, IF, NUM, END};
struct token {
    enum kind kind;
    char *lexname;
    int row;
    int column;
};

struct token *nextToken(FILE *fp)
{
    int c;
    struct token *token = (struct token*)(malloc(sizeof(*token))); // sizeof 里 可不可以是 struct token?

    
    c = fgetc(fp);

    printf("this char is %c\n", c);

    switch (c) {
        case EOF:
            printf("this is EOF\n");
            token->kind = END;
            token->lexname = "end";
            //break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            sprintf(token->lexname, "%d", c);
            //strcpy(token->lexname, (char)c);
            token->kind = NUM;
            //printf("test: %s", token->lexname);
            //exit(0);

            c = fgetc(fp);
            printf("another char is %c\n", c);

            while (c != ' ') {
                printf("test");
                if (!isdigit(c)) {  
                    token->kind = ID;
                    printf("this is %c\n", c);
                } 
                //token->lexname += c;
                sprintf(token->lexname, "%d", c);
                c = fgetc(fp);
            }
            printf("test: %s", token->lexname);
            //printf("aabbcc");
            break;
        case 'i':

            break;


        default:
            printf("this is default. char is %c\n", c);
            break;


    }

    //printf("lexname: %s\n", token->lexname);
    exit(0);

    return (struct token *)token;
}

int main(void)
{
    FILE *fp = fopen("test.txt", "r");

    struct token *token = nextToken(fp); 

    while (token->kind != END) {
        switch (token->kind) {
            case ID:
                printf("ID(%s)  (%d %d)", token->lexname, token->row, token->column);
                break;
            case IF:
                printf("IF      (%d %d)", token->row, token->column);
                break;
            case NUM:
                printf("NUM(%s) (%d %d)", token->lexname, token->row, token->column);
                break;
        }
        struct token *token = nextToken(fp); 

    }

    fclose(fp);

    return 0;
}   