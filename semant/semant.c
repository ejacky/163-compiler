#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

#define TODO()\
  do{\
  printf ("TODO: add your code at file: \"%s\", line: %d\n", __FILE__, __LINE__);\
}while(0)

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Table_insert (Dec_t dec)
{
  
  if (Table_lookup (dec->id) != -1){
    fprintf (stderr, "Error: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
  switch (exp->kind) {
    case EXP_INT : return TYPE_INT;
    case EXP_TRUE :
    case EXP_FALSE : return TYPE_BOOL;
    case EXP_ID: 
      Exp_Id p = (Exp_Id)exp;
      //Exp_Add p = (Exp_Add)exp;
      if (Table_lookup(p->id) == -1) {
          fprintf (stderr, "id not found");
          exit (0);
      } else return Table_lookup(p->id);
    case EXP_ADD:
      Exp_Add p = (Exp_Add)exp;
      Type_Kind_t left = check_exp(p->left);
      Type_Kind_t right = check_exp(p->right);
      if (left != TYPE_INT || right != TYPEO_INT) {
          fprintf (stderr, "dont match");
          exit (0);
      }
      else 
          return TYPE_INT;
    case EXP_AND:
      Type_Kind_t left = check_exp(exp->left);
      Type_Kind_t right = check_exp(exp->right);
      if (left != TYPE_INT || right != TYPEO_INT) {
          fprintf (stderr, "dont match");
          exit (0);
      }
      else 
          return TYPE_INT;
  }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
  switch (s->kind) {
    case STM_ASSIGN:
      Type_t t1 = Table_lookup(s->id);
      Type_t t2 = check_exp(s->exp);
      if (t1 != t2) {
          fprintf (stderr, "dont match");
          exit (0);
      } else return TYPE_INT;
    case STM_PRINTI:
      Type_t t = check_exp(s->exp);
      if (t != TYPE_INT) {
          fprintf (stderr, "dont match");
          exit (0);
      } else return TYPE_INT;
    case STM_PRINTB:
      Type_t t = check_exp(s->exp);
      if (t != TYPE_BOOL) {
          fprintf (stderr, "dont match");
          exit (0);
      } else return TYPE_BOOL;
  }
}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    check_stm(s);
    stms = stms->next;
  }
  return;
  //TODO();
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
