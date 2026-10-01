#include "decls.h"
#include "imports.h"

// entry: 0040bec0
// name : fold_constant_cast
// size : 744
// sig  : short fold_constant_cast(gen_node * cast_node, gen_node * operand, gen_node * node)


short __cdecl fold_constant_cast(gen_node *cast_node,gen_node *operand,gen_node *node)

{
  byte from_class;
  short result;
  int int_result;
  uint uint_result;
  byte from_type;
  byte to_class;
  byte to_type;
  int *value_ptr;
  
  result = 0;
  to_type = cast_node->type;
  to_class = to_type & 0xe0;
  if ((to_class == 0x20) || ((operand->type & 0xe0) == 0x20)) {
    from_type = operand->type;
    from_class = from_type & 0xe0;
    if (from_class == 0x20) {
      from_type = from_type & 0xf8;
      if (from_type == 0x28) {
        if (to_class == 0x20) {
          to_type = to_type & 0xf8;
          if (to_type == 0x28) {
            (node->desc->value).disp = (operand->desc->value).disp;
          }
          else if ((to_type == 0x30) || (to_type == 0x38)) {
            uint_result = float_bits_to_double
                                    ((uint *)&(operand->desc->value).disp,
                                     (uint *)&(node->desc->value).disp);
            result = (short)uint_result;
          }
        }
        else if ((((to_type & 4) == 0) && (to_class != 0x80)) && (to_class != 0x40)) {
          int_result = float_bits_to_int((uint *)&(operand->desc->value).disp,
                                         (uint *)&(node->desc->value).disp);
          result = (short)int_result;
        }
        else {
          int_result = float_bits_to_uint((uint *)&(operand->desc->value).disp,
                                          (uint *)&(node->desc->value).disp);
          result = (short)int_result;
        }
      }
      else if ((from_type == 0x30) || (from_type == 0x38)) {
        if (to_class == 0x20) {
          to_type = to_type & 0xf8;
          if (to_type == 0x28) {
            uint_result = convert_double_to_float
                                    ((uint *)&(operand->desc->value).disp,
                                     (uint *)&(node->desc->value).disp);
            result = (short)uint_result;
          }
          else if ((to_type == 0x30) || (to_type == 0x38)) {
            copy_words((uint *)&(node->desc->value).disp,(uint *)&(operand->desc->value).disp,2);
          }
        }
        else if ((((to_type & 4) == 0) && (to_class != 0x80)) && (to_class != 0x40)) {
          int_result = double_bits_to_int((uint *)&(operand->desc->value).disp,
                                          (uint *)&(node->desc->value).disp);
          result = (short)int_result;
        }
        else {
          int_result = double_bits_to_uint((uint *)&(operand->desc->value).disp,
                                           (uint *)&(node->desc->value).disp);
          result = (short)int_result;
        }
      }
    }
    else if ((((from_type & 4) == 0) && (from_class != 0x80)) && (from_class != 0x40)) {
      to_type = to_type & 0xf8;
      if (to_type == 0x28) {
        int_result = int_to_float_bits((uint *)&(operand->desc->value).disp,
                                       (uint *)&(node->desc->value).disp);
        result = (short)int_result;
      }
      else if ((to_type == 0x30) || (to_type == 0x38)) {
        int_result = int_to_double_bits((uint *)&(operand->desc->value).disp,
                                        (uint *)&(node->desc->value).disp);
        result = (short)int_result;
      }
    }
    else {
      to_type = to_type & 0xf8;
      if (to_type == 0x28) {
        result = uint_to_float_bits(&(operand->desc->value).disp,(uint *)&(node->desc->value).disp);
      }
      else if ((to_type == 0x30) || (to_type == 0x38)) {
        int_result = uint_to_double_bits(&(operand->desc->value).disp,
                                         (uint *)&(node->desc->value).disp);
        result = (short)int_result;
      }
    }
  }
  else {
    (node->desc->value).disp = (operand->desc->value).disp;
  }
  to_type = node->type;
  if ((to_type & 0xf8) == 0) {
    if ((((to_type & 4) == 0) && ((to_type & 0xe0) != 0x80)) && ((to_type & 0xe0) != 0x40)) {
      (node->desc->value).disp = (int)(char)(node->desc->value).disp;
      return result;
    }
    value_ptr = &(node->desc->value).disp;
    *value_ptr = *value_ptr & 0xff;
    return result;
  }
  if ((to_type & 0xf8) == 8) {
    if ((((to_type & 4) == 0) && ((to_type & 0xe0) != 0x80)) && ((to_type & 0xe0) != 0x40)) {
      (node->desc->value).disp = (int)(short)(node->desc->value).disp;
      return result;
    }
    value_ptr = &(node->desc->value).disp;
    *value_ptr = *value_ptr & 0xffff;
  }
  return result;
}



