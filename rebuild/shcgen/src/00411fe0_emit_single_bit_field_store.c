#include "decls.h"
#include "imports.h"

// entry: 00411fe0
// name : emit_single_bit_field_store
// size : 542
// sig  : int emit_single_bit_field_store(gen_node * node, tmpl_entry * entry, ea * value, ea * * operands)


int __cdecl emit_single_bit_field_store(gen_node *node,tmpl_entry *entry,ea *value,ea **operands)

{
  unsigned char _frec_c[12];
#define macro_opnds (*(ea * (*)[2])(_frec_c + 0))
#define entries_used (*(int *)(_frec_c + 8))
  ea *peVar1;
  ea *peVar2;
  ushort uVar3;
  gen_node *pgVar4;
  
  entries_used = 0;
  if (entry->op == 0x2f00) {
    peVar1 = materialize_operand_record_from_descriptor(node,entry->opnd[1],operands);
    if ((value->disp & 1) != 0) {
      peVar2 = materialize_operand_record_from_descriptor(node,0x99,operands);
      emit_psd_for_node(0x81,-1,'\0','\x02',peVar2,peVar1,node);
      return entries_used;
    }
    peVar2 = materialize_operand_record_from_descriptor(node,0xa1,operands);
    emit_psd_for_node(0x80,-1,'\0','\x02',peVar2,peVar1,node);
    return entries_used;
  }
  if (entry->op == 0x3000) {
    entries_used = collect_macro_operand_list(node,entry + 1,macro_opnds,operands);
    if ((value->disp & 1) != 0) {
      peVar1 = materialize_operand_record_from_descriptor(node,0x9c,operands);
      pgVar4 = node;
      peVar2 = copy_ea(macro_opnds[0]);
      emit_psd_for_node(0x2a,-1,'\0','\x02',peVar1,peVar2,pgVar4);
      peVar1 = materialize_operand_record_from_descriptor(node,entry->opnd[1],operands);
      peVar2 = copy_ea(macro_opnds[0]);
      uVar3 = 0x81;
      goto LAB_004121dd;
    }
    uVar3 = 0xa2;
  }
  else {
    entries_used = collect_macro_operand_list(node,entry + 1,macro_opnds,operands);
    if ((value->disp & 1) != 0) {
      peVar1 = materialize_operand_record_from_descriptor(node,0x9d,operands);
      pgVar4 = node;
      peVar2 = copy_ea(macro_opnds[0]);
      emit_psd_for_node(0x2a,-1,'\0','\x02',peVar1,peVar2,pgVar4);
      peVar1 = materialize_operand_record_from_descriptor(node,entry->opnd[1],operands);
      peVar2 = copy_ea(macro_opnds[0]);
      uVar3 = 0x81;
      goto LAB_004121dd;
    }
    uVar3 = 0xa3;
  }
  peVar1 = materialize_operand_record_from_descriptor(node,uVar3,operands);
  pgVar4 = node;
  peVar2 = copy_ea(macro_opnds[0]);
  emit_psd_for_node(0x2a,-1,'\0','\x02',peVar1,peVar2,pgVar4);
  peVar1 = materialize_operand_record_from_descriptor(node,entry->opnd[1],operands);
  peVar2 = copy_ea(macro_opnds[0]);
  uVar3 = 0x80;
LAB_004121dd:
  emit_psd_for_node(uVar3,-1,'\0','\x02',peVar2,peVar1,node);
  free_macro_operand_list(macro_opnds);
  return entries_used;
#undef macro_opnds
#undef entries_used
}



