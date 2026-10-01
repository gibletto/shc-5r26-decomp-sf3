#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_node_free_list
#define g_inline_node_free_list (*(il_node * *)(g_sd + 0x1e784))


// entry: 004211b0
// name : alloc_inline_node
// size : 48
// sig  : il_node * alloc_inline_node(void)


il_node * __cdecl alloc_inline_node(void)

{
  il_node *dst;
  
  dst = g_inline_node_free_list;
  if (g_inline_node_free_list == (il_node *)0x0) {
    return (il_node *)0x0;
  }
  g_inline_node_free_list = g_inline_node_free_list->next;
  clear_bytes((char *)dst,0x68);
  dst->nodes = '\x01';
  return dst;
}



