#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_regalloc_block
#define g_regalloc_block (*(bblock * *)(g_sd + 0x1648c))


// entry: 00406f80
// name : prepare_register_allocation
// size : 120
// sig  : void prepare_register_allocation(void)


int __cdecl prepare_register_allocation(void)

{
  bblock *block;
  ushort *flag_ptr;
  node_list *stmt;
  
  g_pp_count = 1;
  for (block = g_f_chain; block != (bblock *)0x0; block = block->f_next) {
    stmt = block->ilnode;
    g_regalloc_block = block;
    block->startpp = (ushort)g_pp_count;
    if (stmt == (node_list *)0x0) {
      block->endpp = (ushort)g_pp_count;
      g_pp_count = g_pp_count + 1;
    }
    else {
      for (; stmt != (node_list *)0x0; stmt = stmt->next) {
        flag_ptr = &stmt->node->flag;
        *flag_ptr = *flag_ptr | 0x200;
        scan_tree_for_regalloc(block,stmt->node,0);
      }
      block->endpp = (short)g_pp_count - 1;
    }
  }
  return;
}



