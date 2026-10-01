#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_b_chain
#define g_b_chain (*(bblock * *)(g_sd + 0x267f8))


// entry: 0040c620
// name : solve_live_variables
// size : 296
// sig  : void solve_live_variables(void)


int __cdecl solve_live_variables(void)

{
  unsigned char _frec_c0[192];
#define in_set (*(uint (*)[16])(_frec_c0 + 0))
#define out_set (*(uint (*)[16])(_frec_c0 + 64))
#define old_in (*(int (*)[16])(_frec_c0 + 128))
  int iVar1;
  int next_ofs;
  bblock *blk;
  bool changed;
  block_list *succ;
  
  for (blk = g_b_chain; blk != (bblock *)0x0; blk = blk->b_next) {
    iVar1 = 0;
    do {
      next_ofs = iVar1 + 4;
      *(undefined4 *)((int)blk->l_in + iVar1) = 0;
      iVar1 = next_ofs;
    } while (next_ofs < 0x40);
  }
  do {
    changed = false;
    for (blk = g_b_chain; blk != (bblock *)0x0; blk = blk->b_next) {
      iVar1 = 0;
      do {
        *(undefined4 *)((int)out_set + iVar1) = 0;
        next_ofs = iVar1 + 4;
        *(undefined4 *)((int)old_in + iVar1) = *(undefined4 *)((int)blk->l_in + iVar1);
        *(undefined4 *)((int)in_set + iVar1) = 0;
        iVar1 = next_ofs;
      } while (next_ofs < 0x40);
      for (succ = blk->suclst; succ != (block_list *)0x0; succ = succ->next) {
        bitset_or(out_set,out_set,succ->block->l_in,'\x10');
      }
      iVar1 = 0;
      do {
        next_ofs = iVar1 + 4;
        *(undefined4 *)((int)blk->out + iVar1) = *(undefined4 *)((int)out_set + iVar1);
        iVar1 = next_ofs;
      } while (next_ofs < 0x40);
      bitset_and(in_set,blk->out,blk->sets->def,'\x10');
      bitset_or(in_set,in_set,blk->sets->use,'\x10');
      iVar1 = 0;
      do {
        next_ofs = iVar1 + 4;
        *(undefined4 *)((int)blk->l_in + iVar1) = *(undefined4 *)((int)in_set + iVar1);
        iVar1 = next_ofs;
      } while (next_ofs < 0x40);
      iVar1 = bitsets_differ(old_in,(int *)blk->l_in,0x10);
      if (iVar1 != 0) {
        changed = true;
      }
    }
  } while (changed);
  return;
#undef in_set
#undef out_set
#undef old_in
}



