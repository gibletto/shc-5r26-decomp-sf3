#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))
#undef g_used_fpr_mask
#define g_used_fpr_mask (*(unsigned char *)(g_sd + 0x1f9ac))
#undef g_used_gpr_mask
#define g_used_gpr_mask (*(unsigned char *)(g_sd + 0x1ff60))


// entry: 0041b070
// name : initialize_node_descriptor_and_operand_slots
// size : 2325
// sig  : void initialize_node_descriptor_and_operand_slots(gen_node * node)


int __cdecl initialize_node_descriptor_and_operand_slots(gen_node *node)

{
  short sVar1;
  ushort uVar2;
  char *str1;
  byte bVar3;
  node_desc *desc;
  uint uVar4;
  int iVar5;
  uint uVar6;
  gen_node *operand;
  gen_node *second_arg;
  gen_node *child;
  char parent_usage;
  byte bVar7;
  short *lreg_row;
  undefined **name_entry;
  int cmp;
  gen_node *pgVar8;
  char cVar9;
  byte *builtin_chars;
  byte *suffix_chars;
  bool bVar10;
  bool contains_call;
  uchar *flags_ptr;
  bool has_parent_desc;
  ushort lreg_sign;
  ushort *mask_ptr;
  il_op op;
  
  bVar10 = false;
  contains_call = false;
  if (node->op == IL_ID) {
    if (node->symx < 0) {
      uVar2 = node->lreg >> 0xf;
      sVar1 = *g_lreg_table;
      lreg_row = g_lreg_table;
      while ((sVar1 != 0 && (*lreg_row != (ushort)((node->lreg ^ uVar2) - uVar2)))) {
        lreg_row = lreg_row + 0x12;
        sVar1 = *lreg_row;
      }
      node->type = (uchar)lreg_row[2];
    }
    else {
      uVar6 = (int)node->symx + 0xb6;
      uVar4 = (int)uVar6 >> 0x1f;
      iVar5 = (uVar6 ^ uVar4) - uVar4;
      bVar3 = g_symbol_table[iVar5].type;
      node->type = bVar3;
      bVar3 = bVar3 & 0xf8;
      if (((((bVar3 == 0x60) || (bVar3 == 0x68)) || (bVar3 == 0x70)) ||
          ((bVar3 == 0x80 || (bVar3 == 0x88)))) || (bVar3 == 0x90)) {
        node->val = g_symbol_table[iVar5].size;
      }
    }
  }
  desc = alloc_zeroed(0x84);
  node->desc = desc;
  uVar6 = 0;
  do {
    uVar4 = uVar6 + 1;
    node->desc->regs_2c[uVar6] = -1;
    uVar6 = uVar4;
  } while (uVar4 < 5);
  uVar6 = 0;
  do {
    uVar4 = uVar6 + 1;
    node->desc->regs_34[uVar6] = -1;
    uVar6 = uVar4;
  } while (uVar4 < 4);
  uVar6 = 0;
  do {
    uVar4 = uVar6 + 1;
    node->desc->regs_41[uVar6] = -1;
    uVar6 = uVar4;
  } while (uVar4 < 3);
  uVar6 = 0;
  do {
    uVar4 = uVar6 + 1;
    node->desc->regs_44[uVar6] = -1;
    uVar6 = uVar4;
  } while (uVar4 < 2);
  uVar6 = 0;
  do {
    uVar4 = uVar6 + 1;
    node->desc->regs_3d[uVar6] = -1;
    uVar6 = uVar4;
  } while (uVar4 < 2);
  uVar6 = 0;
  do {
    uVar4 = uVar6 + 1;
    node->desc->cond_regs[uVar6] = -1;
    uVar6 = uVar4;
  } while (uVar4 < 5);
  node->desc->addr_reg = -1;
  node->desc->reg_47 = -1;
  pgVar8 = node->parent;
  cVar9 = '\0';
  op = pgVar8->op;
  iVar5 = operand_position(node);
  desc = pgVar8->desc;
  if (desc == (node_desc *)0x0) {
    parent_usage = '\0';
  }
  else {
    parent_usage = desc->usage;
  }
  has_parent_desc = desc != (node_desc *)0x0;
  switch(op) {
  case IL_BLOCK:
  case IL_GLABEL:
  case IL_CLABEL:
  case IL_DLABEL:
    break;
  default:
    report_codegen_message(0x1222,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    break;
  case IL_SWITCH:
    if (iVar5 == 1) {
      fill_ea(&node->desc->dest,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
      node->desc->pref_regs = 1;
      (*(unsigned char *)((char *)&g_used_gpr_mask + 0)) = (byte)g_used_gpr_mask | 1;
      flags_ptr = &node->desc->flags3;
      *flags_ptr = *flags_ptr | 1;
      g_r0_used = 1;
      cVar9 = '\x02';
    }
    break;
  case IL_IF:
    if (iVar5 == 1) {
      cVar9 = '\x01';
    }
    break;
  case IL_FOR:
    if (iVar5 == 4) {
      cVar9 = '\x01';
    }
    break;
  case IL_WHILE:
  case IL_DO:
    if (iVar5 == 2) {
      cVar9 = '\x01';
    }
    break;
  case IL_RETURN:
    cVar9 = '\x02';
    sVar1 = g_request->cpu;
    if ((sVar1 == 4) && ((node->type & 0xf8) == 0x30)) {
      fill_ea(&node->desc->dest,'\x01',' ',-1,'\0',0,(label_ref *)0x0);
      (*(unsigned char *)((char *)&g_used_fpr_mask + 0)) = (byte)g_used_fpr_mask | 3;
      mask_ptr = &node->desc->fpref_regs;
      *(byte *)mask_ptr = (byte)*mask_ptr | 3;
    }
    else {
      if ((sVar1 == 2) && (g_request->fpu_mode == '\x03')) {
        bVar3 = 1;
      }
      else {
        bVar3 = -(sVar1 == 4) & 2;
      }
      if ((bVar3 == 0) || ((node->type & 0xf8) != 0x28)) {
        bVar3 = node->type & 0xe0;
        if (((bVar3 == 0) ||
            (((bVar7 = node->type & 0xf8, bVar7 == 0x28 || (bVar7 == 0x40)) || (bVar3 == 0x80)))) ||
           (bVar7 == 0x48)) {
          fill_ea(&node->desc->dest,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
          (*(unsigned char *)((char *)&g_used_gpr_mask + 0)) = (byte)g_used_gpr_mask | 1;
          mask_ptr = &node->desc->pref_regs;
          *(byte *)mask_ptr = (byte)*mask_ptr | 1;
          g_r0_used = 1;
        }
        else {
          fill_ea(&node->desc->dest,'\b','l',-1,'\0',0,(label_ref *)0x0);
          flags_ptr = &node->desc->flags3;
          *flags_ptr = *flags_ptr | 0x20;
        }
      }
      else {
        fill_ea(&node->desc->dest,'\x01','\x10',-1,'\0',0,(label_ref *)0x0);
        (*(unsigned char *)((char *)&g_used_fpr_mask + 0)) = (byte)g_used_fpr_mask | 1;
        mask_ptr = &node->desc->fpref_regs;
        *(byte *)mask_ptr = (byte)*mask_ptr | 1;
      }
    }
    break;
  case IL_CAST:
  case IL_PLUS:
    cVar9 = parent_usage;
    if ((has_parent_desc) && (desc->usage == '\x01')) {
      cVar9 = '\x02';
    }
    break;
  case IL_MINUS:
  case IL_ASTER:
  case IL_CMPL:
  case IL_ARG:
    cVar9 = '\x02';
    break;
  case IL_AMPER:
  case IL_QUALIFY:
  case IL_B_QUALIFY:
    cVar9 = '\x03';
    break;
  case IL_NOT:
    cVar9 = parent_usage;
    break;
  case IL_CALL:
  case IL_A_ADD:
  case IL_A_SUB:
  case IL_A_MUL:
  case IL_A_DIV:
  case IL_A_MOD:
  case IL_A_SL:
  case IL_A_SR:
  case IL_A_AND:
  case IL_A_XOR:
  case IL_A_OR:
  case IL_ASSIGN:
    bVar10 = true;
    cVar9 = (iVar5 == 1) + '\x02';
    break;
  case IL_PRI:
  case IL_PRD:
  case IL_POI:
  case IL_POD:
    bVar10 = true;
    cVar9 = '\x03';
    break;
  case IL_ADD:
  case IL_SUB:
  case IL_MUL:
  case IL_DIV:
  case IL_MOD:
  case IL_SL:
  case IL_SR:
  case IL_B_AND:
  case IL_B_XOR:
  case IL_B_OR:
  case IL_EQ:
  case IL_NE:
  case IL_LT:
  case IL_LE:
  case IL_GT:
  case IL_GE:
    cVar9 = '\x02';
    break;
  case IL_AND:
  case IL_OR:
    if ((parent_usage != '\0') || (iVar5 != 2)) {
      cVar9 = '\x01';
    }
    break;
  case IL_COMMA:
    if (iVar5 == 2) {
      cVar9 = parent_usage;
    }
    break;
  case IL_COND:
    cVar9 = '\x01';
    if (iVar5 != 1) {
      cVar9 = parent_usage;
    }
  }
  node->desc->usage = cVar9;
  if (node->desc->usage == '\0') {
    if (node->op == IL_POI) {
      node->op = IL_PRI;
    }
    else if (node->op == IL_POD) {
      node->op = IL_PRD;
    }
  }
  bVar3 = node->type;
  bVar7 = bVar3 & 0xe0;
  if (((bVar7 == 0x60) || (bVar7 == 0x80)) &&
     ((((bVar3 & 0x18) == 0x10 || (((bVar3 & 0xf8) == 0x10 || ((bVar3 & 0xf8) == 0x18)))) ||
      ((bVar7 == 0x20 || (bVar7 == 0x40)))))) {
    flags_ptr = &node->desc->flags2;
    *flags_ptr = *flags_ptr | 1;
  }
  if ((node->type & 2) != 0) {
    flags_ptr = &node->desc->flags2;
    *flags_ptr = *flags_ptr | 0x40;
  }
  for (child = node->child; child != (gen_node *)0x0; child = child->next) {
    initialize_node_descriptor_and_operand_slots(child);
    mask_ptr = &node->desc->need_regs;
    *mask_ptr = *mask_ptr | child->desc->need_regs;
  }
  if ((has_parent_desc) && (((node->desc->flags2 & 0x40) != 0 || (bVar10)))) {
    flags_ptr = &pgVar8->desc->flags2;
    *flags_ptr = *flags_ptr | 0x40;
  }
  if (node->op != IL_CALL) goto LAB_0041b732;
  child = node->child;
  if ((((child != (gen_node *)0x0) && (child->op == IL_ID)) && (0 < child->symx)) &&
     (uVar6 = (int)child->symx + 0xb6, uVar4 = (int)uVar6 >> 0x1f,
     str1 = g_symbol_table[(uVar6 ^ uVar4) - uVar4].name, str1 != (char *)0x0)) {
    iVar5 = stock_strncmp(str1,s__builtin__0045841c,9);
    if (iVar5 == 0) {
      iVar5 = 0;
      name_entry = &g_builtin_names;
      do {
        builtin_chars = *name_entry;
        suffix_chars = (byte *)(str1 + 9);
        do {
          bVar3 = *suffix_chars;
          bVar10 = bVar3 < *builtin_chars;
          if (bVar3 != *builtin_chars) {
LAB_0041b55f:
            cmp = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
            goto LAB_0041b564;
          }
          if (bVar3 == 0) break;
          bVar3 = suffix_chars[1];
          bVar10 = bVar3 < builtin_chars[1];
          if (bVar3 != builtin_chars[1]) goto LAB_0041b55f;
          suffix_chars = suffix_chars + 2;
          builtin_chars = builtin_chars + 2;
        } while (bVar3 != 0);
        cmp = 0;
LAB_0041b564:
        if (cmp == 0) {
          node->desc->builtin = (&g_builtin_ids)[iVar5];
          break;
        }
        name_entry = name_entry + 1;
        iVar5 = iVar5 + 1;
      } while (name_entry < &g_builtin_names_end);
    }
    cVar9 = node->desc->builtin;
    if ((cVar9 == '\x16') || (cVar9 == '\x17')) {
      child = node->child;
      operand = (gen_node *)0x0;
      if (child != (gen_node *)0x0) {
        operand = child->next;
      }
      if (operand == (gen_node *)0x0) {
        operand = (gen_node *)0x0;
      }
      else {
        if (child != (gen_node *)0x0) {
          operand = child->next->child;
        }
        else {
          operand = (*(gen_node * *)0x00000010);
        }
      }
      second_arg = (gen_node *)0x0;
      if (child != (gen_node *)0x0) {
        second_arg = child->next;
      }
      if (second_arg == (gen_node *)0x0) {
LAB_0041b5f7:
        second_arg = (gen_node *)0x0;
      }
      else {
        second_arg = (gen_node *)0x0;
        if (child != (gen_node *)0x0) {
          second_arg = child->next;
        }
        if (second_arg->child == (gen_node *)0x0) goto LAB_0041b5f7;
        if (child == (gen_node *)0x0) {
          second_arg = (*(gen_node * *)0x00000010)->next;
        }
        else {
          second_arg = child->next->child->next;
        }
      }
      bVar3 = operand->type;
      if ((((bVar3 & 0xe0) == 0x80) &&
          ((((bVar3 & 0x18) == 0x10 || ((bVar3 & 0xf8) == 0x10)) || ((bVar3 & 0xf8) == 0x18)))) ||
         (((operand->op == IL_ID && (0 < operand->symx)) &&
          ((uVar6 = (int)operand->symx + 0xb6, uVar4 = (int)uVar6 >> 0x1f,
           g_symbol_table[(uVar6 ^ uVar4) - uVar4].sclass == '\t' ||
           (((bVar3 & 0xe0) == 0x80 && (g_symbol_table[(uVar6 ^ uVar4) - uVar4].sclass == '\x05'))))
          )))) {
        bVar3 = second_arg->type;
        if ((((bVar3 & 0xe0) == 0x80) &&
            ((((bVar3 & 0x18) == 0x10 || ((bVar3 & 0xf8) == 0x10)) || ((bVar3 & 0xf8) == 0x18)))) ||
           (((second_arg->op == IL_ID && (0 < second_arg->symx)) &&
            ((uVar6 = (int)second_arg->symx + 0xb6, uVar4 = (int)uVar6 >> 0x1f,
             g_symbol_table[(uVar6 ^ uVar4) - uVar4].sclass == '\t' ||
             (((bVar3 & 0xe0) == 0x80 && (g_symbol_table[(uVar6 ^ uVar4) - uVar4].sclass == '\x05'))
             )))))) {
          operand = (gen_node *)0x0;
          if (child != (gen_node *)0x0) {
            operand = child->next;
          }
          flags_ptr = &operand->desc->flags2;
          *flags_ptr = *flags_ptr | 1;
        }
      }
    }
  }
  cVar9 = node->desc->builtin;
  if ((cVar9 == '\0') || ((('\x17' < cVar9 && (cVar9 < '\x1c')) || (cVar9 == '\x1c')))) {
    mask_ptr = &node->desc->need_regs;
    *(byte *)mask_ptr = (byte)*mask_ptr | 0xf0;
  }
  cVar9 = node->desc->builtin;
  if ((cVar9 == '\0') || (cVar9 == '\x1c')) {
    contains_call = true;
  }
  if (cVar9 == '\0') {
    flags_ptr = &node->desc->flags7;
    *flags_ptr = *flags_ptr | 0x20;
  }
LAB_0041b732:
  if ((has_parent_desc) && (((node->desc->flags7 & 0x10) != 0 || (contains_call)))) {
    flags_ptr = &pgVar8->desc->flags7;
    *flags_ptr = *flags_ptr | 0x10;
  }
  mark_node_clobbering_r0(node);
  if ((((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) &&
      (node->op == IL_ASTER)) &&
     ((((node->type & 0xe0) == 0 || (bVar3 = node->type & 0xf8, bVar3 == 0x40)) || (bVar3 == 0x28)))
     ) {
    count_indexed_address_operands(node);
  }
  if (node->op == IL_ID) {
    flags_ptr = &node->desc->flags3;
    *flags_ptr = *flags_ptr | 0x80;
    uVar2 = node->lreg;
    lreg_sign = (short)uVar2 >> 0xf;
    sVar1 = g_request->cpu;
    if ((sVar1 != 2) || (bVar3 = 1, g_request->fpu_mode != '\x03')) {
      bVar3 = -(sVar1 == 4) & 2;
    }
    if (((bVar3 == 0) || ((node->type & 0xf8) != 0x28)) &&
       ((sVar1 != 4 || ((node->type & 0xf8) != 0x30)))) {
      if (uVar2 == 0x8000) {
        mask_ptr = &node->desc->need_regs;
        *mask_ptr = *mask_ptr | 0x8000;
      }
      else if ((uVar2 ^ lreg_sign) == lreg_sign) {
        uVar6 = (int)node->symx + 0xb6;
        uVar4 = (int)uVar6 >> 0x1f;
        iVar5 = (uVar6 ^ uVar4) - uVar4;
        if ((g_symbol_table[iVar5].storage.type & 0x1f) == 1) {
          mask_ptr = &node->desc->need_regs;
          *mask_ptr = *mask_ptr | 1 << (g_symbol_table[iVar5].storage.base & 0x1fU);
        }
      }
      else {
        sVar1 = *g_lreg_table;
        lreg_row = g_lreg_table;
        while ((sVar1 != 0 && (*lreg_row != (ushort)((uVar2 ^ lreg_sign) - lreg_sign)))) {
          lreg_row = lreg_row + 0x12;
          sVar1 = *lreg_row;
        }
        if (0 < lreg_row[1]) {
          mask_ptr = &node->desc->need_regs;
          *mask_ptr = *mask_ptr | 1 << ((byte)lreg_row[1] & 0x1f);
        }
      }
    }
  }
  op = node->op;
  if (((op == IL_MUL) || (op == IL_DIV)) || (op == IL_MOD)) {
    child = node->child;
    operand = (gen_node *)0x0;
    if (child == (gen_node *)0x0) {
      child = (gen_node *)0x0;
    }
    else {
      operand = child->next;
      child = child->next;
    }
    operand->type = child->type & 3 | node->type;
  }
  op = node->op;
  if ((('O' < (char)op) && ((char)op < '_')) || (('7' < (char)op && ((char)op < '>')))) {
    node->child->type = node->type;
  }
  if (node->op == IL_ASSIGN) {
    bVar3 = node->child->type & 0xe0;
    if ((bVar3 != 0x60) && (bVar3 != 0x80)) {
      node->child->type = node->type;
    }
  }
  if ((has_parent_desc) && ((node->desc->flags7 & 0x20) != 0)) {
    flags_ptr = &pgVar8->desc->flags7;
    *flags_ptr = *flags_ptr | 0x20;
  }
  if (((node->type & 0xf8) == 0x28) && ((node->op == IL_ADD || (node->op == IL_A_ADD)))) {
    pgVar8 = node->child;
    if (pgVar8->op != IL_MUL) {
      if (pgVar8 == (gen_node *)0x0) {
        pgVar8 = (gen_node *)0x0;
      }
      else {
        pgVar8 = pgVar8->next;
      }
      if (pgVar8->op != IL_MUL) {
        return;
      }
    }
    if ((pgVar8->type & 0xf8) == 0x28) {
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        bVar3 = 1;
      }
      else {
        bVar3 = -(g_request->cpu == 4) & 2;
      }
      if (bVar3 != 0) {
        flags_ptr = &node->desc->flags7;
        *flags_ptr = *flags_ptr | 0x80;
        flags_ptr = &pgVar8->desc->flags7;
        *flags_ptr = *flags_ptr | 0x80;
      }
    }
  }
  return;
}



