#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 004123d0
// name : path_avoids_block
// size : 132
// sig  : int path_avoids_block(bblock * block, short skip_no, short target_no)


int __cdecl path_avoids_block(bblock *block,short skip_no,short target_no)

{
  int result;
  block_list *succ;
  short blkno;
  byte *flagp;
  
  result = 0;
  succ = block->suclst;
  if (succ == (block_list *)0x0) {
    return 0;
  }
  do {
    blkno = succ->block->number;
    if ((((g_cur_loop->start->number <= blkno) && (blkno <= g_cur_loop->exit->number)) &&
        (skip_no != blkno)) && ((succ->block->flag & 0x400) == 0)) {
      if (target_no == blkno) {
        return 1;
      }
      if (block->number != target_no) {
        flagp = (byte *)((int)&block->flag + 1);
        *flagp = *flagp | 4;
      }
      result = path_avoids_block(succ->block,skip_no,target_no);
      if (result != 0) {
        return result;
      }
    }
    succ = succ->next;
    if (succ == (block_list *)0x0) {
      return result;
    }
  } while( true );
}



