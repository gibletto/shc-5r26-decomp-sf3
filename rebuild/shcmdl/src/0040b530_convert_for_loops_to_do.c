#include "decls.h"
#include "imports.h"

// entry: 0040b530
// name : convert_for_loops_to_do
// size : 112
// sig  : void convert_for_loops_to_do(loop * lp)


int __cdecl convert_for_loops_to_do(loop *lp)

{
  il_node *parent;
  
  if ((lp != (loop *)0x0) && (g_has_goto == '\0')) {
    if (lp->next != (loop *)0x0) {
      convert_for_loops_to_do(lp->next);
    }
    if (lp->child != (loop *)0x0) {
      convert_for_loops_to_do(lp->child);
    }
    if (((lp->repet != 0) || ((lp->flag & 0x8000) != 0)) && ((lp->flag & 0x1000) == 0)) {
      parent = lp->node;
      if (parent->op == IL_FOR) {
        delete_operand(parent,3);
        delete_operand(parent,1);
      }
      parent->op = IL_DO;
      lp->flag = lp->flag | 0x400;
    }
  }
  return;
}



