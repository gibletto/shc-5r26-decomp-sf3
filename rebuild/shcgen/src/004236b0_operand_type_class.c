#include "decls.h"
#include "imports.h"

// entry: 004236b0
// name : operand_type_class
// size : 127
// sig  : short operand_type_class(gen_node * node)


short __cdecl operand_type_class(gen_node *node)

{
  short local_2;
  
  switch(node->type & 0xf8) {
  case 0:
  case 8:
    return 0;
  case 0x10:
  case 0x18:
    return 1;
  default:
    report_codegen_message(0x1226,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case 0x28:
    return 3;
  case 0x30:
  case 0x38:
    return 4;
  case 0x40:
  case 0x48:
  case 0x80:
  case 0x88:
  case 0x90:
    return 2;
  }
}



