#include "decls.h"
#include "imports.h"

// entry: 0040bd00
// name : fold_constant_not
// size : 166
// sig  : short fold_constant_not(gen_node * operand, gen_node * node)


short __cdecl fold_constant_not(gen_node *operand,gen_node *node)

{
  short result;
  int int_result;
  uint uint_result;
  byte type_class;
  byte type_bits;
  
  result = 0;
  type_bits = operand->type;
  type_class = type_bits & 0xe0;
  if (type_class == 0x20) {
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      int_result = fold_lnot_float((uint *)&(operand->desc->value).disp,&(node->desc->value).disp);
      return (short)int_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      uint_result = fold_lnot_double((uint *)&(operand->desc->value).disp,&(node->desc->value).disp)
      ;
      result = (short)uint_result;
    }
    return result;
  }
  if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
    int_result = fold_int_not(&(operand->desc->value).disp,&(node->desc->value).disp);
    return (short)int_result;
  }
  int_result = fold_lnot_unsigned(&(operand->desc->value).disp,&(node->desc->value).disp);
  return (short)int_result;
}



