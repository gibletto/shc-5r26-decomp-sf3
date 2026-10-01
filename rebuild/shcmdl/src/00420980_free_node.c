#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_node_free_list
#define g_node_free_list (*(il_node * *)(g_sd + 0x26864))


// entry: 00420980
// name : free_node
// size : 19
// sig  : void free_node(il_node * node)


int __cdecl free_node(il_node *node)

{
  node->next = g_node_free_list;
  g_node_free_list = node;
  return;
}



