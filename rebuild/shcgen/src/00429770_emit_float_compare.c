#include "decls.h"
#include "imports.h"

// entry: 00429770
// name : emit_float_compare
// size : 114
// sig  : void emit_float_compare(gen_node * node, ea * left, ea * right)


int __cdecl emit_float_compare(gen_node *node,ea *left,ea *right)

{
  ea *dst_copy;
  ea *src_copy;
  
  if ((node->op != IL_GT) && (node->op != IL_LE)) {
    dst_copy = copy_ea(left);
    src_copy = copy_ea(right);
    emit_psd_for_node(0xc1,-1,'\0','\x02',src_copy,dst_copy,node);
    return;
  }
  dst_copy = copy_ea(right);
  src_copy = copy_ea(left);
  emit_psd_for_node(0xc1,-1,'\0','\x02',src_copy,dst_copy,node);
  return;
}



