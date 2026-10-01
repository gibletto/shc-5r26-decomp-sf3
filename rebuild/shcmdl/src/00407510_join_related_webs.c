#include "decls.h"
#include "imports.h"

// entry: 00407510
// name : join_related_webs
// size : 527
// sig  : void join_related_webs(il_node * node)


int __cdecl join_related_webs(il_node *node)

{
  int pos;
  dutbl *other_web;
  il_node *piVar1;
  il_node *rhs;
  il_node *operand;
  dutbl *tail;
  dutbl *du;
  dutbl *next_du;
  il_op op;
  il_node *ref;
  
  du = node->duptr;
  tail = du;
  do {
    if (du == (dutbl *)0x0) {
      return;
    }
    for (ref = du->node; ref != (il_node *)0x0; ref = ref->refchn) {
      op = ref->op;
      if (op == IL_ID) {
        op = ref->parent->op;
        if ((((op & IL_NON_F0) == IL_A_ADD) || ((op & IL_NON_F8) == IL_PRI)) &&
           ((pos = operand_index(ref), pos == 1 && ((ref->parent->flag & 4) == 0)))) {
          mark_web_allocatable(ref->parent);
          join_related_webs(ref->parent);
          other_web = ref->parent->duptr;
          goto LAB_004076e6;
        }
        other_web = (dutbl *)0x0;
        piVar1 = ref->parent;
        if (piVar1->op == IL_CAST) {
          piVar1 = piVar1->parent;
        }
        if ((piVar1->op & IL_NON_F0) == IL_ADD) {
          piVar1 = piVar1->parent;
          if (piVar1->op == IL_CAST) {
            piVar1 = piVar1->parent;
          }
          if (((piVar1->op == IL_ASSIGN) && (piVar1->child->op == IL_ID)) &&
             ((piVar1->child->nleaf == ref->nleaf && ((piVar1->flag & 4) == 0)))) {
            mark_web_allocatable(piVar1);
            join_related_webs(piVar1);
            other_web = piVar1->duptr;
          }
        }
        if (other_web != (dutbl *)0x0) goto LAB_004076e6;
      }
      else {
        if (((((op & IL_NON_F0) == IL_A_ADD) && (op != IL_ASSIGN)) || ((op & IL_NON_F8) == IL_PRI))
           && ((piVar1 = ref->child, piVar1->op == IL_ID && ((piVar1->flag & 4) == 0)))) {
          mark_web_allocatable(piVar1->cmnexp);
          join_related_webs(ref->child->cmnexp);
          other_web = ref->child->cmnexp->duptr;
        }
        else {
          piVar1 = ref->child;
          if (piVar1->lreg == -0x8000) {
            other_web = piVar1->duptr;
          }
          else {
            other_web = (dutbl *)0x0;
            if (op == IL_ASSIGN) {
              rhs = piVar1->next;
              operand = rhs;
              if (rhs->op == IL_CAST) {
                operand = rhs->child;
              }
              if ((operand->op & IL_NON_F0) == IL_ADD) {
                operand = operand->child;
                if (operand->op == IL_CAST) {
                  operand = operand->child;
                }
                if (((operand->op != IL_ID) || (piVar1->nleaf != operand->nleaf)) ||
                   ((operand->flag & 4) != 0)) {
                  if (rhs->op == IL_CAST) {
                    rhs = rhs->child;
                  }
                  operand = rhs->child->next;
                  if (operand->op == IL_CAST) {
                    operand = operand->child;
                  }
                  if (((operand->op != IL_ID) || (piVar1->nleaf != operand->nleaf)) ||
                     ((operand->flag & 4) != 0)) goto LAB_004076e2;
                }
                mark_web_allocatable(operand->cmnexp);
                join_related_webs(operand->cmnexp);
                other_web = operand->cmnexp->duptr;
              }
            }
LAB_004076e2:
            if (other_web == (dutbl *)0x0) goto LAB_004076f9;
          }
        }
LAB_004076e6:
        next_du = tail->next;
        while (next_du != (dutbl *)0x0) {
          tail = tail->next;
          next_du = tail->next;
        }
        tail->next = other_web;
      }
LAB_004076f9: ;
    }
    du = du->next;
  } while( true );
}



