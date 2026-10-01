#include "decls.h"
#include "imports.h"

// entry: 0041c130
// name : set_node_lreg_number
// size : 96
// sig  : void set_node_lreg_number(short lregno, const_use * item, il_node * stmt, il_node * target)


int __cdecl set_node_lreg_number(short lregno,const_use *item,il_node *stmt,il_node *target)

{
  int count;
  ushort flag;
  
  count = 1;
  if (((item->block->lptbl == (loop *)0x0) && ((item->flag & 1) == 0)) && (item->latest == stmt)) {
    flag = stmt->flag;
    while ((flag & 0x200) == 0) {
      stmt = stmt->parent;
      flag = stmt->flag;
    }
    count = count_matching_leaf_nodes(stmt,target);
  }
  if (count == 0) {
    target->lreg = -lregno;
    return;
  }
  target->lreg = lregno;
  return;
}



