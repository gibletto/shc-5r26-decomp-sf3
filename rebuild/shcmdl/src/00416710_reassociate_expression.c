#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_released_nodes
#define g_released_nodes (*(il_node * *)(g_sd + 0x1e4d0))
#undef g_term_list
#define g_term_list (*(term * *)(g_sd + 0x1e4c8))


// entry: 00416710
// name : reassociate_expression
// size : 480
// sig  : il_node * reassociate_expression(il_node * expr)


il_node * __cdecl reassociate_expression(il_node *expr)

{
  uint is_zero;
  int result;
  il_node *piVar1;
  short sVar2;
  il_op child_op;
  ushort line;
  short listno;
  il_op parent_op;
  
  sVar2 = 0;
  parent_op = expr->parent->op;
  switch(expr->op) {
  case IL_MINUS:
    child_op = expr->child->op;
    if (((child_op == IL_ADD) || (child_op == IL_SUB)) &&
       ((parent_op != IL_ADD && (parent_op != IL_SUB)))) {
      sVar2 = 1;
    }
    else if ((child_op == IL_MUL) && (parent_op != IL_MUL)) {
      sVar2 = 2;
    }
    break;
  case IL_ADD:
  case IL_SUB:
    if (((parent_op != IL_ADD) && (parent_op != IL_SUB)) && (parent_op != IL_MINUS)) {
      sVar2 = 1;
    }
    break;
  case IL_MUL:
    if (((parent_op != IL_MUL) && (parent_op != IL_MINUS)) &&
       ((parent_op != IL_SL ||
        ((expr->parent->child->next->op != IL_CONST ||
         (piVar1 = expr->child->next, is_zero = is_const_value(piVar1,0,piVar1->type), is_zero != 0)
         ))))) {
      sVar2 = 2;
    }
    break;
  case IL_B_AND:
    if (parent_op != IL_B_AND) {
      sVar2 = 3;
    }
    break;
  case IL_B_XOR:
    if (parent_op != IL_B_XOR) {
      sVar2 = 5;
    }
    break;
  case IL_B_OR:
    if (parent_op != IL_B_OR) {
      sVar2 = 4;
    }
  }
  if (sVar2 != 0) {
    if (((byte)g_debug_flags & 0x80) != 0) {
      dump_tree(expr,1,s_level_road_004359b0);
    }
    g_term_list = (term *)0x0;
    g_released_nodes = (il_node *)0x0;
    g_negation_count = 0;
    g_reassoc_side_effect = (uint)((expr->flag & 2) != 0);
    operand_index(expr);
    result = collect_reassociation_terms(expr,sVar2,0,expr->op);
    if (result == -1) {
      free_term_list();
    }
    else {
      piVar1 = new_const_node(expr->type & 0xfc,0);
      sVar2 = expr->filn;
      listno = expr->listno;
      line = expr->line;
      replace_node(expr,piVar1);
      free_released_nodes();
      expr = piVar1;
      if (g_term_list != (term *)0x0) {
        if ((g_term_list->op == 'A') && (g_reassoc_side_effect == 0)) {
          move_positive_term_first();
        }
        expr = build_tree_from_terms();
        replace_and_free_node(piVar1,expr);
      }
      expr->filn = sVar2;
      expr->line = line;
      expr->listno = listno;
    }
    if (((byte)g_debug_flags & 0x80) != 0) {
      dump_tree(expr,1,s_level_road_change_0043599c);
    }
  }
  return expr;
}



