#include "decls.h"
#include "imports.h"
#include "poolrules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_request
#define g_stage_request (*(request * *)(g_sd + 0x1ee88))


// entry: 0042baa0
// name : decide_literal_pool_placement
// size : 3227
// sig  : uint decide_literal_pool_placement(psd * rec, FILE * lit_out)


uint __cdecl decide_literal_pool_placement(psd *rec,FILE *lit_out)

{
  unsigned char _frec_9[9];
#define lit_flag (*(bool *)(_frec_9 + 0))
#define lit_ref (*(label_ref * *)(_frec_9 + 1))
#define code_bytes (*(uint *)(_frec_9 + 5))
  char word_sym;
  byte use_ea2;
  short sVar1;
  int iVar2;
  undefined3 extraout_var = 0;
  uint uVar3;
  undefined3 extraout_var_00 = 0;
  ea *disp_ea;
  ea *labels_ea;
  int literal_bytes;
  ea *new_literal;
  uint pool_size;
  bool fits;
  label_ref *imm_labels;
  psd_op rec_op;
  
  literal_bytes = 0;
  pool_size = 0;
  new_literal = (ea *)0x0;
  code_bytes = 0;
  rec_op = rec->op;
  if (rec_op == OP_CASEJMP) {
LAB_0042c5d6:
    if (rec_op == OP_NON_10) {
LAB_0042c5de:
      if (g_pool_code_bytes + g_pool_pending_literal_bytes != 0) {
        fits = g_pool_carried_code_bytes + g_pool_carried_literal_bytes + g_pool_code_bytes +
               g_pool_pending_literal_bytes <=
               (int)((-(uint)(g_pool_carried_has_word == '\x01') & 0xfffffe02) + 0x3cc);
        if (fits) {
          pool_size = CONCAT22((short)((uint)g_pool_carried_literal_bytes >> 0x10),
                               (short)g_pool_carried_literal_bytes +
                               (short)g_pool_pending_literal_bytes);
        }
        else {
          pool_size = g_pool_pending_literal_bytes & 0xffff;
        }
        lit_flag = !fits;
        if ((short)pool_size == 0) {
          g_pool_flush_pending = 1;
        }
        else {
          uVar3 = write_file_bytes(lit_out,&lit_flag,1);
          if (uVar3 == 0xffffffff) {
            report_compiler_message(0,0,0xce7,(char *)0x0);
          }
          g_pool_flush_pending = 0;
        }
      }
    }
    if (rec->op == OP_CASEJMP) {
      pool_size = CONCAT22((short)(pool_size >> 0x10),0x400);
    }
    clear_pool_literal_table((literal_table *)&g_word_literal_table);
    clear_pool_literal_table((literal_table *)&g_long_literal_table);
    clear_pool_literal_table((literal_table *)&g_frame_offset_literal_table);
    if (g_pool_carried_literal_bytes + g_pool_pending_literal_bytes == 0) {
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
    g_pool_after_enter = '\0';
    g_pool_after_exit = '\0';
    g_pool_carried_has_word = '\0';
    goto LAB_0042c710;
  }
  if ((((rec_op == OP_CTBL) || (rec_op == OP_PROGRAM)) || (rec_op == OP_CENT)) ||
     ((rec_op == OP_NON_10 && (rec->ea2 == (ea *)0x0)))) {
    if (rec_op == OP_CASEJMP) goto LAB_0042c5d6;
    if (rec_op != OP_NON_10) {
      if (rec_op == OP_PROGRAM) {
        g_pool_carried_code_bytes = 0x400;
      }
      goto LAB_0042c710;
    }
    goto LAB_0042c5de;
  }
  iVar2 = POOL_RECORD_SIZE(rec,compute_record_code_size(rec));
  code_bytes = (uint)(short)iVar2;
  switch(rec->op) {
  case OP_ENTER:
    g_pool_after_enter = '\x01';
    g_pool_after_exit = '\0';
    literal_bytes = 8;
    break;
  case OP_EXIT:
    if (g_pool_after_enter != '\x01') {
      literal_bytes = 4;
    }
    g_pool_after_exit = '\x01';
    g_pool_after_enter = '\0';
    break;
  case OP_RETURN:
    if (g_pool_after_enter != '\x01') {
      literal_bytes = 4;
    }
    iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,rec->ea1->disp,rec->ea1->labels
                             );
    if (iVar2 == 0) {
      literal_bytes = literal_bytes + 4;
    }
    g_pool_after_exit = '\x01';
    break;
  case OP_CALL:
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
  case OP_MOVA_FC:
    lit_ref = alloc_zeroed(8);
    sVar1 = rec->ea1->labels->labno1;
    lit_ref->labno1 = sVar1;
    if (g_stage_request->pic == 0) {
      word_sym = get_symbol_attr_bit5_or_forced(sVar1);
      if (CONCAT31(extraout_var,word_sym) == 0) {
        iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,0,lit_ref);
        if (iVar2 == 0) {
          literal_bytes = 4;
        }
      }
      else {
        iVar2 = find_pool_literal((literal_table *)&g_word_literal_table,0,lit_ref);
        if (iVar2 == 0) {
          g_pool_segment_has_word = '\x01';
          literal_bytes = 2;
        }
      }
    }
    else {
      lit_ref->labno2 = -g_literal_label_serial;
      g_literal_label_serial = g_literal_label_serial + 1;
      iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,
                                (rec->op == OP_MOVA_FC) - 1 & 0xfffffffc,lit_ref);
      if (iVar2 == 0) {
        literal_bytes = 4;
      }
      else {
        report_compiler_message(0,0,0x12f3,(char *)0x0);
      }
    }
    pool_free(lit_ref,8);
    break;
  case OP_MOV_LOC:
    use_ea2 = rec->misc & 0x80;
    if (use_ea2 == 0) {
      labels_ea = rec->ea1;
    }
    else {
      labels_ea = rec->ea2;
    }
    if (use_ea2 == 0) {
      disp_ea = rec->ea1;
    }
    else {
      disp_ea = rec->ea2;
    }
    iVar2 = find_pool_literal((literal_table *)&g_frame_offset_literal_table,disp_ea->disp,
                              labels_ea->labels);
    if (iVar2 != 0) break;
    goto LAB_0042bdfa;
  case OP_MOVA_LC:
    iVar2 = find_pool_literal((literal_table *)&g_frame_offset_literal_table,rec->ea1->disp,
                              rec->ea1->labels);
    goto joined_r0x0042bdf8;
  case OP_MOVA_PC:
  case OP_MOVI:
    if (rec->op == OP_MOVI) {
      imm_labels = rec->ea1->labels;
      if ((((imm_labels == (label_ref *)0x0) && (iVar2 = rec->ea1->disp, -0x81 < iVar2)) &&
          (iVar2 < 0x80)) || (iVar2 = get_marked_symbol_kind(imm_labels), iVar2 == 1)) break;
    }
    if ((((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) &&
        (uVar3 = rec->ea1->disp, -0x8001 < (int)uVar3)) && ((int)uVar3 < 0x8000)) {
      iVar2 = find_pool_literal((literal_table *)&g_word_literal_table,uVar3,(label_ref *)0x0);
      if (iVar2 == 0) {
        g_pool_segment_has_word = '\x01';
        literal_bytes = 2;
      }
    }
    else {
      iVar2 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
      if ((iVar2 == 0) && (iVar2 = get_marked_symbol_kind(rec->ea1->labels), iVar2 == 0)) {
        iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,rec->ea1->disp,
                                  rec->ea1->labels);
        goto joined_r0x0042bdf8;
      }
      iVar2 = find_pool_literal((literal_table *)&g_word_literal_table,rec->ea1->disp,
                                rec->ea1->labels);
      if (iVar2 == 0) {
        g_pool_segment_has_word = '\x01';
        literal_bytes = 2;
      }
    }
    break;
  case OP_NON_2C:
    iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0
                             );
    goto joined_r0x0042bdf8;
  case OP_NON_2E:
    iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,
                              (-(uint)((rec->flg & 3U) == 3) & 0x200001) - 0x180001,(label_ref *)0x0
                             );
