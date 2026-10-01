#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_aux_index
#define g_current_aux_index (*(int *)(g_sd + 0xf8ec))
#undef g_request_copy
#define g_request_copy (*(request * *)(g_sd + 0x129a8))


// entry: 0042be20
// name : decide_literal_pool_placement
// size : 6749
// sig  : int decide_literal_pool_placement(psd * rec, FILE * lit_out)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl decide_literal_pool_placement(psd *rec,FILE *lit_out)

{
  unsigned char _frec_44[68];
#define lit_disp2 (*(uint *)(_frec_44 + 0))
#define lit_refs2 (*(label_ref * *)(_frec_44 + 4))
#define frame_disp2 (*(int *)(_frec_44 + 8))
#define pool_reach (*(int *)(_frec_44 + 12))
#define lit_disp (*(uint *)(_frec_44 + 16))
#define lit_refs (*(label_ref * *)(_frec_44 + 20))
#define frame_disp (*(int *)(_frec_44 + 24))
#define pool_bytes (*(short *)(_frec_44 + 28))
#define code_bytes (*(int *)(_frec_44 + 36))
#define fpscr_value (*(uint *)(_frec_44 + 40))
#define new_lit_ea (*(ea * *)(_frec_44 + 44))
#define flush_flag (*(bool (*)[4])(_frec_44 + 48))
#define stack_imm (*(uint *)(_frec_44 + 52))
#define new_lit_bytes (*(int *)(_frec_44 + 56))
#define tmp_ref (*(label_ref * *)(_frec_44 + 60))
  short pending_bytes;
  int found;
  uint uVar1;
  int iVar2;
  
  pool_bytes = 0;
  new_lit_ea = (ea *)0x0;
  new_lit_bytes = 0;
  code_bytes = 0;
  if (((((rec->op == OP_C_JMP) || (rec->op == OP_CTBL)) || (rec->op == OP_PRGRAM)) ||
      (rec->op == OP_CENT)) || ((rec->op == OP_B_ASM && (rec->ea2 == (ea *)0x0)))) {
    if ((rec->op == OP_C_JMP) || (rec->op == OP_B_ASM)) {
      if ((rec->op == OP_B_ASM) && (g_pool_code_bytes + g_pool_pending_literal_bytes != 0)) {
        flush_flag[0] =
             g_pool_code_bytes + g_pool_pending_literal_bytes + g_pool_carried_code_bytes +
             g_pool_carried_literal_bytes <=
             (int)((-(uint)(g_pool_carried_has_word == '\x01') & 0xfffffe02) + 0x3cc);
        pool_bytes = (short)g_pool_pending_literal_bytes;
        if (flush_flag[0]) {
          pool_bytes = pool_bytes + (short)g_pool_carried_literal_bytes;
        }
        flush_flag[0] = !flush_flag[0];
        if (pool_bytes == 0) {
          g_pool_flush_pending = 1;
        }
        else {
          uVar1 = write_file_bytes(lit_out,flush_flag,1);
          if (uVar1 == 0xffffffff) {
            report_message_at_source_line(0,0,0xce7,(char *)0x0);
          }
          g_pool_flush_pending = 0;
        }
      }
      if (rec->op == OP_C_JMP) {
        pool_bytes = 0x400;
      }
      clear_pool_literal_table(&g_word_literal_table);
      clear_pool_literal_table(&g_long_literal_table);
      clear_pool_literal_table(&g_frame_offset_literal_table);
      if (g_pool_pending_literal_bytes + g_pool_carried_literal_bytes == 0) {
        if (g_pool_carried_code_bytes < 0x400) {
          g_pool_carried_code_bytes = 0;
        }
      }
      else {
        g_pool_carried_code_bytes = 0x400;
      }
      g_pool_carried_literal_bytes = 0;
      g_pool_code_bytes = 0;
      g_pool_pending_literal_bytes = 0;
      g_pool_segment_has_word = '\0';
      g_pool_carried_has_word = '\0';
    }
    else if (rec->op == OP_PRGRAM) {
      g_pool_carried_code_bytes = 0x400;
    }
  }
  else {
    pending_bytes = compute_record_code_size(rec);
    code_bytes = (int)pending_bytes;
    switch(rec->op) {
    case OP_ENTER:
      if (((g_aux_record_table[_g_current_aux_index].flags & 0x4000) != 0) &&
         ((g_aux_record_table[_g_current_aux_index].flags & 0x1800) != 0)) {
        if (((byte)(g_aux_record_table[_g_current_aux_index].flags >> 8) & 0x18) == 8) {
          stack_imm = g_aux_record_table[_g_current_aux_index].stack_value;
          if (((int)stack_imm < -0x80) || (0x7f < (int)stack_imm)) {
            if (((int)stack_imm < -0x8000) || (0x7fff < (int)stack_imm)) {
              iVar2 = find_pool_literal(&g_long_literal_table,stack_imm,(label_ref *)0x0);
              if (iVar2 == 0) {
                new_lit_bytes = new_lit_bytes + 4;
              }
            }
            else {
              iVar2 = find_pool_literal(&g_word_literal_table,stack_imm,(label_ref *)0x0);
              if (iVar2 == 0) {
                new_lit_bytes = new_lit_bytes + 2;
                g_pool_segment_has_word = '\x01';
              }
            }
          }
        }
        else {
          tmp_ref = pool_alloc(8);
          tmp_ref->labno1 = (short)g_aux_record_table[_g_current_aux_index].stack_value;
          tmp_ref->labno2 = 0;
          iVar2 = get_symbol_attribute_bits(tmp_ref->labno1);
          if ((iVar2 != 1) &&
             ((iVar2 = get_symbol_attribute_bits(tmp_ref->labno1), iVar2 == 0 ||
              (((byte)(g_aux_record_table[_g_current_aux_index].flags >> 8) & 0x18) != 0x10)))) {
            iVar2 = symbol_address_is_abs16(tmp_ref->labno1);
            if (iVar2 == 0) {
              iVar2 = find_pool_literal(&g_long_literal_table,0,tmp_ref);
              if (iVar2 == 0) {
                new_lit_bytes = new_lit_bytes + 4;
              }
            }
            else {
              iVar2 = find_pool_literal(&g_word_literal_table,0,tmp_ref);
              if (iVar2 == 0) {
                new_lit_bytes = new_lit_bytes + 2;
                g_pool_segment_has_word = '\x01';
              }
            }
          }
          pool_free(tmp_ref,8);
        }
      }
      iVar2 = g_aux_record_table[_g_current_aux_index].frame_size;
      if ((iVar2 < -0x7f) || (0x80 < iVar2)) {
        if ((iVar2 < 0x8001) && (-0x8000 < iVar2)) {
          iVar2 = find_pool_literal(&g_word_literal_table,-iVar2,(label_ref *)0x0);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 2;
            g_pool_segment_has_word = '\x01';
          }
        }
        else {
          iVar2 = find_pool_literal(&g_long_literal_table,-iVar2,(label_ref *)0x0);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 4;
          }
        }
      }
      break;
    case OP_EXIT:
      uVar1 = g_aux_record_table[_g_current_aux_index].sp_adjust +
              g_aux_record_table[_g_current_aux_index].frame_size;
      if ((0x7f < (int)uVar1) || ((int)uVar1 < -0x80)) {
        if (((int)uVar1 < -0x8000) || (0x7fff < (int)uVar1)) {
          iVar2 = find_pool_literal(&g_long_literal_table,uVar1,(label_ref *)0x0);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 4;
          }
        }
        else {
          iVar2 = find_pool_literal(&g_word_literal_table,uVar1,(label_ref *)0x0);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 2;
            g_pool_segment_has_word = '\x01';
          }
        }
      }
      break;
    case OP_RETURN:
      pending_bytes = count_saved_registers(g_current_aux_index);
      if (pending_bytes < 2) {
        uVar1 = g_aux_record_table[_g_current_aux_index].sp_adjust +
                g_aux_record_table[_g_current_aux_index].frame_size;
        if ((0x7f < (int)uVar1) || ((int)uVar1 < -0x80)) {
          if (((int)uVar1 < -0x8000) || (0x7fff < (int)uVar1)) {
            iVar2 = find_pool_literal(&g_long_literal_table,uVar1,(label_ref *)0x0);
            if (iVar2 == 0) {
              new_lit_bytes = new_lit_bytes + 4;
            }
          }
          else {
            iVar2 = find_pool_literal(&g_word_literal_table,uVar1,(label_ref *)0x0);
            if (iVar2 == 0) {
              new_lit_bytes = new_lit_bytes + 2;
              g_pool_segment_has_word = '\x01';
            }
          }
        }
      }
      else {
        tmp_ref = pool_alloc(8);
        tmp_ref->labno1 = rec->ea1->labels->labno1;
        if (g_request_copy->pic == 0) {
          iVar2 = find_pool_literal(&g_long_literal_table,0,tmp_ref);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 4;
          }
        }
        else {
          tmp_ref->labno2 = -g_literal_label_serial;
          g_literal_label_serial = g_literal_label_serial + 1;
          iVar2 = find_pool_literal(&g_long_literal_table,0xfffffffc,tmp_ref);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 4;
          }
          else {
            report_message_at_source_line(0,0,0x12f3,(char *)0x0);
          }
        }
        pool_free(tmp_ref,8);
      }
      break;
    case OP_CALL:
    case OP_JUMP:
    case OP_JUMPT:
    case OP_JUMPF:
    case OP_MVA_FC:
      tmp_ref = pool_alloc(8);
      tmp_ref->labno1 = rec->ea1->labels->labno1;
      if (g_request_copy->pic == 0) {
        iVar2 = symbol_address_is_abs16(tmp_ref->labno1);
        if (iVar2 == 0) {
          iVar2 = find_pool_literal(&g_long_literal_table,0,tmp_ref);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 4;
          }
        }
        else {
          iVar2 = find_pool_literal(&g_word_literal_table,0,tmp_ref);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 2;
            g_pool_segment_has_word = '\x01';
          }
        }
      }
      else {
        tmp_ref->labno2 = -g_literal_label_serial;
        g_literal_label_serial = g_literal_label_serial + 1;
        iVar2 = find_pool_literal(&g_long_literal_table,(rec->op == OP_MVA_FC) - 1 & 0xfffffffc,
                                  tmp_ref);
        if (iVar2 == 0) {
          new_lit_bytes = new_lit_bytes + 4;
        }
        else {
          report_message_at_source_line(0,0,0x12f3,(char *)0x0);
        }
      }
      pool_free(tmp_ref,8);
      break;
    case OP_MV_LOC:
      if ((rec->misc & 0x80U) == 0) {
        frame_disp = rec->ea1->disp;
      }
      else {
        frame_disp = rec->ea2->disp;
      }
      iVar2 = frame_offset_to_sp_displacement(frame_disp,rec->sptravel);
      if ((0x7f < iVar2) || (iVar2 < -0x80)) {
        if ((rec->misc & 0x80U) == 0) {
          lit_refs = rec->ea1->labels;
        }
        else {
          lit_refs = rec->ea2->labels;
        }
        if ((rec->misc & 0x80U) == 0) {
          lit_disp = rec->ea1->disp;
        }
        else {
          lit_disp = rec->ea2->disp;
        }
        found = find_pool_literal(&g_frame_offset_literal_table,lit_disp,lit_refs);
        if (found == 0) {
          if ((iVar2 < 0x8000) && (-0x8001 < iVar2)) {
            new_lit_bytes = new_lit_bytes + 2;
          }
          else {
            new_lit_bytes = new_lit_bytes + 4;
          }
          if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
            g_pool_segment_has_word = '\x01';
          }
        }
      }
      break;
    case OP_MVA_LC:
      iVar2 = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
      if (((0x7f < iVar2) || (iVar2 < -0x80)) &&
         (found = find_pool_literal(&g_frame_offset_literal_table,rec->ea1->disp,rec->ea1->labels),
         found == 0)) {
        if ((iVar2 < 0x8000) && (-0x8001 < iVar2)) {
          new_lit_bytes = new_lit_bytes + 2;
        }
        else {
          new_lit_bytes = new_lit_bytes + 4;
        }
        if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
          g_pool_segment_has_word = '\x01';
        }
      }
      break;
    case OP_MVA_PC:
    case OP_MOVI:
      if ((rec->op != OP_MOVI) ||
         ((((rec->ea1->labels != (label_ref *)0x0 || (rec->ea1->disp < -0x80)) ||
           (0x7f < rec->ea1->disp)) &&
          (iVar2 = get_marked_symbol_attr_low_bits(rec->ea1->labels), iVar2 != 1)))) {
        if (((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) &&
           ((-0x8001 < rec->ea1->disp && (rec->ea1->disp < 0x8000)))) {
          iVar2 = find_pool_literal(&g_word_literal_table,rec->ea1->disp,rec->ea1->labels);
          if (iVar2 == 0) {
            new_lit_bytes = new_lit_bytes + 2;
            g_pool_segment_has_word = '\x01';
          }
        }
        else {
          iVar2 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
          if ((iVar2 == 0) &&
             (iVar2 = get_marked_symbol_attr_low_bits(rec->ea1->labels), iVar2 == 0)) {
            iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,rec->ea1->labels);
            if (iVar2 == 0) {
              new_lit_bytes = new_lit_bytes + 4;
            }
          }
          else {
            iVar2 = find_pool_literal(&g_word_literal_table,rec->ea1->disp,rec->ea1->labels);
            if (iVar2 == 0) {
              new_lit_bytes = new_lit_bytes + 2;
              g_pool_segment_has_word = '\x01';
            }
          }
        }
      }
      break;
    case OP_MOVIF:
      iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0);
      if (iVar2 == 0) {
        new_lit_bytes = new_lit_bytes + 4;
      }
      break;
    case OP_DUMMY_2D:
      break;
    case OP_FPRSET:
      if ((rec->flg & 3) == 3) {
        fpscr_value = 0x80000;
      }
      else {
        fpscr_value = 0xffe7ffff;
      }
      iVar2 = find_pool_literal(&g_long_literal_table,fpscr_value,(label_ref *)0x0);
      if (iVar2 == 0) {
        new_lit_bytes = new_lit_bytes + 4;
      }
    }
    if (((((rec->op == OP_RTS) || (rec->op == OP_RTE)) || (rec->op == OP_BRA)) ||
        ((rec->op == OP_JUMP || (rec->op == OP_JMP)))) ||
       ((rec->op == OP_EXIT || (rec->op == OP_RETURN)))) {
      if ((g_request_copy->flags_13d & 8) == 0) {
        if (g_request_copy->align16 != '\0') {
          new_lit_bytes = new_lit_bytes + 0xe;
        }
      }
      else {
        new_lit_bytes = new_lit_bytes + 0x3c;
      }
      if ((g_pool_carried_has_word == '\x01') || (g_pool_segment_has_word == '\x01')) {
        pool_reach = 0x1fe;
      }
      else {
        pool_reach = 0x3fc;
      }
      if ((pool_reach + -0x30 <
           g_pool_code_bytes + g_pool_pending_literal_bytes + code_bytes + new_lit_bytes +
           g_pool_carried_code_bytes + g_pool_carried_literal_bytes) || (g_pool_flush_pending == 1))
      {
        g_pool_carried_literal_bytes = g_pool_pending_literal_bytes + new_lit_bytes;
        pool_bytes = (short)g_pool_carried_literal_bytes;
        g_pool_carried_code_bytes = g_pool_code_bytes + code_bytes;
        flush_flag[0] = true;
        if ((g_word_literal_table.head == (literal_entry *)0x0) &&
           (g_pool_segment_has_word != '\x01')) {
          g_pool_carried_has_word = '\0';
        }
        else {
          g_pool_carried_has_word = '\x01';
        }
        g_pool_flush_pending = 0;
      }
      else {
        g_pool_carried_literal_bytes =
             g_pool_carried_literal_bytes + g_pool_pending_literal_bytes + new_lit_bytes;
        pool_bytes = (short)g_pool_carried_literal_bytes;
        g_pool_carried_code_bytes = g_pool_carried_code_bytes + g_pool_code_bytes + code_bytes;
        flush_flag[0] = false;
        if ((g_word_literal_table.head != (literal_entry *)0x0) ||
           (g_pool_segment_has_word == '\x01')) {
          g_pool_carried_has_word = '\x01';
        }
      }
      uVar1 = write_file_bytes(lit_out,flush_flag,1);
      if (uVar1 == 0xffffffff) {
        report_message_at_source_line(0,0,0xce7,(char *)0x0);
      }
      clear_pool_literal_table(&g_word_literal_table);
      clear_pool_literal_table(&g_long_literal_table);
      clear_pool_literal_table(&g_frame_offset_literal_table);
      code_bytes = 0;
      new_lit_bytes = 0;
      g_pool_code_bytes = 0;
      g_pool_pending_literal_bytes = 0;
      g_pool_segment_has_word = '\0';
    }
    else {
      pending_bytes = (short)g_pool_pending_literal_bytes;
      if ((g_word_literal_table.head == (literal_entry *)0x0) && (g_pool_segment_has_word != '\x01')
         ) {
        if (0x3cc < g_pool_code_bytes + g_pool_pending_literal_bytes + code_bytes + new_lit_bytes) {
          g_pool_carried_literal_bytes = g_pool_pending_literal_bytes;
          if (((g_request_copy->flags_13d & 8) == 0) || (pending_bytes == 0)) {
            pool_bytes = pending_bytes;
            if ((g_request_copy->align16 != '\0') && (pending_bytes != 0)) {
              pool_bytes = pending_bytes + 0xe;
            }
          }
          else {
            pool_bytes = pending_bytes + 0x3c;
          }
          g_pool_carried_code_bytes = g_pool_code_bytes + 4;
          flush_flag[0] = true;
          g_pool_carried_has_word = '\0';
          if (pool_bytes == 0) {
            g_pool_flush_pending = 1;
          }
          else {
            uVar1 = write_file_bytes(lit_out,flush_flag,1);
            if (uVar1 == 0xffffffff) {
              report_message_at_source_line(0,0,0xce7,(char *)0x0);
            }
            g_pool_flush_pending = 0;
          }
          clear_pool_literal_table(&g_word_literal_table);
          clear_pool_literal_table(&g_long_literal_table);
          clear_pool_literal_table(&g_frame_offset_literal_table);
          g_pool_code_bytes = 0;
          g_pool_pending_literal_bytes = 0;
          if (rec->op == OP_B_ASM) {
            g_pool_carried_code_bytes = 0x400;
            code_bytes = 0;
          }
        }
      }
      else if (0x1ce < g_pool_code_bytes + g_pool_pending_literal_bytes + code_bytes + new_lit_bytes
              ) {
        g_pool_carried_literal_bytes = g_pool_pending_literal_bytes;
        if (((g_request_copy->flags_13d & 8) == 0) || (pending_bytes == 0)) {
          pool_bytes = pending_bytes;
          if ((g_request_copy->align16 != '\0') && (pending_bytes != 0)) {
            pool_bytes = pending_bytes + 0xe;
          }
        }
        else {
          pool_bytes = pending_bytes + 0x3c;
        }
        g_pool_carried_code_bytes = g_pool_code_bytes + 4;
        flush_flag[0] = true;
        g_pool_carried_has_word = '\x01';
        if (pool_bytes == 0) {
          g_pool_flush_pending = 1;
        }
        else {
          uVar1 = write_file_bytes(lit_out,flush_flag,1);
          if (uVar1 == 0xffffffff) {
            report_message_at_source_line(0,0,0xce7,(char *)0x0);
          }
          g_pool_flush_pending = 0;
        }
        clear_pool_literal_table(&g_word_literal_table);
        clear_pool_literal_table(&g_long_literal_table);
        clear_pool_literal_table(&g_frame_offset_literal_table);
        g_pool_code_bytes = 0;
        g_pool_pending_literal_bytes = 0;
        g_pool_segment_has_word = '\0';
        if (rec->op == OP_B_ASM) {
          g_pool_carried_code_bytes = 0x400;
          code_bytes = 0;
        }
      }
    }
    switch(rec->op) {
    case OP_ENTER:
      new_lit_bytes = 0;
      if (((g_aux_record_table[_g_current_aux_index].flags & 0x4000) != 0) &&
         ((g_aux_record_table[_g_current_aux_index].flags & 0x1800) != 0)) {
        if (((byte)(g_aux_record_table[_g_current_aux_index].flags >> 8) & 0x18) == 8) {
          stack_imm = g_aux_record_table[_g_current_aux_index].stack_value;
          if (((int)stack_imm < -0x80) || (0x7f < (int)stack_imm)) {
            if (((int)stack_imm < -0x8000) || (0x7fff < (int)stack_imm)) {
              iVar2 = find_pool_literal(&g_long_literal_table,stack_imm,(label_ref *)0x0);
              if (iVar2 == 0) {
                new_lit_bytes = 4;
                add_pool_literal(&g_long_literal_table,stack_imm,(label_ref *)0x0);
              }
            }
            else {
              iVar2 = find_pool_literal(&g_word_literal_table,stack_imm,(label_ref *)0x0);
              if (iVar2 == 0) {
                new_lit_bytes = 2;
                add_pool_literal(&g_word_literal_table,stack_imm,(label_ref *)0x0);
              }
            }
          }
        }
        else {
          tmp_ref = pool_alloc(8);
          tmp_ref->labno1 = (short)g_aux_record_table[_g_current_aux_index].stack_value;
          tmp_ref->labno2 = 0;
          iVar2 = get_symbol_attribute_bits(tmp_ref->labno1);
          if ((iVar2 != 1) &&
             ((iVar2 = get_symbol_attribute_bits(tmp_ref->labno1), iVar2 == 0 ||
              (((byte)(g_aux_record_table[_g_current_aux_index].flags >> 8) & 0x18) != 0x10)))) {
            iVar2 = symbol_address_is_abs16(tmp_ref->labno1);
            if (iVar2 == 0) {
              iVar2 = find_pool_literal(&g_long_literal_table,0,tmp_ref);
              if (iVar2 == 0) {
                new_lit_bytes = 4;
                add_pool_literal(&g_long_literal_table,0,tmp_ref);
              }
            }
            else {
              iVar2 = find_pool_literal(&g_word_literal_table,0,tmp_ref);
              if (iVar2 == 0) {
                new_lit_bytes = 2;
                add_pool_literal(&g_word_literal_table,0,tmp_ref);
              }
            }
          }
          pool_free(tmp_ref,8);
        }
      }
      iVar2 = g_aux_record_table[_g_current_aux_index].frame_size;
      if ((iVar2 < -0x7f) || (0x80 < iVar2)) {
        if ((iVar2 < 0x8001) && (-0x8000 < iVar2)) {
          found = find_pool_literal(&g_word_literal_table,-iVar2,(label_ref *)0x0);
          if (found == 0) {
            new_lit_bytes = new_lit_bytes + 2;
            add_pool_literal(&g_word_literal_table,-iVar2,(label_ref *)0x0);
          }
        }
        else {
          found = find_pool_literal(&g_long_literal_table,-iVar2,(label_ref *)0x0);
          if (found == 0) {
            new_lit_bytes = new_lit_bytes + 4;
            add_pool_literal(&g_long_literal_table,-iVar2,(label_ref *)0x0);
          }
        }
      }
      break;
    case OP_EXIT:
    case OP_RETURN:
    case OP_JUMP:
    case OP_DUMMY_2D:
      break;
    case OP_CALL:
    case OP_JUMPT:
    case OP_JUMPF:
    case OP_MVA_FC:
      tmp_ref = pool_alloc(8);
      tmp_ref->labno1 = rec->ea1->labels->labno1;
      if (g_request_copy->pic == 0) {
        iVar2 = symbol_address_is_abs16(tmp_ref->labno1);
        if (iVar2 == 0) {
          iVar2 = find_pool_literal(&g_long_literal_table,0,tmp_ref);
          if (iVar2 == 0) {
            new_lit_bytes = 4;
            add_pool_literal(&g_long_literal_table,0,tmp_ref);
          }
        }
        else {
          iVar2 = find_pool_literal(&g_word_literal_table,0,tmp_ref);
          if (iVar2 == 0) {
            new_lit_bytes = 2;
            add_pool_literal(&g_word_literal_table,0,tmp_ref);
          }
        }
      }
      else {
        tmp_ref->labno2 = -g_literal_label_serial;
        g_literal_label_serial = g_literal_label_serial + 1;
        iVar2 = find_pool_literal(&g_long_literal_table,(rec->op == OP_MVA_FC) - 1 & 0xfffffffc,
                                  tmp_ref);
        if (iVar2 == 0) {
          new_lit_bytes = 4;
        }
        else {
          report_message_at_source_line(0,0,0x12f3,(char *)0x0);
        }
      }
      pool_free(tmp_ref,8);
      break;
    case OP_MV_LOC:
      if ((rec->misc & 0x80U) == 0) {
        frame_disp2 = rec->ea1->disp;
      }
      else {
        frame_disp2 = rec->ea2->disp;
      }
      iVar2 = frame_offset_to_sp_displacement(frame_disp2,rec->sptravel);
      if ((0x7f < iVar2) || (iVar2 < -0x80)) {
        if ((rec->misc & 0x80U) == 0) {
          lit_refs2 = rec->ea1->labels;
        }
        else {
          lit_refs2 = rec->ea2->labels;
        }
        if ((rec->misc & 0x80U) == 0) {
          lit_disp2 = rec->ea1->disp;
        }
        else {
          lit_disp2 = rec->ea2->disp;
        }
        found = find_pool_literal(&g_frame_offset_literal_table,lit_disp2,lit_refs2);
        if (found == 0) {
          if ((iVar2 < 0x8000) && (-0x8001 < iVar2)) {
            new_lit_bytes = 2;
          }
          else {
            new_lit_bytes = 4;
          }
          if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
            g_pool_segment_has_word = '\x01';
          }
          if ((rec->misc & 0x80U) == 0) {
            new_lit_ea = rec->ea1;
          }
          else {
            new_lit_ea = rec->ea2;
          }
        }
      }
      break;
    case OP_MVA_LC:
      iVar2 = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
      if (((0x7f < iVar2) || (iVar2 < -0x80)) &&
         (found = find_pool_literal(&g_frame_offset_literal_table,rec->ea1->disp,rec->ea1->labels),
         found == 0)) {
        if ((iVar2 < 0x8000) && (-0x8001 < iVar2)) {
          new_lit_bytes = 2;
        }
        else {
          new_lit_bytes = 4;
        }
        if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
          g_pool_segment_has_word = '\x01';
        }
        new_lit_ea = rec->ea1;
      }
      break;
    case OP_MVA_PC:
    case OP_MOVI:
      if ((rec->op != OP_MOVI) ||
         ((((rec->ea1->labels != (label_ref *)0x0 || (rec->ea1->disp < -0x80)) ||
           (0x7f < rec->ea1->disp)) &&
          (iVar2 = get_marked_symbol_attr_low_bits(rec->ea1->labels), iVar2 != 1)))) {
        if (((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) &&
           ((-0x8001 < rec->ea1->disp && (rec->ea1->disp < 0x8000)))) {
          iVar2 = find_pool_literal(&g_word_literal_table,rec->ea1->disp,rec->ea1->labels);
          if (iVar2 == 0) {
            new_lit_bytes = 2;
            new_lit_ea = rec->ea1;
          }
        }
        else {
          iVar2 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
          if ((iVar2 == 0) &&
             (iVar2 = get_marked_symbol_attr_low_bits(rec->ea1->labels), iVar2 == 0)) {
            iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,rec->ea1->labels);
            if (iVar2 == 0) {
              new_lit_bytes = 4;
              new_lit_ea = rec->ea1;
            }
          }
          else {
            iVar2 = find_pool_literal(&g_word_literal_table,rec->ea1->disp,rec->ea1->labels);
            if (iVar2 == 0) {
              new_lit_bytes = 2;
              new_lit_ea = rec->ea1;
            }
          }
        }
      }
      break;
    case OP_MOVIF:
      iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0);
      if (iVar2 == 0) {
        new_lit_bytes = 4;
        new_lit_ea = rec->ea1;
      }
      break;
    case OP_FPRSET:
      if ((rec->flg & 3) == 3) {
        fpscr_value = 0x80000;
      }
      else {
        fpscr_value = 0xffe7ffff;
      }
      iVar2 = find_pool_literal(&g_long_literal_table,fpscr_value,(label_ref *)0x0);
      if (iVar2 == 0) {
        new_lit_bytes = new_lit_bytes + 4;
        add_pool_literal(&g_long_literal_table,fpscr_value,(label_ref *)0x0);
      }
    }
    if (new_lit_ea != (ea *)0x0) {
      if ((rec->op == OP_MV_LOC) || (rec->op == OP_MVA_LC)) {
        add_pool_literal(&g_frame_offset_literal_table,new_lit_ea->disp,new_lit_ea->labels);
      }
      else if (new_lit_bytes == 2) {
        add_pool_literal(&g_word_literal_table,new_lit_ea->disp,new_lit_ea->labels);
      }
      else {
        add_pool_literal(&g_long_literal_table,new_lit_ea->disp,new_lit_ea->labels);
      }
    }
  }
  g_pool_pending_literal_bytes = g_pool_pending_literal_bytes + new_lit_bytes;
  g_pool_code_bytes = g_pool_code_bytes + code_bytes;
  if (pool_bytes == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = pool_bytes + 2;
  }
  return iVar2;
#undef lit_disp2
#undef lit_refs2
#undef frame_disp2
#undef pool_reach
#undef lit_disp
#undef lit_refs
#undef frame_disp
#undef pool_bytes
#undef code_bytes
#undef fpscr_value
#undef new_lit_ea
#undef flush_flag
#undef stack_imm
#undef new_lit_bytes
#undef tmp_ref
}



