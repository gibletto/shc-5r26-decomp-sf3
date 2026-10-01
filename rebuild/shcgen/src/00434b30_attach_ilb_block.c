#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))


// entry: 00434b30
// name : attach_ilb_block
// size : 318
// sig  : gen_node * attach_ilb_block(gen_node * node)


gen_node * __cdecl attach_ilb_block(gen_node *node)

{
  short full;
  gen_node *pgVar1;
  int *count_slot;
  int count;
  il_op op;
  
  if (0 < g_ilb_depth) {
    do {
      op = g_ilb_cursor->op;
      if ((((((op == IL_FUNC) || (op == IL_BLOCK)) || (op == IL_IF)) ||
           ((op == IL_SWITCH || (op == IL_FOR)))) ||
          ((op == IL_WHILE || ((op == IL_DO || (op == IL_CLABEL)))))) ||
         ((op == IL_DLABEL || (op == IL_GLABEL)))) break;
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      g_ilb_depth = g_ilb_depth + -1;
      g_ilb_cursor = g_ilb_cursor->parent;
    } while (0 < g_ilb_depth);
    if (0 < g_ilb_depth) goto LAB_00434bba;
  }
  report_message_by_code((char *)0x0,0,0x12d7,(char *)0x0);
  stock_exit(0xb);
LAB_00434bba:
  full = ilb_node_operands_full(g_ilb_cursor,g_ilb_depth);
  if (full == 0) {
    pgVar1 = last_operand(g_ilb_cursor);
    if (pgVar1 == (gen_node *)0x0) {
      g_ilb_cursor->child = node;
    }
    else {
      pgVar1->next = node;
    }
    node->parent = g_ilb_cursor;
    g_ilb_cursor = node;
    count_slot = (int *)(g_ilb_depth * 4 + g_ilb_operand_counts);
    count = *count_slot;
    if (count < 0x7f) {
      *count_slot = count + 1;
    }
    g_ilb_depth = g_ilb_depth + 1;
    *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
    return node;
  }
  g_ilb_cursor = g_ilb_cursor->parent;
  *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
  g_ilb_depth = g_ilb_depth + -1;
  pgVar1 = attach_ilb_block(node);
  return pgVar1;
}



