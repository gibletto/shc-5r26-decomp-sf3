#include "decls.h"
#include "imports.h"

// entry: 00429600
// name : emit_float_arith_op
// size : 368
// sig  : void emit_float_arith_op(gen_node * node, ea * src, ea * dst, int reverse)


int __cdecl emit_float_arith_op(gen_node *node,ea *src,ea *dst,int reverse)

{
  ea *dst_copy;
  ea *src_copy;
  il_op node_op;
  
  node_op = node->op;
  if ((((node_op == IL_ADD) || (node_op == IL_A_ADD)) || (node_op == IL_PRI)) || (node_op == IL_POI)
     ) {
    if (reverse == 0) {
      dst_copy = copy_ea(dst);
      src_copy = copy_ea(src);
      emit_psd_for_node(0xb8,-1,'\0','\x02',src_copy,dst_copy,node);
      return;
    }
    dst_copy = copy_ea(dst);
    src_copy = copy_ea(src);
    emit_psd_for_node(0xba,-1,'\0','\x02',src_copy,dst_copy,node);
    return;
  }
  if (((node_op != IL_SUB) && (node_op != IL_A_SUB)) && ((node_op != IL_PRD && (node_op != IL_POD)))
     ) {
    if ((node_op != IL_MUL) && (node_op != IL_A_MUL)) {
      dst_copy = copy_ea(dst);
      src_copy = copy_ea(src);
      emit_psd_for_node(0xbe,-1,'\0','\x02',src_copy,dst_copy,node);
      return;
    }
    dst_copy = copy_ea(dst);
    src_copy = copy_ea(src);
    emit_psd_for_node(0xbc,-1,'\0','\x02',src_copy,dst_copy,node);
    return;
  }
  if (reverse == 0) {
    dst_copy = copy_ea(dst);
    src_copy = copy_ea(src);
    emit_psd_for_node(0xba,-1,'\0','\x02',src_copy,dst_copy,node);
    return;
  }
  dst_copy = copy_ea(dst);
  src_copy = copy_ea(src);
  emit_psd_for_node(0xb8,-1,'\0','\x02',src_copy,dst_copy,node);
  return;
}



