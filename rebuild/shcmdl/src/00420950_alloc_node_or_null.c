#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_node_free_list
#define g_node_free_list (*(il_node * *)(g_sd + 0x26864))


// entry: 00420950
// name : alloc_node_or_null
// size : 48
// sig  : il_node * alloc_node_or_null(void)


il_node * alloc_node_or_null(void)

{
  il_node *dst;
  
  dst = g_node_free_list;
  if (g_node_free_list == (il_node *)0x0) {
    return (il_node *)0x0;
  }
  g_node_free_list = g_node_free_list->next;
  clear_bytes((char *)dst,0x68);
  dst->nodes = '\x01';
  return dst;
}



