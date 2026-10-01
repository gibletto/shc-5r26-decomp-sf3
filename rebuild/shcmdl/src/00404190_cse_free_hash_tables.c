#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))


// entry: 00404190
// name : cse_free_hash_tables
// size : 164
// sig  : void cse_free_hash_tables(void)


int __cdecl cse_free_hash_tables(void)

{
  undefined4 *leaf_bucket;
  node_list **expr_bucket;
  node_cell **const_bucket;
  node_cell *const_cell;
  bblock *expr_cell;
  undefined4 *leaf_entry;
  node_cell *next_cell;
  undefined4 *next_entry;
  bblock *next_expr_cell;
  
  leaf_bucket = &g_leaf_def_hash;
  do {
    leaf_entry = (undefined4 *)*leaf_bucket;
    while (leaf_entry != (undefined4 *)0x0) {
      g_leaf_table[*(short *)(leaf_entry + 1)].lastnd = (il_node *)0x0;
      next_entry = (undefined4 *)*leaf_entry;
      pool_free(leaf_entry,8);
      leaf_entry = next_entry;
    }
    *leaf_bucket = 0;
    leaf_bucket = leaf_bucket + 1;
  } while (leaf_bucket < &g_dag_unread_word2);
  const_bucket = g_cse_const_hash;
  do {
    const_cell = *const_bucket;
    while (const_cell != (node_cell *)0x0) {
      next_cell = const_cell->next;
      pool_free(const_cell,8);
      const_cell = next_cell;
    }
    *const_bucket = (node_cell *)0x0;
    const_bucket = const_bucket + 1;
  } while (const_bucket < &g_has_goto);
  expr_bucket = g_expr_hash;
  do {
    expr_cell = (bblock *)*expr_bucket;
    while (expr_cell != (bblock *)0x0) {
      next_expr_cell = (bblock *)expr_cell->ilnode;
      pool_free(expr_cell,8);
      expr_cell = next_expr_cell;
    }
    *expr_bucket = (node_list *)0x0;
    expr_bucket = expr_bucket + 1;
  } while (expr_bucket < &g_cfg_next_block);
  return;
}



