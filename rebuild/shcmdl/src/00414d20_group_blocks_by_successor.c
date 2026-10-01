#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_exit_block
#define g_exit_block (*(bblock * *)(g_sd + 0x267cc))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00414d20
// name : group_blocks_by_successor
// size : 90
// sig  : void group_blocks_by_successor(void)


int __cdecl group_blocks_by_successor(void)

{
  bblock *block;
  bblock *succ;
  block_list *succ_item;
  
  block = g_f_chain->f_next;
  do {
    if (block == (bblock *)0x0) {
      return;
    }
    if ((block->ilnode != (node_list *)0x0) &&
       (succ_item = block->suclst, succ_item != (block_list *)0x0)) {
      if (succ_item->next == (block_list *)0x0) {
        succ = succ_item->block;
LAB_00414d66:
        add_block_to_successor_group(block,succ);
      }
      else if (succ_item != (block_list *)0x0) {
        do {
          succ = g_exit_block;
          if (succ_item->block->number == g_exit_block->number) goto LAB_00414d66;
          succ_item = succ_item->next;
        } while (succ_item != (block_list *)0x0);
      }
    }
    block = block->f_next;
  } while( true );
}



