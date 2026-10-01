#include "decls.h"
#include "imports.h"

// entry: 00411b40
// name : emit_movt_result
// size : 200
// sig  : void emit_movt_result(gen_node * node, char t_is_value, ea * reg)


int __cdecl emit_movt_result(gen_node *node,char t_is_value,ea *reg)

{
  ea *first;
  ea *second;
  
  first = copy_ea(reg);
  emit_psd_for_node(0x42,-1,'\0','\x02',first,(ea *)0x0,(gen_node *)0x0);
  if (t_is_value == '\0') {
    if (reg->base == '\0') {
      first = new_ea_operand_with_flags('\a',-1,-1,1,'\0',(label_ref *)0x0);
      second = copy_ea(reg);
      emit_psd_for_node(0x82,-1,'\0','\x02',first,second,(gen_node *)0x0);
      return;
    }
    first = new_ea_operand_with_flags('\a',-1,-1,-1,'\0',(label_ref *)0x0);
    second = copy_ea(reg);
    emit_psd_for_node(0x60,-1,'\0','\x02',first,second,(gen_node *)0x0);
    first = copy_ea(reg);
    second = copy_ea(reg);
    emit_psd_for_node(0x78,-1,'\0','\x02',second,first,(gen_node *)0x0);
  }
  return;
}



