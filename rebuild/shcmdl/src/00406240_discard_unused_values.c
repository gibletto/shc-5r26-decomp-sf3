#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00406240
// name : discard_unused_values
// size : 434
// sig  : il_node * discard_unused_values(il_node * node)


il_node * __cdecl discard_unused_values(il_node *node)

{
  ushort uVar1;
  il_node *result;
  il_node *kept;
  byte bVar2;
  uint side_effects;
  il_op op;
  il_node *operand;
  
  uVar1 = node->flag & 0x20;
  result = node;
  if ((((uVar1 == 0) || (node->op == IL_COMMA)) &&
      ((op = node->op, (char)op < '0' || ('=' < (char)op)))) &&
     ((((char)op < 'P' || ('_' < (char)op)) && ((node->type & 2) == 0)))) {
    side_effects = 0;
    bVar2 = 0;
    kept = node->child;
    for (operand = kept; operand != (il_node *)0x0; operand = operand->next) {
      if ((operand->flag & 0x42) != 0) {
        side_effects = side_effects | 1 << (bVar2 & 0x1f);
      }
      bVar2 = bVar2 + 1;
    }
    bVar2 = (uVar1 == 0) - 1U & 2;
    if (side_effects == 0 && bVar2 == 0) {
      if ((((g_options->warnings == '\x01') && (uVar1 = node->line, uVar1 != 0)) && (op != IL_NULL))
         && ((g_suppress_no_effect_warning == '\0' && (g_last_warned_line != uVar1)))) {
        g_last_warned_line = uVar1;
        report_message(10,node,(char *)0x0);
      }
      result = new_node(IL_NULL,node->type & 0xfc);
      replace_and_free_node(node,result);
    }
    else if (((op != IL_AND) && (op != IL_OR)) && (op != IL_COND)) {
      if (((side_effects & 1) == 0) || ((side_effects & 2) == 0 && bVar2 == 0)) {
        if ((side_effects & 1) == 0) {
          kept = kept->next;
        }
        result = copy_tree(0,kept);
        replace_node(node,result);
        free_tree(node);
      }
      else {
        node->op = IL_COMMA;
      }
    }
  }
  op = result->op;
  if ((((char)op < '0') || ('=' < (char)op)) && (((char)op < 'P' || ('_' < (char)op)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 2;
  }
  uVar1 = node->flag | uVar1;
  node->flag = uVar1;
  node->flag = ((result->type & 2) == 0) - 1 & 0x40 | uVar1;
  for (operand = result->child; operand != (il_node *)0x0; operand = operand->next) {
    uVar1 = (byte)operand->flag & 2 | result->flag;
    result->flag = uVar1;
    result->flag = (byte)operand->flag & 0x40 | uVar1;
  }
  return result;
}



