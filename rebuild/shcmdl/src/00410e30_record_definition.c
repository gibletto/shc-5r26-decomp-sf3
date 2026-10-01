#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_dag_block
#define g_dag_block (*(bblock * *)(g_sd + 0x1e724))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00410e30
// name : record_definition
// size : 248
// sig  : void record_definition(il_node * node)


int __cdecl record_definition(il_node *node)

{
  uint *leaf_set;
  byte kind;
  short nleaf;
  byte ty;
  
  if (((&g_op_class)[(char)node->op] & 0x20) != 0) {
    ty = node->child->type;
    kind = ty & 0xf0;
    if ((((kind != 0x60) && (kind != 0x70)) && (kind != 0x80)) &&
       (((kind != 0x90 && ((g_leaf_table[node->child->nleaf].flag & 7) == 0)) && ((ty & 2) == 0))))
    {
      if (0xff < g_def_count) {
        free_def_tables_and_abort();
      }
      nleaf = node->child->nleaf;
      node->nleaf = nleaf;
      leaf_set = g_leaf_table[nleaf].gen;
      if (leaf_set == (uint *)0x0) {
        leaf_set = pool_alloc(0x20);
        if (leaf_set == (uint *)0x0) {
          free_def_tables_and_abort();
        }
        g_leaf_table[node->nleaf].gen = leaf_set;
      }
      add_to_gen_use_sets(g_dag_block->sets->gen,g_def_count,node,8,leaf_set);
      if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 0x40) != 0) {
        FID_conflict__wprintf(s_set_block_gen__08x_def_no__d_00435444,node,(int)g_def_count);
      }
      g_def_count = g_def_count + 1;
    }
  }
  return;
}



