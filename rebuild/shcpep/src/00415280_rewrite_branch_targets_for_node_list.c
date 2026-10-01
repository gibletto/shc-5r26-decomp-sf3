#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_block
#define g_current_block (*(code_node * *)(g_sd + 0x5c38))
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_last_block
#define g_last_block (*(code_node * *)(g_sd + 0x5bc4))


// entry: 00415280
// name : rewrite_branch_targets_for_node_list
// size : 105
// sig  : void rewrite_branch_targets_for_node_list(void)


int __cdecl rewrite_branch_targets_for_node_list(void)

{
  code_node *block;
  psd *rec;
  psd_op op;
  code_node *prev_block;
  
  prev_block = (code_node *)0x0;
  for (block = g_current_node_list; block != (code_node *)0x0; block = block->next_block) {
    if (((block->target_labno != 0) && (rec = find_block_final_record(block), rec != (psd *)0x0)) &&
       ((op = rec->op, op == OP_JUMP ||
        (((op == OP_JUMPT || (op == OP_RETURN)) || (op == OP_JUMPF)))))) {
      g_tail_merge_in_list = 1;
      g_last_block = prev_block;
      g_current_block = block;
      rewrite_branch_target_chains(rec);
    }
    prev_block = block;
  }
  return;
}



