#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_gen_node_exhausted_handler
#define g_gen_node_exhausted_handler (*(int (**)())(g_sd + 0x1ff94))
#undef g_gen_node_free_head
#define g_gen_node_free_head (*(gen_node * *)(g_sd + 0x1e62c))
#undef g_gen_node_free_tail
#define g_gen_node_free_tail (*(gen_node * *)(g_sd + 0x1e628))


// entry: 00433580
// name : alloc_gen_node
// size : 53
// sig  : gen_node * alloc_gen_node(il_op op)


gen_node * __cdecl alloc_gen_node(il_op op)

{
  gen_node *node;
  gen_node **next_slot;
  
  node = g_gen_node_free_head;
  if (g_gen_node_free_head == g_gen_node_free_tail) {
    (*g_gen_node_exhausted_handler)();
    return (gen_node *)0x0;
  }
  next_slot = &g_gen_node_free_head->next;
  g_gen_node_free_head = g_gen_node_free_head->next;
  *next_slot = (gen_node *)0x0;
  node->op = op;
  return node;
}



