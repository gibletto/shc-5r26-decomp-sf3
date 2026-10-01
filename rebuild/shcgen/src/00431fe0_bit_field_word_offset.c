#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00431fe0
// name : bit_field_word_offset
// size : 65
// sig  : int bit_field_word_offset(gen_node * node)


int __cdecl bit_field_word_offset(gen_node *node)

{
  int bit_pos;
  node_desc *desc;
  
  if (g_request->unknown_028[2] == '\0') {
    bit_pos = (int)node->desc->bit_offset;
  }
  else {
    desc = node->desc;
    bit_pos = node_value_size(node);
    bit_pos = (bit_pos * 8 - (int)desc->bit_offset) - (int)desc->bit_width;
  }
  return ((int)(bit_pos + (bit_pos >> 0x1f & 0xfU)) >> 4) * 2;
}



