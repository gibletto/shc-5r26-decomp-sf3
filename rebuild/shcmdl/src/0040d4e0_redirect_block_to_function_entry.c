#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))
#undef g_exit_block
#define g_exit_block (*(bblock * *)(g_sd + 0x267cc))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 0040d4e0
// name : redirect_block_to_function_entry
// size : 251
// sig  : void redirect_block_to_function_entry(bblock * block)


int __cdecl redirect_block_to_function_entry(bblock *block)

{
  block_list *item;
  block_list **link;
  bblock *blk;
  block_list **succ_head;
  
  link = &g_exit_block->prelst;
  blk = (*link)->block;
  while (blk != block) {
    item = *link;
    link = &item->next;
    blk = item->next->block;
  }
  item = *link;
  succ_head = &block->suclst;
  *link = item->next;
  pool_free(item,8);
  blk = (*succ_head)->block;
  link = succ_head;
  while (blk != g_exit_block) {
    item = *link;
    link = &item->next;
    blk = item->next->block;
  }
  item = *link;
  *link = item->next;
  pool_free(item,8);
  item = pool_alloc(8);
  if (item == (block_list *)0x0) {
    abort_function_optimization();
  }
  item->block = g_bn_chain->suclst->block;
  item->next = *succ_head;
  *succ_head = item;
  item = pool_alloc(8);
  if (item == (block_list *)0x0) {
    abort_function_optimization();
  }
  item->block = block;
  item->next = g_bn_chain->suclst->block->prelst;
  g_bn_chain->suclst->block->prelst = item;
  for (blk = g_bn_chain; blk != (bblock *)0x0; blk = blk->bn_next) {
    *(byte *)&blk->flag = (byte)blk->flag & 0xfe;
  }
  g_f_chain = (bblock *)0x0;
  link_blocks_reverse_postorder(g_bn_chain);
  compute_dominators();
  return;
}



