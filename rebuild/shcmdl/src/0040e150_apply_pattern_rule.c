#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 0040e150
// name : apply_pattern_rule
// size : 184
// sig  : il_node * apply_pattern_rule(il_node * node)


il_node * __cdecl apply_pattern_rule(il_node *node)

{
  int has_float;
  il_op op;
  
  op = node->op;
  if (*(int *)(&g_pattern_rules + (char)op * 4) != 0) {
    if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 4) != 0) {
      dump_tree(node,1,s_patren_matching_start_004352cc);
    }
    if ((node->op == IL_CAST) || (has_float = tree_has_float(node), has_float == 0)) {
      if (((node->op & IL_NON_F0) != IL_A_ADD) || (((node->child->type ^ node->type) & 0xfc) == 0))
      {
        node = (il_node *)(**(code **)(&g_pattern_rules + (char)op * 4))(node);
      }
    }
    else if (((g_options->option_bits & 2) != 0) && ((node->op == IL_DIV || (node->op == IL_A_DIV)))
            ) {
      if ((((node->child->type ^ node->type) & 0xfc) == 0) &&
         (((node->child->next->type ^ node->type) & 0xfc) == 0)) {
        node = float_div_by_const_to_mul(node);
      }
    }
    if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 4) != 0) {
      dump_tree(node,1,s_patren_matching_end_004352b8);
    }
  }
  return node;
}



