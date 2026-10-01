#include "decls.h"
#include "imports.h"

// entry: 0040bb20
// name : condition_defs_block_inversion
// size : 201
// sig  : char condition_defs_block_inversion(loop * lp, il_node * expr)


char __cdecl condition_defs_block_inversion(loop *lp,il_node *expr)

{
  byte bVar1;
  char sub_result;
  int iVar2;
  char result;
  int outside_defs;
  short def_blkno;
  dutbl *du;
  node_list *link;
  bool no_chain;
  il_node *sub;
  
  result = '\0';
  no_chain = false;
  sub = expr->child;
  outside_defs = 0;
  for (; sub != (il_node *)0x0; sub = sub->next) {
    sub_result = condition_defs_block_inversion(lp,sub);
    result = result + sub_result;
  }
  if ((expr->cmnexp == (il_node *)0x0) || (du = expr->cmnexp->duptr, du == (dutbl *)0x0)) {
    no_chain = true;
  }
  else {
    for (link = du->links; link != (node_list *)0x0; link = link->next) {
      def_blkno = link->node->duptr->block->number;
      if (def_blkno < lp->start->number) {
        outside_defs = outside_defs + 1;
        iVar2 = def_blkno + -1;
        bVar1 = (byte)(iVar2 >> 0x1f);
        if ((lp->start->domlst[(int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5] &
            1 << ((((byte)iVar2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1 & 0x1f)) == 0) {
          result = '\x01';
        }
      }
    }
  }
  if (1 < outside_defs) {
    result = '\0';
  }
  if ((!no_chain) && (outside_defs == 0)) {
    result = '\x01';
  }
  return result;
}



