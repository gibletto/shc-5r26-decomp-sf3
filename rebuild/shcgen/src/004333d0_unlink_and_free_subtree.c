#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))
#undef g_unlink_parent
#define g_unlink_parent (*(gen_node * *)(g_sd + 0x1ff9c))


// entry: 004333d0
// name : unlink_and_free_subtree
// size : 184
// sig  : void unlink_and_free_subtree(gen_node * node)


int __cdecl unlink_and_free_subtree(gen_node *node)

{
  int position;
  gen_node *pgVar1;
  
  if (node != (gen_node *)0x0) {
    g_unlink_parent = node->parent;
    if (g_unlink_parent == (gen_node *)0x0) {
      g_unlink_parent = (gen_node *)0x0;
    }
    else {
      position = operand_position(node);
      if (position < 2) {
        if (node->next == (gen_node *)0x0) {
          g_unlink_parent->child = (gen_node *)0x0;
        }
        else {
          g_unlink_parent->child = node->next;
        }
      }
      else {
        pgVar1 = find_previous_operand(node);
        if (node->next == (gen_node *)0x0) {
          pgVar1->next = (gen_node *)0x0;
        }
        else {
          pgVar1->next = node->next;
        }
      }
    }
    free_gen_node_subtree(node);
    if ((g_ilb_cursor == g_unlink_parent) && (g_unlink_parent != (gen_node *)0x0)) {
      g_ilb_depth = 0;
      pgVar1 = g_unlink_parent->parent;
      while (pgVar1 != (gen_node *)0x0) {
        g_ilb_depth = g_ilb_depth + 1;
        g_unlink_parent = g_unlink_parent->parent;
        pgVar1 = g_unlink_parent->parent;
      }
    }
    g_unlink_parent = (gen_node *)0x0;
  }
  return;
}



