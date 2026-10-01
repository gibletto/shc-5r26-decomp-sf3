#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_released_nodes
#define g_released_nodes (*(il_node * *)(g_sd + 0x1e4d0))


// entry: 00416f80
// name : free_released_nodes
// size : 88
// sig  : void free_released_nodes(void)


int __cdecl free_released_nodes(void)

{
  il_node *node;
  il_node *next;
  
  node = g_released_nodes;
  while (node != (il_node *)0x0) {
    next = node->cmnexp;
    if (((g_debug_flags & 0x100) != 0) || ((g_debug_flags & 0x80) != 0)) {
      FID_conflict__wprintf
                (s_relnode__08x__name__s_004359bc,node,(&g_op_names_upper)[(char)node->op]);
    }
    free_node(node);
    node = next;
  }
  return;
}



