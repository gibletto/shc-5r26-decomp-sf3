#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))


// entry: 00434a20
// name : attach_ilb_function
// size : 272
// sig  : gen_node * attach_ilb_function(gen_node * node)


gen_node * __cdecl attach_ilb_function(gen_node *node)

{
  gen_node *last;
  int *count_slot;
  int count;
  
  if (0 < g_ilb_depth) {
    do {
      if ((g_ilb_cursor->op == IL_FUNC) || (g_ilb_cursor->op == IL_ASM)) break;
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      g_ilb_depth = g_ilb_depth + -1;
      g_ilb_cursor = g_ilb_cursor->parent;
    } while (0 < g_ilb_depth);
    if (0 < g_ilb_depth) {
      g_ilb_cursor->next = node;
      node->parent = g_ilb_cursor->parent;
      g_ilb_cursor = node;
      count_slot = (int *)(g_ilb_operand_counts + -4 + g_ilb_depth * 4);
      count = *count_slot;
      if (count < 0x7f) {
        *count_slot = count + 1;
      }
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      return node;
    }
  }
  if (g_ilb_cursor->op == IL_FILE) {
    last = last_operand(g_ilb_cursor);
    if (last == (gen_node *)0x0) {
      g_ilb_cursor->child = node;
    }
    else {
      last->next = node;
    }
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



