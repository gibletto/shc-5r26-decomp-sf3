#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_gen_node_free_head
#define g_gen_node_free_head (*(gen_node * *)(g_sd + 0x1e62c))
#undef g_gen_node_free_tail
#define g_gen_node_free_tail (*(gen_node * *)(g_sd + 0x1e628))
#undef g_ilb_operand_counts
#define g_ilb_operand_counts (*(void * *)(g_sd + 0x1ffa0))


// entry: 00433280
// name : init_gen_node_pool
// size : 196
// sig  : short init_gen_node_pool(short node_size, short count)


short __cdecl init_gen_node_pool(short node_size,short count)

{
  gen_node *last;
  gen_node *fresh;
  short n;
  int size;
  
  if ((0x27 < node_size) && (0 < count)) {
    size = (int)node_size;
    g_gen_node_size = size;
    last = stock_calloc(1,size);
    g_gen_node_free_head = last;
    if (last == (gen_node *)0x0) {
      return -1;
    }
    n = 1;
    if (1 < count) {
      do {
        fresh = stock_calloc(1,size);
        last->next = fresh;
        if (fresh == (gen_node *)0x0) {
          return -1;
        }
        last->parent = (gen_node *)0x0;
        last->child = (gen_node *)0x0;
        n = n + 1;
        last = last->next;
      } while (n < count);
    }
    last->next = (gen_node *)0x0;
    last->parent = (gen_node *)0x0;
    last->child = (gen_node *)0x0;
    g_gen_node_free_tail = last;
    g_ilb_operand_counts = stock_calloc(0x800,4);
    return -(ushort)(g_ilb_operand_counts == (void *)0x0);
  }
  return -1;
}



