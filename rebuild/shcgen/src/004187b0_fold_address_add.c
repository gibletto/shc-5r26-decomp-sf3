#include "decls.h"
#include "imports.h"
#include "memindexrules.h"

// entry: 004187b0
// name : fold_address_add
// size : 3463
// sig  : short fold_address_add(gen_node * node, gen_node * left, gen_node * right)


short __cdecl fold_address_add(gen_node *node,gen_node *left,gen_node *right)

{
  unsigned char _frec_1a[26];
#define left_class (*(short *)(_frec_1a + 0))
#define right_class (*(short *)(_frec_1a + 2))
#define fold_result (*(short *)(_frec_1a + 4))
#define local_10 (*(ea * *)(_frec_1a + 10))
#define const_class (*(short *)(_frec_1a + 14))
#define const_node (*(gen_node * *)(_frec_1a + 18))
#define saved_content_hit (*(int *)(_frec_1a + 22))
  int iVar1;
  byte bVar2;
  short reg;
  ushort uVar3;
  node_desc **desc_ref;
  label_ref *merged_labels;
  uint uVar4;
  uint uVar5;
  ea *value_ea;
  ea *peVar6;
  ea *peVar7;
  char cVar8;
  gen_node *pgVar9;
  node_desc *desc;
  int *disp_ptr;
  uchar *flags_ptr;
  gen_node *grandparent;
  int left_disp;
  il_op op;
  ushort *regs_ptr;
  tmpl_header *tmpl;
  
  fold_result = 0;
  left_class = classify_address_operand(left);
  right_class = classify_address_operand(right);
  desc = left->desc;
  bVar2 = 0;
  peVar7 = desc->mem_ea;
  if (peVar7 != (ea *)0x0) {
    bVar2 = peVar7->type & 0x1f;
  }
  if (((bVar2 == 0) && (peVar7 = &desc->dest, (peVar7->type & 0x1f) == 0)) &&
     (peVar7 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    peVar7 = &desc->value;
  }
  desc = right->desc;
  bVar2 = 0;
  peVar6 = desc->mem_ea;
  if (peVar6 != (ea *)0x0) {
    bVar2 = peVar6->type & 0x1f;
  }
  if (((bVar2 == 0) && (peVar6 = &desc->dest, (peVar6->type & 0x1f) == 0)) &&
     (peVar6 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    peVar6 = &desc->value;
  }
  const_node = (gen_node *)0x0;
  pgVar9 = node->parent;
  if (((left_class == 6) || (left_class == 7)) && ((right_class == 1 || (right_class == 3)))) {
    const_node = right;
    local_10 = peVar6;
    const_class = left_class;
  }
  else if (((right_class == 6) || (right_class == 7)) && ((left_class == 1 || (left_class == 3)))) {
    const_node = left;
    local_10 = peVar7;
    const_class = right_class;
  }
  if (const_node != (gen_node *)0x0) {
    saved_content_hit = g_content_hit;
    reg = find_register_holding_constant(local_10,'@');
    if ((reg != -1) && (((const_class == 6 && (reg != 0)) || ((const_class == 7 && (reg == 0)))))) {
      if (local_10->labels != (label_ref *)0x0) {
        free_label_ref_list(local_10->labels);
      }
      saved_content_hit = g_content_hit;
      bVar2 = (byte)reg;
      fill_ea(local_10,'\x01',bVar2,-1,'\0',0,(label_ref *)0x0);
      flags_ptr = &g_gpr_contents[reg].flags;
      if ((*flags_ptr & 0x80) == 0) {
        desc_ref = &const_node->desc;
        (*desc_ref)->opnd_class = '\0';
        uVar3 = 1 << (bVar2 & 0x1f);
        (*desc_ref)->busy_regs = (*desc_ref)->busy_regs | uVar3;
        g_used_gpr_mask = g_used_gpr_mask | (*desc_ref)->busy_regs;
        (*desc_ref)->temp_regs = (*desc_ref)->temp_regs | uVar3;
        *flags_ptr = *flags_ptr | 0x80;
      }
      else {
        desc_ref = &const_node->desc;
        (*desc_ref)->opnd_class = '\x01';
        uVar3 = 1 << (bVar2 & 0x1f);
        (*desc_ref)->busy_regs = (*desc_ref)->busy_regs | uVar3;
        g_used_gpr_mask = g_used_gpr_mask | (*desc_ref)->busy_regs;
      }
      local_10 = (ea *)&const_node->desc;
      (*(node_desc **)local_10)->reused_regs = (*(node_desc **)local_10)->reused_regs | uVar3;
      if ((pgVar9 != (gen_node *)0x0) && (pgVar9->desc != (node_desc *)0x0)) {
        regs_ptr = &pgVar9->desc->reused_regs;
        *regs_ptr = *regs_ptr | (*(node_desc **)local_10)->reused_regs;
      }
      if (left == const_node) {
        left_class = classify_address_operand(left);
      }
      else {
        right_class = classify_address_operand(right);
      }
    }
    g_content_hit = saved_content_hit;
  }
  switch((&g_add_fold_kind)[(int)right_class + left_class * 9]) {
  default:
    report_codegen_message(0x1221,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    break;
  case 1:
    if (left_class == 2) {
      iVar1 = peVar7->disp;
      if (iVar1 < 0) {
        if (peVar6->disp + iVar1 < -3) goto LAB_00418abe;
        if (iVar1 < 0) {
          return 0;
        }
      }
      if (peVar6->disp + iVar1 < 0) {
        return 0;
      }
    }
LAB_00418abe:
    copy_words((uint *)&node->desc->value,(uint *)peVar7,3);
    disp_ptr = &(node->desc->value).disp;
    *disp_ptr = *disp_ptr + peVar6->disp;
    merged_labels = combine_label_ref_lists(peVar7->labels,peVar6->labels,1);
    fold_result = 1;
    (node->desc->value).labels = merged_labels;
    break;
  case 2:
    if (right_class == 2) {
      iVar1 = peVar6->disp;
      if (iVar1 < 0) {
        if (peVar7->disp + iVar1 < -3) goto LAB_00418b29;
        if (iVar1 < 0) {
          return 0;
        }
      }
      if (peVar7->disp + iVar1 < 0) {
        return 0;
      }
    }
LAB_00418b29:
    copy_words((uint *)&node->desc->value,(uint *)peVar6,3);
    disp_ptr = &(node->desc->value).disp;
    *disp_ptr = *disp_ptr + peVar7->disp;
    merged_labels = combine_label_ref_lists(peVar7->labels,peVar6->labels,1);
    fold_result = 1;
    (node->desc->value).labels = merged_labels;
    break;
  case 3:
    if ((pgVar9->op == IL_ASTER) &&
       ((((pgVar9->type & 0xe0) == 0 || (bVar2 = pgVar9->type & 0xf8, bVar2 == 0x40)) ||
        (bVar2 == 0x28)))) {
      copy_words((uint *)&node->desc->value,(uint *)peVar7,3);
      if (peVar7->base == '\0') {
        (node->desc->value).base = peVar6->base;
      }
      (node->desc->value).index = '\0';
      peVar7 = &node->desc->value;
      peVar7->type = peVar7->type & 0xf9 | 9;
      fold_result = 1;
      peVar7 = &node->desc->value;
      peVar7->type = peVar7->type | 0x40;
    }
    break;
  case 4:
    if (((left_class == 7) && (pgVar9->op == IL_ASTER)) &&
       ((((pgVar9->type & 0xe0) == 0 ||
         ((bVar2 = pgVar9->type & 0xf8, bVar2 == 0x40 || (bVar2 == 0x28)))) &&
        (reg = fold_large_displacement_into_r0_index(node,left,right), reg != 0)))) {
      return 1;
    }
    iVar1 = peVar6->disp;
    left_disp = peVar7->disp;
    copy_words((uint *)&node->desc->value,(uint *)peVar7,3);
    (node->desc->value).disp = iVar1 + left_disp;
    merged_labels = combine_label_ref_lists(peVar7->labels,peVar6->labels,1);
    (node->desc->value).labels = merged_labels;
    value_ea = &node->desc->value;
    value_ea->type = value_ea->type & 0xf8 | 8;
    value_ea = &node->desc->value;
    value_ea->type = value_ea->type | 0x40;
    if (peVar7->disp == 0) {
      return 1;
    }
    iVar1 = peVar6->disp;
    goto joined_r0x00418d24;
  case 5:
    if (((right_class == 7) && (pgVar9->op == IL_ASTER)) &&
       ((((pgVar9->type & 0xe0) == 0 ||
         ((bVar2 = pgVar9->type & 0xf8, bVar2 == 0x40 || (bVar2 == 0x28)))) &&
        (reg = fold_large_displacement_into_r0_index(node,left,right), reg != 0)))) {
      return 1;
    }
    iVar1 = peVar6->disp;
    left_disp = peVar7->disp;
    copy_words((uint *)&node->desc->value,(uint *)peVar6,3);
    (node->desc->value).disp = iVar1 + left_disp;
    merged_labels = combine_label_ref_lists(peVar7->labels,peVar6->labels,1);
    (node->desc->value).labels = merged_labels;
    value_ea = &node->desc->value;
    value_ea->type = value_ea->type & 0xf8 | 8;
    value_ea = &node->desc->value;
    value_ea->type = value_ea->type | 0x40;
    if (peVar7->disp == 0) {
      return 1;
    }
    iVar1 = peVar6->disp;
joined_r0x00418d24:
    if (iVar1 == 0) {
      return 1;
    }
    goto LAB_00419523;
  case 6:
    if (((pgVar9->op == IL_ASTER) &&
        ((((pgVar9->type & 0xe0) == 0 || (bVar2 = pgVar9->type & 0xf8, bVar2 == 0x40)) ||
         (bVar2 == 0x28)))) &&
       (reg = fold_large_displacement_into_r0_index(node,left,right), reg != 0)) {
      fold_result = 1;
    }
    else if ((node->type & 0xe0) == 0x80) {
      iVar1 = peVar6->disp;
      cVar8 = peVar7->base;
      left_disp = peVar7->disp;
      if (cVar8 == -1) {
        cVar8 = peVar6->base;
      }
      merged_labels = combine_label_ref_lists(peVar7->labels,peVar6->labels,1);
      fill_ea(&node->desc->value,'\b',cVar8,-1,'\0',iVar1 + left_disp,merged_labels);
      fold_result = 1;
      peVar7 = &node->desc->value;
      peVar7->type = peVar7->type | 0x40;
    }
    break;
  case 7:
    if (pgVar9->op == IL_ASTER) {
      if (pgVar9->desc->usage == '\x03') {
        grandparent = pgVar9->parent;
        op = grandparent->op;
        if ((op == IL_ASSIGN) && ((grandparent->desc->flags7 & 0x20) != 0)) {
          return 0;
        }
        if (((('7' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`')))) &&
           ((tmpl = grandparent->desc->tmpl, tmpl != (tmpl_header *)0x0 &&
            ((tmpl->excluded & 1) != 0)))) {
          return 0;
        }
      }
      if (((((pgVar9->type & 0xe0) == 0) || (bVar2 = pgVar9->type & 0xf8, bVar2 == 0x40)) ||
          (bVar2 == 0x28)) &&
         ((left->desc->opnd_class == '\x01' && (right->desc->opnd_class == '\x01')))) {
        fill_ea(&right->desc->dest,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
        g_r0_used = 1;
        desc = right->desc;
        peVar6 = &left->desc->value;
        pgVar9 = right;
        uVar4 = ea_register_mask(peVar6);
        uVar5 = ea_register_mask(peVar6);
        emit_operand_transfer
                  (&desc->value,&desc->dest,'0',right,0xc00,right->type,
                   uVar5 | (int)(short)node->desc->busy_regs,uVar4,(int)pgVar9);
        copy_words((uint *)&node->desc->value,(uint *)peVar7,3);
        (node->desc->value).index = '\0';
        peVar7 = &node->desc->value;
        peVar7->type = peVar7->type & 0xf9 | 9;
        fold_result = 1;
        peVar7 = &node->desc->value;
        peVar7->type = peVar7->type | 0x40;
      }
    }
    break;
  case 8:
    if (pgVar9->op != IL_ASTER) {
      return 0;
    }
    if ((((pgVar9->type & 0xe0) != 0) && (bVar2 = pgVar9->type & 0xf8, bVar2 != 0x40)) &&
       (bVar2 != 0x28)) {
      return 0;
    }
    if ((int)left->desc - (int)peVar7 != -0x68) {
      return 0;
    }
    if ((int)right->desc - (int)peVar6 != -0x68) {
      return 0;
    }
    if ((node->desc->flags2 & 0x80) != 0) {
      return 0;
    }
    if (left_class == 7 && MEM_INDEX_PLAIN(node,left,right)) {
      return 0;
    }
    if (left_class == 7) {
      g_r0_used = 1;
      reg = 0;
    }
    else {
      cVar8 = '\0';
      uVar3 = 0;
      uVar4 = result_reg_exclusion_mask(node);
      reg = choose_general_register((ushort)uVar4 | 1,uVar3,cVar8);
      if (reg == -1) {
        reg = choose_general_register(1,0,'\0');
      }
    }
    fill_ea(&right->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
    desc = right->desc;
    pgVar9 = right;
    uVar4 = ea_register_mask(peVar7);
    uVar5 = ea_register_mask(peVar7);
    emit_operand_transfer
              (&desc->value,&desc->dest,'0',right,0xc00,right->type,
               uVar5 | (int)(short)node->desc->busy_regs,uVar4,(int)pgVar9);
    record_variable_in_register(right,reg);
    regs_ptr = &node->desc->cached_regs;
    *regs_ptr = *regs_ptr | right->desc->cached_regs;
    if (left_class == 7) {
      copy_words((uint *)&node->desc->value,(uint *)peVar7,3);
      (node->desc->value).index = '\0';
      peVar7 = &node->desc->value;
      peVar7->type = peVar7->type & 0xf9 | 9;
    }
    else if (left_class == 6) {
      copy_words((uint *)&node->desc->value,(uint *)&right->desc->dest,3);
      (node->desc->value).index = '\0';
      peVar7 = &node->desc->value;
      peVar7->type = peVar7->type & 0xf9 | 9;
    }
    else {
      merged_labels = combine_label_ref_lists(peVar7->labels,(label_ref *)0x0,1);
      fill_ea(&node->desc->value,'\b',(char)reg,-1,'\0',peVar7->disp,merged_labels);
    }
    goto LAB_0041951c;
  case 9:
    if (pgVar9->op != IL_ASTER) {
      return 0;
    }
    if ((((pgVar9->type & 0xe0) != 0) && (bVar2 = pgVar9->type & 0xf8, bVar2 != 0x40)) &&
       (bVar2 != 0x28)) {
      return 0;
    }
    if ((int)left->desc - (int)peVar7 != -0x68) {
      return 0;
    }
    if ((int)right->desc - (int)peVar6 != -0x68) {
      return 0;
    }
    if ((node->desc->flags2 & 0x80) != 0) {
      return 0;
    }
    if (right_class == 7 && MEM_INDEX_PLAIN(node,left,right)) {
      return 0;
    }
    if (right_class == 7) {
      g_r0_used = 1;
      reg = 0;
    }
    else {
      cVar8 = '\0';
      uVar3 = 0;
      uVar4 = result_reg_exclusion_mask(node);
      reg = choose_general_register((ushort)uVar4 | 1,uVar3,cVar8);
      if (reg == -1) {
        reg = choose_general_register(1,0,'\0');
      }
    }
    copy_ea_into(&left->desc->dest,&left->desc->value);
    peVar7 = alloc_zeroed(0xc);
    left->desc->addr_reg_ea = peVar7;
    fill_ea(left->desc->addr_reg_ea,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
    peVar7 = copy_ea(left->desc->addr_reg_ea);
    left->desc->mem_ea = peVar7;
    flags_ptr = &left->desc->flags3;
    *flags_ptr = *flags_ptr | 4;
    pgVar9 = left;
    uVar4 = ea_register_mask(peVar6);
    uVar5 = ea_register_mask(peVar6);
    emit_operand_transfer
              (&left->desc->dest,left->desc->addr_reg_ea,'P',left,0xc00,left->type,
               uVar5 | (int)(short)node->desc->busy_regs,uVar4,(int)pgVar9);
    record_variable_in_register(left,reg);
    regs_ptr = &node->desc->cached_regs;
    *regs_ptr = *regs_ptr | left->desc->cached_regs;
    if (right_class == 7) {
      copy_words((uint *)&node->desc->value,(uint *)peVar6,3);
      (node->desc->value).index = '\0';
      peVar7 = &node->desc->value;
      peVar7->type = peVar7->type & 0xf9 | 9;
    }
    else if (right_class == 6) {
      desc = left->desc;
      bVar2 = 0;
      peVar7 = desc->mem_ea;
      if (peVar7 != (ea *)0x0) {
        bVar2 = peVar7->type & 0x1f;
      }
      if (((bVar2 == 0) && (peVar7 = &desc->dest, (peVar7->type & 0x1f) == 0)) &&
         (peVar7 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        peVar7 = &desc->value;
      }
      copy_words((uint *)&node->desc->value,(uint *)peVar7,3);
      (node->desc->value).index = '\0';
      peVar7 = &node->desc->value;
      peVar7->type = peVar7->type & 0xf9 | 9;
    }
    else {
      merged_labels = combine_label_ref_lists((label_ref *)0x0,peVar6->labels,1);
      fill_ea(&node->desc->value,'\b',(char)reg,-1,'\0',peVar6->disp,merged_labels);
    }
    goto LAB_0041951c;
  case 10:
    if (pgVar9->op != IL_ASTER) {
      return 0;
    }
    if ((((pgVar9->type & 0xe0) != 0) && (bVar2 = pgVar9->type & 0xf8, bVar2 != 0x40)) &&
       (bVar2 != 0x28)) {
      return 0;
    }
    if ((int)left->desc - (int)peVar7 != -0x68) {
      return 0;
    }
    if ((int)right->desc - (int)peVar6 != -0x68) {
      return 0;
    }
    if ((node->desc->flags2 & 0x80) != 0) {
      return 0;
    }
    cVar8 = '\0';
    uVar3 = 0;
    uVar4 = ea_register_mask(peVar7);
    uVar5 = result_reg_exclusion_mask(node);
    reg = choose_general_register((ushort)uVar4 | (ushort)uVar5 | 1,uVar3,cVar8);
    if (reg == -1) {
      cVar8 = '\0';
      uVar3 = 0;
      uVar4 = ea_register_mask(peVar7);
      reg = choose_general_register((ushort)uVar4 | 1,uVar3,cVar8);
    }
    fill_ea(&right->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
    desc = right->desc;
    pgVar9 = right;
    uVar4 = ea_register_mask(peVar7);
    uVar5 = ea_register_mask(peVar7);
    emit_operand_transfer
              (&desc->value,&desc->dest,'0',right,0xc00,right->type,
               uVar5 | (int)(short)node->desc->busy_regs,uVar4,(int)pgVar9);
    record_variable_in_register(right,reg);
    regs_ptr = &node->desc->cached_regs;
    *regs_ptr = *regs_ptr | right->desc->cached_regs;
    desc = right->desc;
    bVar2 = 0;
    peVar7 = desc->mem_ea;
    if (peVar7 != (ea *)0x0) {
      bVar2 = peVar7->type & 0x1f;
    }
    if (((bVar2 == 0) && (peVar7 = &desc->dest, (peVar7->type & 0x1f) == 0)) &&
       (peVar7 = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      peVar7 = &desc->value;
    }
    copy_ea_into(&left->desc->dest,&left->desc->value);
    peVar6 = alloc_zeroed(0xc);
    left->desc->addr_reg_ea = peVar6;
    fill_ea(left->desc->addr_reg_ea,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
    g_r0_used = 1;
    desc = left->desc;
    peVar6 = copy_ea(desc->addr_reg_ea);
    desc->mem_ea = peVar6;
    flags_ptr = &left->desc->flags3;
    *flags_ptr = *flags_ptr | 4;
    desc = left->desc;
    pgVar9 = left;
    uVar4 = ea_register_mask(peVar7);
    uVar5 = ea_register_mask(peVar7);
    emit_operand_transfer
              (&desc->dest,desc->addr_reg_ea,'P',left,0xc00,left->type,
               uVar5 | (int)(short)node->desc->busy_regs,uVar4,(int)pgVar9);
    if (left->op == IL_ID) {
      record_variable_in_register(left,0);
      regs_ptr = &node->desc->cached_regs;
      *regs_ptr = *regs_ptr | left->desc->cached_regs;
    }
    copy_words((uint *)&node->desc->value,(uint *)peVar7,3);
    (node->desc->value).index = '\0';
    peVar7 = &node->desc->value;
    peVar7->type = peVar7->type & 0xf9 | 9;
LAB_0041951c:
    peVar7 = &node->desc->value;
    peVar7->type = peVar7->type | 0x40;
LAB_00419523:
    fold_result = 5;
    break;
  case 0xff:
    break;
  }
  return fold_result;
#undef left_class
#undef right_class
#undef fold_result
#undef local_10
#undef const_class
#undef const_node
#undef saved_content_hit
}



