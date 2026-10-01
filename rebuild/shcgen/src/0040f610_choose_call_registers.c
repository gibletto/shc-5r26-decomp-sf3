#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040f610
// name : choose_call_registers
// size : 547
// sig  : void choose_call_registers(gen_node * call, int pushed_bytes, int return_size)


int __cdecl choose_call_registers(gen_node *call,int pushed_bytes,int return_size)

{
  char cVar1;
  byte ea_kind;
  short reg;
  uint uVar2;
  node_desc *desc;
  ea *callee_ea;
  gen_node *arg_list;
  ushort preferred;
  ushort result_mask;
  gen_node *arg;
  il_op arg_op;
  ea *result_ea;
  
  result_mask = 0;
  arg_list = (gen_node *)0x0;
  if (call->child != (gen_node *)0x0) {
    arg_list = call->child->next;
  }
  if (pushed_bytes == -1) {
    pushed_bytes = 0;
    arg = arg_list->child;
    arg_op = arg->op;
    while (arg_op != IL_E_ARG) {
      if ((arg->desc->flags2 & 8) != 0) {
        uVar2 = node_value_size(arg);
        if ((uVar2 & 3) != 0) {
          uVar2 = (uVar2 & 0xfffffffc) + 4;
        }
        pushed_bytes = pushed_bytes + uVar2;
      }
      arg = arg->next;
      arg_op = arg->op;
    }
  }
  desc = call->child->desc;
  ea_kind = 0;
  callee_ea = desc->mem_ea;
  if (callee_ea != (ea *)0x0) {
    ea_kind = callee_ea->type & 0x1f;
  }
  if (((ea_kind == 0) && (callee_ea = &desc->dest, (callee_ea->type & 0x1f) == 0)) &&
     (callee_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    callee_ea = &desc->value;
  }
  if (((call->type & 0xe0) != 0x60) && ((g_request->cpu == 4 || ((call->type & 0xf8) != 0x30))))
  goto LAB_0040f763;
  return_size = return_size + 4;
  if ((((call->desc->dest).type & 0x1f) == 0) &&
     ((((call->desc->value).type & 0x1f) == 0 && (pushed_bytes == 0)))) goto LAB_0040f763;
  if (call->desc->regs_34[0] == -1) {
LAB_0040f713:
    result_ea = &call->desc->value;
    if ((((result_ea->type & 0x1f) != 0) && ((call->type & 0xe0) == 0x60)) ||
       (result_ea = &call->desc->dest, (result_ea->type & 0x1f) != 0)) {
      uVar2 = ea_register_mask(result_ea);
      result_mask = (ushort)uVar2;
    }
    cVar1 = '\0';
    preferred = 0;
    uVar2 = ea_register_mask(callee_ea);
    reg = choose_general_register((ushort)uVar2 | result_mask,preferred,cVar1);
    cVar1 = (char)reg;
    desc = call->desc;
  }
  else {
    uVar2 = ea_register_mask(callee_ea);
    desc = call->desc;
    if ((1 << (desc->regs_34[0] & 0x1fU) & ~uVar2) == 0) goto LAB_0040f713;
    cVar1 = desc->regs_34[0];
  }
  desc->regs_34[1] = cVar1;
LAB_0040f763:
  ea_kind = callee_ea->type & 0x1f;
  if ((ea_kind != 2) &&
     ((((ea_kind != 8 || (callee_ea->disp != 0)) || (callee_ea->labels != (label_ref *)0x0)) &&
      (arg_list->desc->regs_2c[0] == -1)))) {
    reg = choose_general_register(1,0,'\0');
    arg_list->desc->regs_2c[0] = (char)reg;
  }
  if ((arg_list->desc->fpu_mode_flags & 1) != 0) {
    reg = choose_general_register((ushort)(1 << (arg_list->desc->regs_2c[0] & 0x1fU)) | 1,0,'\0');
    arg_list->desc->regs_2c[2] = (char)reg;
    reg = choose_general_register
                    ((ushort)(1 << (arg_list->desc->regs_2c[0] & 0x1fU)) |
                     (ushort)(1 << (arg_list->desc->regs_2c[2] & 0x1fU)) | 1,0,'\0');
    arg_list->desc->regs_2c[3] = (char)reg;
  }
  if ((0x7f < return_size + pushed_bytes) && (desc = arg_list->desc, desc->regs_2c[1] == -1)) {
    if (desc->regs_2c[0] != -1) {
      desc->regs_2c[1] = desc->regs_2c[0];
      return;
    }
    reg = choose_general_register(1,0,'\0');
    arg_list->desc->regs_2c[1] = (char)reg;
  }
  return;
}



