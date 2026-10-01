#include "decls.h"
#include "imports.h"

// entry: 004294f0
// name : emit_add_constant_minus_one
// size : 151
// sig  : void emit_add_constant_minus_one(gen_node * node, ea * imm, ea * dst, ea * * temps)


int __cdecl emit_add_constant_minus_one(gen_node *node,ea *imm,ea *dst,ea **temps)

{
  ea *peVar1;
  int new_disp;
  ea *peVar2;
  gen_node *pgVar3;
  
  peVar1 = copy_ea(imm);
  new_disp = peVar1->disp + -1;
  peVar1->disp = new_disp;
  if ((new_disp < 0x80) && (-1 < new_disp)) {
    pgVar3 = (gen_node *)0x0;
    peVar2 = copy_ea(dst);
    emit_psd_for_node(0x60,-1,'\0','\x02',peVar1,peVar2,pgVar3);
    return;
  }
  pgVar3 = (gen_node *)0x0;
  peVar2 = copy_ea(*temps);
  emit_psd_for_node(0x2a,-1,'\0','\x02',peVar1,peVar2,pgVar3);
  pgVar3 = (gen_node *)0x0;
  peVar1 = copy_ea(dst);
  peVar2 = copy_ea(*temps);
  emit_psd_for_node(0x60,-1,'\0','\x02',peVar2,peVar1,pgVar3);
  return;
}



