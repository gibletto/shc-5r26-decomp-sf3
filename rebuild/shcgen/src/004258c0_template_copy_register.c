#include "decls.h"
#include "imports.h"

// entry: 004258c0
// name : template_copy_register
// size : 98
// sig  : short template_copy_register(gen_node * node, uchar opnd_code)


short __cdecl template_copy_register(gen_node *node,uchar opnd_code)

{
  short reg;
  
  reg = -1;
  switch(opnd_code) {
  case '\x03':
    reg = (short)node->desc->regs_2c[0];
    break;
  case '\x04':
    reg = (short)node->desc->regs_2c[1];
    break;
  case '\x05':
    reg = 0;
    break;
  case '\v':
    reg = 0x10;
  }
  if (((reg < 0) || (3 < reg)) && ((reg < 0x10 || (0x13 < reg)))) {
    reg = -1;
  }
  return reg;
}



