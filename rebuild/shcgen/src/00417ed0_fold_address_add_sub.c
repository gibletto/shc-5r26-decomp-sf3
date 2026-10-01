#include "decls.h"
#include "imports.h"

// entry: 00417ed0
// name : fold_address_add_sub
// size : 875
// sig  : short fold_address_add_sub(gen_node * node, gen_node * left, gen_node * right)


short __cdecl fold_address_add_sub(gen_node *node,gen_node *left,gen_node *right)

{
  label_ref *list;
  byte bVar1;
  byte kind;
  short result;
  short reg;
  int too_long;
  ushort uVar2;
  uint fold_flags;
  node_desc *desc;
  uchar *flags_ptr;
  gen_node *parent;
  ushort *regs_ptr;
  
  fold_flags = 0;
  g_r0_index_loaded = 0;
  bVar1 = node->type & 0xf8;
  if ((((bVar1 == 0x10) || (bVar1 == 0x18)) || (bVar1 == 0x40)) || ((node->type & 0xe0) == 0x80)) {
    if (node->op == IL_ADD) {
      if (g_r0_variable != 0) {
        move_r0_variable_operand_into_r0(node,left,right);
      }
      uVar2 = fold_address_add(node,left,right);
    }
    else {
      if (node->op != IL_SUB) {
        report_codegen_message(0x1221,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        goto LAB_00417f79;
      }
      uVar2 = fold_address_sub(node,left,right);
    }
    fold_flags = (uint)uVar2;
  }
LAB_00417f79:
  result = (short)fold_flags;
  if ((fold_flags & 1) != 0) {
    parent = node->parent;
    bVar1 = (node->desc->value).type & 0x1f;
    if ((bVar1 == 2) || (bVar1 == 8)) {
      result = displacement_ok_for_dereference(node,fold_flags & 4);
    }
    if ((result != 0) && (too_long = ea_label_list_too_long(&node->desc->value), too_long == 0)) {
      desc = node->desc;
      bVar1 = (desc->value).type & 0x1f;
      if (((((bVar1 != 2) || ((desc->value).base != 'l')) &&
           ((bVar1 != 8 || ((desc->value).base != 'l')))) &&
          (((bVar1 != 2 && (bVar1 != 8)) ||
           (((desc->value).disp == 0 && ((desc->value).labels == (label_ref *)0x0)))))) ||
         ((parent->op != IL_ASTER || ((parent->type & 0xf8) != 0x48)))) {
        if (bVar1 == 1) {
          bVar1 = (desc->value).base;
          if (((((char)bVar1 < '\x0f') && ((1 << (bVar1 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)
               ) || (((char)bVar1 < ' ' &&
                     (('\x0f' < (char)bVar1 &&
                      ((1 << (bVar1 - 0x10 & 0x1f) & (int)(short)~g_var_fpr_mask) != 0)))))) ||
             (((char)bVar1 < '/' &&
              (('\x1f' < (char)bVar1 &&
               (((int)(short)g_var_fpr_mask &
                (1 << (bVar1 - 0x1f & 0x1f) | 1 << (bVar1 - 0x20 & 0x1f))) == 0)))))) {
            desc->opnd_class = '\0';
          }
          else {
            desc->opnd_class = '\x01';
          }
        }
        else if ((bVar1 == 7) && ((desc->value).labels == (label_ref *)0x0)) {
          desc->opnd_class = '\x02';
        }
        else {
          desc->opnd_class = '\x03';
        }
        reg = find_register_holding_constant(&node->desc->value,'@');
        if (reg == -1) {
          desc = node->desc;
          bVar1 = (desc->value).base;
          kind = (desc->value).type & 0x1f;
          if ((((kind != 0) && (kind != 0xd)) && (kind != 7)) &&
             (((kind != 0xe && (-1 < (char)bVar1)) && ((char)bVar1 < '\x0f')))) {
            uVar2 = 1 << (bVar1 & 0x1f);
            desc->busy_regs = desc->busy_regs | uVar2;
            g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
            regs_ptr = &node->desc->temp_regs;
            *regs_ptr = *regs_ptr | uVar2;
          }
          desc = node->desc;
          if (((((desc->value).type & 0x1f) == 9) && ((desc->value).index == '\0')) &&
             (g_r0_index_loaded == 0)) {
            desc->busy_regs = desc->busy_regs | 1;
            g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
            regs_ptr = &node->desc->temp_regs;
            *regs_ptr = *regs_ptr | 1;
          }
        }
        else {
          list = (node->desc->value).labels;
          if (list != (label_ref *)0x0) {
            free_label_ref_list(list);
          }
          bVar1 = (byte)reg;
          fill_ea(&node->desc->value,'\x01',bVar1,-1,'\0',0,(label_ref *)0x0);
          flags_ptr = &g_gpr_contents[reg].flags;
          if ((*flags_ptr & 0x80) == 0) {
            node->desc->opnd_class = '\0';
            uVar2 = 1 << (bVar1 & 0x1f);
            regs_ptr = &node->desc->busy_regs;
            *regs_ptr = *regs_ptr | uVar2;
            g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
            regs_ptr = &node->desc->temp_regs;
            *regs_ptr = *regs_ptr | uVar2;
            *flags_ptr = *flags_ptr | 0x80;
          }
          else {
            node->desc->opnd_class = '\x01';
            uVar2 = 1 << (bVar1 & 0x1f);
            regs_ptr = &node->desc->busy_regs;
            *regs_ptr = *regs_ptr | uVar2;
            g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
          }
          regs_ptr = &node->desc->reused_regs;
          *regs_ptr = *regs_ptr | uVar2;
        }
        node->desc->tmpl = (tmpl_header *)0x0;
        flags_ptr = &node->desc->flags3;
        *flags_ptr = *flags_ptr | 0x80;
        flags_ptr = &node->desc->flags3;
        *flags_ptr = *flags_ptr | 8;
        return result;
      }
    }
    bVar1 = (node->desc->value).type & 0x1f;
    if ((bVar1 == 7) || (bVar1 == 0xd)) {
      free_label_ref_list((node->desc->value).labels);
    }
    result = 0;
  }
  return result;
}



