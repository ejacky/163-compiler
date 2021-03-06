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
    case EXP_ID: {
      Exp_Id p = (Exp_Id)exp;
      //Exp_Add p = (Exp_Add)exp;
      if (Table_lookup(p->id) == -1) {
          fprintf (stderr, "id not found");
          exit (0);
      } else return (Type_t)Table_lookup(p->id);
    }

    case EXP_ADD:{
      Exp_Add p = (Exp_Add)exp;
      
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_INT || right != TYPE_INT) {
          fprintf (stderr, "dont match Exp_Add");
          exit (0);
      }
      else 
          return TYPE_INT;
    }

    case EXP_AND:{
      Exp_And p = (Exp_And)exp;
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_INT || right != TYPE_INT) {
          fprintf (stderr, "dont match Exp_And");
          exit (0);
      }
      else 
          return TYPE_INT;
    }
  }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t s)
{
  switch (s->kind) {
    case STM_ASSIGN: {
      Stm_Assign p = (Stm_Assign)s;
      Type_t t1 = Table_lookup(p->id);
      Type_t t2 = check_exp(p->exp);
      if (t1 != t2) {
          fprintf (stderr, "dont match Stm_Assign");
          exit (0);
      } 
      return ;
    }

    case STM_PRINTI: {
      Stm_Printi p = (Stm_Printi)s;
      Type_t t = check_exp(p->exp);
      if (t != TYPE_INT) {
          fprintf (stderr, "dont match STM_PRINTI, type is %d\n", t);
          exit (0);
      } 
      return;
    }
    case STM_PRINTB: {
      Stm_Printb p = (Stm_Printb)s;
      Type_t t = check_exp(p->exp);
      if (t != TYPE_BOOL) {
          fprintf (stderr, "dont match STM_PRINTB");
          exit (0);
      }
      return; 
    }
    default :
      break;
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
