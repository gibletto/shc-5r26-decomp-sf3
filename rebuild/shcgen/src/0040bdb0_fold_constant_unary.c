#include "decls.h"
#include "imports.h"

// entry: 0040bdb0
// name : fold_constant_unary
// size : 265
// sig  : short fold_constant_unary(char op, gen_node * operand, gen_node * node)


short __cdecl fold_constant_unary(char op,gen_node *operand,gen_node *node)

{
  byte type_bits;
  short result;
  uint uint_result;
  byte type_class;
  
  result = 0;
  if (op == '%') {
    type_bits = operand->type;
    type_class = type_bits & 0xe0;
    if (type_class != 0x20) {
      if ((((type_bits & 4) == 0) && (type_class != 0x80)) && (type_class != 0x40)) {
        uint_result = fold_int_neg(&(operand->desc->value).disp,&(node->desc->value).disp);
        return (short)uint_result;
      }
      uint_result = fold_neg_unsigned(&(operand->desc->value).disp,&(node->desc->value).disp);
      return (short)uint_result;
    }
    type_bits = type_bits & 0xf8;
    if (type_bits == 0x28) {
      uint_result = fold_neg_float((uint *)&(operand->desc->value).disp,
                                   (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    if ((type_bits == 0x30) || (type_bits == 0x38)) {
      uint_result = fold_neg_double((uint *)&(operand->desc->value).disp,
                                    (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
  }
  else {
    if (op != '-') {
      return result;
    }
    if ((((operand->type & 4) == 0) && (type_bits = operand->type & 0xe0, type_bits != 0x80)) &&
       (type_bits != 0x40)) {
      uint_result = fold_int_cmpl((uint *)&(operand->desc->value).disp,
                                  (uint *)&(node->desc->value).disp);
      return (short)uint_result;
    }
    uint_result = fold_bnot_unsigned((uint *)&(operand->desc->value).disp,
                                     (uint *)&(node->desc->value).disp);
    result = (short)uint_result;
  }
  return result;
}



