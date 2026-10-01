#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00406340
// name : emit_node_code
// size : 1262
// sig  : void emit_node_code(gen_node * node)


int __cdecl emit_node_code(gen_node *node)

{
  unsigned char _frec_1c[28];
#define local_1c (*(ea * *)(_frec_1c + 0))
#define local_18 (*(ea * *)(_frec_1c + 4))
#define local_14 (*(ea * *)(_frec_1c + 8))
#define local_10 (*(undefined4 *)(_frec_1c + 12))
#define local_c (*(undefined4 *)(_frec_1c + 16))
#define local_8 (*(undefined4 *)(_frec_1c + 20))
#define local_4 (*(undefined4 *)(_frec_1c + 24))
  byte bVar1;
  byte bVar2;
  tmpl_header *tmpl;
  byte bVar3;
  char cVar4;
  node_desc *desc;
  code *handler;
  il_op op;
  
  if (((node->desc->usage == '\0') && ((node->desc->flags2 & 0x40) == 0)) &&
     (node->parent->op != IL_COMMA)) goto LAB_004067bd;
  if ((node->op < IL_CAST) || (IL_COND < node->op)) {
    report_codegen_message(0x11fe,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  if ((((node->parent != (gen_node *)0x0) && (desc = node->parent->desc, desc != (node_desc *)0x0))
      && (((desc->flags3 & 1) != 0 &&
          (((desc = node->desc, desc->usage == '\x02' && ((desc->flags2 & 8) == 0)) &&
           (desc->target_regs == 0)))))) &&
     ((bVar1 = (desc->dest).type & 0x1f, bVar1 == 0 ||
      ((bVar1 == 1 &&
       ((((bVar1 = (desc->dest).base, (char)bVar1 < '\x0f' &&
          ((1 << (bVar1 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)) ||
         (((char)bVar1 < ' ' &&
          (('\x0f' < (char)bVar1 &&
           (((int)(short)~g_var_fpr_mask & 1 << (bVar1 - 0x10 & 0x1f)) != 0)))))) ||
        (((char)bVar1 < '/' &&
         (('\x1f' < (char)bVar1 &&
          (((int)(short)g_var_fpr_mask & (1 << (bVar1 - 0x1f & 0x1f) | 1 << (bVar1 - 0x20 & 0x1f)))
           == 0)))))))))))) {
    desc->flags3 = desc->flags3 | 1;
  }
  if ((node->desc->flags7 & 0x80) == 0) {
    handler = *(code **)(&g_emit_handler_by_op + (uint)node->op * 4);
    if (handler == 0) {
      report_codegen_message(0x11fe,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    }
    else if (handler != (code *)0x1) {
      if (((node->op == IL_ARG) && (cVar4 = node->desc->builtin, cVar4 != '\0')) &&
         (cVar4 != '\x1d')) {
        emit_node_operands_and_template(node);
      }
      else {
        (*handler)(node);
      }
    }
  }
  else {
    if ((node->op == IL_ADD) || (node->op == IL_A_ADD)) {
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(g_request->cpu == 4) & 2;
      }
      if (bVar1 != 0) {
        emit_float_multiply_add(node);
        goto LAB_0040652b;
      }
    }
    report_codegen_message(0x11fe,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
LAB_0040652b:
  desc = node->desc;
  bVar1 = desc->flags3;
  if ((bVar1 & 0x20) == 0) {
    if ((((desc->value).type & 0x1f) == 0) ||
       ((((bVar2 = (desc->dest).type & 0x1f, bVar2 == 0 || ((bVar1 & 4) != 0)) &&
         (((desc->flags2 & 0xc) == 0 && ((desc->ftarget_regs == 0 || (bVar2 != 0)))))) &&
        ((desc->target_regs == 0 || (bVar2 != 0)))))) {
      bVar2 = 0;
      if (desc->saved_ea != (ea *)0x0) {
        bVar2 = desc->saved_ea->type & 0x1f;
      }
      if (bVar2 != 0) {
        bVar2 = 0;
        if (desc->saved_reg_ea != (ea *)0x0) {
          bVar2 = desc->saved_reg_ea->type & 0x1f;
        }
        if ((bVar2 != 0) || ((bVar1 & 0x10) != 0)) goto LAB_004065ba;
      }
    }
    else {
LAB_004065ba:
      move_node_result_to_destination(node);
    }
  }
  else if ((((desc->value).type & 0x1f) != 0) && (((desc->dest).type & 0x1f) != 0)) {
    load_node_address_register(node);
    store_node_value_through_address(node);
  }
  op = node->op;
  if (((((node->desc->usage == '\x01') && (op != IL_NOT)) && (op != IL_COND)) && (op != IL_COMMA))
     && ((((((op != IL_EQ && (op != IL_NE)) && ((op != IL_LE && ((op != IL_GE && (op != IL_LT))))))
           && (op != IL_GT)) && ((op != IL_AND && (op != IL_OR)))) ||
         ((node->desc->flags3 & 0x80) != 0)))) {
    emit_branch_on_node_value(node);
  }
  desc = node->desc;
  if (((desc->usage == '\0') && ((desc->flags2 & 0x40) != 0)) &&
     (((op == IL_ASTER || (op == IL_QUALIFY)) || ((op == IL_ID && ((desc->flags3 & 0x80) != 0))))))
  {
    local_1c = &desc->value;
    local_18 = new_ea_operand_with_flags('\x01',desc->regs_2c[0],-1,0,'\0',(label_ref *)0x0);
    local_14 = new_ea_operand_with_flags('\x01',node->desc->regs_2c[0],-1,0,'\0',(label_ref *)0x0);
    bVar1 = node->type;
    bVar2 = bVar1 & 0xe0;
    if ((bVar2 == 0x60) || (bVar2 == 0x80)) {
      if (((bVar1 & 0x18) == 0) || (bVar3 = bVar1 & 0xf8, bVar3 == 0)) {
        node->type = '\0';
      }
      else if ((((bVar2 == 0x60) || (bVar2 == 0x80)) && ((bVar1 & 0x18) == 8)) || (bVar3 == 8)) {
        node->type = '\b';
      }
      else if ((((bVar2 == 0x60) || (bVar2 == 0x80)) && ((bVar1 & 0x18) == 0x10)) ||
              (((bVar3 == 0x10 || (bVar3 == 0x18)) || ((bVar2 == 0x20 || (bVar2 == 0x40)))))) {
        node->type = '\x10';
      }
    }
    else {
      bVar2 = bVar1 & 0xf8;
      if ((bVar2 == 0x30) || (bVar2 == 0x38)) {
        node->type = '\x10';
      }
      else {
        if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
          bVar3 = 1;
        }
        else {
          bVar3 = -(g_request->cpu == 4) & 2;
        }
        if ((bVar3 != 0) && (bVar2 == 0x28)) {
          node->type = '\x10';
        }
      }
    }
    tmpl = select_transfer_template
                     (1,1,local_1c,local_18,local_14,node->type,node->desc->usage,node);
    if (tmpl != (tmpl_header *)0x0) {
      local_10 = 0;
      local_c = 0;
      local_8 = 0;
      local_4 = 0;
      emit_template_record_sequence_for_node(node,tmpl->entries,&local_1c);
    }
    node->type = bVar1;
    free_ea(local_18);
    free_ea(local_14);
  }
LAB_004067bd:
  if (((node->desc->usage == '\0') && (tmpl = node->desc->tmpl, tmpl != (tmpl_header *)0x0)) &&
     ((tmpl->flags & 0x10) != 0)) {
    if ((g_nested_operand_emit == '\x01') || (cVar4 = '\0', g_stmt_pushed_operand == '\x01')) {
      cVar4 = '\x01';
    }
    local_1c = copy_ea((ea *)&g_ea_imm8);
    local_18 = copy_ea((ea *)&g_ea_r15);
    emit_psd_for_node(0x60,-1,cVar4,'\x02',local_1c,local_18,(gen_node *)0x0);
  }
  return;
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8
#undef local_4
}



