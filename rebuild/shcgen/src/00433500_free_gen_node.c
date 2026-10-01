#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_gen_node_free_tail
#define g_gen_node_free_tail (*(gen_node * *)(g_sd + 0x1e628))


// entry: 00433500
// name : free_gen_node
// size : 115
// sig  : void free_gen_node(gen_node * node)


int __cdecl free_gen_node(gen_node *node)

{
  uint words;
  uint extra;
  node_desc **cursor;
  
  g_gen_node_free_tail->next = node;
  g_gen_node_free_tail = node;
  node->symx = 0;
  node->op = IL_FILE;
  node->call_06 = 0;
  node->type = '\0';
  node->bit_offset = '\0';
  node->bit_width = '\0';
  node->filn = 0;
  node->parent = (gen_node *)0x0;
  node->line = 0;
  node->child = (gen_node *)0x0;
  node->lreg = 0;
  node->next = (gen_node *)0x0;
  node->listno = 0;
  node->val = 0;
  node->val2 = 0;
  node->val3 = 0;
  if ((0x28 < g_gen_node_size) && (extra = g_gen_node_size - 0x28, 0 < (int)extra)) {
    cursor = &node->desc;
    for (words = extra >> 2; words != 0; words = words - 1) {
      *cursor = (node_desc *)0x0;
      cursor = cursor + 1;
    }
    for (extra = extra & 3; extra != 0; extra = extra - 1) {
      *(undefined1 *)cursor = 0;
      cursor = (node_desc **)((int)cursor + 1);
    }
  }
  return;
}



