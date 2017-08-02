%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex();
    void yyerror(char *s);

%}
%left '+'

%%  
lines: line
    | line lines;
line: exp '\n'     {printf("value=%d\n", $1);}
;    

exp: n             {$$=$1;}
   | exp '+' exp   {$$=$1+$3;}
;

n: '1' {$$=1;} 
| '2'  {$$=2;}
| '3'  {$$=3;}
| '4'  {$$=4;}
| '5'  {$$=5;}
| '6'  {$$=6;}
| '7'  {$$=7;}
| '8'  {$$=8;}
| '9'  {$$=9;}
| '0'  {$$=0;}
;
%%
int yylex()
{
    return getchar();
}

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char **argv)
{
    yyparse();
    return 0;
}