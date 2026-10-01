#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00431f90
// name : bit_field_byte_offset
// size : 72
// sig  : int bit_field_byte_offset(gen_node * node)


int __cdecl bit_field_byte_offset(gen_node *node)

{
  int bit_pos;
  node_desc *desc;
  
  if (g_request->unknown_028[2] == '\0') {
    bit_pos = (int)node->desc->bit_offset;
    return (int)(bit_pos + (bit_pos >> 0x1f & 7U)) >> 3;
  }
  desc = node->desc;
  bit_pos = node_value_size(node);
  bit_pos = (bit_pos * 8 - (int)desc->bit_offset) - (int)desc->bit_width;
  return (int)(bit_pos + (bit_pos >> 0x1f & 7U)) >> 3;
}



