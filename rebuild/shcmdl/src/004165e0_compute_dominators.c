#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 004165e0
// name : compute_dominators
// size : 303
// sig  : void compute_dominators(void)


int __cdecl compute_dominators(void)

{
  unsigned char _frec_20[32];
#define doms (*(uint (*)[8])(_frec_20 + 0))
  byte bVar1;
  int next_ofs;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  uint bits;
  bblock *blk;
  bool changed;
  block_list *pred;
  
  iVar4 = 0;
  do {
    next_ofs = iVar4 + 4;
    *(undefined4 *)((int)g_f_chain->domlst + iVar4) = 0;
    iVar4 = next_ofs;
  } while (next_ofs < 0x20);
  iVar4 = g_f_chain->number + -1;
  bVar1 = (byte)(iVar4 >> 0x1f);
  g_f_chain->domlst[(int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5] =
       1 << ((((byte)iVar4 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1 & 0x1f);
  for (blk = g_f_chain->f_next; blk != (bblock *)0x0; blk = blk->f_next) {
    puVar2 = blk->domlst;
    for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar2 = 0xffffffff;
      puVar2 = puVar2 + 1;
    }
  }
  do {
    changed = false;
    for (blk = g_f_chain->f_next; blk != (bblock *)0x0; blk = blk->f_next) {
      puVar2 = blk->prelst->block->domlst;
      puVar3 = doms;
      for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      for (pred = blk->prelst->next; pred != (block_list *)0x0; pred = pred->next) {
        puVar2 = doms;
        puVar3 = pred->block->domlst;
        do {
          bits = *puVar3;
          puVar3 = puVar3 + 1;
          *puVar2 = *puVar2 & bits;
          puVar2 = puVar2 + 1;
        } while (puVar2 < (void *)(_frec_20 + 0x20));
      }
      iVar4 = blk->number + -1;
      bVar1 = (byte)(iVar4 >> 0x1f);
      puVar3 = doms;
      puVar2 = blk->domlst;
      doms[(int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5] =
           doms[(int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5] |
           1 << ((((byte)iVar4 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1 & 0x1f);
      do {
        if (*puVar2 != *puVar3) {
          changed = true;
        }
        *puVar2 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar2 = puVar2 + 1;
      } while (puVar3 < (void *)(_frec_20 + 0x20));
    }
  } while (changed);
  return;
#undef doms
}



