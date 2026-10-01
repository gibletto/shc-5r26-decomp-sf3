#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))


// entry: 004349a0
// name : begin_ilb_file
// size : 122
// sig  : gen_node * begin_ilb_file(gen_node * node)


gen_node * __cdecl begin_ilb_file(gen_node *node)

{
  short i;
  int ix;
  il_op op;
  
  if (g_ilb_cursor != (gen_node *)0x0) {
    op = g_ilb_cursor->op;
    while ((op != IL_FILE && (0 < g_ilb_depth))) {
      *(undefined4 *)(g_ilb_operand_counts + g_ilb_depth * 4) = 0;
      g_ilb_depth = g_ilb_depth + -1;
      g_ilb_cursor = g_ilb_cursor->parent;
      op = g_ilb_cursor->op;
    }
    unlink_and_free_subtree(g_ilb_cursor);
  }
  i = 0;
  g_ilb_depth = 0;
  do {
    ix = (int)i;
    i = i + 1;
    *(undefined4 *)(g_ilb_operand_counts + ix * 4) = 0;
  } while (i < 0x800);
  g_ilb_cursor = node;
  return node;
}



