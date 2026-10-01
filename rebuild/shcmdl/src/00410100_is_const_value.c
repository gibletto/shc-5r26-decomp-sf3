#include "decls.h"
#include "imports.h"

// entry: 00410100
// name : is_const_value
// size : 329
// sig  : uint is_const_value(il_node * node, uint value, uchar type)


uint __cdecl is_const_value(il_node *node,uint value,uchar type)

{
  unsigned char _frec_14[20];
#define res (*(uint (*)[4])(_frec_14 + 0))
#define converted (*(uint *)(_frec_14 + 16))
  uchar to_type;
  byte kind;
  
  to_type = type;
  res[0] = 0;
  res[1] = 0;
  res[2] = 0;
  if (node->op == IL_CONST) {
    kind = type & 0xe0;
    if ((kind == 0) || ((type & 0xf8) == 0x40)) {
      convert_constant(type,type,(uint *)&node->val,&converted);
      convert_constant(to_type,to_type,&value,&value);
      res[0] = (uint)(converted == value);
    }
    else {
      if (kind == 0x20) {
        if ((type & 0x18) == 8) {
          convert_int_to_float(&value,res + 1);
          fold_float_eq((uint *)&node->val,res + 1,(int *)res);
          return res[0];
        }
        if ((type & 0x18) == 0x10) {
          convert_int_to_double(&value,res + 1);
          fold_double_eq((uint *)&node->val,res + 1,(int *)res);
          return res[0];
        }
      }
      if ((kind == 0x20) && ((type & 0x18) == 0x18)) {
        convert_int_to_ldouble(&value,res + 1);
        fold_long_double_eq((uint *)&node->val,res + 1,(int *)res);
        return res[0];
      }
    }
  }
  return res[0];
#undef res
#undef converted
}



