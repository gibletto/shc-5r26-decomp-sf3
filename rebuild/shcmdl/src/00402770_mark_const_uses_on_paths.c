#include "decls.h"
#include "imports.h"

// entry: 00402770
// name : mark_const_uses_on_paths
// size : 261
// sig  : void mark_const_uses_on_paths(bblock * block, block_list * link, lreg * reg)


int __cdecl mark_const_uses_on_paths(bblock *block,block_list *link,lreg *reg)

{
  bblock *pred;
  block_list *pred_link;
  byte *flag_hi;
  undefined4 *use;
  
  if ((*(bblock **)((int)reg->chain + 0x14) != block) && (block->prelst != (block_list *)0x0)) {
    for (use = *(undefined4 **)((int)reg->chain + 8); use != (undefined4 *)0x0;
        use = (undefined4 *)*use) {
      if ((bblock *)use[1] == block) {
        *(byte *)(use + 4) = *(byte *)(use + 4) | 1;
      }
    }
    flag_hi = (byte *)((int)&block->flag + 1);
    *flag_hi = *flag_hi | 2;
    pred = block->prelst->block;
    if (*(bblock **)((int)reg->chain + 0x14) != pred) {
LAB_004027be:
      if (((pred->flag & 0x200U) == 0) && (pred->prelst != (block_list *)0x0))
      goto code_r0x004027ca;
      for (pred_link = block->prelst->next; pred_link != (block_list *)0x0;
          pred_link = pred_link->next) {
        if ((pred_link->block->flag & 0x200) == 0) {
          mark_const_uses_on_paths(pred_link->block,pred_link,reg);
        }
      }
    }
LAB_00402810:
    if (*(bblock **)((int)reg->chain + 0x14) == pred) {
      for (pred_link = block->prelst->next; pred_link != (block_list *)0x0;
          pred_link = pred_link->next) {
        if ((pred_link->block->flag & 0x200U) == 0) {
          mark_const_uses_on_paths(pred_link->block,pred_link,reg);
        }
      }
    }
    else {
      pred_link = link->next;
      if (pred_link != (block_list *)0x0) {
        do {
          if ((pred_link->block->flag & 0x200U) == 0) {
            mark_const_uses_on_paths(pred_link->block,pred_link,reg);
          }
          pred_link = pred_link->next;
        } while (pred_link != (block_list *)0x0);
        return;
      }
    }
  }
  return;
code_r0x004027ca:
  mark_const_uses_on_paths(pred,block->prelst,reg);
  if ((pred->prelst == (block_list *)0x0) ||
     (pred = pred->prelst->block, *(bblock **)((int)reg->chain + 0x14) == pred)) goto LAB_00402810;
  goto LAB_004027be;
}



