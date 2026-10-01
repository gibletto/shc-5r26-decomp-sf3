#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_b_chain
#define g_b_chain (*(bblock * *)(g_sd + 0x267f8))
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00405e30
// name : dump_cfg_blocks
// size : 460
// sig  : void dump_cfg_blocks(void)


int __cdecl dump_cfg_blocks(void)

{
  char bit;
  int i;
  int bitno;
  bblock *block;
  byte sign;
  
  for (block = g_bn_chain; block != (bblock *)0x0; block = block->bn_next) {
    FID_conflict__wprintf(s_B_d__00433620,(int)block->number);
    FID_conflict__wprintf(s____tcount____d_0043360c,(int)block->tcount);
    FID_conflict__wprintf(s____ilnode___004335fc);
    dump_ilnode_list(block->ilnode);
    FID_conflict__wprintf(s____prelst___00433838);
    dump_block_list(block->prelst);
    FID_conflict__wprintf(s____suclst___00433824);
    i = 1;
    dump_block_list(block->suclst);
    FID_conflict__wprintf(s____domlst___00433810);
    do {
      bitno = i + -1;
      sign = (byte)(bitno >> 0x1f);
      if ((1 << ((((byte)bitno ^ sign) - sign & 0x1f ^ sign) - sign & 0x1f) &
          block->domlst[(int)(bitno + (bitno >> 0x1f & 0x1fU)) >> 5]) != 0) {
        FID_conflict__wprintf(&g_str_block_number_comma,i);
      }
      i = i + 1;
    } while (i < 0x101);
    if (block->lptbl == (loop *)0x0) {
      FID_conflict__wprintf(s____lpnumber__004337e4);
    }
    else {
      FID_conflict__wprintf(s____lpnumber_LP_d_004337f8,(int)block->lptbl->lpnumber);
    }
    i = 0;
    FID_conflict__wprintf(s____flag___00433698);
    do {
      bit = (char)i;
      i = i + 1;
      FID_conflict__wprintf
                (&g_str_percent_1d,(uint)((1 << (0x1fU - bit & 0x1f) & (int)block->flag) != 0));
    } while (i < 0x20);
    FID_conflict__wprintf(&g_str_newline);
  }
  FID_conflict__wprintf(s_______f_chain_004337d0);
  for (block = g_f_chain; block != (bblock *)0x0; block = block->f_next) {
    FID_conflict__wprintf(s_B_d__004337c8,(int)block->number);
  }
  FID_conflict__wprintf(&g_str_newline);
  FID_conflict__wprintf(s_______b_chain_004337b8);
  for (block = g_b_chain; block != (bblock *)0x0; block = block->b_next) {
    FID_conflict__wprintf(s_B_d__004337c8,(int)block->number);
  }
  FID_conflict__wprintf(&g_str_newline);
  return;
}



