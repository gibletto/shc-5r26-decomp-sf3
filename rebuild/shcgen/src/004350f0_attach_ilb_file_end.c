#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))


// entry: 004350f0
// name : attach_ilb_file_end
// size : 169
// sig  : gen_node * attach_ilb_file_end(gen_node * node)


gen_node * __cdecl attach_ilb_file_end(gen_node *node)

{
  gen_node *last;
  
  if (-1 < g_ilb_depth) {
    do {
      if (g_ilb_cursor->op == IL_FILE) break;
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      g_ilb_depth = g_ilb_depth + -1;
      g_ilb_cursor = g_ilb_cursor->parent;
    } while (-1 < g_ilb_depth);
    if (-1 < g_ilb_depth) {
      last = last_operand(g_ilb_cursor);
      if (last == (gen_node *)0x0) {
        g_ilb_cursor->child = node;
      }
      else {
        last->next = node;
      }
      node->parent = g_ilb_cursor;
      g_ilb_cursor = node;
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0xffffffff;
      g_ilb_depth = g_ilb_depth + 1;
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      return node;
    }
  }
  return (gen_node *)0x0;
}



