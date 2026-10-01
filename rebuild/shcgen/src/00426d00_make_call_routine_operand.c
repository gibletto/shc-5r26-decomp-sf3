#include "decls.h"
#include "imports.h"

// entry: 00426d00
// name : make_call_routine_operand
// size : 172
// sig  : ea * make_call_routine_operand(uint opnd_code, gen_node * node)


ea * __cdecl make_call_routine_operand(uint opnd_code,gen_node *node)

{
  gen_node *from;
  short labno;
  ea *operand;
  gen_node *to;
  
  to = (gen_node *)0x0;
  labno = (short)g_operand_desc_table[opnd_code & 0xffff];
  from = node->child;
  if (from != (gen_node *)0x0) {
    to = from->next;
  }
  switch(opnd_code & 0xffff) {
  case 0xfe:
    labno = select_arithmetic_routine(node);
    break;
  case 0xff:
    labno = select_conversion_routine(from,node);
    break;
  case 0x100:
    labno = select_conversion_routine(to,from);
    break;
  case 0x101:
    labno = select_bitfield_routine(0x101,from->type);
    break;
  case 0x102:
    labno = select_bitfield_routine(0x102,node->type);
    break;
  case 0x103:
    labno = select_copy_routine(node);
    break;
  case 0x104:
    labno = select_conversion_routine(from,to);
    break;
  case 0x105:
    labno = select_shift_routine(node);
  }
  operand = new_label_operand(labno);
  return operand;
}



