#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041d130
// name : count_expression_tree
// size : 402
// sig  : void count_expression_tree(il_node * node, bblock * block)


int __cdecl count_expression_tree(il_node *node,bblock *block)

{
  int is_builtin;
  il_node *child;
  il_op child_op;
  char saved_in_builtin;
  short symx;
  
  node->cse_head = (il_node *)0x0;
  node->cse_next = (il_node *)0x0;
  saved_in_builtin = g_in_builtin_call;
  if (((&g_op_class)[(char)node->op] & 0x80) != 0) {
    count_conditional_operands(node,block);
    return;
  }
  for (child = node->child; g_in_builtin_call = saved_in_builtin, child != (il_node *)0x0;
      child = child->next) {
    if ((((saved_in_builtin == '\0') && (node->op == IL_CALL)) && (node->child->op == IL_ID)) &&
       ((symx = node->child->symx, -1 < symx &&
        (is_builtin = is_builtin_name(g_symtab[symx].name), is_builtin != 0)))) {
      g_in_builtin_call = '\x01';
    }
    count_expression_tree(child,block);
  }
  switch((&g_op_class)[(char)node->op]) {
  case 1:
    break;
  case 2:
    count_variable_reference(node,block);
    return;
  default:
    cse_clear_node(node);
    return;
  case 4:
  case 8:
    cse_number_arith_expr(node,block);
    return;
  case 0x10:
    if (node->op != IL_ASTER) {
      cse_number_memory_ref(node,block);
      return;
    }
    cse_clear_node(node);
    return;
  case 0x20:
    cse_note_assignment(node);
    return;
  case 0x40:
    child_op = node->child->op;
    if ((child_op == IL_ASTER) ||
       (((child_op == IL_ID && (symx = node->child->symx, -1 < symx)) &&
        (is_builtin = is_memory_safe_builtin(g_symtab[symx].name), is_builtin == 0)))) {
      g_memory_clobbered = 1;
    }
    cse_clear_node(node);
    return;
  }
  if (saved_in_builtin == '\0') {
    count_common_expression(node,block);
    return;
  }
  cse_clear_node(node);
  return;
}



