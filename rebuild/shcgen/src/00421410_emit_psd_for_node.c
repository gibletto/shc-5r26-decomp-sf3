#include "decls.h"
#include "imports.h"

// entry: 00421410
// name : emit_psd_for_node
// size : 210
// sig  : void emit_psd_for_node(ushort op, char tmp, char flag_20, uchar size, ea * src, ea * dst, gen_node * node)


int __cdecl emit_psd_for_node(ushort op,char tmp,char flag_20,uchar size,ea *src,ea *dst,gen_node *node)

{
  byte type_bits;
  uchar misc;
  
  if ((node != (gen_node *)0x0) &&
     (((node->type & 2) != 0 ||
      ((type_bits = (node->desc->dest).type, (type_bits & 0x1f) != 0 && ((type_bits & 0x80) != 0))))
     )) {
    if (src != (ea *)0x0) {
      type_bits = src->type & 0x1f;
      if ((type_bits == 2) || (type_bits == 8)) {
        src->type = src->type | 0x80;
      }
    }
    if (dst != (ea *)0x0) {
      type_bits = dst->type & 0x1f;
      if ((type_bits == 2) || (type_bits == 8)) {
        dst->type = dst->type | 0x80;
      }
    }
  }
  if (((node == (gen_node *)0x0) ||
      ((((node->type & 4) == 0 && (type_bits = node->type & 0xe0, type_bits != 0x80)) &&
       (type_bits != 0x40)))) ||
     ((((op != 0x27 && (op != 0x1800)) && (op != 0x1900)) && (op != 0x1a00)))) {
    misc = '\0';
  }
  else {
    misc = '@';
  }
  emit_psd_instruction(op,tmp,flag_20,size,misc,src,dst);
  return;
}



