#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_template_extra_operands
#define g_template_extra_operands (*(ea * *)(g_sd + 0x18aa0))


// entry: 00425f60
// name : assign_template_slot_registers
// size : 3240
// sig  : void assign_template_slot_registers(gen_node * node, tmpl_header * tmpl, uchar slot_kind, ea * extra0, ea * extra1, uint operand_regs, gen_node * account_node)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
assign_template_slot_registers
          (gen_node *node,tmpl_header *tmpl,uchar slot_kind,ea *extra0,ea *extra1,uint operand_regs,
          gen_node *account_node)

{
  short sVar1;
  gen_node *extra_opnd;
  uint uVar2;
  uint uVar3;
  ea *opnd_ea;
  node_desc *desc;
  byte bVar4;
  ushort uVar5;
  ushort uVar6;
  char *slot_regs;
  int iVar7;
  tmpl_entry *entry;
  ushort uVar8;
  uint uVar10;
  bool ascending;
  short slot;
  short target_reg;
  uint local_2c;
  uint local_28;
  node_desc **local_24;
  undefined1 local_20;
  gen_node *right_opnd;
  char *slot_uses;
  undefined1 local_14;
  uint target_mask;
  gen_node *left_opnd;
  uint spec_kind;
  uint chosen_mask;
  ushort uVar9;
  ushort *mask_ptr;
  uchar result;
  bool result_slot_known;
  char swap;
  
  left_opnd = node->child;
  if (left_opnd == (gen_node *)0x0) {
    right_opnd = (gen_node *)0x0;
  }
  else {
    right_opnd = left_opnd->next;
  }
  result_slot_known = false;
  chosen_mask = 0;
  local_24 = (node_desc **)0x0;
  target_mask = 0;
  local_20 = 0;
  target_reg = -1;
  if ((((tmpl->flags2 & 6) == 0) || ((node->desc->fpu_mode_flags & 1) != 0)) ||
     ((slot_kind & 0xf0) != 0x10)) {
    slot_uses = (char *)0xffffffff;
    local_14 = 0xff;
  }
  else {
    slot_uses = (char *)0x0;
    local_14 = 0;
    entry = tmpl->entries;
    uVar5 = entry->op;
    while (uVar5 != 0xff00) {
      if ((entry->op != 0x3800) && (entry->op != 0x3900)) {
        uVar5 = entry->opnd[0];
        if ((((uVar5 == 0x5e) || ((uVar5 == 0x5f || (uVar5 == 0x60)))) || (uVar5 == 0x61)) ||
           (uVar5 == 0x62)) {
          slot_regs = (char *)((int)&slot_uses + ((g_operand_desc_table[uVar5] & 0xfc000) >> 0xe));
          *slot_regs = *slot_regs + '\x01';
        }
        uVar5 = entry->opnd[1];
        if ((((uVar5 == 0x5e) || (uVar5 == 0x5f)) || (uVar5 == 0x60)) ||
           ((uVar5 == 0x61 || (uVar5 == 0x62)))) {
          slot_regs = (char *)((int)&slot_uses + ((g_operand_desc_table[uVar5] & 0xfc000) >> 0xe));
          *slot_regs = *slot_regs + '\x01';
        }
      }
      entry = entry + 1;
      uVar5 = entry->op;
    }
  }
  switch(slot_kind & 0xf0) {
  case 0x10:
    sVar1 = -1;
    result = tmpl->result;
    if (result == '\x03') {
      sVar1 = 0;
    }
    else if (result == '\x04') {
      sVar1 = 1;
    }
    else if (result == '\b') {
      sVar1 = 0;
    }
    else if (result == '\n') {
      sVar1 = 2;
    }
    if (sVar1 != -1) {
      iVar7 = r0_result_left_to_chooser(node,tmpl);
      if (iVar7 == 0) {
        desc = node->desc;
        if (((desc->dest).type & 0x1f) == 1) {
          target_reg = (short)(desc->dest).base;
          target_mask = ea_register_mask(&desc->dest);
LAB_004261b2: ;
        }
        else if (desc->target_regs == 0) {
          if (desc->ftarget_regs != 0) {
            target_reg = float_mask_to_register(desc->ftarget_regs);
            target_mask = (int)(short)node->desc->ftarget_regs << 0x10;
            goto LAB_004261b2;
          }
        }
        else {
          target_reg = mask_to_register((int)(short)desc->target_regs);
          target_mask = (int)(short)node->desc->target_regs;
        }
        if (((target_mask != 0) && (desc = node->desc, desc->pref_regs == 0)) &&
           (desc->fpref_regs == 0)) {
          desc->fpref_regs = (ushort)(target_mask >> 0x10);
          node->desc->pref_regs = (ushort)target_mask;
        }
      }
      result_slot_known = true;
      *(undefined1 *)((int)&local_24 + (int)sVar1) = 2;
    }
    slot_regs = node->desc->regs_2c;
    break;
  case 0x20:
    slot_regs = node->desc->regs_34;
    break;
  case 0x30:
    slot_regs = node->desc->regs_41;
    break;
  case 0x40:
    slot_regs = node->desc->regs_44;
    break;
  case 0x50:
    slot_regs = &node->desc->addr_reg;
    break;
  case 0x60:
    slot_regs = node->desc->regs_3d;
    break;
  case 0x70:
    slot_regs = &node->desc->reg_47;
    break;
  default:
    report_codegen_message(0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    slot_regs = slot_uses;
  }
  slot = 0;
  do {
    iVar7 = (int)slot;
    uVar2 = tmpl->reg_spec[iVar7];
    if (uVar2 == 0) break;
    if (*(char *)((int)&slot_uses + iVar7) != '\0') {
      uVar10 = 0;
      if ((uVar2 & 0x2000) != 0) {
        sVar1 = reusable_operand_register
                          (node,extra0,extra1,uVar2,target_reg,*(char *)((int)&local_24 + iVar7));
        bVar4 = (byte)sVar1;
        slot_regs[iVar7] = bVar4;
        if (bVar4 != 0xff) {
          if (((char)bVar4 < ' ') && (-1 < (char)bVar4)) {
            uVar3 = 1 << (bVar4 & 0x1f);
          }
          else {
            local_28 = 1 << (bVar4 - 0x20 & 0x1f);
            uVar3 = (1 << (bVar4 - 0x1f & 0x1f) | local_28) << 0x10;
          }
          invalidate_register_contents(uVar3);
          *(undefined1 *)((int)&local_24 + iVar7) = 1;
        }
      }
      spec_kind = uVar2 & 0x380000;
      if (((spec_kind == 0x80000) || (*(char *)((int)&local_24 + iVar7) == '\x01')) ||
         (spec_kind == 0x100000)) {
        if (spec_kind == 0x80000) {
          bVar4 = (byte)uVar2 & 0xf;
          (*(unsigned short *)((char *)&local_2c + 0)) = (ushort)(char)bVar4;
          slot_regs[iVar7] = bVar4;
        }
        else if (spec_kind == 0x100000) {
          uVar2 = uVar2 & 0xf;
          if ((uVar2 == 1) && (left_opnd != (gen_node *)0x0)) {
            bVar4 = 0;
            desc = left_opnd->desc;
            opnd_ea = desc->mem_ea;
            if (opnd_ea != (ea *)0x0) {
              bVar4 = opnd_ea->type & 0x1f;
            }
            if ((bVar4 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) {
              bVar4 = g_ea_pop.base;
              if ((desc->flags2 & 8) != 0) goto LAB_00426971;
              opnd_ea = &desc->value;
            }
            bVar4 = opnd_ea->base;
LAB_00426971:
            slot_regs[iVar7] = bVar4;
          }
          else {
            if ((uVar2 == 2) && (right_opnd != (gen_node *)0x0)) {
              bVar4 = 0;
              desc = right_opnd->desc;
              opnd_ea = desc->mem_ea;
              if (opnd_ea != (ea *)0x0) {
                bVar4 = opnd_ea->type & 0x1f;
              }
              if ((bVar4 == 0) && (opnd_ea = &desc->dest, ((desc->dest).type & 0x1f) == 0)) {
                if ((desc->flags2 & 8) == 0) goto LAB_0042696b;
                opnd_ea = &g_ea_pop;
              }
LAB_0042696e:
              bVar4 = opnd_ea->base;
              goto LAB_00426971;
            }
            if (((uVar2 == 5) && (opnd_ea = extra0, extra0 != (ea *)0x0)) ||
               ((uVar2 == 6 && (opnd_ea = extra1, extra1 != (ea *)0x0)))) goto LAB_0042696e;
            if ((uVar2 == 3) && (extra_opnd = nth_operand(node,3), extra_opnd != (gen_node *)0x0)) {
              desc = extra_opnd->desc;
              bVar4 = 0;
              opnd_ea = desc->mem_ea;
              if (opnd_ea != (ea *)0x0) {
                bVar4 = opnd_ea->type & 0x1f;
              }
              if ((bVar4 == 0) && (opnd_ea = &desc->dest, ((desc->dest).type & 0x1f) == 0)) {
                if ((desc->flags2 & 8) == 0) goto LAB_0042696b;
                opnd_ea = &g_ea_pop;
              }
              goto LAB_0042696e;
            }
            if ((uVar2 == 4) && (extra_opnd = nth_operand(node,4), extra_opnd != (gen_node *)0x0)) {
              desc = extra_opnd->desc;
              bVar4 = 0;
              opnd_ea = desc->mem_ea;
              if (opnd_ea != (ea *)0x0) {
                bVar4 = opnd_ea->type & 0x1f;
              }
              if (((bVar4 == 0) && (opnd_ea = &desc->dest, ((desc->dest).type & 0x1f) == 0)) &&
                 (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
LAB_0042696b:
                opnd_ea = &desc->value;
              }
              goto LAB_0042696e;
            }
          }
          bVar4 = slot_regs[iVar7];
          (*(unsigned short *)((char *)&local_2c + 0)) = (ushort)(char)bVar4;
          if (((short)(ushort)local_2c < 0x20) && (-1 < (char)bVar4)) {
            uVar2 = 1 << (bVar4 & 0x1f);
          }
          else {
            uVar2 = (1 << (bVar4 - 0x1f & 0x1f) | 1 << (bVar4 - 0x20 & 0x1f)) << 0x10;
          }
          invalidate_register_contents(uVar2);
        }
        else if (*(char *)((int)&local_24 + iVar7) == '\x01') {
          (*(unsigned short *)((char *)&local_2c + 0)) = (ushort)slot_regs[iVar7];
        }
      }
      else {
        uVar3 = uVar10;
        if (((uVar2 & 0x40000) != 0) && (uVar3 = chosen_mask, (uVar2 & 0x3c000) != 0)) {
          if (((uVar2 & 0x4000) != 0) && (bVar4 = *slot_regs, bVar4 != 0xff)) {
            if (((char)bVar4 < ' ') && (-1 < (char)bVar4)) {
              uVar10 = 1 << (bVar4 & 0x1f);
            }
            else {
              uVar10 = (1 << (bVar4 - 0x1f & 0x1f) | 1 << (bVar4 - 0x20 & 0x1f)) << 0x10;
            }
          }
          if (((uVar2 & 0x8000) != 0) && (bVar4 = slot_regs[1], bVar4 != 0xff)) {
            if (((char)bVar4 < ' ') && (-1 < (char)bVar4)) {
              uVar3 = 1 << (bVar4 & 0x1f);
            }
            else {
              local_28 = 1 << (bVar4 - 0x20 & 0x1f);
              uVar3 = (1 << (bVar4 - 0x1f & 0x1f) | local_28) << 0x10;
            }
            uVar10 = uVar10 | uVar3;
          }
          if (((uVar2 & 0x10000) != 0) && (bVar4 = slot_regs[2], bVar4 != 0xff)) {
            if (((char)bVar4 < ' ') && (-1 < (char)bVar4)) {
              uVar3 = 1 << (bVar4 & 0x1f);
            }
            else {
              local_28 = 1 << (bVar4 - 0x20 & 0x1f);
              uVar3 = (1 << (bVar4 - 0x1f & 0x1f) | local_28) << 0x10;
            }
            uVar10 = uVar10 | uVar3;
          }
          uVar3 = uVar10;
          if (((uVar2 & 0x20000) != 0) && (bVar4 = slot_regs[3], bVar4 != 0xff)) {
            if (((char)bVar4 < ' ') && (-1 < (char)bVar4)) {
              uVar3 = 1 << (bVar4 & 0x1f);
            }
            else {
              local_28 = 1 << (bVar4 - 0x20 & 0x1f);
              uVar3 = (1 << (bVar4 - 0x1f & 0x1f) | local_28) << 0x10;
            }
            uVar3 = uVar10 | uVar3;
          }
        }
        if (((uVar2 & 0x80) != 0) && (left_opnd != (gen_node *)0x0)) {
          desc = left_opnd->desc;
          bVar4 = 0;
          opnd_ea = desc->mem_ea;
          if (opnd_ea != (ea *)0x0) {
            bVar4 = opnd_ea->type & 0x1f;
          }
          if (((bVar4 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
             (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            opnd_ea = &desc->value;
          }
          uVar10 = ea_register_mask(opnd_ea);
          uVar3 = uVar3 | uVar10;
        }
        if (((uVar2 & 0x200) != 0) && (extra0 != (ea *)0x0)) {
          uVar10 = ea_register_mask(extra0);
          uVar3 = uVar3 | uVar10;
        }
        if (((uVar2 & 0x40) != 0) && (right_opnd != (gen_node *)0x0)) {
          desc = right_opnd->desc;
          bVar4 = 0;
          opnd_ea = desc->mem_ea;
          if (opnd_ea != (ea *)0x0) {
            bVar4 = opnd_ea->type & 0x1f;
          }
          if (((bVar4 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
             (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            opnd_ea = &desc->value;
          }
          uVar10 = ea_register_mask(opnd_ea);
          uVar3 = uVar3 | uVar10;
        }
        if (((uVar2 & 0x100) != 0) && (extra1 != (ea *)0x0)) {
          uVar10 = ea_register_mask(extra1);
          uVar3 = uVar3 | uVar10;
        }
        if (((uVar2 & 0x20) != 0) &&
           (extra_opnd = nth_operand(node,3), extra_opnd != (gen_node *)0x0)) {
          desc = extra_opnd->desc;
          bVar4 = 0;
          opnd_ea = desc->mem_ea;
          if (opnd_ea != (ea *)0x0) {
            bVar4 = opnd_ea->type & 0x1f;
          }
          if (((bVar4 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
             (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            opnd_ea = &desc->value;
          }
          uVar10 = ea_register_mask(opnd_ea);
          uVar3 = uVar3 | uVar10;
        }
        if (((uVar2 & 0x10) != 0) &&
           (extra_opnd = nth_operand(node,4), extra_opnd != (gen_node *)0x0)) {
          desc = extra_opnd->desc;
          bVar4 = 0;
          opnd_ea = desc->mem_ea;
          if (opnd_ea != (ea *)0x0) {
            bVar4 = opnd_ea->type & 0x1f;
          }
          if (((bVar4 == 0) && (opnd_ea = &desc->dest, (opnd_ea->type & 0x1f) == 0)) &&
             (opnd_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
            opnd_ea = &desc->value;
          }
          uVar10 = ea_register_mask(opnd_ea);
          uVar3 = uVar3 | uVar10;
        }
        uVar10 = uVar3 | uVar2 & 0xf;
        if (*(char *)((int)&local_24 + iVar7) == '\x02') {
          if ((uVar2 & 0x3000000) == 0) {
            uVar5 = node->desc->pref_regs;
          }
          else {
            uVar5 = node->desc->fpref_regs;
          }
        }
        else if (result_slot_known) {
          if ((uVar2 & 0x3000000) == 0) {
            uVar5 = ~node->desc->pref_regs & 0xf;
          }
          else {
            uVar5 = ~node->desc->fpref_regs & 0xf;
          }
        }
        else {
          uVar5 = 0;
        }
        if (spec_kind != 0x180000) {
          uVar5 = uVar5 | 1;
        }
        if ((*(char *)((int)&local_24 + iVar7) == '\x02') && (target_reg != -1)) {
          local_2c = (uint)tmpl->fclobbers;
          local_28 = (uint)tmpl->clobbers;
          if ((target_mask & (local_2c << 0x10 | local_28 | uVar10)) == 0) {
            slot_regs[iVar7] = (byte)target_reg;
            (*(unsigned short *)((char *)&local_2c + 0)) = (ushort)(char)(byte)target_reg;
            goto LAB_004269cd;
          }
        }
        uVar6 = (ushort)((operand_regs | uVar10) >> 0x10);
        uVar8 = (ushort)(uVar3 >> 0x10);
        if ((uVar2 & 0x2000000) == 0) {
          if ((uVar2 & 0x1000000) == 0) {
            ascending = spec_kind != 0x180000;
            local_28 = (uint)(short)uVar5;
            (*(unsigned short *)((char *)&local_2c + 0)) =
                 choose_general_register((ushort)(operand_regs | uVar10),uVar5,ascending);
            if ((ushort)local_2c == -1) {
              (*(unsigned short *)((char *)&local_2c + 0)) = choose_general_register((ushort)uVar10,uVar5,ascending);
              if ((ushort)local_2c == -1) {
                report_codegen_message
                          (0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
              }
              else {
                slot_regs[iVar7] = (byte)(ushort)local_2c;
              }
            }
            else {
              slot_regs[iVar7] = (byte)(ushort)local_2c;
            }
          }
          else {
            (*(unsigned short *)((char *)&local_2c + 0)) = choose_float_register(uVar6,uVar5);
            if ((ushort)local_2c == -1) {
              (*(unsigned short *)((char *)&local_2c + 0)) = choose_float_register(uVar8,uVar5);
              if ((ushort)local_2c == -1) {
                report_codegen_message
                          (0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
              }
              else {
                slot_regs[iVar7] = (byte)(ushort)local_2c;
              }
            }
            else {
              slot_regs[iVar7] = (byte)(ushort)local_2c;
            }
          }
        }
        else {
          (*(unsigned short *)((char *)&local_2c + 0)) = choose_float_register_pair(uVar6,uVar5);
          if ((ushort)local_2c == -1) {
            (*(unsigned short *)((char *)&local_2c + 0)) = choose_float_register_pair(uVar8,uVar5);
            if ((ushort)local_2c == -1) {
              report_codegen_message
                        (0x1227,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
            }
            else {
              slot_regs[iVar7] = (byte)(ushort)local_2c;
            }
          }
          else {
            slot_regs[iVar7] = (byte)(ushort)local_2c;
          }
        }
      }
LAB_004269cd:
      if (((short)(ushort)local_2c < 0x20) && (-1 < (short)(ushort)local_2c)) {
        uVar2 = 1 << ((byte)local_2c & 0x1f);
      }
      else {
        uVar2 = (1 << ((byte)local_2c - 0x1f & 0x1f) | 1 << ((byte)local_2c - 0x20 & 0x1f)) << 0x10;
      }
      chosen_mask = chosen_mask | uVar2;
      if (((short)(ushort)local_2c < 0) || (0xf < (short)(ushort)local_2c)) {
        if (((short)(ushort)local_2c < 0x10) || (0x1f < (short)(ushort)local_2c)) {
          if ((0x1f < (short)(ushort)local_2c) && ((short)(ushort)local_2c < 0x2f)) {
            mask_ptr = &account_node->desc->ftemp_regs;
            *mask_ptr = *mask_ptr |
                        1 << ((byte)local_2c - 0x1f & 0x1f) | 1 << ((byte)local_2c - 0x20 & 0x1f);
          }
        }
        else {
          mask_ptr = &account_node->desc->ftemp_regs;
          *mask_ptr = *mask_ptr | 1 << ((byte)local_2c - 0x10 & 0x1f);
        }
      }
      else {
        mask_ptr = &account_node->desc->temp_regs;
        *mask_ptr = *mask_ptr | 1 << ((byte)local_2c & 0x1f);
      }
    }
    slot = slot + 1;
  } while (slot < 5);
  if ((tmpl->flags & 8) != 0) {
    right_opnd = (gen_node *)((uint)right_opnd & 0xffff0000);
    (*(unsigned short *)((char *)&local_2c + 0)) = 0xffff;
    entry = tmpl->entries;
    if (entry->op != 0xff00) {
      uVar5 = (ushort)slot_uses;
      uVar6 = (ushort)slot_uses;
      do {
        if ((short)right_opnd != 0) {
          return;
        }
        if ((entry->flags & 4) != 0) {
          zero_words((uint *)&g_template_extra_operands,7);
          _g_template_extra_operands = extra0;
          _DAT_00458aa4 = extra1;
          extra0 = materialize_operand_record_from_descriptor
                             (node,entry->opnd[0],(ea **)&g_template_extra_operands);
          uVar9 = (ushort)(g_operand_desc_table[entry->opnd[1]] >> 0xe);
          uVar8 = uVar9 & 0x3f;
          if ((ushort)local_2c == 0xffff) {
            uVar2 = ea_register_mask(extra0);
            local_28 = uVar2 & 0xffff;
            uVar5 = 1 << (node->desc->regs_2c[(short)uVar8] & 0x1fU);
            (*(unsigned short *)((char *)&local_2c + 0)) = uVar8;
          }
          else {
            uVar2 = ea_register_mask(extra0);
            chosen_mask = CONCAT22((*(unsigned short *)((char *)&chosen_mask + 2)),(short)uVar2);
            left_opnd = (gen_node *)(CONCAT22((*(unsigned short *)((char *)&left_opnd + 2)),uVar9) & 0xffff003f);
            right_opnd = (gen_node *)CONCAT22((*(unsigned short *)((char *)&right_opnd + 2)),1);
            uVar6 = 1 << (node->desc->regs_2c[(short)uVar8] & 0x1fU);
          }
          local_24 = &node->desc;
          free_ea(extra0);
          if (((short)right_opnd != 0) &&
             ((((ushort)local_28 & uVar6) != 0 || (((ushort)chosen_mask & uVar5) != 0)))) {
            slot_regs = (*local_24)->regs_2c + (short)(ushort)local_2c;
            swap = *slot_regs;
            *slot_regs = (*local_24)->regs_2c[(short)left_opnd];
            (*local_24)->regs_2c[(short)left_opnd] = swap;
          }
        }
        entry = entry + 1;
      } while (entry->op != 0xff00);
    }
  }
  return;
}



