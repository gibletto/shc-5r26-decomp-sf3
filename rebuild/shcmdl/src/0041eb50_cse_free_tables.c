#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#undef g_cse_variables
#define g_cse_variables (*(node_list * *)(g_sd + 0x267a4))
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 0041eb50
// name : cse_free_tables
// size : 198
// sig  : void cse_free_tables(void)


int __cdecl cse_free_tables(void)

{
  node_list **bucket;
  node_cell **const_bucket;
  il_node *cell;
  bblock *item;
  node_list *next;
  il_node *next_cell;
  bblock *next_item;
  
  bucket = g_expr_hash;
  do {
    item = (bblock *)*bucket;
    while (item != (bblock *)0x0) {
      next_item = (bblock *)item->ilnode;
      pool_free(item,8);
      item = next_item;
    }
    *bucket = (node_list *)0x0;
    bucket = bucket + 1;
  } while (bucket < &g_cfg_next_block);
  const_bucket = g_const_hash;
  do {
    cell = (il_node *)*const_bucket;
    while (cell != (il_node *)0x0) {
      next_cell = *(il_node **)&cell->op;
      pool_free(cell,8);
      cell = next_cell;
    }
    *const_bucket = (node_cell *)0x0;
    const_bucket = const_bucket + 1;
  } while (const_bucket < &g_memory_refs);
  while (next = (node_list *)0x0, g_cse_variables != (node_list *)0x0) {
    g_leaf_table[g_cse_variables->node->nleaf].lastnd = (il_node *)0x0;
    next = g_cse_variables->next;
    pool_free(g_cse_variables,8);
    g_cse_variables = next;
  }
  while (g_cse_variables = next, g_memory_refs != (node_list *)0x0) {
    next = g_memory_refs->next;
    pool_free(g_memory_refs,8);
    g_memory_refs = next;
    next = g_cse_variables;
  }
  return;
}



