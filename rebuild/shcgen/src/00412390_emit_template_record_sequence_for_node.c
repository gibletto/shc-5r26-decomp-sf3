#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 00412390
// name : emit_template_record_sequence_for_node
// size : 5409
// sig  : void emit_template_record_sequence_for_node(gen_node * node, tmpl_entry * entries, ea * * operands)


int __cdecl emit_template_record_sequence_for_node(gen_node *node,tmpl_entry *entries,ea **operands)

{
  unsigned char _frec_3a[58];
#define saved_type (*(byte *)(_frec_3a + 0))
#define size_code (*(uchar *)(_frec_3a + 1))
#define opnd0 (*(ea * *)(_frec_3a + 2))
#define opnd1 (*(ea * *)(_frec_3a + 6))
#define opnd2 (*(ea * *)(_frec_3a + 10))
#define opnd3 (*(undefined4 *)(_frec_3a + 14))
#define opnd4 (*(undefined4 *)(_frec_3a + 18))
#define opnd5 (*(undefined4 *)(_frec_3a + 22))
#define opnd6 (*(undefined4 *)(_frec_3a + 26))
#define local_1c (*(ushort * *)(_frec_3a + 30))
#define left_node (*(gen_node * *)(_frec_3a + 34))
#define macro_opnds (*(ea * (*)[2])(_frec_3a + 38))
#define right_node (*(gen_node * *)(_frec_3a + 46))
#define parent_node (*(gen_node * *)(_frec_3a + 50))
#define second_code (*(ushort * *)(_frec_3a + 54))
  byte bVar1;
  char cVar2;
  short labno;
  short sVar3;
  ushort uVar4;
  int iVar5;
  ea *opnd;
  gen_node *target_node;
  tmpl_header *tmpl;
  ushort *puVar6;
  uint source_kind;
  ushort usage2_flag;
  bool t_is_value;
  uchar size;
  uint opnd_desc;
  
  parent_node = node->parent;
  left_node = node->child;
  if (left_node == (gen_node *)0x0) {
    right_node = (gen_node *)0x0;
  }
  else {
    right_node = left_node->next;
  }
  uVar4 = entries->op;
  do {
    if (uVar4 == 0xff00) {
      return;
    }
    puVar6 = &entries->flags;
    if ((*puVar6 & 1) == 0) {
LAB_004124bc:
      cVar2 = g_nested_operand_emit;
      uVar4 = *puVar6;
      if ((((((uVar4 & 0x10) == 0) || ((node->type & 4) != 0)) ||
           (bVar1 = node->type & 0xe0, bVar1 == 0x80)) || (bVar1 == 0x40)) &&
         (((uVar4 & 0x20) == 0 || (node->desc->bit_width != ' ')))) {
        usage2_flag = uVar4 & 0x40;
        if ((usage2_flag != 0) && ((uVar4 & 0x80) != 0)) {
          target_node = parent_node;
          if (node->op != IL_ARG) {
            target_node = node;
          }
          if (target_node->desc->usage != '\x02') {
            target_node = parent_node;
            if (node->op != IL_ARG) {
              target_node = node;
            }
            if (target_node->desc->usage != '\x03') goto LAB_0041389b;
          }
        }
        if (usage2_flag == 0) {
LAB_00412549:
          if ((uVar4 & 0x80) != 0) {
            target_node = parent_node;
            if (node->op != IL_ARG) {
              target_node = node;
            }
            if (target_node->desc->usage != '\x03') goto LAB_0041389b;
          }
        }
        else {
          if ((uVar4 & 0x80) == 0) {
            target_node = parent_node;
            if (node->op != IL_ARG) {
              target_node = node;
            }
            if (target_node->desc->usage != '\x02') goto LAB_0041389b;
          }
          if (usage2_flag == 0) goto LAB_00412549;
        }
        uVar4 = entries->op;
        if (uVar4 == 0x23) {
          switch((uint)entries->opnd[0]) {
          case 0xfe:
            sVar3 = select_arithmetic_routine(node);
            break;
          case 0xff:
            sVar3 = select_conversion_routine(left_node,node);
            break;
          case 0x100:
            sVar3 = select_conversion_routine(right_node,left_node);
            break;
          case 0x101:
            sVar3 = select_bitfield_routine(0x101,left_node->type);
            break;
          case 0x102:
            sVar3 = select_bitfield_routine(0x102,node->type);
            break;
          case 0x103:
            sVar3 = select_copy_routine(node);
            break;
          case 0x104:
            sVar3 = select_conversion_routine(left_node,right_node);
            break;
          case 0x105:
            sVar3 = select_shift_routine(node);
            break;
          default:
            sVar3 = (short)g_operand_desc_table[entries->opnd[0]];
          }
          opnd0 = new_label_operand(sVar3);
          opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
          emit_psd_for_node(0x23,opnd1->base,'\0','\x02',opnd0,(ea *)0x0,node);
          free_ea(opnd1);
        }
        else if (uVar4 == 0xa00) {
          g_nested_operand_emit = '\x01';
          local_1c = (ushort *)CONCAT31((*(unsigned int *)((char *)&local_1c + 1) & 0xffffff),cVar2);
          target_node = right_node;
          if ((node->desc->flags2 & 0x80) == 0) {
            target_node = left_node;
          }
          emit_node_code(target_node);
          g_nested_operand_emit = (char)local_1c;
        }
        else if (uVar4 == 0xb00) {
          g_nested_operand_emit = '\x01';
          local_1c = (ushort *)CONCAT31((*(unsigned int *)((char *)&local_1c + 1) & 0xffffff),cVar2);
          if ((node->desc->flags2 & 0x80) == 0) {
            emit_node_code(right_node);
            target_node = left_node;
          }
          else {
            emit_node_code(left_node);
            target_node = right_node;
          }
          load_node_address_register(target_node);
          g_nested_operand_emit = (char)local_1c;
        }
        else if (uVar4 == 0x900) {
          opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
          opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
          emit_shift_by_constant(opnd1,'\x02',opnd0->disp);
          free_ea(opnd0);
          free_ea(opnd1);
        }
        else if (uVar4 == 0x1100) {
          opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
          opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
          if (((node->op == IL_A_DIV) || (node->op == IL_DIV)) ||
             ((((left_node->type & 4) == 0 &&
               ((bVar1 = left_node->type & 0xe0, bVar1 != 0x80 && (bVar1 != 0x40)))) &&
              ((left_node->op != IL_CAST ||
               (((left_node->child == (gen_node *)0x0 ||
                 (((bVar1 = left_node->child->type, (bVar1 & 4) == 0 && ((bVar1 & 0xe0) != 0x80)) &&
                  ((bVar1 & 0xe0) != 0x40)))) || (((bVar1 & 0xf8) != 0 && ((bVar1 & 0xf8) != 8))))))
              )))) {
            cVar2 = '\0';
          }
          else {
            cVar2 = '\x01';
          }
          emit_right_shift_by_constant(opnd1,opnd0->disp,cVar2);
          free_ea(opnd0);
          free_ea(opnd1);
        }
        else if (uVar4 == 0x2000) {
          opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
          opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
          emit_sar_r0_by_rotation(opnd0->disp,opnd1);
          free_ea(opnd0);
          free_ea(opnd1);
        }
        else if (uVar4 == 0x1000) {
          opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
          if (node->op == IL_ARG) {
            sVar3 = node->parent->desc->false_label;
          }
          else {
            sVar3 = node->desc->false_label;
          }
          t_is_value = sVar3 == 0;
          if ((node->op == IL_ARG) && (node->desc->builtin == '\x10')) {
            t_is_value = !t_is_value;
          }
          emit_movt_result(node,t_is_value,opnd0);
          free_ea(opnd0);
        }
        else {
          if ((((uVar4 == 0x300) || (uVar4 == 0x1600)) ||
              ((uVar4 == 0x1700 || (((uVar4 == 0x4200 || (uVar4 == 0x400)) || (uVar4 == 0x200))))))
             || (((uVar4 == 0x600 || (uVar4 == 0x700)) ||
                 ((uVar4 == 0x800 || ((uVar4 == 0x500 || (uVar4 == 0x2300)))))))) {
            uVar4 = resolve_macro_psd_op(node,uVar4,&size_code);
            local_1c = (ushort *)CONCAT22((*(unsigned short *)((char *)&local_1c + 2)),uVar4);
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            opnd1 = opnd;
            if (((*puVar6 & 2) != 0) && (opnd0->base == '\0')) {
              opnd1 = opnd0;
              opnd0 = opnd;
            }
            if ((entries->op == 0x200) &&
               ((((cVar2 = node->desc->builtin, cVar2 == '\r' || (cVar2 == '\x0f')) ||
                 (cVar2 == '\x0e')) && ((opnd1->type & 0x1f) == 0xc)))) {
              opnd1->type = opnd1->type | 0x80;
            }
            cVar2 = -1;
            uVar4 = (ushort)local_1c;
            opnd = opnd1;
            size = size_code;
            goto LAB_0041385b;
          }
          if (((uVar4 == 0x2f00) || (uVar4 == 0x3000)) || (uVar4 == 0x3100)) {
            opnd = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            iVar5 = emit_single_bit_field_store(node,entries,opnd,operands);
            entries = entries + iVar5;
            free_ea(opnd);
          }
          else if (uVar4 == 0x100) {
            iVar5 = emit_push_double_one(node,entries,operands);
            entries = entries + iVar5;
          }
          else if (uVar4 == 0x3200) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            emit_float_arith_op(node,opnd0,opnd1,0);
            free_ea(opnd0);
            free_ea(opnd1);
          }
          else if (uVar4 == 0x3500) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            emit_float_arith_op(node,opnd0,opnd1,1);
            free_ea(opnd0);
            free_ea(opnd1);
          }
          else if (uVar4 == 0x3600) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            emit_float_compare(node,opnd0,opnd1);
            free_ea(opnd0);
            free_ea(opnd1);
          }
          else if (uVar4 == 0x3300) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            iVar5 = emit_unsigned_to_float(node,entries,(int *)operands,opnd0,opnd1);
            entries = entries + iVar5;
            free_ea(opnd0);
            free_ea(opnd1);
          }
          else if (uVar4 == 0x3400) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            iVar5 = emit_float_to_unsigned(node,entries,(int *)operands,opnd0,opnd1);
            entries = entries + iVar5;
            free_ea(opnd0);
            free_ea(opnd1);
          }
          else if (uVar4 == 0x4300) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            iVar5 = emit_unsigned_to_double(node,entries,(int *)operands,opnd0,opnd1);
            entries = entries + iVar5;
            free_ea(opnd0);
            free_ea(opnd1);
          }
          else if (uVar4 == 0x4400) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
            iVar5 = emit_double_to_unsigned(node,entries,(int *)operands,opnd0,opnd1);
            entries = entries + iVar5;
            free_ea(opnd0);
            free_ea(opnd1);
          }
          else if (uVar4 == 0x3700) {
            opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
            emit_fabs_or_fsqrt(node,opnd0);
            free_ea(opnd0);
          }
          else if (((uVar4 == 0xc00) || (uVar4 == 0xd00)) ||
                  ((((uVar4 == 0x2b00 ||
                     (((uVar4 == 0x2700 || (uVar4 == 0x2800)) || (uVar4 == 0xf00)))) ||
                    ((uVar4 == 0x1c00 || (uVar4 == 0xe00)))) || (uVar4 == 0x1b00)))) {
            local_1c = entries->opnd;
            opnd0 = materialize_operand_record_from_descriptor(node,*local_1c,operands);
            second_code = entries->opnd + 1;
            opnd1 = materialize_operand_record_from_descriptor(node,*second_code,operands);
            opnd2 = materialize_operand_record_from_descriptor(node,entries->opnd[2],operands);
            opnd = opnd0;
            if (((*puVar6 & 2) != 0) && (opnd0->base == '\0')) {
              opnd0 = opnd1;
              opnd1 = opnd;
            }
            uVar4 = entries->op;
            puVar6 = second_code;
            if (((uVar4 != 0xf00) && (uVar4 != 0x1c00)) && (uVar4 != 0x2800)) {
              puVar6 = local_1c;
            }
            opnd_desc = g_operand_desc_table[*puVar6];
            source_kind = opnd_desc & 0xfc000000;
            if (source_kind == 0x10000000) {
              target_node = node->child;
            }
            else if (source_kind == 0x14000000) {
              if (node->child == (gen_node *)0x0) {
                target_node = (gen_node *)0x0;
              }
              else {
                target_node = node->child->next;
              }
            }
            else {
              if (source_kind == 0x1c000000) {
                iVar5 = ((opnd_desc & 0x3f00000) >> 0x14) + 2;
              }
              else if ((opnd_desc & 0x3fff) == 0xf) {
                iVar5 = count_operands(node);
                iVar5 = iVar5 + -1;
              }
              else {
                target_node = node;
                if ((opnd_desc & 0x3fff) != 0x10) goto LAB_00413592;
                iVar5 = count_operands(node);
                iVar5 = iVar5 + -2;
              }
              target_node = nth_operand(node,iVar5);
            }
LAB_00413592:
            uVar4 = entries->op;
            if ((uVar4 == 0x1b00) && ((node->desc->flags3 & 0x20) != 0)) {
              tmpl = (tmpl_header *)&g_tmpl_apusha005;
            }
            else {
              if (uVar4 < 0xd01) {
                if (uVar4 == 0xd00) {
                  local_1c = (ushort *)0x3;
                }
                else {
                  if (uVar4 == 0xc00) goto LAB_00413607;
LAB_004135fd:
                  local_1c = (ushort *)0x0;
                }
              }
              else if (uVar4 < 0xf01) {
                if (uVar4 == 0xf00) {
LAB_00413625:
                  local_1c = (ushort *)0x2;
                }
                else {
                  if (uVar4 != 0xe00) goto LAB_004135fd;
LAB_0041361b:
                  local_1c = (ushort *)0x4;
                }
              }
              else {
                if (uVar4 < 0x1c01) {
                  if (uVar4 != 0x1c00) {
                    if (uVar4 == 0x1b00) goto LAB_0041361b;
                    goto LAB_004135fd;
                  }
                  goto LAB_00413625;
                }
                if (uVar4 != 0x2700) {
                  if (uVar4 == 0x2800) goto LAB_00413625;
                  if (uVar4 != 0x2b00) goto LAB_004135fd;
                }
LAB_00413607:
                local_1c = (ushort *)0x1;
              }
              if (uVar4 == 0x1c00) {
                saved_type = target_node->type;
                target_node->type = '@';
              }
              else if (uVar4 == 0x2b00) {
                saved_type = target_node->type;
LAB_004136c3:
                target_node->type = '\x18';
              }
              else if ((uVar4 == 0x2700) || (uVar4 == 0x2800)) {
                saved_type = target_node->type;
                bVar1 = saved_type & 0xe0;
                if ((((bVar1 == 0x60) || (bVar1 == 0x80)) && ((saved_type & 0x18) == 0x10)) ||
                   (((((saved_type & 0xf8) == 0x10 || ((saved_type & 0xf8) == 0x18)) ||
                     (bVar1 == 0x20)) || (bVar1 == 0x40)))) goto LAB_004136c3;
                bVar1 = node->type;
                if (((((bVar1 & 0xe0) == 0x60) || ((bVar1 & 0xe0) == 0x80)) && ((bVar1 & 0x18) == 8)
                    ) || ((bVar1 & 0xf8) == 8)) {
                  target_node->type = '\b';
                }
                else {
                  target_node->type = '\0';
                }
              }
              opnd5 = 0;
              tmpl = select_transfer_template
                               (0,(uint)local_1c,opnd0,opnd1,opnd2,target_node->type,
                                target_node->desc->usage,target_node);
            }
            if (tmpl != (tmpl_header *)0x0) {
              opnd3 = 0;
              opnd4 = 0;
              opnd6 = 0;
              emit_template_record_sequence_for_node(target_node,tmpl->entries,&opnd0);
            }
            uVar4 = entries->op;
            if (((uVar4 == 0x1c00) || (uVar4 == 0x2b00)) || ((uVar4 == 0x2700 || (uVar4 == 0x2800)))
               ) {
              target_node->type = saved_type;
            }
            free_ea(opnd0);
            free_ea(opnd1);
            free_ea(opnd2);
          }
          else if (((uVar4 == 0x25) || (uVar4 == 0x26)) || (uVar4 == 0x24)) {
            sVar3 = find_template_label(node,(short)g_operand_desc_table[entries->opnd[0]]);
            opnd0 = make_label_operand(sVar3);
            opnd = materialize_operand_record_from_descriptor(node,entries->opnd[2],operands);
            local_1c = (ushort *)CONCAT31((*(unsigned int *)((char *)&local_1c + 1) & 0xffffff),opnd->base);
            free_ea(opnd);
            uVar4 = entries->op;
            opnd = (ea *)0x0;
            cVar2 = (char)local_1c;
            size = '\x02';
LAB_0041385b:
            emit_psd_for_node(uVar4,cVar2,'\0',size,opnd0,opnd,node);
          }
          else if (uVar4 == 0x18) {
            sVar3 = (short)g_sptravel;
            labno = find_template_label(node,(short)g_operand_desc_table[entries->opnd[0]]);
            fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,sVar3);
            emit_psd_record((psd *)&g_psd_scratch,0);
          }
          else {
            if (uVar4 == 0x1d00) {
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              cVar2 = node->desc->builtin;
              if ((cVar2 == '\x18') || (cVar2 == '\x19')) {
                uVar4 = 0x4a;
                opnd = (ea *)0x0;
                cVar2 = -1;
                size = '\x02';
              }
              else {
                uVar4 = 0x4b;
                opnd = (ea *)0x0;
                cVar2 = -1;
                size = '\x02';
              }
              goto LAB_0041385b;
            }
            if (uVar4 == 0x1e00) {
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              opnd2 = materialize_operand_record_from_descriptor(node,entries->opnd[2],operands);
              cVar2 = node->desc->builtin;
              if ((cVar2 == '\x18') || (cVar2 == '\x1a')) {
                iVar5 = (node->child->desc->value).disp;
              }
              else if (node->child == (gen_node *)0x0) {
                iVar5 = *(int *)((*(int *)0x00000028) + 0x6c);
              }
              else {
                iVar5 = (node->child->next->desc->value).disp;
              }
              emit_mac_builtin_records((int)cVar2,iVar5,opnd0,opnd1,opnd2);
            }
            else if (uVar4 == 0x1f00) {
              emit_operand_moves_to_target_registers(node,1);
            }
            else if (uVar4 == 0x2100) {
              iVar5 = collect_macro_operand_list(node,entries + 1,macro_opnds,operands);
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              expand_multiply_by_constant(opnd0->disp,opnd1,macro_opnds,1);
              free_ea(opnd1);
              free_ea(opnd0);
              free_macro_operand_list(macro_opnds);
              entries = entries + iVar5;
            }
            else if (((uVar4 == 0x2400) || (uVar4 == 0x2a00)) ||
                    ((uVar4 == 0x2500 || (uVar4 == 0x2600)))) {
              iVar5 = collect_macro_operand_list(node,entries + 1,macro_opnds,operands);
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              opnd = *operands;
              if (opnd == (ea *)0x0) {
                opnd = &right_node->desc->value;
              }
              emit_block_copy_macro(entries->op,opnd0,opnd1,macro_opnds,opnd,node);
              free_ea(opnd1);
              free_ea(opnd0);
              free_macro_operand_list(macro_opnds);
              entries = entries + iVar5;
            }
            else if (uVar4 == 0x2c00) {
              iVar5 = collect_macro_operand_list(node,entries + 1,macro_opnds,operands);
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              emit_symbol_sized_block_copy(node,opnd0,opnd1,macro_opnds);
              free_ea(opnd1);
              free_ea(opnd0);
              free_macro_operand_list(macro_opnds);
              entries = entries + iVar5;
            }
            else if (uVar4 == 0x2d00) {
              iVar5 = collect_macro_operand_list(node,entries + 1,macro_opnds,operands);
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              emit_add_constant_minus_one(node,opnd0,opnd1,macro_opnds);
              free_ea(opnd1);
              free_ea(opnd0);
              free_macro_operand_list(macro_opnds);
              entries = entries + iVar5;
            }
            else if (uVar4 == 0x2e00) {
              iVar5 = collect_macro_operand_list(node,entries + 1,macro_opnds,operands);
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              emit_shad_right_by_constant(node,opnd0,opnd1,macro_opnds);
              free_ea(opnd1);
              free_ea(opnd0);
              free_macro_operand_list(macro_opnds);
              entries = entries + iVar5;
            }
            else if ((uVar4 == 0x3800) || (uVar4 == 0x3900)) {
              bVar1 = node->desc->fpu_mode_flags;
              if ((bVar1 & 4) == 0) {
                bVar1 = bVar1 & 1;
              }
              else {
                bVar1 = bVar1 & 2;
              }
              if (bVar1 != 0) {
                opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
                opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
                opnd = opnd1;
                if (entries->op == 0x3800) {
                  uVar4 = 0x2e;
                  cVar2 = -1;
                  size = '\x02';
                }
                else {
                  uVar4 = 0x2e;
                  cVar2 = -1;
                  size = '\x03';
                }
                goto LAB_0041385b;
              }
            }
            else if (uVar4 == 0x3a00) {
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              emit_paired_fmov(node,opnd0,opnd1);
              free_ea(opnd0);
              free_ea(opnd1);
            }
            else {
              if (uVar4 != 0x4100) {
                opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
                opnd = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
                opnd1 = opnd;
                if (((*puVar6 & 2) != 0) && (opnd0->base == '\0')) {
                  opnd1 = opnd0;
                  opnd0 = opnd;
                }
                opnd = materialize_operand_record_from_descriptor(node,entries->opnd[2],operands);
                if (opnd == (ea *)0x0) {
                  local_1c = (ushort *)CONCAT31((*(unsigned int *)((char *)&local_1c + 1) & 0xffffff),0xff);
                }
                else {
                  local_1c = (ushort *)CONCAT31((*(unsigned int *)((char *)&local_1c + 1) & 0xffffff),opnd->base);
                  free_ea(opnd);
                }
                if ((node->op == IL_ARG) && (cVar2 = node->desc->builtin, cVar2 != '\0')) {
                  switch(cVar2) {
                  case '\a':
                  case '\n':
                  case '\r':
                  case '\x0e':
                  case '\x0f':
                  case '\x10':
                    size_code = '\0';
                    break;
                  case '\b':
                  case '\v':
                  case '\x18':
                  case '\x19':
                    size_code = '\x01';
                    break;
                  case '\t':
                  case '\f':
                  case '\x1a':
                  case '\x1b':
                    size_code = '\x02';
                    break;
                  default:
                    size_code = psd_size_code_of_node(node);
                  }
                  switch(node->desc->builtin) {
                  case '\a':
                  case '\b':
                  case '\t':
                    if ((opnd0->type & 0x1f) == 0xb) {
                      opnd0->type = opnd0->type | 0x80;
                    }
                    break;
                  case '\n':
                  case '\v':
                  case '\f':
                    if ((opnd1->type & 0x1f) == 0xb) {
                      opnd1->type = opnd1->type | 0x80;
                    }
                    break;
                  case '\x10':
                    if ((opnd1->type & 0x1f) == 0xc) {
                      opnd1->type = opnd1->type | 0x80;
                    }
                  }
                }
                else {
                  size_code = psd_size_code_of_node(node);
                }
                uVar4 = entries->op;
                opnd = opnd1;
                cVar2 = (char)local_1c;
                size = size_code;
                goto LAB_0041385b;
              }
              opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
              opnd1 = materialize_operand_record_from_descriptor(node,entries->opnd[1],operands);
              emit_paired_fmov_reverse(node,opnd0,opnd1);
              free_ea(opnd0);
              free_ea(opnd1);
            }
          }
        }
        if ((entries->flags & 8) != 0) {
          opnd0 = materialize_operand_record_from_descriptor(node,entries->opnd[0],operands);
          update_stack_travel(1,opnd0->disp,(psd *)0x0);
          free_ea(opnd0);
        }
      }
    }
    else if ((((entries->op == 0x300) && (cVar2 = left_node->desc->opnd_class, cVar2 != '\x01')) &&
             (cVar2 != '\0')) &&
            ((((left_node->type & 4) == 0 && (bVar1 = left_node->type & 0xe0, bVar1 != 0x80)) &&
             (bVar1 != 0x40)))) {
      local_1c = (ushort *)node_value_size(left_node);
      iVar5 = node_value_size(node);
      if (iVar5 <= (int)local_1c) goto LAB_0041242f;
    }
    else {
LAB_0041242f:
      uVar4 = entries->op;
      if ((uVar4 != 0x300) || ((node->desc->flags7 & 2) == 0)) {
        if (uVar4 == 0x1600) {
          bVar1 = left_node->type;
          if ((((bVar1 & 0xf8) != 0) && ((bVar1 & 0xf8) != 8)) ||
             (((bVar1 & 4) == 0 &&
              (((((bVar1 & 0xe0) != 0x80 && ((bVar1 & 0xe0) != 0x40)) &&
                (cVar2 = left_node->desc->opnd_class, cVar2 != '\x01')) && (cVar2 != '\0'))))))
          goto LAB_0041389b;
        }
        if (((((uVar4 != 0x1700) || ((node->type & 4) != 0)) ||
             (bVar1 = node->type & 0xe0, bVar1 == 0x80)) || (bVar1 == 0x40)) &&
           (((uVar4 != 0x4200 || (bVar1 = node->type & 0xf8, bVar1 == 0)) || (bVar1 == 8))))
        goto LAB_004124bc;
      }
    }
LAB_0041389b:
    entries = entries + 1;
    uVar4 = entries->op;
  } while( true );
#undef saved_type
#undef size_code
#undef opnd0
#undef opnd1
#undef opnd2
#undef opnd3
#undef opnd4
#undef opnd5
#undef opnd6
#undef local_1c
#undef left_node
#undef macro_opnds
#undef right_node
#undef parent_node
#undef second_code
}



