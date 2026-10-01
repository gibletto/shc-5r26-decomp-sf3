#include "decls.h"
#include "imports.h"

// entry: 0041d080
// name : select_conversion_routine
// size : 278
// sig  : short select_conversion_routine(gen_node * from, gen_node * to)


short __cdecl select_conversion_routine(gen_node *from,gen_node *to)

{
  byte type_bits;
  short local_2;
  
  type_bits = from->type;
  if ((type_bits & 0xf8) == 0x30) {
    if ((((to->type & 4) == 0) && (type_bits = to->type & 0xe0, type_bits != 0x80)) &&
       (type_bits != 0x40)) {
      return 0x32;
    }
    return 0x34;
  }
  if ((type_bits & 0xf8) == 0x28) {
    if ((((to->type & 4) == 0) && (type_bits = to->type & 0xe0, type_bits != 0x80)) &&
       (type_bits != 0x40)) {
      return 0x31;
    }
    return 0x33;
  }
  if ((((type_bits & 4) == 0) && ((type_bits & 0xe0) != 0x80)) && ((type_bits & 0xe0) != 0x40)) {
    type_bits = to->type & 0xf8;
    if (type_bits == 0x30) {
      return 0x36;
    }
    if (type_bits == 0x28) {
      return 0x35;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  }
  type_bits = to->type & 0xf8;
  if (type_bits == 0x30) {
    return 0x38;
  }
  if (type_bits == 0x28) {
    return 0x37;
  }
  report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  return local_2;
}



