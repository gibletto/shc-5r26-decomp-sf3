#include "decls.h"
#include "imports.h"

// entry: 00402660
// name : choose_const_dominator
// size : 263
// sig  : void choose_const_dominator(lreg * reg)


int __cdecl choose_const_dominator(lreg *reg)

{
  undefined4 *puVar1;
  bblock *dom;
  bblock *prev_block;
  int *use;
  void *cdata;
  node_list *cell;
  int *last_use;
  loop *lp;
  node_list *next_cell;
  int *next_use;
  undefined4 *other_use;
  loop *outer;
  
  use = *(int **)((int)reg->chain + 8);
  other_use = (undefined4 *)*use;
  last_use = use;
  puVar1 = other_use;
  while ((puVar1 != (undefined4 *)0x0 && (next_use = (int *)*last_use, last_use[1] == next_use[1])))
  {
    puVar1 = (undefined4 *)*next_use;
    last_use = next_use;
  }
  if ((*last_use == 0) && (*(int *)(last_use[1] + 0x30) == 0)) {
    *(undefined2 *)((int)reg->chain + 2) = 2;
    *(undefined4 *)((int)reg->chain + 0x14) = *(undefined4 *)(*(int *)((int)reg->chain + 8) + 4);
    *(undefined4 *)((int)reg->chain + 0x18) = *(undefined4 *)(*(int *)((int)reg->chain + 8) + 8);
    return;
  }
  dom = (bblock *)use[1];
  prev_block = (bblock *)0x0;
  for (; other_use != (undefined4 *)0x0; other_use = (undefined4 *)*other_use) {
    if (prev_block != (bblock *)other_use[1]) {
      dom = find_common_dominator(dom,(bblock *)other_use[1]);
      if (dom == (bblock *)0x0) {
        return;
      }
      prev_block = (bblock *)other_use[1];
    }
  }
  if ((dom != (bblock *)0x0) && (dom->number != 1)) {
    lp = dom->lptbl;
    if (lp != (loop *)0x0) {
      outer = lp->fath;
      while (outer != (loop *)0x0) {
        lp = lp->fath;
        outer = lp->fath;
      }
      dom = lp->pre;
    }
    *(undefined2 *)((int)reg->chain + 2) = 1;
    *(bblock **)((int)reg->chain + 0x14) = dom;
    cdata = reg->chain;
    use = *(int **)((int)cdata + 8);
    if (use != (int *)0x0) {
      do {
        if ((bblock *)use[1] == dom) break;
        use = (int *)*use;
      } while (use != (int *)0x0);
      if (use != (int *)0x0) {
        *(int *)((int)cdata + 0x18) = use[2];
        return;
      }
    }
    cell = dom->ilnode;
    if (cell != (node_list *)0x0) {
      next_cell = cell->next;
      while (next_cell != (node_list *)0x0) {
        cell = cell->next;
        next_cell = cell->next;
      }
      *(il_node **)((int)cdata + 0x18) = cell->node;
      return;
    }
    *(undefined4 *)((int)cdata + 0x18) = 0;
  }
  return;
}



