#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#undef g_dag_block
#define g_dag_block (*(bblock * *)(g_sd + 0x1e724))
#undef g_dag_unread_word2
#define g_dag_unread_word2 (*(int *)(g_sd + 0x1e710))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_defined_leaves
#define g_defined_leaves (*(int * *)(g_sd + 0x267a8))
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 00410b40
// name : build_block_dag_chain
// size : 446
// sig  : void build_block_dag_chain(bblock * block, char make_du)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl build_block_dag_chain(bblock *block,char make_du)

{
  il_node *piVar1;
  node_cell **const_bucket;
  node_list **expr_bucket;
  bblock *expr_cell;
  ushort *flagp;
  node_list *item;
  il_node *next_const;
  undefined4 *next_def;
  bblock *next_expr;
  
  if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 0x20) != 0) {
    FID_conflict__wprintf(s_DAG_chain_start_00435400);
  }
  g_make_du = make_du;
  g_dag_block = block;
  block->startpp = g_def_count;
  g_value_number = 0;
  _g_dag_unread_word2 = 0;
  _g_dag_unread_word1 = 0;
  g_defined_leaves = (undefined4 *)0x0;
  g_in_builtin_call = '\0';
  for (item = g_dag_block->ilnode; item != (node_list *)0x0; item = item->next) {
    build_dag(item->node);
  }
  while (g_defined_leaves != (undefined4 *)0x0) {
    piVar1 = g_leaf_table[*(short *)(g_defined_leaves + 1)].lastnd;
    if (piVar1->refchn == (il_node *)0x0) {
      if (((&g_op_class)[(char)piVar1->op] & 0x20) == 0) {
        *(byte *)&piVar1->flag = (byte)piVar1->flag | 0x80;
      }
    }
    else {
      flagp = &piVar1->refchn->flag;
      *(byte *)flagp = (byte)*flagp | 0x80;
    }
    if (g_make_du != '\0') {
      record_definition(piVar1);
    }
    g_leaf_table[*(short *)(g_defined_leaves + 1)].lastnd = (il_node *)0x0;
    next_def = (undefined4 *)*g_defined_leaves;
    pool_free(g_defined_leaves,8);
    g_defined_leaves = next_def;
  }
  g_dag_block->endpp = g_def_count;
  const_bucket = g_const_hash;
  do {
    piVar1 = (il_node *)*const_bucket;
    while (piVar1 != (il_node *)0x0) {
      next_const = *(il_node **)&piVar1->op;
      pool_free(piVar1,8);
      piVar1 = next_const;
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
  if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 0x20) != 0) {
    FID_conflict__wprintf(s_DAG_chain_end_block_No___d_004353e0,(int)g_dag_block->number);
    FID_conflict__wprintf(s_node_val_no_cmnexp_refchn_refcnt_004353a0);
    for (item = g_dag_block->ilnode; item != (node_list *)0x0; item = item->next) {
      dump_dag_chain_node(item->node);
    }
    _fflush((FILE *)&stock_stdout);
  }
  return;
}



