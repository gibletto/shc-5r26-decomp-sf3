#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_lreg
#define g_current_lreg (*(lreg * *)(g_sd + 0x1e4c4))


// entry: 00402d10
// name : add_block_to_life_area
// size : 208
// sig  : void add_block_to_life_area(bblock * block)


int __cdecl add_block_to_life_area(bblock *block)

{
  unsigned char _frec_40[64];
#define live_set (*(uint (*)[16])(_frec_40 + 0))
  uchar any;
  undefined4 *area_entry;
  char *node;
  undefined3 extraout_var = 0;
  short leafno;
  block_list *succ;
  
  area_entry = make_life_area_entry(block->startpp,block->endpp);
  *(byte *)&block->flag = (byte)block->flag | 8;
  *area_entry = g_current_lreg->life;
  g_current_lreg->life = area_entry;
  node = *(char **)((int)g_current_lreg->chain + 0x10);
  if (*node != 'p') {
    node = *(char **)(node + 0x14);
  }
  leafno = *(short *)(node + 0x58);
  for (succ = block->suclst; succ != (block_list *)0x0; succ = succ->next) {
    if ((((succ->block->flag & 0x18U) == 0) && (g_leaf_table[leafno].use != (uint *)0x0)) &&
       (succ->block->l_in != (uint *)0x0)) {
      clear_bytes((char *)live_set,0x40);
      bitset_and(live_set,g_leaf_table[leafno].use,succ->block->l_in,'\x10');
      any = any_bit_set(live_set,0x10);
      if (CONCAT31(extraout_var,any) == 1) {
        add_block_to_life_area(succ->block);
      }
    }
  }
  return;
#undef live_set
}



