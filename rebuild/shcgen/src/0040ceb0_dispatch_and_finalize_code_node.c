#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_late_handler_table
#define g_late_handler_table (*(unsigned char * *)(g_sd + 0x9848))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0040ceb0
// name : dispatch_and_finalize_code_node
// size : 1823
// sig  : void dispatch_and_finalize_code_node(gen_node * node)


int __cdecl dispatch_and_finalize_code_node(gen_node *node)

{
  unsigned char _frec_8[8];
#define sel (*(tmpl_select * *)(_frec_8 + 0))
#define alt_sel (*(tmpl_select * *)(_frec_8 + 4))
  uchar type;
  byte type_class;
  short sVar1;
  int iVar2;
  uint ea_mask;
  ea *operand;
  uint uVar3;
  gen_node *pgVar4;
  int *frame_low_ptr;
  gen_node *second_child;
  ushort uVar5;
  byte bVar6;
  node_desc *desc;
  char cVar7;
  char cVar8;
  label_ref *plVar9;
  uchar *flags_ptr;
  ushort *mask_ptr;
  il_op node_op;
  gen_node *parent_node;
  
  node_op = node->op;
  iVar2 = map_code_node_opcode_to_late_handler_index((short)(char)node_op);
  parent_node = node->parent;
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    node->desc->fpscr_pr = g_fpscr_pr;
  }
  if ((((node->type & 0xf8) == 0x30) && (node->desc->usage == '\x01')) && (g_request->cpu != 4)) {
    flags_ptr = &node->desc->flags2;
    *flags_ptr = *flags_ptr | 8;
  }
  desc = node->desc;
  if (((desc->usage != '\0') || ((desc->flags2 & 0x40) != 0)) || (parent_node->op == IL_COMMA)) {
    if (iVar2 != -1) {
      if ((desc->flags7 & 0x80) == 0) {
        cVar8 = (&g_late_handler_kind)[iVar2];
        if (cVar8 == '\x03') {
          (*(code *)(&g_late_handler_table)[iVar2])(node);
        }
        else {
          if (cVar8 == '\x01') {
            cVar8 = '\x01';
            sel = (tmpl_select *)(&g_late_handler_table)[iVar2];
          }
          else if (cVar8 == '\x02') {
            cVar8 = '\x02';
            sel = (tmpl_select *)(&g_late_handler_table)[iVar2];
          }
          else {
            iVar2 = select_cpu_variant((&g_late_handler_table)[iVar2],&sel,&alt_sel);
            if ((short)iVar2 == 0) {
              cVar8 = '\x02';
              sel = alt_sel;
            }
            else {
              cVar8 = '\x01';
            }
          }
          generate_operator_by_template(node,sel,cVar8);
        }
      }
      else {
        generate_float_multiply_add(node);
      }
    }
    if ((node->type & 2) != 0) {
      bVar6 = (node->desc->value).type;
      if ((bVar6 & 0x1f) != 0) {
        (node->desc->value).type = bVar6 | 0x80;
      }
    }
    desc = node->desc;
    if ((desc->flags3 & 0x20) == 0) {
      operand = &desc->value;
      if ((operand->type & 0x1f) != 0) {
        if (((desc->dest).type & 0x1f) == 0) {
          if ((desc->flags2 & 8) == 0) {
            if ((desc->flags2 & 4) == 0) {
              pgVar4 = node;
              if (desc->target_regs == 0) {
                if (desc->ftarget_regs == 0) goto LAB_0040d38b;
                operand = alloc_zeroed(0xc);
                plVar9 = (label_ref *)0x0;
                iVar2 = 0;
                cVar7 = '\0';
                cVar8 = -1;
                sVar1 = float_mask_to_register(node->desc->ftarget_regs);
                fill_ea(operand,'\x01',(char)sVar1,cVar8,cVar7,iVar2,plVar9);
                desc = node->desc;
                ea_mask = ea_register_mask(&desc->value);
                type = node->type;
                uVar3 = (int)(short)desc->fbusy_regs << 0x10 | (int)(short)desc->busy_regs |
                        0xfffffff0;
              }
              else {
                operand = alloc_zeroed(0xc);
                plVar9 = (label_ref *)0x0;
                iVar2 = 0;
                cVar7 = '\0';
                cVar8 = -1;
                sVar1 = mask_to_register((int)(short)node->desc->target_regs);
                fill_ea(operand,'\x01',(char)sVar1,cVar8,cVar7,iVar2,plVar9);
                desc = node->desc;
                ea_mask = ea_register_mask(&desc->value);
                type = node->type;
                uVar3 = (uint)(short)(desc->busy_regs | 0xfff0);
              }
              emit_operand_transfer
                        (&desc->value,operand,'0',node,0xc00,type,uVar3,ea_mask,(int)pgVar4);
              free_ea(operand);
            }
            else {
              pgVar4 = node;
              ea_mask = ea_register_mask(operand);
              emit_operand_transfer
                        (operand,&g_ea_push,'`',node,0x1500,node->type,
                         (int)(short)(desc->busy_regs | 0xfff0),ea_mask,(int)pgVar4);
            }
          }
          else {
            pgVar4 = node;
            ea_mask = ea_register_mask(operand);
            emit_operand_transfer
                      (operand,&g_ea_push,'0',node,0x1500,node->type,
                       (int)(short)(desc->busy_regs | 0xfff0),ea_mask,(int)pgVar4);
          }
        }
        else {
          sVar1 = ea_operands_equal(operand,&desc->dest);
          if (sVar1 == 0) {
            bVar6 = node->type;
            type_class = bVar6 & 0xe0;
            if (((type_class == 0x80) &&
                ((parent_node->op != IL_ASSIGN || ((parent_node->type & 0xe0) != 0x80)))) ||
               ((type_class == 0x60 && (((node->desc->dest).type & 0x1f) == 1)))) {
              bVar6 = 0x40;
            }
            if (parent_node->op == IL_ASSIGN) {
              desc = node->desc;
              pgVar4 = parent_node;
              ea_mask = ea_register_mask(&desc->dest);
              uVar3 = ea_register_mask(&desc->value);
              emit_operand_transfer
                        (&desc->value,&desc->dest,'0',node,5,bVar6,
                         (int)(short)desc->fbusy_regs << 0x10 | (int)(short)desc->busy_regs |
                         0xfffffff0,ea_mask | uVar3,(int)pgVar4);
            }
            else if ((type_class == 0x60) && (desc = node->desc, ((desc->dest).type & 0x1f) == 1)) {
              pgVar4 = node;
              ea_mask = ea_register_mask(&desc->dest);
              uVar3 = ea_register_mask(&desc->value);
              emit_operand_transfer
                        (&desc->value,&desc->dest,'0',node,0xd00,bVar6,
                         (int)(short)(desc->busy_regs | 0xfff0),ea_mask | uVar3,(int)pgVar4);
            }
            else {
              desc = node->desc;
              pgVar4 = node;
              ea_mask = ea_register_mask(&desc->dest);
              uVar3 = ea_register_mask(&desc->value);
              emit_operand_transfer
                        (&desc->value,&desc->dest,'0',node,5,bVar6,
                         (int)(short)(desc->busy_regs | 0xfff0),ea_mask | uVar3,(int)pgVar4);
            }
          }
        }
      }
    }
    else if (((desc->value).type & 0x1f) != 0) {
      uVar5 = 2;
      if ((node->type & 0xe0) != 0x60) {
        uVar5 = desc->pref_regs;
      }
      cVar8 = '\0';
      ea_mask = ea_register_mask(&desc->value);
      sVar1 = choose_general_register((ushort)ea_mask,uVar5,cVar8);
      bVar6 = (byte)sVar1;
      uVar5 = 1 << (bVar6 & 0x1f);
      mask_ptr = &node->desc->busy_regs;
      *mask_ptr = *mask_ptr | uVar5;
      g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
      mask_ptr = &node->desc->temp_regs;
      *mask_ptr = *mask_ptr | uVar5;
      operand = alloc_zeroed(0xc);
      node->desc->addr_reg_ea = operand;
      fill_ea(node->desc->addr_reg_ea,'\x01',bVar6,-1,'\0',0,(label_ref *)0x0);
      node->desc->addr_reg = bVar6;
      desc = node->desc;
      operand = copy_ea(desc->addr_reg_ea);
      desc->mem_ea = operand;
      operand = node->desc->mem_ea;
      operand->type = operand->type & 0xf8 | 8;
      desc = node->desc;
      pgVar4 = node;
      ea_mask = ea_register_mask(&desc->value);
      emit_operand_transfer
                (&desc->value,desc->mem_ea,'0',node,5,node->type,
                 (int)(short)(desc->busy_regs | 0xfff0),ea_mask,(int)pgVar4);
    }
  }
