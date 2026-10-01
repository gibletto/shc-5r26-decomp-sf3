#include "decls.h"
#include "imports.h"

// entry: 00425950
// name : record_operand_copy_in_register
// size : 457
// sig  : void record_operand_copy_in_register(gen_node * node, tmpl_header * tmpl, short reg, ushort opnd_code, gen_node * operand)


int __cdecl
record_operand_copy_in_register
          (gen_node *node,tmpl_header *tmpl,short reg,ushort opnd_code,gen_node *operand)

{
  ea *opnd1;
  ea *opnd2;
  ea *opnd3;
  uint written;
  tmpl_entry *entry;
  tmpl_entry *ptVar1;
  ushort op;
  
  if (reg != -1) {
    ptVar1 = tmpl->entries;
    op = ptVar1->op;
    entry = ptVar1;
    while (op != 0xff00) {
      entry = entry + 1;
      op = entry->op;
    }
    entry = entry + -1;
    if (ptVar1 <= entry) {
      while (((((op = entry->op, op != 0xc00 || (entry->opnd[0] != opnd_code)) &&
               ((op != 0xf00 || (entry->opnd[1] != opnd_code)))) &&
              ((op != 0x2700 || (entry->opnd[0] != opnd_code)))) &&
             ((op != 0x2800 || (entry->opnd[1] != opnd_code))))) {
        if ((((op == 0x2b00) && (entry->opnd[0] == opnd_code)) ||
            ((op == 0x1c00 && (entry->opnd[1] == opnd_code)))) ||
           (entry = entry + -1, entry < ptVar1)) break;
      }
    }
    if (reg != -1) {
      do {
        ptVar1 = entry + 1;
        op = ptVar1->op;
        if (op == 0xff00) break;
        if (((op < 0x24) || (0x26 < op)) && (op != 0x18)) {
          if (op == 0x23) {
            opnd1 = make_call_routine_operand((uint)entry[1].opnd[0],node);
          }
          else {
            opnd1 = materialize_operand_record_from_descriptor
                              (node,entry[1].opnd[0],(ea **)&g_template_extra_operands);
          }
        }
        else {
          opnd1 = (ea *)0x0;
        }
        opnd2 = materialize_operand_record_from_descriptor
                          (node,entry[1].opnd[1],(ea **)&g_template_extra_operands);
        opnd3 = materialize_operand_record_from_descriptor
                          (node,entry[1].opnd[2],(ea **)&g_template_extra_operands);
        written = invalidate_regs_written_by_entry(ptVar1->op,opnd1,opnd2,opnd3);
        free_ea(opnd1);
        free_ea(opnd2);
        free_ea(opnd3);
        if ((written & 1 << ((byte)reg & 0x1f)) != 0) {
          reg = -1;
        }
        entry = ptVar1;
      } while (reg != -1);
      if (reg != -1) {
        if (operand->op == IL_ID) {
          forget_register_copies_of_variable(operand);
          record_variable_in_register(operand,reg);
          return;
        }
        record_constant_in_register(&operand->desc->value,reg,operand);
      }
    }
  }
  return;
}



