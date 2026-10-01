#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 0040c4f0
// name : solve_reaching_definitions
// size : 298
// sig  : void solve_reaching_definitions(void)


int __cdecl solve_reaching_definitions(void)

{
  unsigned char _frec_40[64];
#define in_set (*(uint (*)[8])(_frec_40 + 0))
#define out_set (*(uint (*)[8])(_frec_40 + 32))
  int iVar1;
  int next_ofs;
  uint *p;
  bblock *blk;
  bool changed;
  block_list *pred;
  
  for (blk = g_f_chain; blk != (bblock *)0x0; blk = blk->f_next) {
    iVar1 = 0;
    do {
      next_ofs = iVar1 + 4;
      *(undefined4 *)((int)blk->sets->reach_out + iVar1) =
           *(undefined4 *)((int)blk->sets->gen + iVar1);
      *(undefined4 *)((int)blk->d_in + iVar1) = 0;
      iVar1 = next_ofs;
    } while (next_ofs < 0x20);
  }
  do {
    changed = false;
    for (blk = g_f_chain; blk != (bblock *)0x0; blk = blk->f_next) {
      p = out_set;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        *p = 0;
        p = p + 1;
      }
      p = in_set;
      for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
        *p = 0;
        p = p + 1;
      }
      for (pred = blk->prelst; pred != (block_list *)0x0; pred = pred->next) {
        bitset_or(in_set,in_set,pred->block->sets->reach_out,'\b');
      }
      iVar1 = bitsets_differ((int *)in_set,(int *)blk->d_in,8);
      if (iVar1 != 0) {
        iVar1 = 0;
        do {
          next_ofs = iVar1 + 4;
          *(undefined4 *)((int)blk->d_in + iVar1) = *(undefined4 *)((int)in_set + iVar1);
          iVar1 = next_ofs;
        } while (next_ofs < 0x20);
        bitset_and(out_set,blk->d_in,blk->sets->kill,'\b');
        bitset_or(out_set,out_set,blk->sets->gen,'\b');
        iVar1 = 0;
        do {
          next_ofs = iVar1 + 4;
          *(undefined4 *)((int)blk->sets->reach_out + iVar1) = *(undefined4 *)((int)out_set + iVar1)
          ;
          iVar1 = next_ofs;
        } while (next_ofs < 0x20);
        changed = true;
      }
    }
  } while (changed);
  return;
#undef in_set
#undef out_set
}



