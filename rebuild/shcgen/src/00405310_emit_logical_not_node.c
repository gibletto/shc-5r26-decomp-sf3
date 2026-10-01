#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00405310
// name : emit_logical_not_node
// size : 129
// sig  : void emit_logical_not_node(gen_node * node)


int __cdecl emit_logical_not_node(gen_node *node)

{
  ea *src;
  ea *dst;
  gen_node *child;
  byte desc_flags;
  
  child = node->child;
  desc_flags = node->desc->flags3;
  if (((desc_flags & 0x80) != 0) && ((desc_flags & 8) != 0)) {
    emit_node_code(child);
    return;
  }
  emit_node_operands_and_template(node);
  if ((node->desc->false_label != 0) && (((child->type & 0xf8) == 0x30 && (g_request->cpu != 4)))) {
    src = copy_ea(&g_ea_imm1);
    dst = copy_ea((ea *)&g_ea_r0);
    emit_psd_for_node(0x82,-1,'\0','\x02',src,dst,(gen_node *)0x0);
  }
  return;
}



