#include "decls.h"
#include "imports.h"

// entry: 0040fca0
// name : check_trapa_svc_arguments
// size : 599
// sig  : void check_trapa_svc_arguments(gen_node * args)


int __cdecl check_trapa_svc_arguments(gen_node *args)

{
  byte arg_type;
  int arg_index;
  gen_node *arg;
  node_desc *desc;
  uint next_i;
  uint i;
  byte type_class;
  int missing;
  
  if (args->desc->builtin == '\x1c') {
    arg_index = count_operands(args);
    arg_index = arg_index + -1;
    if (arg_index < 2) {
      report_codegen_message(0xaf0,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      if (arg_index < 2) {
        missing = 2 - arg_index;
        arg_index = arg_index + missing;
        do {
          arg = alloc_gen_node(IL_CONST);
          arg->type = '\x10';
          args->val = 0;
          desc = alloc_zeroed(0x84);
          arg->desc = desc;
          i = 0;
          do {
            next_i = i + 1;
            arg->desc->regs_2c[i] = -1;
            i = next_i;
          } while (next_i < 5);
          i = 0;
          do {
            next_i = i + 1;
            arg->desc->regs_34[i] = -1;
            i = next_i;
          } while (next_i < 4);
          i = 0;
          do {
            next_i = i + 1;
            arg->desc->regs_41[i] = -1;
            i = next_i;
          } while (next_i < 3);
          i = 0;
          do {
            next_i = i + 1;
            arg->desc->regs_44[i] = -1;
            i = next_i;
          } while (next_i < 2);
          i = 0;
          do {
            next_i = i + 1;
            arg->desc->regs_3d[i] = -1;
            i = next_i;
          } while (next_i < 2);
          i = 0;
          do {
            next_i = i + 1;
            arg->desc->cond_regs[i] = -1;
            i = next_i;
          } while (next_i < 5);
          arg->desc->addr_reg = -1;
          arg->desc->reg_47 = -1;
          arg->desc->usage = '\x02';
          prepend_operand(args,arg);
          missing = missing + -1;
        } while (missing != 0);
      }
    }
    else if (6 < arg_index) {
      report_codegen_message(0xaf0,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    arg = nth_operand(args,arg_index);
    arg_type = arg->type;
    if (((((arg_type & 0xf8) != 0x10) || ((arg_type & 4) != 0)) || ((arg_type & 0xe0) == 0x80)) ||
       ((arg_type & 0xe0) == 0x40)) {
      report_codegen_message(0xaf1,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      arg->type = '\x10';
    }
    arg = nth_operand(args,arg_index + -1);
    arg_type = arg->type;
    if ((((arg_type & 0xf8) != 0x10) || ((arg_type & 4) != 0)) ||
       (((arg_type & 0xe0) == 0x80 || ((arg_type & 0xe0) == 0x40)))) {
      report_codegen_message(0xaf1,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      arg->type = '\x10';
    }
    arg_index = arg_index + -2;
    if (0 < arg_index) {
      do {
        arg = nth_operand(args,arg_index);
        arg_type = arg->type & 0xe0;
        if (((arg_type != 0) && (type_class = arg->type & 0xf8, type_class != 0x28)) &&
           ((type_class != 0x40 && ((arg_type != 0x80 && (type_class != 0x48)))))) {
          report_codegen_message(0xaf1,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
          arg->type = '\x10';
        }
        arg_index = arg_index + -1;
      } while (arg_index != 0);
    }
  }
  return;
}



