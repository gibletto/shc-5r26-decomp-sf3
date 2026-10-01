#include "decls.h"
#include "imports.h"

// entry: 0041cfa0
// name : select_copy_routine
// size : 162
// sig  : short select_copy_routine(gen_node * node)


short __cdecl select_copy_routine(gen_node *node)

{
  short local_2;
  node_desc *desc;
  
  desc = node->desc;
  if (node->op != IL_ARG) {
    if ((desc->flags2 & 1) == 0) {
      return 0x12;
    }
    if (node->val < 0x41) {
      return 0xb0 - (ushort)((node->val & 7U) == 0);
    }
    return 0x11;
  }
  if (desc->builtin == '\x16') {
    return ((desc->flags2 & 1) == 0) + 0x47;
  }
  if (desc->builtin != '\x17') {
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  }
  return ((desc->flags2 & 1) == 0) + 0x49;
}



