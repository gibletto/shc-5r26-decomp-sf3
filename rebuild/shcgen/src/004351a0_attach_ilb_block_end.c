#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))


// entry: 004351a0
// name : attach_ilb_block_end
// size : 282
// sig  : gen_node * attach_ilb_block_end(gen_node * node)


gen_node * __cdecl attach_ilb_block_end(gen_node *node)

{
  short full;
  gen_node *pgVar1;
  
  if (0 < g_ilb_depth) {
    do {
      if (g_ilb_cursor->op == IL_BLOCK) break;
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      g_ilb_depth = g_ilb_depth + -1;
      g_ilb_cursor = g_ilb_cursor->parent;
    } while (0 < g_ilb_depth);
    if (0 < g_ilb_depth) {
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
        *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0xffffffff;
        g_ilb_depth = g_ilb_depth + 1;
        *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
        if (g_ilb_cursor->parent->parent->op == IL_FUNC) {
          *(undefined4 *)(g_ilb_operand_counts + -8 + g_ilb_depth * 4) = 0xffffffff;
        }
        return node;
      }
      g_ilb_cursor = g_ilb_cursor->parent;
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      g_ilb_depth = g_ilb_depth + -1;
      pgVar1 = attach_ilb_block_end(node);
      return pgVar1;
    }
  }
  return (gen_node *)0x0;
}



