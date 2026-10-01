#include "decls.h"
#include "imports.h"

// entry: 00429590
// name : emit_shad_right_by_constant
// size : 107
// sig  : void emit_shad_right_by_constant(gen_node * node, ea * imm, ea * dst, ea * * temps)


int __cdecl emit_shad_right_by_constant(gen_node *node,ea *imm,ea *dst,ea **temps)

{
  ea *peVar1;
  ea *temp_copy;
  gen_node *pgVar2;
  
  peVar1 = copy_ea(imm);
  pgVar2 = (gen_node *)0x0;
  peVar1->disp = -peVar1->disp;
  temp_copy = copy_ea(*temps);
  emit_psd_for_node(0x2a,-1,'\0','\x02',peVar1,temp_copy,pgVar2);
  pgVar2 = (gen_node *)0x0;
  peVar1 = copy_ea(dst);
  temp_copy = copy_ea(*temps);
  emit_psd_for_node(0x48,-1,'\0','\x02',temp_copy,peVar1,pgVar2);
  return;
}



