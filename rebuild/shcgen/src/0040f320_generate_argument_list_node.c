#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040f320
// name : generate_argument_list_node
// size : 744
// sig  : void generate_argument_list_node(gen_node * args)


int __cdecl generate_argument_list_node(gen_node *args)

{
  uchar *puVar1;
  short sVar2;
  uint uVar3;
  ea *operand;
  byte ea_kind;
  ushort callee_regs;
  char ascending;
  uint return_size;
  int pushed_bytes;
  gen_node *arg;
  il_op arg_op;
  gen_node *call;
  gen_node *callee;
  node_desc *desc;
  gen_node *next_arg;
  gen_node *prev;
  ushort saved_var_gpr_mask;
  ushort target_mask;
  
  call = args->parent;
  pushed_bytes = 0;
  callee = call->child;
  return_size = 0;
  uVar3 = node_value_size(call);
  if ((((call->type & 0xe0) == 0x60) && (desc = call->desc, ((desc->value).type & 0x1f) == 0)) &&
     (((desc->dest).type & 0x1f) == 0)) {
    if (((desc->usage == '\0') || ((desc->flags2 & 8) != 0)) &&
       (return_size = uVar3, (uVar3 & 3) != 0)) {
      return_size = (uVar3 & 0xfffffffc) + 4;
    }
    if (0x7f < (int)return_size) {
      ea_kind = 0;
      desc = callee->desc;
      operand = desc->mem_ea;
      if (operand != (ea *)0x0) {
        ea_kind = operand->type & 0x1f;
      }
      if (((ea_kind == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
         (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        operand = &desc->value;
      }
      ascending = '\0';
      callee_regs = 0;
      uVar3 = ea_register_mask(operand);
      sVar2 = choose_general_register((ushort)uVar3,callee_regs,ascending);
      call->desc->regs_34[0] = (char)sVar2;
    }
  }
  else if (((g_request->cpu != 4) && ((call->type & 0xf8) == 0x30)) &&
          ((((call->desc->dest).type & 0x1f) == 0 && (call->desc->usage == '\0')))) {
    return_size = uVar3;
  }
  assign_argument_registers(args,0);
  uVar3 = ea_register_mask(&callee->desc->value);
  callee_regs = (ushort)uVar3 & 0xf;
  arg_op = args->child->op;
  next_arg = args->child;
  prev = args;
  while (arg = next_arg, arg_op != IL_E_ARG) {
    arg->desc->busy_regs = prev->desc->busy_regs;
    arg->desc->fbusy_regs = prev->desc->fbusy_regs;
    arg->desc->frame_top = prev->desc->frame_top;
    puVar1 = &arg->desc->flags7;
    *puVar1 = *puVar1 | prev->desc->flags7 & 0x40;
    arg->desc->busy_regs = arg->desc->busy_regs & 0xfff0 | callee_regs;
    saved_var_gpr_mask = g_var_gpr_mask;
    desc = arg->desc;
    target_mask = desc->target_regs;
    if ((target_mask != 0) && ((desc->need_regs & target_mask) == 0)) {
      desc->pref_regs = target_mask;
      desc = arg->desc;
      if ((desc->busy_regs & desc->target_regs) != 0) {
        desc->busy_regs = desc->target_regs ^ desc->busy_regs;
      }
      target_mask = arg->desc->target_regs;
      if ((g_var_gpr_mask & target_mask) != 0) {
        g_var_gpr_mask = g_var_gpr_mask ^ target_mask;
      }
    }
    dispatch_and_finalize_code_node(arg);
    desc = arg->desc;
    if ((((desc->target_regs != 0) || (desc->ftarget_regs != 0)) &&
        ((desc->cached_regs != 0 || (desc->fcached_regs != 0)))) &&
       ((args->desc->flags7 & 0x10) != 0)) {
      invalidate_register_contents
                ((int)(short)desc->fcached_regs << 0x10 | (int)(short)desc->cached_regs);
    }
    if ((arg->desc->temp_regs & callee_regs) != 0) {
      callee_regs = 0;
    }
    g_var_gpr_mask = saved_var_gpr_mask;
    if ((arg->desc->flags2 & 8) != 0) {
      uVar3 = node_value_size(arg);
      if ((uVar3 & 3) != 0) {
        uVar3 = (uVar3 & 0xfffffffc) + 4;
      }
      pushed_bytes = pushed_bytes + uVar3;
    }
    next_arg = arg->next;
    prev = arg;
    arg_op = arg->next->op;
  }
  save_register_arguments_clobbered_by_later_ones(args,0);
  sVar2 = resolve_operand_register_conflicts(call,callee,args);
  if (sVar2 != 0) {
    operand = callee->desc->mem_ea;
    ea_kind = 0;
    if (operand != (ea *)0x0) {
      ea_kind = operand->type & 0x1f;
    }
    if (ea_kind != 0) {
      operand->type = operand->type | 0x40;
    }
  }
  if (call->desc->usage != '\0') {
    return_size = 0;
  }
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    if (g_fpscr_pr != '\0') {
      puVar1 = &args->desc->fpu_mode_flags;
      *puVar1 = *puVar1 | 1;
    }
    g_fpscr_pr = '\x02';
  }
  choose_call_registers(call,pushed_bytes,return_size);
  return;
}