joined_r0x0042bdf8:
    if (iVar2 == 0) {
LAB_0042bdfa:
      literal_bytes = 4;
    }
  }
  rec_op = rec->op;
  if (((rec_op == OP_RTS) || (rec_op == OP_RTE)) ||
     (((rec_op == OP_BRA || (((rec_op == OP_JUMP || (rec_op == OP_JMP)) || (rec_op == OP_EXIT)))) ||
      (rec_op == OP_RETURN)))) {
    if ((g_stage_request->flags_13d & 8) == 0) {
      if (g_stage_request->pool_flag_14b != '\0') {
        literal_bytes = literal_bytes + 0xe;
      }
    }
    else {
      literal_bytes = literal_bytes + 0x3c;
    }
    if ((g_pool_carried_has_word == '\x01') || (iVar2 = 0x3fc, g_pool_segment_has_word == '\x01')) {
      iVar2 = 0x1fe;
    }
    if ((iVar2 + -0x30 <
         (int)(g_pool_carried_code_bytes + g_pool_carried_literal_bytes + g_pool_code_bytes +
               code_bytes + g_pool_pending_literal_bytes + literal_bytes)) ||
       (g_pool_flush_pending == 1)) {
      lit_flag = true;
      g_pool_carried_literal_bytes = g_pool_pending_literal_bytes + literal_bytes;
      pool_size = g_pool_carried_literal_bytes & 0xffff;
      g_pool_carried_code_bytes = g_pool_code_bytes + code_bytes;
      if ((g_word_literal_table == 0) &&
         ((((g_frame_offset_literal_table == 0 && (g_pool_segment_has_word != '\x01')) &&
           (g_pool_after_enter != '\x01')) && (g_pool_after_exit != '\x01')))) {
        g_pool_carried_has_word = '\0';
      }
      else {
        g_pool_carried_has_word = '\x01';
      }
      g_pool_flush_pending = 0;
    }
    else {
      lit_flag = false;
      g_pool_carried_literal_bytes =
           g_pool_carried_literal_bytes + g_pool_pending_literal_bytes + literal_bytes;
      pool_size = g_pool_carried_literal_bytes & 0xffff;
      g_pool_carried_code_bytes = g_pool_carried_code_bytes + g_pool_code_bytes + code_bytes;
      if (((g_word_literal_table != 0) || (g_frame_offset_literal_table != 0)) ||
         ((g_pool_segment_has_word == '\x01' ||
          ((g_pool_after_enter == '\x01' || (g_pool_after_exit == '\x01')))))) {
        g_pool_carried_has_word = '\x01';
      }
    }
    uVar3 = write_file_bytes(lit_out,&lit_flag,1);
    if (uVar3 == 0xffffffff) {
      report_compiler_message(0,0,0xce7,(char *)0x0);
    }
    clear_pool_literal_table((literal_table *)&g_word_literal_table);
    literal_bytes = 0;
    clear_pool_literal_table((literal_table *)&g_long_literal_table);
    clear_pool_literal_table((literal_table *)&g_frame_offset_literal_table);
    code_bytes = 0;
    g_pool_code_bytes = 0;
    g_pool_pending_literal_bytes = 0;
    g_pool_segment_has_word = '\0';
    g_pool_after_enter = '\0';
    g_pool_after_exit = '\0';
  }
  else {
    sVar1 = (short)g_pool_pending_literal_bytes;
    if ((((g_word_literal_table == 0) && (g_frame_offset_literal_table == 0)) &&
        (g_pool_segment_has_word != '\x01')) &&
       ((g_pool_after_enter != '\x01' && (g_pool_after_exit != '\x01')))) {
      if (0x3cc < (int)(g_pool_code_bytes + code_bytes + g_pool_pending_literal_bytes +
                       literal_bytes)) {
        pool_size = g_pool_pending_literal_bytes & 0xffff;
        g_pool_carried_literal_bytes = g_pool_pending_literal_bytes;
        if (((g_stage_request->flags_13d & 8) == 0) || (sVar1 == 0)) {
          if ((g_stage_request->pool_flag_14b != '\0') && (sVar1 != 0)) {
            pool_size = (uint)(ushort)(sVar1 + 0xe);
          }
        }
        else {
          pool_size = (uint)(ushort)(sVar1 + 0x3c);
        }
        lit_flag = true;
        g_pool_carried_has_word = '\0';
        g_pool_carried_code_bytes = g_pool_code_bytes + 4;
        if ((short)pool_size == 0) {
          g_pool_flush_pending = 1;
        }
        else {
          uVar3 = write_file_bytes(lit_out,&lit_flag,1);
          if (uVar3 == 0xffffffff) {
            report_compiler_message(0,0,0xce7,(char *)0x0);
          }
          g_pool_flush_pending = 0;
        }
        clear_pool_literal_table((literal_table *)&g_word_literal_table);
        clear_pool_literal_table((literal_table *)&g_long_literal_table);
        clear_pool_literal_table((literal_table *)&g_frame_offset_literal_table);
        g_pool_code_bytes = 0;
        g_pool_pending_literal_bytes = 0;
        g_pool_after_enter = '\0';
        g_pool_after_exit = '\0';
        if (rec->op == OP_NON_10) {
          g_pool_carried_code_bytes = 0x400;
          code_bytes = 0;
        }
      }
    }
    else if (0x1ce < (int)(g_pool_code_bytes + code_bytes + g_pool_pending_literal_bytes +
                          literal_bytes)) {
      pool_size = g_pool_pending_literal_bytes & 0xffff;
      g_pool_carried_literal_bytes = g_pool_pending_literal_bytes;
      if (((g_stage_request->flags_13d & 8) == 0) || (sVar1 == 0)) {
        if ((g_stage_request->pool_flag_14b != '\0') && (sVar1 != 0)) {
          pool_size = (uint)(ushort)(sVar1 + 0xe);
        }
      }
      else {
        pool_size = (uint)(ushort)(sVar1 + 0x3c);
      }
      g_pool_carried_code_bytes = g_pool_code_bytes + 4;
      lit_flag = true;
      g_pool_carried_has_word = '\x01';
      if ((short)pool_size == 0) {
        g_pool_flush_pending = 1;
      }
      else {
        uVar3 = write_file_bytes(lit_out,&lit_flag,1);
        if (uVar3 == 0xffffffff) {
          report_compiler_message(0,0,0xce7,(char *)0x0);
        }
        g_pool_flush_pending = 0;
      }
      clear_pool_literal_table((literal_table *)&g_word_literal_table);
      clear_pool_literal_table((literal_table *)&g_long_literal_table);
      clear_pool_literal_table((literal_table *)&g_frame_offset_literal_table);
      g_pool_code_bytes = 0;
      g_pool_pending_literal_bytes = 0;
      g_pool_segment_has_word = '\0';
      g_pool_after_enter = '\0';
      g_pool_after_exit = '\0';
      if (rec->op == OP_NON_10) {
        g_pool_carried_code_bytes = 0x400;
        code_bytes = 0;
      }
    }
  }
  switch(rec->op) {
  case OP_CALL:
  case OP_JUMPT:
  case OP_JUMPF:
  case OP_MOVA_FC:
    lit_ref = alloc_zeroed(8);
    sVar1 = rec->ea1->labels->labno1;
    lit_ref->labno1 = sVar1;
    if (g_stage_request->pic == 0) {
      word_sym = get_symbol_attr_bit5_or_forced(sVar1);
      if (CONCAT31(extraout_var_00,word_sym) == 0) {
        iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,0,lit_ref);
        if (iVar2 == 0) {
          literal_bytes = 4;
          add_pool_literal((literal_table *)&g_long_literal_table,0,lit_ref);
        }
      }
      else {
        iVar2 = find_pool_literal((literal_table *)&g_word_literal_table,0,lit_ref);
        if (iVar2 == 0) {
          literal_bytes = 2;
          add_pool_literal((literal_table *)&g_word_literal_table,0,lit_ref);
        }
      }
    }
    else {
      lit_ref->labno2 = -g_literal_label_serial;
      g_literal_label_serial = g_literal_label_serial + 1;
      iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,
                                (rec->op == OP_MOVA_FC) - 1 & 0xfffffffc,lit_ref);
      if (iVar2 == 0) {
        literal_bytes = 4;
      }
      else {
        report_compiler_message(0,0,0x12f3,(char *)0x0);
      }
    }
    pool_free(lit_ref,8);
    break;
  case OP_MOV_LOC:
    use_ea2 = rec->misc & 0x80;
    if (use_ea2 == 0) {
      labels_ea = rec->ea1;
    }
    else {
      labels_ea = rec->ea2;
    }
    if (use_ea2 == 0) {
      disp_ea = rec->ea1;
    }
    else {
      disp_ea = rec->ea2;
    }
    iVar2 = find_pool_literal((literal_table *)&g_frame_offset_literal_table,disp_ea->disp,
                              labels_ea->labels);
    if (iVar2 == 0) {
      literal_bytes = 4;
      if ((rec->misc & 0x80U) == 0) {
        new_literal = rec->ea1;
      }
      else {
        new_literal = rec->ea2;
      }
    }
    break;
  case OP_MOVA_LC:
    iVar2 = find_pool_literal((literal_table *)&g_frame_offset_literal_table,rec->ea1->disp,
                              rec->ea1->labels);
    if (iVar2 == 0) {
      literal_bytes = 4;
      new_literal = rec->ea1;
    }
    break;
  case OP_MOVA_PC:
  case OP_MOVI:
    if (rec->op == OP_MOVI) {
      imm_labels = rec->ea1->labels;
      if ((((imm_labels == (label_ref *)0x0) && (iVar2 = rec->ea1->disp, -0x81 < iVar2)) &&
          (iVar2 < 0x80)) || (iVar2 = get_marked_symbol_kind(imm_labels), iVar2 == 1)) break;
    }
    if (((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) &&
       ((uVar3 = rec->ea1->disp, -0x8001 < (int)uVar3 && ((int)uVar3 < 0x8000)))) {
      iVar2 = find_pool_literal((literal_table *)&g_word_literal_table,uVar3,(label_ref *)0x0);
      if (iVar2 == 0) {
        literal_bytes = 2;
        new_literal = rec->ea1;
      }
    }
    else {
      iVar2 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
      if ((iVar2 == 0) && (iVar2 = get_marked_symbol_kind(rec->ea1->labels), iVar2 == 0)) {
        iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,rec->ea1->disp,
                                  rec->ea1->labels);
        if (iVar2 == 0) {
          literal_bytes = 4;
          new_literal = rec->ea1;
        }
      }
      else {
        iVar2 = find_pool_literal((literal_table *)&g_word_literal_table,rec->ea1->disp,
                                  rec->ea1->labels);
        if (iVar2 == 0) {
          literal_bytes = 2;
          new_literal = rec->ea1;
        }
      }
    }
    break;
  case OP_NON_2C:
    iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0
                             );
    if (iVar2 == 0) {
      literal_bytes = 4;
      new_literal = rec->ea1;
    }
    break;
  case OP_NON_2E:
    lit_ref = (label_ref *)((-(uint)((rec->flg & 3U) == 3) & 0x200001) - 0x180001);
    iVar2 = find_pool_literal((literal_table *)&g_long_literal_table,(uint)lit_ref,(label_ref *)0x0)
    ;
    if (iVar2 == 0) {
      literal_bytes = literal_bytes + 4;
      add_pool_literal((literal_table *)&g_long_literal_table,(uint)lit_ref,(label_ref *)0x0);
    }
  }
  if (new_literal != (ea *)0x0) {
    if ((rec->op == OP_MOV_LOC) || (rec->op == OP_MOVA_LC)) {
      add_pool_literal((literal_table *)&g_frame_offset_literal_table,new_literal->disp,
                       new_literal->labels);
    }
    else if (literal_bytes == 2) {
      add_pool_literal((literal_table *)&g_word_literal_table,new_literal->disp,new_literal->labels)
      ;
    }
    else {
      add_pool_literal((literal_table *)&g_long_literal_table,new_literal->disp,new_literal->labels)
      ;
    }
  }
LAB_0042c710:
  g_pool_pending_literal_bytes = g_pool_pending_literal_bytes + literal_bytes;
  g_pool_code_bytes = g_pool_code_bytes + code_bytes;
  if ((short)pool_size != 0) {
    return pool_size + 2;
  }
  return code_bytes & 0xffff0000;
#undef lit_flag
#undef lit_ref
#undef code_bytes
}



