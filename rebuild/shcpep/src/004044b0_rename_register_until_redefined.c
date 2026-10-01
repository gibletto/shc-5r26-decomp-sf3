#include "decls.h"
#include "imports.h"

// entry: 004044b0
// name : rename_register_until_redefined
// size : 225
// sig  : char rename_register_until_redefined(psd * rec, uchar from_reg, uchar to_reg)


char __cdecl rename_register_until_redefined(psd *rec,uchar from_reg,uchar to_reg)

{
  uchar changed;
  char uses;
  char *base;
  
  changed = record_changes_register(rec,from_reg);
  if (changed == '\0') {
    if (rec->ea1 != (ea *)0x0) {
      uses = operand_uses_register(rec,from_reg,'\x01');
      if ((uses != '\0') && (base = &rec->ea1->base, *base == from_reg)) {
        *base = to_reg;
      }
    }
    if (rec->ea2 != (ea *)0x0) {
      uses = operand_uses_register(rec,from_reg,'\x02');
      if ((uses != '\0') && (base = &rec->ea2->base, *base == from_reg)) {
        *base = to_reg;
      }
    }
    return '\0';
  }
  if (*(short *)(&g_op_dest_operand + (uint)rec->op * 2) != 1) {
    if (*(short *)(&g_op_dest_operand + (uint)rec->op * 2) != 2) {
      return '\x01';
    }
    if (rec->ea1 != (ea *)0x0) {
      uses = operand_uses_register(rec,from_reg,'\x01');
      if ((uses != '\0') && (base = &rec->ea1->base, *base == from_reg)) {
        *base = to_reg;
      }
    }
    return '\x01';
  }
  return '\x01';
}



