#include "decls.h"
#include "imports.h"

// entry: 00428910
// name : constant_condition_is_zero
// size : 210
// sig  : int constant_condition_is_zero(gen_node * node)


int __cdecl constant_condition_is_zero(gen_node *node)

{
  unsigned char _frec_4[4];
#define is_zero (*(int *)(_frec_4 + 0))
  byte float_kind;
  node_desc *desc;
  
  desc = node->desc;
  is_zero = 0;
  if ((((desc->value).type & 0x1f) != 7) || ((desc->value).labels == (label_ref *)0x0)) {
    if ((node->type & 0xe0) != 0x20) {
      fold_int_eq(&(desc->value).disp,(int *)&g_zero_constant,&is_zero);
      return is_zero;
    }
    float_kind = node->type & 0xf8;
    if (float_kind == 0x28) {
      fold_float_eq((uint *)&(desc->value).disp,(uint *)&g_zero_constant,&is_zero);
      return is_zero;
    }
    if ((float_kind != 0x30) && (float_kind != 0x38)) {
      report_codegen_message(0x1226,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return is_zero;
    }
    fold_double_eq((uint *)&(desc->value).disp,(uint *)&g_zero_constant,&is_zero);
  }
  return is_zero;
#undef is_zero
}



