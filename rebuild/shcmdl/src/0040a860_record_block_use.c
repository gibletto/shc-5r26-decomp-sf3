#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_dag_block
#define g_dag_block (*(bblock * *)(g_sd + 0x1e724))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 0040a860
// name : record_block_use
// size : 237
// sig  : void record_block_use(il_node * node)


int __cdecl record_block_use(il_node *node)

{
  byte type_class;
  uint *leaf_set;
  
  type_class = node->type & 0xf0;
  if ((((type_class != 0x60) && (type_class != 0x70)) && (type_class != 0x80)) &&
     (((type_class != 0x90 && ((node->type & 0xf8) != 0x48)) &&
      (((g_leaf_table[node->nleaf].flag & 7) == 0 &&
       (((&g_op_class)[(char)node->cmnexp->op] & 0x20) == 0)))))) {
    if (0x1ff < g_use_count) {
      free_def_tables_and_abort();
    }
    leaf_set = g_leaf_table[node->nleaf].use;
    if (leaf_set == (uint *)0x0) {
      leaf_set = pool_alloc(0x40);
      if (leaf_set == (uint *)0x0) {
        free_def_tables_and_abort();
      }
      g_leaf_table[node->nleaf].use = leaf_set;
    }
    add_to_gen_use_sets(g_dag_block->sets->use,g_use_count,node,0x10,leaf_set);
    if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 0x40) != 0) {
      FID_conflict__wprintf(s_set_block_use__08x_use_no__d_00434f60,node,(int)g_use_count);
    }
    g_use_count = g_use_count + 1;
  }
  return;
}



