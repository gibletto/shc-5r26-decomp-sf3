#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_iv_copy_list
#define g_iv_copy_list (*(node_list * *)(g_sd + 0x3a00))


// entry: 004174e0
// name : free_induction_tables
// size : 183
// sig  : void free_induction_tables(void)


int __cdecl free_induction_tables(void)

{
  iv_use *block;
  iv_entry *iv;
  iv_entry *next_iv;
  node_list *item;
  node_list *next_item;
  iv_use *next_use;
  
  iv = g_iv_table + 1;
  do {
    block = iv->uses;
    while (block != (iv_use *)0x0) {
      next_use = block->next;
      item = block->factors;
      while (item != (node_list *)0x0) {
        next_item = item->next;
        pool_free(item,8);
        item = next_item;
      }
      block->expr = (il_node *)0x0;
      block->id = (il_node *)0x0;
      block->incr = (il_node *)0x0;
      block->test_adjust = 0;
      block->copy = (il_node *)0x0;
      block->copy_id = (il_node *)0x0;
      pool_free(block,0x24);
      iv->uses = (iv_use *)0x0;
      block = next_use;
    }
    next_iv = iv + 1;
    free_tree(iv->step);
    iv->step = (il_node *)0x0;
    iv->update = (il_node *)0x0;
    iv->block = (bblock *)0x0;
    iv = next_iv;
    item = g_iv_copy_list;
  } while (next_iv < (iv_entry *)&g_iv_negated_count);
  while (item != (node_list *)0x0) {
    free_tree(item->node);
    next_item = item->next;
    pool_free(item,8);
    item = next_item;
  }
  g_iv_copy_list = (node_list *)0x0;
  return;
}



