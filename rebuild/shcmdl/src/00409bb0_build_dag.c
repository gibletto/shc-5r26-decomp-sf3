#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00409bb0
// name : build_dag
// size : 321
// sig  : void build_dag(il_node * node)


int __cdecl build_dag(il_node *node)

{
  byte type_class;
  int is_builtin;
  il_node *child;
  char in_builtin;
  short symx;
  
  in_builtin = g_in_builtin_call;
  if (((&g_op_class)[(char)node->op] & 0x80) != 0) {
    dag_conditional(node);
    return;
  }
  for (child = node->child; g_in_builtin_call = in_builtin, child != (il_node *)0x0;
      child = child->next) {
    if ((((in_builtin == '\0') && (node->op == IL_CALL)) && (node->child->op == IL_ID)) &&
       ((symx = node->child->symx, -1 < symx &&
        (is_builtin = is_builtin_name(g_symtab[symx].name), is_builtin != 0)))) {
      g_in_builtin_call = '\x01';
    }
    build_dag(child);
  }
  switch((&g_op_class)[(char)node->op]) {
  case 1:
    if (in_builtin == '\0') {
      dag_constant(node);
      return;
    }
    clear_common_links(node);
    return;
  case 2:
    dag_variable(node);
    return;
  default:
    clear_common_links(node);
    return;
  case 4:
  case 8:
    dag_operator(node);
    return;
  case 0x10:
    break;
  case 0x20:
    dag_assignment(node);
    return;
  case 0x40:
    clear_common_links(node);
    invalidate_memory_leaf_values();
    free_dag_node_list();
    return;
  }
  if ((node->op == IL_ASTER) &&
     ((type_class = node->type & 0xf0, type_class == 0x80 || (type_class == 0x90)))) {
    dag_operator(node);
    return;
  }
  dag_indirection(node);
  return;
}



