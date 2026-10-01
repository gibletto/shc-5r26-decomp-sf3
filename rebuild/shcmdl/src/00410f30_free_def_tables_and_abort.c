#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#undef g_defined_leaves
#define g_defined_leaves (*(int * *)(g_sd + 0x267a8))
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 00410f30
// name : free_def_tables_and_abort
// size : 177
// sig  : void free_def_tables_and_abort(void)


int __cdecl free_def_tables_and_abort(void)

{
  node_cell **const_bucket;
  node_list **expr_bucket;
  il_node *const_cell;
  bblock *expr_cell;
  il_node *next_const;
  undefined4 *next_def;
  bblock *next_expr;
  
  while (g_defined_leaves != (undefined4 *)0x0) {
    g_leaf_table[*(short *)(g_defined_leaves + 1)].lastnd = (il_node *)0x0;
    next_def = (undefined4 *)*g_defined_leaves;
    pool_free(g_defined_leaves,8);
    g_defined_leaves = next_def;
  }
  g_defined_leaves = (undefined4 *)0x0;
  const_bucket = g_const_hash;
  do {
    const_cell = (il_node *)*const_bucket;
    while (const_cell != (il_node *)0x0) {
      next_const = *(il_node **)&const_cell->op;
      pool_free(const_cell,8);
      const_cell = next_const;
    }
    *const_bucket = (node_cell *)0x0;
    const_bucket = const_bucket + 1;
  } while (const_bucket < &g_memory_refs);
  expr_bucket = g_expr_hash;
  do {
    expr_cell = (bblock *)*expr_bucket;
    while (expr_cell != (bblock *)0x0) {
      next_expr = (bblock *)expr_cell->ilnode;
      pool_free(expr_cell,8);
      expr_cell = next_expr;
    }
    *expr_bucket = (node_list *)0x0;
    expr_bucket = expr_bucket + 1;
  } while (expr_bucket < &g_cfg_next_block);
  free_dag_node_list();
  abort_function_optimization();
  return;
}



