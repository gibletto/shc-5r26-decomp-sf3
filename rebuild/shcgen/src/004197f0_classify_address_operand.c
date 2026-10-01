#include "decls.h"
#include "imports.h"

// entry: 004197f0
// name : classify_address_operand
// size : 280
// sig  : short classify_address_operand(gen_node * operand)


short __cdecl classify_address_operand(gen_node *operand)

{
  short sVar1;
  byte ea_type;
  byte kind;
  ea *operand_ea;
  node_desc *desc;
  
  ea_type = 0;
  desc = operand->desc;
  operand_ea = desc->mem_ea;
  if (operand_ea != (ea *)0x0) {
    ea_type = operand_ea->type & 0x1f;
  }
  if (((ea_type == 0) && (operand_ea = &desc->dest, (operand_ea->type & 0x1f) == 0)) &&
     (operand_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    operand_ea = &desc->value;
  }
  sVar1 = 0;
  ea_type = operand_ea->type;
  kind = ea_type & 0x1f;
  if ((kind == 7) && (operand_ea->labels == (label_ref *)0x0)) {
    return 3;
  }
  if ((((kind == 2) && (operand_ea->base == 'l')) || ((kind == 8 && (operand_ea->base == 'l')))) &&
     ((ea_type & 0x40) != 0)) {
    return 2;
  }
  if (((kind == 7) && (operand_ea->labels != (label_ref *)0x0)) ||
     ((kind == 0xd && ((ea_type & 0x40) != 0)))) {
    return 1;
  }
  if (((((kind == 2) || (kind == 8)) && (operand_ea->base != 'l')) &&
      ((operand_ea->disp != 0 || (operand_ea->labels != (label_ref *)0x0)))) &&
     ((ea_type & 0x40) != 0)) {
    return 5 - (ushort)(operand_ea->base == '\0');
  }
  if (kind == 1) {
LAB_004198cf:
    if (operand_ea->base != 'l') {
      return 7 - (ushort)(operand_ea->base == '\0');
    }
  }
  else if ((kind == 2) ||
          (((kind == 8 && (operand_ea->disp == 0)) && (operand_ea->labels == (label_ref *)0x0)))) {
    if ((ea_type & 0x40) == 0) goto LAB_004198e8;
    goto LAB_004198cf;
  }
  if ((ea_type & 0x40) != 0) {
    return 0;
  }
LAB_004198e8:
  if ((((kind == 0xd) || (kind == 2)) || (kind == 8)) || ((kind == 4 || (kind == 9)))) {
    sVar1 = 8;
  }
  return sVar1;
}



