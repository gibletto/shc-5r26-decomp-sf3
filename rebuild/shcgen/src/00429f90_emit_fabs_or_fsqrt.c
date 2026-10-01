#include "decls.h"
#include "imports.h"

// entry: 00429f90
// name : emit_fabs_or_fsqrt
// size : 94
// sig  : void emit_fabs_or_fsqrt(gen_node * node, ea * operand)


int __cdecl emit_fabs_or_fsqrt(gen_node *node,ea *operand)

{
  ea *operand_copy;
  ea *peVar1;
  char builtin_no;
  
  builtin_no = node->desc->builtin;
  if ((builtin_no != '\x1f') && (builtin_no != '0')) {
    peVar1 = (ea *)0x0;
    operand_copy = copy_ea(operand);
    emit_psd_for_node(0xd4,-1,'\0','\x02',operand_copy,peVar1,node);
    return;
  }
  peVar1 = (ea *)0x0;
  operand_copy = copy_ea(operand);
  emit_psd_for_node(0xd2,-1,'\0','\x02',operand_copy,peVar1,node);
  return;
}



