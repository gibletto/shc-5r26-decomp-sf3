#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_r0_variable
#define g_r0_variable (*(short * *)(g_sd + 0x1f9a8))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004042e0
// name : prepare_identifier_node
// size : 1350
// sig  : void prepare_identifier_node(gen_node * node)


int __cdecl prepare_identifier_node(gen_node *node)

{
  ea *dst;
  byte bVar1;
  short sVar2;
  sym_entry *sym;
  ea *ea_copy;
  short *lreg_rec;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char base;
  gen_node *pgVar7;
  node_desc *desc;
  uchar *flags_p;
  ushort *regs_p;
  
  desc = node->desc;
  dst = &desc->value;
  if (((g_request->cpu == 4) && ((node->type & 0xf8) == 0x30)) || (desc->usage == '\x03')) {
    sVar2 = -1;
  }
  else {
    sVar2 = find_register_holding_variable(node);
  }
  if (sVar2 != -1) {
    iVar6 = (int)sVar2;
    bVar1 = (byte)sVar2;
    fill_ea(dst,'\x01',bVar1,-1,'\0',0,(label_ref *)0x0);
    if (((sVar2 < 0x10) || (0x13 < sVar2)) ||
       (((&g_fpr_contents_flags_by_reg)[iVar6 * 0x18] & 0x80) == 0)) {
      if (((sVar2 < 0) || (3 < sVar2)) ||
         (((g_gpr_contents[iVar6].flags & 0x80) == 0 &&
          (((g_r0_variable == (short *)0x0 || (node->symx != *g_r0_variable)) ||
           (uVar4 = (int)node->lreg >> 0x1f,
           (int)g_r0_variable[1] != ((int)node->lreg ^ uVar4) - uVar4)))))) {
        node->desc->opnd_class = '\0';
        if ((sVar2 < 0x10) || (0x13 < sVar2)) {
          uVar3 = 1 << (bVar1 & 0x1f);
          regs_p = &node->desc->busy_regs;
          *regs_p = *regs_p | uVar3;
          g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
          regs_p = &node->desc->temp_regs;
          *regs_p = *regs_p | uVar3;
          g_gpr_contents[iVar6].flags = g_gpr_contents[iVar6].flags | 0x80;
        }
        else {
          uVar3 = 1 << (bVar1 - 0x10 & 0x1f);
          regs_p = &node->desc->fbusy_regs;
          *regs_p = *regs_p | uVar3;
          g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
          regs_p = &node->desc->ftemp_regs;
          *regs_p = *regs_p | uVar3;
          (&g_fpr_contents_flags_by_reg)[iVar6 * 0x18] =
               (&g_fpr_contents_flags_by_reg)[iVar6 * 0x18] | 0x80;
        }
      }
      else {
        node->desc->opnd_class = '\x01';
        regs_p = &node->desc->busy_regs;
        *regs_p = *regs_p | 1 << (bVar1 & 0x1f);
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
      }
    }
    else {
      node->desc->opnd_class = '\x01';
      regs_p = &node->desc->fbusy_regs;
      *regs_p = *regs_p | 1 << (bVar1 - 0x10 & 0x1f);
      g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
    }
    regs_p = &node->desc->reused_regs;
    *regs_p = *regs_p | 1 << (bVar1 & 0x1f);
    regs_p = &node->desc->freused_regs;
    *regs_p = *regs_p | 1 << (bVar1 - 0x10 & 0x1f);
    return;
  }
  uVar3 = node->lreg;
  if (uVar3 == 0x8000) {
    sVar2 = g_request->cpu;
    if ((sVar2 == 4) && ((node->type & 0xf8) == 0x30)) {
      base = '.';
    }
    else {
      if ((sVar2 == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(sVar2 == 4) & 2;
      }
      if ((bVar1 == 0) || ((node->type & 0xf8) != 0x28)) {
        base = '\x0f';
      }
      else {
        base = '\x1f';
      }
    }
    fill_ea(&node->desc->value,'\x01',base,-1,'\0',0,(label_ref *)0x0);
    node->desc->opnd_class = '\x01';
    return;
  }
  if (uVar3 != 0) {
    sVar2 = *g_lreg_table;
    lreg_rec = g_lreg_table;
    while ((sVar2 != 0 &&
           (*lreg_rec != (ushort)((uVar3 ^ (short)uVar3 >> 0xf) - ((short)uVar3 >> 0xf))))) {
      lreg_rec = lreg_rec + 0x12;
      sVar2 = *lreg_rec;
    }
    copy_ea_into(dst,(ea *)(lreg_rec + 0xc));
    bVar1 = dst->type & 0x1f;
    if (((bVar1 != 2) || ((desc->value).base != 'l')) &&
       ((bVar1 != 8 || ((desc->value).base != 'l')))) {
      if (0 < node->lreg) {
        node->desc->opnd_class = '\x01';
        return;
      }
      node->desc->opnd_class = '\0';
      return;
    }
    node->desc->opnd_class = '\x03';
    return;
  }
  uVar4 = (int)node->symx + 0xb6;
  uVar5 = (int)uVar4 >> 0x1f;
  sym = g_symbol_table + ((uVar4 ^ uVar5) - uVar5);
  if (sym->sclass == '\x02') {
    sym->flags = sym->flags | 8;
  }
  uVar4 = (int)node->symx + 0xb6;
  uVar5 = (int)uVar4 >> 0x1f;
  copy_ea_into(dst,&g_symbol_table[(uVar4 ^ uVar5) - uVar5].storage);
  if ((node->type & 0xf8) == 0x48) {
    if (node->desc->usage == '\x03') {
      dst->type = dst->type | 0x40;
    }
    else {
      dst->type = dst->type & 0xf7 | 7;
    }
    if (((g_request->cpu != 0) && (g_request->pic != 0)) &&
       ((node->parent == (gen_node *)0x0 ||
        ((node->parent->op != IL_CALL || (iVar6 = operand_position(node), iVar6 != 1)))))) {
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p & 0x7f;
      ea_copy = copy_ea(dst);
      node->desc->ea_54 = ea_copy;
      free_label_ref_list((desc->value).labels);
      node->desc->tmpl = (tmpl_header *)&g_tmpl_aid001;
      pgVar7 = node;
      uVar4 = result_reg_exclusion_mask(node);
      apply_template_to_node(node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,uVar4,pgVar7);
    }
    if (((node->parent != (gen_node *)0x0) && (node->parent->op != IL_CALL)) &&
       (uVar4 = (int)node->symx + 0xb6, uVar5 = (int)uVar4 >> 0x1f,
       (g_symbol_table[(uVar4 ^ uVar5) - uVar5].flags & 0x10) != 0)) {
      report_codegen_message
                (0x7e4,node->filn,(uint)node->line,(int)node->listno,
                 g_symbol_table[(uVar4 ^ uVar5) - uVar5].name);
    }
    goto LAB_00404809;
  }
  if ((node->type & 0xe0) == 0x80) {
    pgVar7 = node->parent;
    if (pgVar7 == (gen_node *)0x0) {
LAB_0040471e:
      if (node->desc->usage != '\x03') goto LAB_00404726;
    }
    else {
      if ((pgVar7->op == IL_ASSIGN) && (iVar6 = operand_position(node), iVar6 == 2)) {
        if ((pgVar7->type & 0xe0) == 0x80) goto LAB_00404729;
      }
      else if ((pgVar7 == (gen_node *)0x0) || (pgVar7->op != IL_AMPER)) goto LAB_0040471e;
LAB_00404726:
      dst->type = dst->type | 0x40;
    }
LAB_00404729:
    bVar1 = dst->type;
    if (((bVar1 & 0x40) == 0) || ((bVar1 & 0x1f) != 0xd)) goto LAB_00404809;
    dst->type = bVar1 & 0xf7 | 7;
    bVar1 = bVar1 & 0xb7 | 7;
  }
  else {
    if ((node->desc->usage == '\x03') || ((dst->type & 0x1f) != 0xd)) goto LAB_00404809;
    dst->type = dst->type & 0xf7 | 7;
    sVar2 = find_register_holding_constant(dst,'@');
    if (sVar2 != -1) {
      free_label_ref_list((desc->value).labels);
      bVar1 = (byte)sVar2;
      fill_ea(dst,'\b',bVar1,-1,'\0',0,(label_ref *)0x0);
      flags_p = &g_gpr_contents[sVar2].flags;
      if ((*flags_p & 0x80) == 0) {
        uVar3 = 1 << (bVar1 & 0x1f);
        regs_p = &node->desc->busy_regs;
        *regs_p = *regs_p | uVar3;
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
        regs_p = &node->desc->temp_regs;
        *regs_p = *regs_p | uVar3;
        *flags_p = *flags_p | 0x80;
      }
      else {
        uVar3 = 1 << (bVar1 & 0x1f);
        regs_p = &node->desc->busy_regs;
        *regs_p = *regs_p | uVar3;
        g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
      }
      regs_p = &node->desc->reused_regs;
      *regs_p = *regs_p | uVar3;
      goto LAB_00404809;
    }
    bVar1 = dst->type & 0xfd | 0xd;
  }
  dst->type = bVar1;
LAB_00404809:
  if ((dst->type & 0x1f) == 1) {
    node->desc->opnd_class = '\x01';
    return;
  }
  node->desc->opnd_class = '\x03';
  return;
}



