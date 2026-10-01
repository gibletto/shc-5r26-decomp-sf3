#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))
#undef g_unlink_parent
#define g_unlink_parent (*(gen_node * *)(g_sd + 0x1ff9c))


// entry: 00433490
// name : free_gen_node_subtree
// size : 100
// sig  : void free_gen_node_subtree(gen_node * node)


int __cdecl free_gen_node_subtree(gen_node *node)

{
  gen_node *child;
  gen_node *next_child;
  
  if ((node->parent == (gen_node *)0x0) && (node->op == IL_FILE)) {
    g_ilb_cursor = (gen_node *)0x0;
  }
  if (node == g_ilb_cursor) {
    g_ilb_cursor = g_unlink_parent;
  }
  child = node->child;
  next_child = (gen_node *)0x0;
  if (child != (gen_node *)0x0) {
    next_child = child->next;
  }
  free_gen_node(node);
  if (child != (gen_node *)0x0) {
    for (; free_gen_node_subtree(child), next_child != (gen_node *)0x0;
        next_child = next_child->next) {
      child = next_child;
    }
  }
  return;
}



