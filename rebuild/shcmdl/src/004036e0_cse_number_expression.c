#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004036e0
// name : cse_number_expression
// size : 456
// sig  : void cse_number_expression(il_node * node)


int __cdecl cse_number_expression(il_node *node)

{
  byte type_class;
  int is_builtin;
  il_node *child;
  char in_builtin;
  il_op op;
  short symx;
  
  in_builtin = g_in_builtin_call;
  if ((node->flag2 & 1) == 0) {
    if ((node->op == IL_GOTO) || (node->op == IL_GLABEL)) {
      g_cse_has_goto_or_label = '\x01';
    }
    op = node->op;
    if ((((op != IL_IF) && (op != IL_FOR)) && (op != IL_WHILE)) &&
       ((op != IL_DO && (op != IL_SWITCH)))) {
      if (((&g_op_class)[(char)op] & 0x80) != 0) {
        cse_number_conditional(node);
        return;
      }
      for (child = node->child; g_in_builtin_call = in_builtin, child != (il_node *)0x0;
          child = child->next) {
        if (((in_builtin == '\0') && (node->op == IL_CALL)) &&
           ((node->child->op == IL_ID &&
            ((symx = node->child->symx, -1 < symx &&
             (is_builtin = is_builtin_name(g_symtab[symx].name), is_builtin != 0)))))) {
          g_in_builtin_call = '\x01';
        }
        cse_number_expression(child);
      }
      op = node->op;
      switch((&g_op_class)[(char)op]) {
      case 1:
        if (in_builtin == '\0') {
          cse_number_constant(node);
          return;
        }
        cse_clear_value_number(node);
        return;
      case 2:
        cse_number_identifier(node);
        return;
      default:
        cse_clear_value_number(node);
        return;
      case 4:
      case 8:
        goto switchD_004037c6_caseD_4;
      case 0x10:
        if ((op == IL_ASTER) &&
           ((type_class = node->type & 0xf0, type_class == 0x80 || (type_class == 0x90)))) {
          cse_number_operator(node);
          return;
        }
        cse_clear_value_number(node);
        return;
      }
    }
    g_cse_nesting = g_cse_nesting + '\x01';
    for (child = node->child; child != (il_node *)0x0; child = child->next) {
      cse_number_expression(child);
    }
    g_cse_nesting = g_cse_nesting + -1;
  }
  return;
switchD_004037c6_caseD_4:
  if ((op != IL_NOT) &&
     (((((op != IL_CAST || ((node->type & 0xe0) != 0)) || (node->child->op != IL_ID)) ||
       ((type_class = node->child->type & 0xf8, type_class != 8 && (type_class != 0)))) ||
      ((op = node->parent->op, op != IL_MUL && (op != IL_A_MUL)))))) {
    cse_number_operator(node);
    return;
  }
  cse_clear_value_number(node);
  return;
}



