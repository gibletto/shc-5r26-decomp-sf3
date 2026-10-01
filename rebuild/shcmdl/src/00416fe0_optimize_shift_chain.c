#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_released_nodes
#define g_released_nodes (*(il_node * *)(g_sd + 0x1e4d0))
#undef g_term_list
#define g_term_list (*(term * *)(g_sd + 0x1e4c8))


// entry: 00416fe0
// name : optimize_shift_chain
// size : 315
// sig  : il_node * optimize_shift_chain(il_node * node)


il_node * __cdecl optimize_shift_chain(il_node *node)

{
  int rc;
  il_node *piVar1;
  il_node *piVar2;
  il_node *innermost;
  il_op op;
  il_op shift_op;
  
  shift_op = node->op;
  innermost = node;
  if ((((shift_op == IL_SL) || (shift_op == IL_SR)) && (node->parent->op != shift_op)) &&
     ((node->child->op == shift_op && ((node->flag & 2) == 0)))) {
    if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 1) != 0) {
      dump_tree(node,1,s_opt_shift_004359e8);
    }
    g_term_list = (term *)0x0;
    g_released_nodes = (il_node *)0x0;
    op = node->op;
    piVar1 = node;
    while (piVar2 = piVar1, op == shift_op) {
      rc = collect_reassociation_terms(piVar2->child->next,1,0,IL_ADD);
      if (rc == -1) {
        free_term_list();
        return node;
      }
      piVar1 = piVar2->child;
      innermost = piVar2;
      if (piVar1->op != shift_op) break;
      piVar2->cmnexp = g_released_nodes;
      op = piVar1->op;
      g_released_nodes = piVar2;
    }
    piVar1 = new_const_node(innermost->child->next->type & 0xfc,0);
    replace_node(innermost->child->next,piVar1);
    replace_node(node,innermost);
    free_released_nodes();
    if (g_term_list != (term *)0x0) {
      if (g_term_list->op == 'A') {
        move_positive_term_first();
      }
      piVar2 = build_tree_from_terms();
      replace_and_free_node(piVar1,piVar2);
      apply_pattern_rule(piVar2);
    }
    if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 1) != 0) {
      dump_tree(innermost,1,s_opt_shift_chnage_004359d4);
    }
  }
  return innermost;
}



