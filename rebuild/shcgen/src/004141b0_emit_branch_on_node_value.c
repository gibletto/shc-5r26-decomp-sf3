#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 004141b0
// name : emit_branch_on_node_value
// size : 578
// sig  : void emit_branch_on_node_value(gen_node * node)


int __cdecl emit_branch_on_node_value(gen_node *node)

{
  unsigned char _frec_1d[29];
#define false_op (*(char *)(_frec_1d + 0))
#define opnd0 (*(ea * *)(_frec_1d + 1))
#define opnd1 (*(undefined4 *)(_frec_1d + 5))
#define opnd2 (*(undefined4 *)(_frec_1d + 9))
#define opnd3 (*(undefined4 *)(_frec_1d + 13))
#define opnd4 (*(undefined4 *)(_frec_1d + 17))
#define opnd5 (*(undefined4 *)(_frec_1d + 21))
#define opnd6 (*(undefined4 *)(_frec_1d + 25))
  byte bVar1;
  int is_zero;
  ea *label_opnd;
  char cVar2;
  tmpl_entry *entries;
  node_desc *desc;
  short label;
  
  desc = node->desc;
  cVar2 = desc->opnd_class;
  if (cVar2 == '\x02') {
    is_zero = constant_condition_is_zero(node);
    if ((is_zero != 0) && (label = node->desc->false_label, label != 0)) {
      label_opnd = new_label_operand(label);
      emit_psd_for_node(0x24,node->desc->cond_regs[0],'\0','\x02',label_opnd,(ea *)0x0,
                        (gen_node *)0x0);
      return;
    }
    is_zero = constant_condition_is_zero(node);
    if ((is_zero == 0) && (label = node->desc->true_label, label != 0)) {
      label_opnd = new_label_operand(label);
      emit_psd_for_node(0x24,node->desc->cond_regs[0],'\0','\x02',label_opnd,(ea *)0x0,
                        (gen_node *)0x0);
      return;
    }
  }
  else {
    if ((desc->flags2 & 0x20) == 0) {
      bVar1 = node->type & 0xf8;
      if (bVar1 == 0x30) {
        entries = (tmpl_entry *)&g_test_double_fpu_entries;
        if (g_request->cpu != 4) {
          entries = (tmpl_entry *)&g_test_double_soft_entries;
        }
      }
      else if (bVar1 == 0x28) {
        if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
          bVar1 = 1;
        }
        else {
          bVar1 = -(g_request->cpu == 4) & 2;
        }
        if (bVar1 == 0) {
          entries = (tmpl_entry *)&g_test_float_soft_reg_entries;
          if (cVar2 != '\0') {
            entries = (tmpl_entry *)&g_test_float_soft_mem_entries;
          }
        }
        else {
          entries = (tmpl_entry *)&g_test_float_fpu_entries;
        }
      }
      else if ((cVar2 == '\0') || (cVar2 == '\x01')) {
        if ((bVar1 == 0) || (bVar1 == 8)) {
          entries = (tmpl_entry *)&g_test_short_reg_entries;
          if (cVar2 != '\0') {
            entries = (tmpl_entry *)&g_test_short_fixed_reg_entries;
          }
        }
        else {
          entries = (tmpl_entry *)&g_test_int_reg_entries;
        }
      }
      else if ((bVar1 == 0) || (bVar1 == 8)) {
        entries = (tmpl_entry *)&g_test_short_mem_entries;
      }
      else {
        entries = (tmpl_entry *)&g_test_int_mem_entries;
      }
      opnd0 = (ea *)0x0;
      opnd1 = 0;
      opnd2 = 0;
      opnd3 = 0;
      opnd4 = 0;
      opnd5 = 0;
      opnd6 = 0;
      if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
        desc->fpu_mode_flags = desc->fpu_mode_flags | 4;
      }
      emit_template_record_sequence_for_node(node,entries,&opnd0);
    }
    if ((node->op == IL_CALL) && (node->desc->builtin == '\x14')) {
      false_op = '&';
      cVar2 = '%';
    }
    else {
      false_op = '%';
      cVar2 = '&';
    }
    label = node->desc->true_label;
    if (label != 0) {
      label_opnd = new_label_operand(label);
      emit_psd_for_node((short)cVar2,node->desc->cond_regs[0],'\0','\x02',label_opnd,(ea *)0x0,
                        (gen_node *)0x0);
      return;
    }
    label_opnd = new_label_operand(node->desc->false_label);
    emit_psd_for_node((short)false_op,node->desc->cond_regs[0],'\0','\x02',label_opnd,(ea *)0x0,
                      (gen_node *)0x0);
  }
  return;
#undef false_op
#undef opnd0
#undef opnd1
#undef opnd2
#undef opnd3
#undef opnd4
#undef opnd5
#undef opnd6
}



