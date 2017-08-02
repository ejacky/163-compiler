#include "ast.h"
#include <stdio.h>

extern Exp_t tree;
void yyparse ();

int main (int argc, char **argv)
{
  yyparse();
  Exp_print (tree);
  printf("\n");
  int calcu = Exp_calculator(tree);
  printf("the value = %d\n", calcu);
  return 0;
}