LAB_0040d38b:
  if (((((node->type & 0xf8) == 0x30) && (desc = node->desc, desc->usage == '\x01')) &&
      (desc->opnd_class == '\x02')) && (g_request->cpu != 4)) {
    desc->flags2 = desc->flags2 & 0xf7;
  }
  if ((node->desc->usage == '\x01') &&
     (((((char)node_op < '`' || ('l' < (char)node_op)) &&
       ((node_op != IL_NOT && (node_op != IL_COND)))) || ((node->desc->flags3 & 0x80) != 0)))) {
    assign_condition_value_registers(node);
  }
  desc = node->desc;
  if (((desc->usage == '\0') && ((desc->flags2 & 0x40) != 0)) &&
     (((node_op == IL_ID && ((desc->flags3 & 0x80) != 0)) ||
      ((node_op == IL_ASTER || (node_op == IL_QUALIFY)))))) {
    sVar1 = choose_general_register(desc->busy_regs,0,'\0');
    if (sVar1 == -1) {
      sVar1 = choose_general_register(0,0xf,'\0');
    }
    node->desc->regs_2c[0] = (byte)sVar1;
    uVar5 = 1 << ((byte)sVar1 & 0x1f);
    mask_ptr = &node->desc->busy_regs;
    *mask_ptr = *mask_ptr | uVar5;
    g_used_gpr_mask = g_used_gpr_mask | node->desc->busy_regs;
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | uVar5;
    invalidate_register_contents((int)(short)uVar5);
  }
  if (((node->child != (gen_node *)0x0) && (desc = node->child->desc, (desc->flags2 & 2) != 0)) &&
     (desc->usage == '\x03')) {
    invalidate_variable_register_contents(0xf000f);
  }
  if ((((node->desc->flags2 & 2) != 0) && (parent_node != (gen_node *)0x0)) &&
     (parent_node->desc != (node_desc *)0x0)) {
    flags_ptr = &parent_node->desc->flags2;
    *flags_ptr = *flags_ptr | 2;
  }
  node_op = node->op;
  if (((node_op == IL_COND) || (node_op == IL_AND)) || (node_op == IL_OR)) {
    flags_ptr = &node->desc->flags3;
    *flags_ptr = *flags_ptr | 1;
  }
  if (node->child != (gen_node *)0x0) {
    mask_ptr = &node->desc->temp_regs;
    *mask_ptr = *mask_ptr | node->child->desc->temp_regs;
    mask_ptr = &node->desc->ftemp_regs;
    *mask_ptr = *mask_ptr | node->child->desc->ftemp_regs;
    pgVar4 = node->child;
    second_child = (gen_node *)0x0;
    if (pgVar4 != (gen_node *)0x0) {
      second_child = pgVar4->next;
    }
    if (second_child != (gen_node *)0x0) {
      if (pgVar4 == (gen_node *)0x0) {
        pgVar4 = (gen_node *)0x0;
      }
      else {
        pgVar4 = pgVar4->next;
      }
      mask_ptr = &node->desc->temp_regs;
      *mask_ptr = *mask_ptr | pgVar4->desc->temp_regs;
      if (node->child == (gen_node *)0x0) {
        pgVar4 = (gen_node *)0x0;
      }
      else {
        pgVar4 = node->child->next;
      }
      mask_ptr = &node->desc->ftemp_regs;
      *mask_ptr = *mask_ptr | pgVar4->desc->ftemp_regs;
    }
  }
  if ((parent_node != (gen_node *)0x0) && (parent_node->desc != (node_desc *)0x0)) {
    mask_ptr = &parent_node->desc->temp_regs;
    *mask_ptr = *mask_ptr | node->desc->temp_regs;
    mask_ptr = &parent_node->desc->ftemp_regs;
    *mask_ptr = *mask_ptr | node->desc->ftemp_regs;
    mask_ptr = &parent_node->desc->cached_regs;
    *mask_ptr = *mask_ptr | node->desc->cached_regs;
    mask_ptr = &parent_node->desc->reused_regs;
    *mask_ptr = *mask_ptr | node->desc->reused_regs;
    mask_ptr = &parent_node->desc->fcached_regs;
    *mask_ptr = *mask_ptr | node->desc->fcached_regs;
    mask_ptr = &parent_node->desc->freused_regs;
    *mask_ptr = *mask_ptr | node->desc->freused_regs;
    frame_low_ptr = &parent_node->desc->frame_low;
    iVar2 = node->desc->frame_low;
    if (iVar2 < *frame_low_ptr) {
      *frame_low_ptr = iVar2;
    }
    if ((node->desc->flags3 & 1) != 0) {
      flags_ptr = &parent_node->desc->flags3;
      *flags_ptr = *flags_ptr | 1;
    }
  }
  if ((g_request->cpu == 4) && (g_request->unknown_155[2] == '\0')) {
    node->desc->fpscr_pr = g_fpscr_pr;
  }
  return;
#undef sel
#undef alt_sel
}



