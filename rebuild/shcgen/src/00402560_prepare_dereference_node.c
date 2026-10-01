#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00402560
// name : prepare_dereference_node
// size : 2085
// sig  : void prepare_dereference_node(gen_node * node)


int __cdecl prepare_dereference_node(gen_node *node)

{
  byte bVar1;
  ea *operand;
  int iVar2;
  uint uVar3;
  uint excluded;
  byte bVar4;
  ea *addr_ea;
  ushort mask;
  short reg;
  ushort uVar5;
  uchar type;
  char cVar6;
  gen_node *pgVar7;
  uchar access_type;
  gen_node *child;
  node_desc *desc;
  uchar *flags_p;
  label_ref *ref;
  ushort *regs_p;
  
  child = node->child;
  child->desc->busy_regs = node->desc->busy_regs;
  child->desc->fbusy_regs = node->desc->fbusy_regs;
  child->desc->frame_top = node->desc->frame_top;
  flags_p = &child->desc->flags7;
  *flags_p = *flags_p | node->desc->flags7 & 0x40;
  desc = child->desc;
  if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
    desc->pref_regs = node->desc->pref_regs;
    child->desc->fpref_regs = node->desc->fpref_regs;
  }
  dispatch_and_finalize_code_node(child);
  if ((node->type & 0xe0) == 0x80) {
    if (child->desc->opnd_class == '\x02') {
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p | 8;
      if (node->desc->tmpl == (tmpl_header *)0x0) {
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
      }
    }
    node->desc->busy_regs = child->desc->busy_regs;
    node->desc->fbusy_regs = child->desc->fbusy_regs;
    node->desc->frame_top = child->desc->frame_top;
    bVar4 = 0;
    desc = child->desc;
    operand = desc->mem_ea;
    if (operand != (ea *)0x0) {
      bVar4 = operand->type & 0x1f;
    }
    if (((bVar4 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
       (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      operand = &desc->value;
    }
    copy_ea_into(&node->desc->value,operand);
    node->desc->opnd_class = child->desc->opnd_class;
    if ((child->desc->flags2 & 2) != 0) {
      flags_p = &node->desc->flags2;
      *flags_p = *flags_p | 2;
    }
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 8;
    goto LAB_00402d76;
  }
  iVar2 = node_value_size(node);
  pgVar7 = node->parent;
  if ((((node->type & 0xe0) == 0x60) ||
      ((((cVar6 = node->desc->usage, cVar6 == '\x03' || (cVar6 == '\0')) || (child->op != IL_POI))
       && (((pgVar7 == (gen_node *)0x0 || (pgVar7->op != IL_ASSIGN)) ||
           ((pgVar7->desc->usage != '\0' || ((cVar6 != '\x03' || (child->op != IL_PRD)))))))))) ||
     ((((iVar2 != 1 && ((iVar2 != 2 && (iVar2 != 4)))) && ((g_request->cpu != 4 || (iVar2 != 8))))
      || ((((child->val != iVar2 || (pgVar7 = child->child, pgVar7 == (gen_node *)0x0)) ||
           (pgVar7->op != IL_ID)) || (((pgVar7->desc->value).type & 0x1f) != 1)))))) {
    flags_p = &node->desc->flags3;
    *flags_p = *flags_p | 8;
    desc = child->desc;
    cVar6 = desc->opnd_class;
    if (cVar6 == '\x02') {
LAB_00402c37:
      flags_p = &node->desc->flags3;
      *flags_p = *flags_p | 8;
      if (node->desc->tmpl == (tmpl_header *)0x0) {
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 0x80;
      }
LAB_00402c4e:
      node->desc->busy_regs = child->desc->busy_regs;
      node->desc->fbusy_regs = child->desc->fbusy_regs;
      node->desc->frame_top = child->desc->frame_top;
      bVar4 = 0;
      desc = child->desc;
      operand = desc->mem_ea;
      if (operand != (ea *)0x0) {
        bVar4 = operand->type & 0x1f;
      }
      if (((bVar4 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
         (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        operand = &desc->value;
      }
      copy_ea_into(&node->desc->value,operand);
      node->desc->opnd_class = child->desc->opnd_class;
      (node->desc->value).type = (node->desc->value).type & 0xfd | 0xd;
    }
    else {
      operand = &desc->value;
      bVar4 = operand->type & 0x1f;
      if (((bVar4 == 7) && (ref = (desc->value).labels, ref != (label_ref *)0x0)) &&
         (ref->labno2 == 0)) {
        if (ref == (label_ref *)0x0) {
          uVar3 = 0;
        }
        else {
          uVar3 = (uint)ref->labno1;
        }
        if ((g_symbol_table[(uVar3 ^ (int)uVar3 >> 0x1f) - ((int)uVar3 >> 0x1f)].attr & 3) != 0) {
          if (cVar6 == '\x02') goto LAB_00402c37;
          goto LAB_00402c4e;
        }
      }
      if (bVar4 == 9) {
        if (node->desc->usage != '\x03') {
LAB_004028ac:
          if ((cVar6 == '\0') || (cVar6 == '\x01')) {
            addr_ea = desc->mem_ea;
            bVar4 = 0;
            if (addr_ea != (ea *)0x0) {
              bVar4 = addr_ea->type & 0x1f;
            }
            if (((bVar4 == 0) && (addr_ea = &desc->dest, ((desc->dest).type & 0x1f) == 0)) &&
               (addr_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
              addr_ea = operand;
            }
            reg = (short)addr_ea->base;
          }
          else {
            bVar4 = node->type & 0xf8;
            if (bVar4 == 0x28) {
              if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
                bVar1 = 1;
              }
              else {
                bVar1 = -(g_request->cpu == 4) & 2;
              }
              if (bVar1 == 0) goto LAB_004028fb;
LAB_00402926:
              mask = node->desc->target_regs;
              if (mask == 0) {
                iVar2 = operand_access_needs_r0(operand,'@');
                mask = 1;
                if (iVar2 == 0) {
                  mask = node->desc->pref_regs;
                }
                if (((child->desc->value).type & 0x1f) == 9) {
                  bVar4 = node->type & 0xf8;
                  if (bVar4 == 0x28) {
                    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
                      bVar1 = 1;
                    }
                    else {
                      bVar1 = -(g_request->cpu == 4) & 2;
                    }
                    if (bVar1 == 0) goto LAB_004029af;
                  }
                  else {
LAB_004029af:
                    if ((bVar4 != 0x30) || (g_request->cpu != 4)) goto LAB_00402a67;
                  }
                  desc = node->desc;
                  bVar1 = (desc->dest).type & 0x1f;
                  if ((bVar1 == 0) || (bVar1 != 1)) {
                    if (desc->ftarget_regs == 0) {
                      mask = desc->fpref_regs;
                      if (bVar4 == 0x28) {
                        uVar3 = result_reg_exclusion_mask(node);
                        reg = choose_float_register((ushort)(uVar3 >> 0x10),mask);
                        if (reg == -1) {
                          reg = choose_float_register(0,node->desc->fpref_regs);
                        }
                      }
                      else {
                        uVar3 = result_reg_exclusion_mask(node);
                        reg = choose_float_register_pair((ushort)(uVar3 >> 0x10),mask);
                        if (reg == -1) {
                          reg = choose_float_register_pair(0,node->desc->fpref_regs);
                        }
                      }
                    }
                    else {
                      reg = float_mask_to_register(desc->ftarget_regs);
                    }
                  }
                  else {
                    reg = (short)(desc->dest).base;
                  }
                }
                else {
LAB_00402a67:
                  cVar6 = '\0';
                  uVar5 = mask;
                  uVar3 = result_reg_exclusion_mask(node);
                  reg = choose_general_register((ushort)uVar3,uVar5,cVar6);
                  if (reg == -1) {
                    reg = choose_general_register(0,mask,'\0');
                  }
                }
              }
              else {
                reg = mask_to_register((int)(short)mask);
              }
            }
            else {
LAB_004028fb:
              if ((bVar4 == 0x30) && (g_request->cpu == 4)) goto LAB_00402926;
              bVar4 = (node->desc->dest).type & 0x1f;
              if ((bVar4 == 0) || (bVar4 != 1)) goto LAB_00402926;
              reg = (short)(node->desc->dest).base;
            }
            fill_ea(&child->desc->dest,'\x01',(char)reg,-1,'\0',0,(label_ref *)0x0);
            bVar4 = (child->desc->value).type;
            if ((bVar4 & 0x1f) == 9) {
              (child->desc->value).type = bVar4 & 0xbf;
              access_type = node->type;
            }
            else {
              access_type = '@';
            }
            desc = child->desc;
            pgVar7 = node;
            uVar3 = ea_register_mask(&desc->value);
            excluded = result_reg_exclusion_mask(child);
            emit_operand_transfer
                      (&desc->value,&desc->dest,'0',child,0xc00,access_type,excluded,uVar3,
                       (int)pgVar7);
          }
          if (((child->desc->value).type & 0x1f) == 9) {
            flags_p = &child->desc->flags3;
            *flags_p = *flags_p | 2;
            type = '\x01';
          }
          else {
            type = '\b';
          }
          bVar4 = (byte)reg;
          fill_ea(&node->desc->value,type,bVar4,-1,'\0',0,(label_ref *)0x0);
          if ((reg < 0x2f) && (0x1f < reg)) {
            uVar5 = 1 << (bVar4 - 0x1f & 0x1f);
            mask = 1 << (bVar4 - 0x20 & 0x1f);
            regs_p = &node->desc->fbusy_regs;
            *regs_p = *regs_p | uVar5 | mask;
            g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
            regs_p = &node->desc->ftemp_regs;
            *regs_p = *regs_p | uVar5 | mask;
          }
          else if ((reg < 0x20) && (0xf < reg)) {
            mask = 1 << (bVar4 - 0x10 & 0x1f);
            regs_p = &node->desc->fbusy_regs;
            *regs_p = *regs_p | mask;
            g_used_fpr_mask = g_used_fpr_mask | node->desc->fbusy_regs;
            regs_p = &node->desc->ftemp_regs;
            *regs_p = *regs_p | mask;
          }
          else {
            mask = 1 << (bVar4 & 0x1f);
            regs_p = &node->desc->busy_regs;
            *regs_p = *regs_p | mask;
            g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
            regs_p = &node->desc->temp_regs;
            *regs_p = *regs_p | mask;
          }
          goto LAB_00402cd3;
        }
      }
      else if (((operand->type & 0x40) == 0) || ((node->type & 0xf8) == 0x48)) goto LAB_004028ac;
      if (cVar6 == '\x02') {
        flags_p = &node->desc->flags3;
        *flags_p = *flags_p | 8;
        if (node->desc->tmpl == (tmpl_header *)0x0) {
          flags_p = &node->desc->flags3;
          *flags_p = *flags_p | 0x80;
        }
      }
      node->desc->busy_regs = child->desc->busy_regs;
      node->desc->fbusy_regs = child->desc->fbusy_regs;
      node->desc->frame_top = child->desc->frame_top;
      bVar4 = 0;
      desc = child->desc;
      operand = desc->mem_ea;
      if (operand != (ea *)0x0) {
        bVar4 = operand->type & 0x1f;
      }
      if (((bVar4 == 0) && (operand = &desc->dest, (operand->type & 0x1f) == 0)) &&
         (operand = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        operand = &desc->value;
      }
      copy_ea_into(&node->desc->value,operand);
      node->desc->opnd_class = child->desc->opnd_class;
      operand = &node->desc->value;
      operand->type = operand->type & 0xbf;
    }
  }
  else {
    release_node_registers(child);
    cVar6 = (child->child->desc->value).base;
    if (child->op == IL_PRD) {
      fill_ea(&node->desc->value,'\x03',cVar6,-1,'\0',0,(label_ref *)0x0);
    }
    else {
      fill_ea(&node->desc->value,'\x04',cVar6,-1,'\0',0,(label_ref *)0x0);
    }
  }
LAB_00402cd3:
  desc = node->desc;
  if (((desc->value).type & 0x1f) == 1) {
    bVar4 = (desc->value).base;
    if (((((char)bVar4 < '\x0f') && ((1 << (bVar4 & 0x1f) & (int)(short)~g_var_gpr_mask) != 0)) ||
        (((char)bVar4 < ' ' &&
         (('\x0f' < (char)bVar4 && ((1 << (bVar4 - 0x10 & 0x1f) & (int)(short)~g_var_fpr_mask) != 0)
          ))))) ||
       (((char)bVar4 < '/' &&
        (('\x1f' < (char)bVar4 &&
         (((int)(short)g_var_fpr_mask & (1 << (bVar4 - 0x1f & 0x1f) | 1 << (bVar4 - 0x20 & 0x1f)))
          == 0)))))) {
      desc->opnd_class = '\0';
    }
    else {
      desc->opnd_class = '\x01';
    }
  }
  else {
    desc->opnd_class = '\x03';
  }
  if ((node->type & 0xf8) == 0x48) {
    operand = &node->desc->value;
    operand->type = operand->type | 0x40;
  }
  flags_p = &node->desc->flags2;
  *flags_p = *flags_p | 2;
LAB_00402d76:
  flags_p = &node->desc->flags3;
  *flags_p = *flags_p | 0x80;
  return;
}



