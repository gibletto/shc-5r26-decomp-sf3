#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00422180
// name : generate_operator_by_template
// size : 4739
// sig  : void generate_operator_by_template(gen_node * node, tmpl_select * select, char operand_count)


int __cdecl generate_operator_by_template(gen_node *node,tmpl_select *select,char operand_count)

{
  bool bVar1;
  bool bVar2;
  byte bVar3;
  short sVar4;
  tmpl_header **out;
  ea *opnd_ea;
  int iVar5;
  uint uVar6;
  uint excluded;
  ushort *mask_ptr;
  ea *other_ea;
  byte bVar7;
  ushort reg_mask;
  gen_node *right;
  bool bVar8;
  char ascending;
  short left_target_reg;
  short right_target_reg;
  short reselect;
  int saved_hit;
  ushort right_mask;
  node_desc *desc;
  uchar *flag_byte;
  label_ref *labels;
  gen_node *left_opnd;
  il_op op;
  gen_node *parent_node;
  tmpl_header *tmpl;
  
  left_target_reg = -1;
  right_target_reg = -1;
  bVar1 = false;
  bVar2 = false;
  out = &node->desc->tmpl;
  if ((*out == (tmpl_header *)0x0) &&
     (sVar4 = select_node_template(node,select,operand_count,'\x01',out), sVar4 != 0)) {
    bVar8 = true;
  }
  else {
    bVar8 = false;
  }
  left_opnd = node->child;
  right = (gen_node *)0x0;
  if (left_opnd != (gen_node *)0x0) {
    right = left_opnd->next;
  }
  apply_template_operand_constraints(node);
  parent_node = node->parent;
  if (((g_r0_variable == 0) &&
      (((node->op == IL_ADD || (node->op == IL_SUB)) && (parent_node != (gen_node *)0x0)))) &&
     (parent_node->op == IL_ASTER)) {
    if (parent_node->desc->usage == '\x03') {
      op = parent_node->parent->op;
      if (((op == IL_ASSIGN) && ((parent_node->parent->desc->flags7 & 0x20) != 0)) ||
         (((('7' < (char)op && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`')))) &&
          ((tmpl = parent_node->parent->desc->tmpl, tmpl != (tmpl_header *)0x0 &&
           ((tmpl->excluded & 1) != 0)))))) goto LAB_004222a6;
    }
    if ((((((parent_node->type & 0xe0) == 0) || (bVar3 = parent_node->type & 0xf8, bVar3 == 0x40))
         || (bVar3 == 0x28)) &&
        ((left_opnd == (gen_node *)0x0 ||
         ((left_opnd->op != IL_CONST &&
          ((left_opnd->op != IL_ID || (left_opnd->desc->need_regs != 0)))))))) &&
       ((right == (gen_node *)0x0 ||
        ((right->op != IL_CONST && ((right->op != IL_ID || (right->desc->need_regs != 0)))))))) {
      bVar1 = true;
    }
  }
LAB_004222a6:
  if (left_opnd != (gen_node *)0x0) {
    left_opnd->desc->busy_regs = node->desc->busy_regs;
    left_opnd->desc->fbusy_regs = node->desc->fbusy_regs;
    left_opnd->desc->frame_top = node->desc->frame_top;
    flag_byte = &left_opnd->desc->flags7;
    *flag_byte = *flag_byte | node->desc->flags7 & 0x40;
    desc = left_opnd->desc;
    if ((desc->pref_regs == 0) && (desc->fpref_regs == 0)) {
      desc->pref_regs = node->desc->pref_regs;
      left_opnd->desc->fpref_regs = node->desc->fpref_regs;
    }
    tmpl = node->desc->tmpl;
    if (tmpl != (tmpl_header *)0x0) {
      mask_ptr = &left_opnd->desc->busy_regs;
      *mask_ptr = *mask_ptr & ~(ushort)tmpl->clobbers;
    }
    if (bVar1) {
      left_opnd->desc->pref_regs = 1;
    }
    dispatch_and_finalize_code_node(left_opnd);
    if (right != (gen_node *)0x0) {
      right->desc->busy_regs = left_opnd->desc->busy_regs;
      right->desc->fbusy_regs = left_opnd->desc->fbusy_regs;
      right->desc->frame_top = left_opnd->desc->frame_top;
      flag_byte = &right->desc->flags7;
      *flag_byte = *flag_byte | left_opnd->desc->flags7 & 0x40;
      op = node->op;
      if (((((op == IL_ADD) || (op == IL_MUL)) || (('_' < (char)op && ((char)op < 'h')))) ||
          (((op == IL_B_AND || (op == IL_B_XOR)) || (op == IL_B_OR)))) &&
         ((mask_ptr = &right->desc->pref_regs, *mask_ptr == 0 && (left_opnd->desc->fpref_regs == 0))
         )) {
        *mask_ptr = node->desc->pref_regs;
        right->desc->fpref_regs = node->desc->fpref_regs;
      }
      if (((bVar1) && (((left_opnd->desc->value).type & 0x1f) == 1)) &&
         ((left_opnd->desc->value).base != '\0')) {
        right->desc->pref_regs = 1;
      }
      dispatch_and_finalize_code_node(right);
    }
  }
  if (((('_' < (char)node->op) && ((char)node->op < 'h')) && (left_opnd->op == IL_CAST)) &&
     (right->op == IL_CAST)) {
    bVar3 = left_opnd->child->type;
    if ((((((bVar3 & 4) != 0) || ((bVar3 & 0xe0) == 0x80)) || ((bVar3 & 0xe0) == 0x40)) &&
        (((bVar7 = right->child->type, (bVar7 & 4) != 0 || ((bVar7 & 0xe0) == 0x80)) ||
         ((bVar7 & 0xe0) == 0x40)))) &&
       ((((bVar7 ^ bVar3) & 0xf8) == 0 && (((bVar3 & 0xf8) == 0 || ((bVar3 & 0xf8) == 8)))))) {
      desc = left_opnd->child->desc;
      bVar3 = 0;
      opnd_ea = desc->mem_ea;
      if (opnd_ea != (ea *)0x0) {
        bVar3 = opnd_ea->type & 0x1f;
      }
      other_ea = opnd_ea;
      if (((bVar3 == 0) && (other_ea = &desc->dest, ((desc->dest).type & 0x1f) == 0)) &&
         (other_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        other_ea = &desc->value;
      }
      if ((other_ea->type & 0x1f) != 1) {
        bVar3 = 0;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
           (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          opnd_ea = &desc->value;
        }
        if ((opnd_ea->type & 0x1f) != 7) {
          bVar3 = 0;
          desc = right->child->desc;
          opnd_ea = desc->mem_ea;
          if (opnd_ea != (ea *)0x0) {
            bVar3 = opnd_ea->type & 0x1f;
          }
          other_ea = opnd_ea;
          if (((bVar3 == 0) && (other_ea = &desc->dest, ((desc->dest).type & 0x1f) == 0)) &&
             (other_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            other_ea = &desc->value;
          }
          if ((other_ea->type & 0x1f) != 1) {
            bVar3 = 0;
            if (opnd_ea != (ea *)0x0) {
              bVar3 = opnd_ea->type & 0x1f;
            }
            if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
               (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
              opnd_ea = &desc->value;
            }
            if ((opnd_ea->type & 0x1f) != 7) {
              flag_byte = &left_opnd->desc->flags7;
              *flag_byte = *flag_byte | 2;
              flag_byte = &right->desc->flags7;
              *flag_byte = *flag_byte | 2;
              left_opnd->type = left_opnd->type | 4;
              right->type = right->type | 4;
            }
          }
        }
      }
    }
  }
  if (((left_opnd != (gen_node *)0x0) && (left_opnd->desc->opnd_class == '\x02')) &&
     ((right == (gen_node *)0x0 || (right->desc->opnd_class == '\x02')))) {
    fold_constant_node(node);
    return;
  }
  if (((node->op == IL_CAST) && ((node->type & 0xe0) != 0x20)) &&
     (iVar5 = reuse_operand_value_for_cast(node), iVar5 != 0)) {
    return;
  }
  if (bVar8) {
    select_node_template(node,select,operand_count,'\0',&node->desc->tmpl);
  }
  reselect = resolve_operand_register_conflicts(node,left_opnd,right);
  op = node->op;
  if (((('7' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`')))) &&
     ((((op != IL_ASSIGN && (left_opnd->op != IL_B_QUALIFY)) &&
       (((left_opnd->type & 0xe0) == 0 ||
        ((bVar3 = left_opnd->type & 0xf8, bVar3 == 0x40 || (bVar3 == 0x28)))))) &&
      (desc = left_opnd->desc, ((desc->value).type & 0x1f) == 0xd)))) {
    labels = (desc->value).labels;
    if (labels == (label_ref *)0x0) {
      uVar6 = 0;
    }
    else {
      uVar6 = (uint)labels->labno1;
    }
    if ((g_symbol_table[(uVar6 ^ (int)uVar6 >> 0x1f) - ((int)uVar6 >> 0x1f)].attr & 3) == 0) {
      opnd_ea = copy_ea(&desc->value);
      opnd_ea->type = opnd_ea->type & 0xf7 | 7;
      saved_hit = g_content_hit;
      sVar4 = find_register_holding_constant(opnd_ea,'@');
      if ((sVar4 == -1) ||
         (bVar3 = (byte)sVar4, (1 << (bVar3 & 0x1f) & (uint)node->desc->tmpl->excluded) != 0)) {
        other_ea = &left_opnd->desc->value;
        other_ea->type = other_ea->type | 0x40;
        copy_ea_into(&left_opnd->desc->dest,&left_opnd->desc->value);
        if (right == (gen_node *)0x0) {
          right_mask = 0;
        }
        else {
          desc = right->desc;
          bVar3 = 0;
          other_ea = desc->mem_ea;
          if (other_ea != (ea *)0x0) {
            bVar3 = other_ea->type & 0x1f;
          }
          if (((bVar3 == 0) && (other_ea = &desc->dest, (other_ea->type & 0x1f) == 0)) &&
             (other_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            other_ea = &desc->value;
          }
          uVar6 = ea_register_mask(other_ea);
          right_mask = (ushort)uVar6;
        }
        ascending = '\0';
        tmpl = node->desc->tmpl;
        reg_mask = tmpl->pref_left;
        uVar6 = result_reg_exclusion_mask(node);
        sVar4 = choose_general_register
                          ((ushort)uVar6 | (ushort)tmpl->excluded | right_mask,reg_mask,ascending);
        if (sVar4 == -1) {
          if (right == (gen_node *)0x0) {
            reg_mask = 0;
          }
          else {
            desc = right->desc;
            bVar3 = 0;
            other_ea = desc->mem_ea;
            if (other_ea != (ea *)0x0) {
              bVar3 = other_ea->type & 0x1f;
            }
            if (((bVar3 == 0) && (other_ea = &desc->dest, (other_ea->type & 0x1f) == 0)) &&
               (other_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
              other_ea = &desc->value;
            }
            uVar6 = ea_register_mask(other_ea);
            reg_mask = (ushort)uVar6;
          }
          tmpl = node->desc->tmpl;
          sVar4 = choose_general_register(tmpl->excluded | reg_mask,tmpl->pref_left,'\0');
        }
        other_ea = alloc_zeroed(0xc);
        left_opnd->desc->addr_reg_ea = other_ea;
        fill_ea(left_opnd->desc->addr_reg_ea,'\x01',(byte)sVar4,-1,'\0',0,(label_ref *)0x0);
        other_ea = copy_ea(left_opnd->desc->addr_reg_ea);
        left_opnd->desc->mem_ea = other_ea;
        other_ea = left_opnd->desc->mem_ea;
        other_ea->type = other_ea->type & 0xf8 | 8;
        reg_mask = 1 << ((byte)sVar4 & 0x1f);
        flag_byte = &left_opnd->desc->flags3;
        *flag_byte = *flag_byte | 4;
        mask_ptr = &left_opnd->desc->busy_regs;
        *mask_ptr = *mask_ptr | reg_mask;
        g_used_gpr_mask = g_used_gpr_mask | left_opnd->desc->busy_regs;
        mask_ptr = &left_opnd->desc->temp_regs;
        *mask_ptr = *mask_ptr | reg_mask;
      }
      else {
        saved_hit = g_content_hit;
        free_label_ref_list((left_opnd->desc->value).labels);
        fill_ea(&left_opnd->desc->value,'\b',bVar3,-1,'\0',0,(label_ref *)0x0);
        flag_byte = &g_gpr_contents[sVar4].flags;
        if ((*flag_byte & 0x80) == 0) {
          reg_mask = 1 << (bVar3 & 0x1f);
          mask_ptr = &left_opnd->desc->busy_regs;
          *mask_ptr = *mask_ptr | reg_mask;
          g_used_gpr_mask = g_used_gpr_mask | left_opnd->desc->busy_regs;
          mask_ptr = &left_opnd->desc->temp_regs;
          *mask_ptr = *mask_ptr | reg_mask;
          *flag_byte = *flag_byte | 0x80;
        }
        else {
          reg_mask = 1 << (bVar3 & 0x1f);
          mask_ptr = &left_opnd->desc->busy_regs;
          *mask_ptr = *mask_ptr | reg_mask;
          g_used_gpr_mask = g_used_gpr_mask | left_opnd->desc->busy_regs;
        }
        mask_ptr = &left_opnd->desc->reused_regs;
        *mask_ptr = *mask_ptr | reg_mask;
        mask_ptr = &node->desc->reused_regs;
        *mask_ptr = *mask_ptr | reg_mask;
      }
      g_content_hit = saved_hit;
      free_ea(opnd_ea);
      select_node_template(node,select,operand_count,'\0',&node->desc->tmpl);
      bVar2 = true;
    }
  }
  if (((node->op == IL_ADD) || (node->op == IL_SUB)) &&
     (sVar4 = fold_address_add_sub(node,left_opnd,right), sVar4 != 0)) {
    return;
  }
  if (g_r0_variable != 0) goto LAB_00423356;
  bVar1 = false;
  desc = left_opnd->desc;
  opnd_ea = desc->mem_ea;
  if (opnd_ea == (ea *)0x0) {
    bVar3 = 0;
  }
  else {
    bVar3 = opnd_ea->type & 0x1f;
  }
  if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
     (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
    opnd_ea = &desc->value;
  }
  iVar5 = operand_access_needs_r0(opnd_ea,left_opnd->type);
  bVar8 = iVar5 != 0;
  op = node->op;
  if ((((op == IL_ADD) || (op == IL_SUB)) ||
      ((((op == IL_MUL || ((op == IL_B_AND || (op == IL_B_OR)))) || (op == IL_B_XOR)) ||
       ((((op == IL_A_ADD || (op == IL_A_SUB)) || (op == IL_A_MUL)) ||
        (('_' < (char)op && ((char)op < 'h')))))))) ||
     (((1 < g_request->cpu &&
       (((op == IL_SL || (op == IL_SR)) || ((op == IL_A_SL || (op == IL_A_SR)))))) ||
      (((op == IL_A_AND || (op == IL_A_OR)) || (op == IL_A_XOR)))))) {
    desc = right->desc;
    bVar3 = 0;
    opnd_ea = desc->mem_ea;
    if (opnd_ea != (ea *)0x0) {
      bVar3 = opnd_ea->type & 0x1f;
    }
    if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
       (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
      opnd_ea = &desc->value;
    }
    iVar5 = operand_access_needs_r0(opnd_ea,right->type);
    if (iVar5 != 0) {
      bVar1 = true;
    }
  }
  if (((bVar8) || (bVar1)) &&
     (((((op = node->op, op == IL_ADD || (((op == IL_SUB || (op == IL_MUL)) || (op == IL_B_AND))))
        || (((((op == IL_B_OR || (op == IL_B_XOR)) || (op == IL_A_ADD)) ||
             ((op == IL_A_SUB || (op == IL_A_MUL)))) || (('_' < (char)op && ((char)op < 'h')))))) ||
       (((1 < g_request->cpu &&
         ((((op == IL_SL || (op == IL_SR)) || (op == IL_A_SL)) || (op == IL_A_SR)))) ||
        (((op == IL_A_AND || (op == IL_A_OR)) || (op == IL_A_XOR)))))) &&
      (((left_opnd->desc->usage != '\x03' || (left_opnd->op != IL_B_QUALIFY)) &&
       ((reselect == 0 &&
        ((((node->desc->flags2 & 0x80) == 0 && ((left_opnd->type & 0xf8) != 0x30)) &&
         (bVar3 = right->type & 0xf8, bVar3 != 0x30)))))))))) {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      bVar7 = 1;
    }
    else {
      bVar7 = -(g_request->cpu == 4) & 2;
    }
    if ((bVar7 == 0) || (bVar3 != 0x28)) {
      opnd_ea = left_opnd->desc->mem_ea;
      bVar3 = 0;
      if (opnd_ea != (ea *)0x0) {
        bVar3 = opnd_ea->type & 0x1f;
      }
      if (((bVar3 == 0) && (opnd_ea = &left_opnd->desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (left_opnd->desc->flags2 & 8) == 0)) {
        opnd_ea = &left_opnd->desc->value;
      }
      if ((bVar1) && (!bVar2)) {
        if (op == IL_ADD) {
LAB_00422bd5:
          if (op == IL_MUL) goto LAB_00422bda;
LAB_00422be2:
          if (((((char)op < '`') || ('g' < (char)op)) || (!bVar8)) &&
             (uVar6 = ea_register_mask(opnd_ea), (uVar6 & 1) == 0)) goto LAB_00422c8b;
        }
        else {
          if (op != IL_MUL) {
            if ((((char)op < '`') || ('g' < (char)op)) &&
               ((op != IL_B_AND &&
                (((op != IL_B_XOR && (op != IL_B_OR)) && ((node->desc->pref_regs & 1) != 0))))))
            goto LAB_00422c8b;
            goto LAB_00422bd5;
          }
LAB_00422bda:
          if (!bVar8) goto LAB_00422be2;
        }
        bVar3 = node->desc->tmpl->excluded;
        if ((ushort)((right->desc->temp_regs | right->desc->reused_regs | (ushort)bVar3 | 0x8001) &
                     ~g_var_gpr_mask ^ g_var_gpr_mask) != 0xffff) {
          if (left_opnd->desc->usage == '\x03') {
            load_operand_address_into_new_register(node,left_opnd,right,(ushort)(bVar3 | 1));
          }
          else {
            move_operand_to_new_general_register(node,left_opnd,right,0,(ushort)(bVar3 | 1));
          }
          reselect = 1;
          bVar8 = false;
        }
      }
LAB_00422c8b:
      desc = right->desc;
      bVar3 = 0;
      opnd_ea = desc->mem_ea;
      if (opnd_ea != (ea *)0x0) {
        bVar3 = opnd_ea->type & 0x1f;
      }
      if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
      if (bVar8) {
        uVar6 = ea_register_mask(opnd_ea);
        if ((uVar6 & 1) != 0) {
          desc = left_opnd->desc;
          bVar3 = 0;
          opnd_ea = desc->mem_ea;
          if (opnd_ea != (ea *)0x0) {
            bVar3 = opnd_ea->type & 0x1f;
          }
          if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
             (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            opnd_ea = &desc->value;
          }
          uVar6 = ea_register_mask(opnd_ea);
          if ((~((uVar6 | 0xffff8001) & (int)(short)~g_var_gpr_mask ^ (int)(short)g_var_gpr_mask) &
              0xffff) != 0) {
            move_operand_to_new_general_register
                      (node,left_opnd,right,1,(ushort)(node->desc->tmpl->spill_mask | 1));
            reselect = 1;
          }
        }
        if (!bVar8) goto LAB_00422d6a;
      }
      else {
LAB_00422d6a:
        if ((bVar1) && ((node->desc->pref_regs & 1) == 0)) {
          desc = left_opnd->desc;
          bVar3 = 0;
          opnd_ea = desc->mem_ea;
          if (opnd_ea != (ea *)0x0) {
            bVar3 = opnd_ea->type & 0x1f;
          }
          if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
             (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            opnd_ea = &desc->value;
          }
          uVar6 = ea_register_mask(opnd_ea);
          if ((((byte)uVar6 | (byte)g_var_gpr_mask) & 1) == 0) {
            move_operand_to_new_general_register
                      (node,left_opnd,right,1,node->desc->tmpl->spill_mask | 0xfffe);
            reselect = 1;
          }
        }
        if (!bVar8) goto LAB_00422f2c;
      }
      if ((!bVar1) && ((op = node->op, op == IL_MUL || (('_' < (char)op && ((char)op < 'h')))))) {
        copy_ea_into(&left_opnd->desc->dest,&left_opnd->desc->value);
        opnd_ea = alloc_zeroed(0xc);
        left_opnd->desc->addr_reg_ea = opnd_ea;
        fill_ea(left_opnd->desc->addr_reg_ea,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
        desc = left_opnd->desc;
        opnd_ea = copy_ea(desc->addr_reg_ea);
        desc->mem_ea = opnd_ea;
        desc = right->desc;
        bVar3 = 0;
        opnd_ea = desc->mem_ea;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        other_ea = opnd_ea;
        if (((bVar3 == 0) && (other_ea = &desc->dest, ((desc->dest).type & 0x1f) == 0)) &&
           (other_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          other_ea = &desc->value;
        }
        bVar3 = 0;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
           (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          opnd_ea = &desc->value;
        }
        parent_node = left_opnd;
        uVar6 = ea_register_mask(other_ea);
        excluded = ea_register_mask(opnd_ea);
        emit_operand_transfer
                  (&left_opnd->desc->dest,left_opnd->desc->addr_reg_ea,'P',left_opnd,0xc00,
                   left_opnd->type,excluded,uVar6,(int)parent_node);
        flag_byte = &left_opnd->desc->flags3;
        *flag_byte = *flag_byte | 4;
        left_opnd->desc->opnd_class = '\0';
        mask_ptr = &left_opnd->desc->busy_regs;
        *(byte *)mask_ptr = (byte)*mask_ptr | 1;
        bVar8 = false;
        g_used_gpr_mask = g_used_gpr_mask | left_opnd->desc->busy_regs;
        reselect = 1;
        mask_ptr = &left_opnd->desc->temp_regs;
        *(byte *)mask_ptr = (byte)*mask_ptr | 1;
      }
    }
  }
LAB_00422f2c:
  op = node->op;
  if ((((char)op < '`') || ('g' < (char)op)) &&
     ((bVar8 || ((bVar1 && (((op == IL_ADD || (op == IL_MUL)) ||
                            ((('_' < (char)op && ((char)op < 'h')) ||
                             (((op == IL_B_AND || (op == IL_B_XOR)) || (op == IL_B_OR)))))))))))) {
    node->desc->pref_regs = 1;
  }
  op = node->op;
  if (((('7' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`')))) ||
     (('_' < (char)op && ((char)op < 'h')))) goto LAB_00423356;
  desc = node->desc;
  reg_mask = desc->target_regs;
  if ((reg_mask == 0) &&
     ((desc->ftarget_regs == 0 && ((bVar3 = (desc->dest).type & 0x1f, bVar3 == 0 || (bVar3 != 1)))))
     ) {
    reg_mask = desc->pref_regs;
    if ((reg_mask == 0) || ((reg_mask & ~desc->busy_regs) == 0)) {
      if ((reg_mask & 1) != 0) {
        desc = left_opnd->desc;
        bVar3 = 0;
        opnd_ea = desc->mem_ea;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
           (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          opnd_ea = &desc->value;
        }
        iVar5 = operand_access_needs_r0(opnd_ea,left_opnd->type);
        if (iVar5 != 0) {
          mask_ptr = &node->desc->busy_regs;
          *(byte *)mask_ptr = (byte)*mask_ptr & 0xfe;
        }
      }
      goto LAB_00423356;
    }
    if ((((op == IL_ADD) || (op == IL_MUL)) || (('_' < (char)op && ((char)op < 'h')))) ||
       ((((op == IL_B_AND || (op == IL_B_XOR)) || (op == IL_B_OR)) || (right == (gen_node *)0x0))))
    {
      desc = left_opnd->desc;
      if (desc->opnd_class == '\0') {
        opnd_ea = desc->mem_ea;
        bVar3 = 0;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
           (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          opnd_ea = &desc->value;
        }
        if (((int)(short)reg_mask & 1 << (opnd_ea->base & 0x1fU)) == 0) {
          desc->opnd_class = '\x01';
          reselect = 1;
        }
      }
      if ((right == (gen_node *)0x0) || (desc = right->desc, desc->opnd_class != '\0'))
      goto LAB_00423356;
      opnd_ea = desc->mem_ea;
      bVar3 = 0;
      if (opnd_ea != (ea *)0x0) {
        bVar3 = opnd_ea->type & 0x1f;
      }
      if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
      if ((1 << (opnd_ea->base & 0x1fU) & (int)(short)node->desc->pref_regs) != 0)
      goto LAB_00423356;
      desc->opnd_class = '\x01';
    }
    else {
      sVar4 = single_bit_position((int)(short)reg_mask);
      if ((sVar4 != -1) || (desc = left_opnd->desc, desc->opnd_class != '\0')) goto LAB_00423356;
      opnd_ea = desc->mem_ea;
      bVar3 = 0;
      if (opnd_ea != (ea *)0x0) {
        bVar3 = opnd_ea->type & 0x1f;
      }
      if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
      if ((1 << (opnd_ea->base & 0x1fU) & (int)(short)node->desc->pref_regs) != 0)
      goto LAB_00423356;
      desc->opnd_class = '\x01';
    }
  }
  else {
    if (reg_mask == 0) {
      if (desc->ftarget_regs == 0) {
        sVar4 = (short)(desc->dest).base;
      }
      else {
        sVar4 = float_mask_to_register(desc->ftarget_regs);
      }
    }
    else {
      sVar4 = mask_to_register((int)(short)reg_mask);
    }
    bVar1 = false;
    bVar2 = false;
    if ((left_opnd != (gen_node *)0x0) && (desc = left_opnd->desc, desc->opnd_class == '\0')) {
      opnd_ea = desc->mem_ea;
      if (opnd_ea == (ea *)0x0) {
        bVar3 = 0;
      }
      else {
        bVar3 = opnd_ea->type & 0x1f;
      }
      if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
         (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        opnd_ea = &desc->value;
      }
      if (opnd_ea->base != sVar4) {
        desc->opnd_class = '\x01';
        bVar2 = true;
      }
    }
    op = node->op;
    if ((((op == IL_ADD) || (op == IL_MUL)) || (('_' < (char)op && ((char)op < 'h')))) ||
       (((op == IL_B_AND || (op == IL_B_XOR)) || (op == IL_B_OR)))) {
      if ((right != (gen_node *)0x0) && (desc = right->desc, desc->opnd_class == '\0')) {
        opnd_ea = desc->mem_ea;
        bVar3 = 0;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
           (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          opnd_ea = &desc->value;
        }
        if (opnd_ea->base != sVar4) {
          desc->opnd_class = '\x01';
          bVar1 = true;
        }
      }
      if ((!bVar1) && (desc = right->desc, desc->opnd_class == '\x01')) {
        opnd_ea = desc->mem_ea;
        bVar3 = 0;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
           (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          opnd_ea = &desc->value;
        }
        if (opnd_ea->base == sVar4) {
          desc->opnd_class = '\0';
          right_target_reg = sVar4;
          goto LAB_0042334f;
        }
      }
      if ((!bVar2) && (desc = left_opnd->desc, desc->opnd_class == '\x01')) {
        opnd_ea = desc->mem_ea;
        bVar3 = 0;
        if (opnd_ea != (ea *)0x0) {
          bVar3 = opnd_ea->type & 0x1f;
        }
        if (((bVar3 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
           (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
          opnd_ea = &desc->value;
        }
        if (opnd_ea->base == sVar4) {
          desc->opnd_class = '\0';
          left_target_reg = sVar4;
        }
      }
    }
  }
LAB_0042334f:
  reselect = 1;
LAB_00423356:
  if (reselect == 1) {
    select_node_template(node,select,operand_count,'\0',&node->desc->tmpl);
  }
  left_opnd = node;
  uVar6 = result_reg_exclusion_mask(node);
  apply_template_to_node(node,node->desc->tmpl,'\x10',(ea *)0x0,(ea *)0x0,uVar6,left_opnd);
  if ((node->op == IL_B_AND) && (node->desc->usage == '\x01')) {
    flag_byte = &node->desc->flags2;
    *flag_byte = *flag_byte | 0x20;
    flag_byte = &node->desc->flags7;
    *flag_byte = *flag_byte | 1;
  }
  if (((left_target_reg != -1) && (desc = node->desc, desc->opnd_class == '\0')) &&
     ((desc->value).base == left_target_reg)) {
    desc->opnd_class = '\x01';
  }
  if (((right_target_reg != -1) && (desc = node->desc, desc->opnd_class == '\0')) &&
     ((desc->value).base == right_target_reg)) {
    desc->opnd_class = '\x01';
  }
  return;
}



