#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004053a0
// name : emit_call_node
// size : 3987
// sig  : void emit_call_node(gen_node * node)


int __cdecl emit_call_node(gen_node *node)

{
  unsigned char _frec_39[57];
#define push_type (*(byte *)(_frec_39 + 0))
#define call_flags (*(uchar *)(_frec_39 + 4))
#define nested (*(char *)(_frec_39 + 9))
#define arg_bytes (*(int *)(_frec_39 + 13))
#define local_28 (*(ea * *)(_frec_39 + 17))
#define local_24 (*(ea * *)(_frec_39 + 21))
#define local_20 (*(ea * *)(_frec_39 + 25))
#define local_1c (*(ea * *)(_frec_39 + 29))
#define local_18 (*(undefined4 *)(_frec_39 + 33))
#define local_14 (*(ea * *)(_frec_39 + 37))
#define local_10 (*(undefined4 *)(_frec_39 + 41))
#define ret_size (*(uint *)(_frec_39 + 45))
#define entry_b (*(int *)(_frec_39 + 49))
#define entry_a (*(int *)(_frec_39 + 53))
  node_desc *pnVar1;
  byte bVar2;
  char cVar3;
  ea *peVar4;
  int operand_count;
  int iVar5;
  gen_node *pgVar6;
  tmpl_header *tmpl;
  ea *peVar7;
  uint uVar8;
  gen_node *pgVar9;
  uint uVar10;
  int next_i;
  char *name_p;
  char *builtin_p;
  bool bVar11;
  ushort op;
  tmpl_entry *entries;
  gen_node *pgVar12;
  gen_node *pgVar13;
  short arg_reg;
  bool both_static;
  bool return_space;
  ea **slots;
  
  call_flags = '\0';
  bVar11 = false;
  return_space = false;
  both_static = false;
  pgVar13 = node->parent;
  pgVar9 = pgVar13->child;
  if (node->desc->builtin != '\0') {
    pgVar13 = node->child;
    pgVar9 = (gen_node *)0x0;
    if (pgVar13 != (gen_node *)0x0) {
      pgVar9 = pgVar13->next;
    }
    fill_psd_record_at_line
              ((psd *)&g_psd_scratch,OP_NON_10,pgVar13->filn,pgVar13->line,pgVar13->val,pgVar9->val)
    ;
    emit_psd_record((psd *)&g_psd_scratch,0);
    return;
  }
  if ((((pgVar13->type & 0xe0) == 0x60) && (((pgVar13->desc->value).type & 0x1f) == 0)) &&
     (((pgVar13->desc->dest).type & 0x1f) == 0)) {
    ret_size = node_value_size(pgVar13);
    if ((ret_size & 3) != 0) {
      ret_size = (ret_size & 0xfffffffc) + 4;
    }
    local_28 = new_ea_operand_with_flags('\a',-1,-1,-ret_size,'\0',(label_ref *)0x0);
    pgVar12 = (gen_node *)0x0;
    if ((int)ret_size < 0x80) {
      peVar7 = copy_ea((ea *)&g_ea_r15);
      peVar4 = local_28;
LAB_00405515:
      emit_psd_for_node(0x60,-1,'\0','\x02',peVar4,peVar7,pgVar12);
    }
    else {
      local_24 = new_ea_operand_with_flags
                           ('\x01',pgVar13->desc->regs_34[0],-1,0,'\0',(label_ref *)0x0);
      local_20 = copy_ea(local_24);
      emit_psd_for_node(0x2a,-1,'\0','\x02',local_28,local_24,(gen_node *)0x0);
      pgVar12 = (gen_node *)0x0;
      peVar4 = copy_ea((ea *)&g_ea_r15);
      emit_psd_for_node(0x60,-1,'\0','\x02',local_20,peVar4,pgVar12);
      update_stack_travel(1,ret_size,(psd *)0x0);
    }
    return_space = true;
  }
  else if ((((pgVar13->type & 0xf8) == 0x30) && (((pgVar13->desc->dest).type & 0x1f) == 0)) &&
          (g_request->cpu != 4)) {
    pgVar12 = (gen_node *)0x0;
    peVar7 = copy_ea((ea *)&g_ea_r15);
    peVar4 = copy_ea((ea *)&g_ea_imm_minus8);
    goto LAB_00405515;
  }
  cVar3 = g_nested_operand_emit;
  arg_bytes = g_sptravel;
  g_nested_operand_emit = '\x01';
  operand_count = count_operands(node);
  iVar5 = 1;
  if (1 < operand_count) {
    do {
      next_i = iVar5 + 1;
      pgVar12 = nth_operand(node,iVar5);
      emit_node_code(pgVar12);
      operand_count = count_operands(node);
      iVar5 = next_i;
    } while (next_i < operand_count);
  }
  g_nested_operand_emit = cVar3;
  iVar5 = count_operands(node);
  iVar5 = iVar5 + -1;
  if (0 < iVar5) {
    do {
      pgVar12 = nth_operand(node,iVar5);
      if (((pgVar12->desc->target_regs != 0) ||
          (pgVar12 = nth_operand(node,iVar5), pgVar12->desc->ftarget_regs != 0)) &&
         ((pgVar12 = nth_operand(node,iVar5), ((pgVar12->desc->dest).type & 0x1f) != 0 ||
          (pgVar12 = nth_operand(node,iVar5), (pgVar12->desc->flags2 & 8) != 0)))) {
        if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
          bVar2 = 1;
        }
        else {
          bVar2 = -(g_request->cpu == 4) & 2;
        }
        if (((bVar2 == 0) || (pgVar12 = nth_operand(node,iVar5), (pgVar12->type & 0xf8) != 0x28)) &&
           ((g_request->cpu != 4 ||
            (pgVar12 = nth_operand(node,iVar5), (pgVar12->type & 0xf8) != 0x30)))) {
          pgVar12 = nth_operand(node,iVar5);
          arg_reg = single_bit_position((int)(short)pgVar12->desc->target_regs);
          cVar3 = (char)arg_reg;
        }
        else {
          pgVar12 = nth_operand(node,iVar5);
          arg_reg = float_mask_to_register(pgVar12->desc->ftarget_regs);
          cVar3 = (char)arg_reg;
        }
        slots = &local_28;
        pgVar12 = nth_operand(node,iVar5);
        load_slot_register_operands(4,pgVar12,slots);
        pgVar12 = nth_operand(node,iVar5);
        if ((pgVar12->desc->flags2 & 8) == 0) {
          pgVar12 = nth_operand(node,iVar5);
          local_28 = &pgVar12->desc->dest;
        }
        else {
          local_28 = (ea *)&g_ea_postinc_r15;
        }
        local_24 = new_ea_operand_with_flags('\x01',cVar3,-1,0,'\0',(label_ref *)0x0);
        pgVar12 = nth_operand(node,iVar5);
        pgVar6 = nth_operand(node,iVar5);
        cVar3 = pgVar6->desc->usage;
        pgVar6 = nth_operand(node,iVar5);
        tmpl = select_transfer_template(0,0,local_28,local_24,local_20,pgVar6->type,cVar3,pgVar12);
        if (tmpl != (tmpl_header *)0x0) {
          nth_operand(node,iVar5);
          slots = &local_28;
          entries = tmpl->entries;
          pgVar12 = nth_operand(node,iVar5);
          emit_template_record_sequence_for_node(pgVar12,entries,slots);
        }
        free_slot_register_operands(4,&local_28);
        free_ea(local_24);
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  arg_bytes = g_sptravel - arg_bytes;
  if (((g_request->cpu != 4) && ((pgVar13->type & 0xf8) == 0x30)) ||
     ((pgVar13->type & 0xe0) == 0x60)) {
    local_1c = (ea *)0x0;
    local_18 = 0;
    local_14 = (ea *)0x0;
    local_10 = 0;
    bVar2 = pgVar13->type;
    if (((bVar2 & 0xe0) == 0x60) && (peVar4 = &pgVar13->desc->value, (peVar4->type & 0x1f) != 0)) {
      local_24 = (ea *)&g_ea_predec_r15;
      local_28 = peVar4;
      local_20 = new_ea_operand_with_flags
                           ('\x01',pgVar13->desc->regs_34[1],-1,0,'\0',(label_ref *)0x0);
      tmpl = select_transfer_template
                       (0,4,local_28,local_24,local_20,pgVar13->type,pgVar13->desc->usage,pgVar13);
      if (tmpl != (tmpl_header *)0x0) {
        emit_template_record_sequence_for_node(pgVar13,tmpl->entries,&local_28);
      }
      free_ea(local_20);
    }
    else {
      pnVar1 = pgVar13->desc;
      if (((pnVar1->dest).type & 0x1f) == 0) {
        pgVar12 = (gen_node *)0x0;
        if (arg_bytes == 0) {
          peVar7 = copy_ea((ea *)&g_ea_predec_r15);
          peVar4 = copy_ea((ea *)&g_ea_r15);
        }
        else {
          local_24 = new_ea_operand_with_flags('\x01',pnVar1->regs_34[1],-1,0,'\0',(label_ref *)0x0)
          ;
          local_28 = new_ea_operand_with_flags('\a',-1,-1,arg_bytes,'\0',(label_ref *)0x0);
          pgVar12 = (gen_node *)0x0;
          peVar4 = copy_ea(local_24);
          emit_psd_for_node(0x2a,-1,'\0','\x02',local_28,peVar4,pgVar12);
          pgVar12 = (gen_node *)0x0;
          peVar4 = copy_ea(local_24);
          peVar7 = copy_ea((ea *)&g_ea_r15);
          emit_psd_for_node(0x60,-1,'\0','\x02',peVar7,peVar4,pgVar12);
          pgVar12 = (gen_node *)0x0;
          peVar7 = copy_ea((ea *)&g_ea_predec_r15);
          peVar4 = local_24;
        }
        emit_psd_for_node(0x40,-1,'\0','\x02',peVar4,peVar7,pgVar12);
      }
      else {
        if ((pnVar1->flags3 & 0x20) == 0) {
          uVar8 = 4;
          push_type = bVar2;
        }
        else {
          push_type = 0x40;
          pgVar13->type = '@';
          uVar8 = 6;
        }
        local_24 = (ea *)&g_ea_predec_r15;
        local_28 = &pgVar13->desc->dest;
        local_20 = new_ea_operand_with_flags
                             ('\x01',pgVar13->desc->regs_34[1],-1,0,'\0',(label_ref *)0x0);
        local_14 = new_ea_operand_with_flags
                             ('\x01',pgVar13->desc->regs_34[1],-1,0,'\0',(label_ref *)0x0);
        tmpl = select_transfer_template
                         (0,uVar8,local_28,local_24,local_20,push_type,pgVar13->desc->usage,pgVar13)
        ;
        if (tmpl != (tmpl_header *)0x0) {
          emit_template_record_sequence_for_node(pgVar13,tmpl->entries,&local_28);
        }
        pgVar13->type = bVar2;
        free_ea(local_20);
        free_ea(local_14);
      }
    }
    arg_bytes = arg_bytes + 4;
  }
  load_node_address_register(pgVar9);
  if ((((pgVar13->val3 & 4) != 0) && ((*(byte *)(g_current_aux_record + 0xb) & 0x40) == 0)) &&
     (((pgVar13->type & 0xe0) != 0x60 && ((g_request->cpu == 4 || ((pgVar13->type & 0xf8) != 0x30)))
      ))) {
    iVar5 = count_operands(node);
    iVar5 = iVar5 + -1;
    if (0 < iVar5) {
      do {
        pgVar12 = nth_operand(node,iVar5);
        if (((pgVar12->desc->target_regs & 0xf0) == 0) &&
           (pgVar12 = nth_operand(node,iVar5),
           (((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10 &
           (int)(short)pgVar12->desc->ftarget_regs) == 0)) {
          bVar11 = true;
        }
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    iVar5 = count_operands(node);
    if ((iVar5 == 1) || (!bVar11)) {
      call_flags = 0x80;
    }
  }
  if ((node->desc->fpu_mode_flags & 1) != 0) {
    local_20 = new_ea_operand_with_flags('\x01',node->desc->regs_2c[2],-1,0,'\0',(label_ref *)0x0);
    local_1c = new_ea_operand_with_flags('\x01',node->desc->regs_2c[3],-1,0,'\0',(label_ref *)0x0);
    emit_psd_for_node(0x2e,-1,'\0','\x02',local_20,local_1c,node);
  }
  pnVar1 = pgVar9->desc;
  bVar2 = 0;
  peVar4 = pnVar1->mem_ea;
  if (peVar4 != (ea *)0x0) {
    bVar2 = peVar4->type & 0x1f;
  }
  peVar7 = peVar4;
  if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
     (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
    peVar7 = &pnVar1->value;
  }
  if ((peVar7->type & 0x1f) == 0xd) {
LAB_00405d72:
    bVar2 = 0;
    if (peVar4 != (ea *)0x0) {
      bVar2 = peVar4->type & 0x1f;
    }
    peVar7 = peVar4;
    if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
       (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
      peVar7 = &pnVar1->value;
    }
    if (peVar7->disp != 0) {
LAB_004060cb:
      bVar2 = 0;
      if (peVar4 != (ea *)0x0) {
        bVar2 = peVar4->type & 0x1f;
      }
      if (((bVar2 == 0) && (peVar4 = &pnVar1->dest, (peVar4->type & 0x1f) == 0)) &&
         (peVar4 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
        peVar4 = &pnVar1->value;
      }
      local_28 = copy_ea(peVar4);
      local_28->type = local_28->type & 0xf7 | 7;
      local_28->type = local_28->type & 0xbf;
      local_24 = new_ea_operand_with_flags('\x01',node->desc->regs_2c[0],-1,0,'\0',(label_ref *)0x0)
      ;
      peVar4 = copy_ea(local_24);
      emit_psd_for_node(0x2a,-1,'\0','\x02',local_28,local_24,(gen_node *)0x0);
      peVar4->type = peVar4->type & 0xf8 | 8;
      local_24 = peVar4;
      if (('\a' < peVar4->base) && (peVar4->base < '\x0f')) {
        call_flags = '\0';
      }
      goto LAB_0040617e;
    }
    bVar2 = 0;
    if (peVar4 != (ea *)0x0) {
      bVar2 = peVar4->type & 0x1f;
    }
    peVar7 = peVar4;
    if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
       (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
      peVar7 = &pnVar1->value;
    }
    if (peVar7->labels == (label_ref *)0x0) goto LAB_004060cb;
    bVar2 = 0;
    if (peVar4 != (ea *)0x0) {
      bVar2 = peVar4->type & 0x1f;
    }
    peVar7 = peVar4;
    if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
       (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
      peVar7 = &pnVar1->value;
    }
    if (peVar7->labels->labno2 != 0) goto LAB_004060cb;
    uVar8 = (int)pgVar9->symx + 0xb6;
    uVar10 = (int)uVar8 >> 0x1f;
    iVar5 = 0x10;
    uVar10 = (uVar8 ^ uVar10) - uVar10;
    bVar11 = (uVar10 & 0xfffffff) == 0;
    name_p = g_symbol_table[uVar10].name;
    builtin_p = s__builtin_strcmp_004417a0;
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar11 = *name_p == *builtin_p;
      name_p = name_p + 1;
      builtin_p = builtin_p + 1;
    } while (bVar11);
    if (bVar11) {
      pgVar12 = node->child;
      pgVar6 = (gen_node *)0x0;
      if (pgVar12 != (gen_node *)0x0) {
        pgVar6 = pgVar12->next;
      }
      bVar2 = pgVar12->type;
      if ((((bVar2 & 0xe0) == 0x80) &&
          ((((bVar2 & 0x18) == 0x10 || ((bVar2 & 0xf8) == 0x10)) || ((bVar2 & 0xf8) == 0x18)))) ||
         (((pgVar12->op == IL_ID && (0 < pgVar12->symx)) &&
          ((uVar8 = (int)pgVar12->symx + 0xb6, uVar10 = (int)uVar8 >> 0x1f,
           g_symbol_table[(uVar8 ^ uVar10) - uVar10].sclass == '\t' ||
           (((bVar2 & 0xe0) == 0x80 && (g_symbol_table[(uVar8 ^ uVar10) - uVar10].sclass == '\x05'))
           )))))) {
        bVar2 = pgVar6->type;
        if ((((bVar2 & 0xe0) == 0x80) &&
            ((((bVar2 & 0x18) == 0x10 || ((bVar2 & 0xf8) == 0x10)) || ((bVar2 & 0xf8) == 0x18)))) ||
           (((pgVar6->op == IL_ID && (0 < pgVar6->symx)) &&
            ((uVar8 = (int)pgVar6->symx + 0xb6, uVar10 = (int)uVar8 >> 0x1f,
             g_symbol_table[(uVar8 ^ uVar10) - uVar10].sclass == '\t' ||
             (((bVar2 & 0xe0) == 0x80 &&
              (g_symbol_table[(uVar8 ^ uVar10) - uVar10].sclass == '\x05')))))))) {
          both_static = true;
        }
      }
      if (both_static) {
        local_28 = new_label_operand(0x49);
      }
      else {
        local_28 = new_label_operand(0x4a);
      }
LAB_00405fd0:
      call_flags = '\0';
    }
    else {
      bVar2 = 0;
      pnVar1 = pgVar9->desc;
      peVar4 = pnVar1->mem_ea;
      if (peVar4 != (ea *)0x0) {
        bVar2 = peVar4->type & 0x1f;
      }
      if (((bVar2 == 0) && (peVar4 = &pnVar1->dest, (peVar4->type & 0x1f) == 0)) &&
         (peVar4 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
        peVar4 = &pnVar1->value;
      }
      local_28 = copy_ea(peVar4);
      local_28->type = local_28->type & 0xf7 | 7;
      local_28->type = local_28->type & 0xbf;
      cVar3 = node->desc->regs_2c[0];
      if (('\a' < cVar3) && (cVar3 < '\x0f')) goto LAB_00405fd0;
    }
    if ((pgVar9->op == IL_ID) &&
       (uVar8 = (int)pgVar9->symx + 0xb6, uVar10 = (int)uVar8 >> 0x1f,
       (g_symbol_table[(uVar8 ^ uVar10) - uVar10].sym_flags & 0x40) != 0)) {
      iVar5 = find_symbol_request_entry_a(g_request,pgVar9->symx,&entry_a);
      if ((iVar5 == 0) ||
         (iVar5 = find_symbol_request_entry_b(g_request,pgVar9->symx,&entry_b), iVar5 == 0)) {
        report_codegen_message(0x1248,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      }
      else {
        fill_psd_record_at_line
                  ((psd *)&g_psd_scratch,OP_NON_10,node->child->filn,node->child->line,entry_a,
                   entry_b);
        emit_psd_record((psd *)&g_psd_scratch,0);
      }
      goto LAB_00406199;
    }
    cVar3 = node->desc->regs_2c[0];
    op = 0x23;
    peVar4 = local_28;
  }
  else {
    bVar2 = 0;
    if (peVar4 != (ea *)0x0) {
      bVar2 = peVar4->type & 0x1f;
    }
    peVar7 = peVar4;
    if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
       (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
      peVar7 = &pnVar1->value;
    }
    if ((peVar7->type & 0x1f) == 7) goto LAB_00405d72;
    bVar2 = 0;
    if (peVar4 != (ea *)0x0) {
      bVar2 = peVar4->type & 0x1f;
    }
    peVar7 = peVar4;
    if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
       (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
      peVar7 = &pnVar1->value;
    }
    if ((peVar7->type & 0x1f) != 2) {
      bVar2 = 0;
      if (peVar4 != (ea *)0x0) {
        bVar2 = peVar4->type & 0x1f;
      }
      peVar7 = peVar4;
      if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
         (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
        peVar7 = &pnVar1->value;
      }
      if ((peVar7->type & 0x1f) == 8) {
        bVar2 = 0;
        if (peVar4 != (ea *)0x0) {
          bVar2 = peVar4->type & 0x1f;
        }
        peVar7 = peVar4;
        if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
           (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
          peVar7 = &pnVar1->value;
        }
        if (peVar7->disp == 0) {
          bVar2 = 0;
          if (peVar4 != (ea *)0x0) {
            bVar2 = peVar4->type & 0x1f;
          }
          peVar7 = peVar4;
          if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
             (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
            peVar7 = &pnVar1->value;
          }
          if (peVar7->labels == (label_ref *)0x0) goto LAB_00405cbf;
        }
      }
LAB_00405d45:
      report_codegen_message(0x1201,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      goto LAB_00406199;
    }
LAB_00405cbf:
    bVar2 = 0;
    if (peVar4 != (ea *)0x0) {
      bVar2 = peVar4->type & 0x1f;
    }
    peVar7 = peVar4;
    if (((bVar2 == 0) && (peVar7 = &pnVar1->dest, ((pnVar1->dest).type & 0x1f) == 0)) &&
       (peVar7 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
      peVar7 = &pnVar1->value;
    }
    if (peVar7->base == 'l') goto LAB_00405d45;
    bVar2 = 0;
    if (peVar4 != (ea *)0x0) {
      bVar2 = peVar4->type & 0x1f;
    }
    if (((bVar2 == 0) && (peVar4 = &pnVar1->dest, (peVar4->type & 0x1f) == 0)) &&
       (peVar4 = &g_ea_pop, (pnVar1->flags2 & 8) == 0)) {
      peVar4 = &pnVar1->value;
    }
    peVar4 = copy_ea(peVar4);
    local_28 = peVar4;
    if (('\a' < peVar4->base) && (peVar4->base < '\x0f')) {
      call_flags = '\0';
    }
LAB_0040617e:
    cVar3 = -1;
    op = 0x95;
  }
  emit_psd_instruction(op,cVar3,'\0','\x02',call_flags,peVar4,(ea *)0x0);
LAB_00406199:
  if ((g_nested_operand_emit == '\x01') || (g_stmt_pushed_operand == '\x01')) {
    nested = '\x01';
  }
  else {
    nested = '\0';
  }
  if ((pgVar13->desc->usage == '\0') && (((pgVar13->desc->dest).type & 0x1f) == 0)) {
    if ((g_request->cpu == 4) || ((pgVar13->type & 0xf8) != 0x30)) {
      if ((pgVar13->type & 0xe0) == 0x60) {
        arg_bytes = arg_bytes + ret_size;
      }
    }
    else {
      arg_bytes = arg_bytes + 8;
    }
  }
  else if (return_space) {
    nested = '\x01';
  }
  local_28 = new_ea_operand_with_flags('\a',-1,-1,arg_bytes,'\0',(label_ref *)0x0);
  if (arg_bytes < 0x80) {
    if (arg_bytes == 0) {
      return;
    }
    pgVar13 = (gen_node *)0x0;
    peVar4 = copy_ea((ea *)&g_ea_r15);
    emit_psd_for_node(0x60,-1,nested,'\x02',local_28,peVar4,pgVar13);
    return;
  }
  local_24 = new_ea_operand_with_flags('\x01',node->desc->regs_2c[1],-1,0,'\0',(label_ref *)0x0);
  pgVar13 = (gen_node *)0x0;
  peVar4 = copy_ea(local_24);
  emit_psd_for_node(0x2a,-1,nested,'\x02',local_28,peVar4,pgVar13);
  pgVar13 = (gen_node *)0x0;
  peVar4 = copy_ea((ea *)&g_ea_r15);
  emit_psd_for_node(0x60,-1,nested,'\x02',local_24,peVar4,pgVar13);
  update_stack_travel(1,-arg_bytes,(psd *)0x0);
  return;
#undef push_type
#undef call_flags
#undef nested
#undef arg_bytes
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef ret_size
#undef entry_b
#undef entry_a
}



