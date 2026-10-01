#include "decls.h"
#include "imports.h"

// entry: 00402880
// name : extend_const_life_area_backward
// size : 275
// sig  : void extend_const_life_area_backward(bblock * block, block_list * link, lreg * reg)


int __cdecl extend_const_life_area_backward(bblock *block,block_list *link,lreg *reg)

{
  undefined4 *area_entry;
  bblock *pred;
  block_list *pred_link;
  byte *flag_hi;
  
  if ((*(bblock **)((int)reg->chain + 0x14) != block) && (block->prelst != (block_list *)0x0)) {
    if ((block->flag & 0x200) == 0) {
      area_entry = make_life_area_entry(block->startpp,block->endpp);
      *area_entry = reg->life;
      reg->life = area_entry;
      flag_hi = (byte *)((int)&block->flag + 1);
      *flag_hi = *flag_hi | 2;
    }
    pred = block->prelst->block;
    if (*(bblock **)((int)reg->chain + 0x14) != pred) {
LAB_004028dc:
      if (((pred->flag & 0x200U) == 0) && (pred->prelst != (block_list *)0x0))
      goto code_r0x004028e8;
      for (pred_link = block->prelst->next; pred_link != (block_list *)0x0;
          pred_link = pred_link->next) {
        if ((pred_link->block->flag & 0x200) == 0) {
          extend_const_life_area_backward(pred_link->block,pred_link,reg);
        }
      }
    }
LAB_0040292e:
    if (*(bblock **)((int)reg->chain + 0x14) == pred) {
      for (pred_link = block->prelst->next; pred_link != (block_list *)0x0;
          pred_link = pred_link->next) {
        if ((pred_link->block->flag & 0x200U) == 0) {
          extend_const_life_area_backward(pred_link->block,pred_link,reg);
        }
      }
    }
    else {
      pred_link = link->next;
      if (pred_link != (block_list *)0x0) {
        do {
          if ((pred_link->block->flag & 0x200U) == 0) {
            extend_const_life_area_backward(pred_link->block,pred_link,reg);
          }
          pred_link = pred_link->next;
        } while (pred_link != (block_list *)0x0);
        return;
      }
    }
  }
  return;
code_r0x004028e8:
  extend_const_life_area_backward(pred,block->prelst,reg);
  if ((pred->prelst == (block_list *)0x0) ||
     (pred = pred->prelst->block, *(bblock **)((int)reg->chain + 0x14) == pred)) goto LAB_0040292e;
  goto LAB_004028dc;
}



