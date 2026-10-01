#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))
#undef g_stack_adjust_list
#define g_stack_adjust_list (*(stack_adjust_node * *)(g_sd + 0xcf28))


// entry: 00423f9e
// name : read_next_backend_record
// size : 2442
// sig  : int read_next_backend_record(psd * rec, int mode)


/* WARNING: Variable defined which should be unmapped: rec */

int __cdecl read_next_backend_record(psd *rec,int mode)

{
  unsigned char _frec_18[24];
#define bytes_read (*(uint *)(_frec_18 + 0))
#define op_byte (*(psd_op (*)[4])(_frec_18 + 4))
#define tail_node (*(stack_adjust_node * *)(_frec_18 + 8))
#define new_node (*(stack_adjust_node * *)(_frec_18 + 12))
#define pool_flag (*(char (*)[4])(_frec_18 + 16))
  psd *sched_rec;
  int close_status;
  uint flag_bytes_read;
  stack_adjust_node *adjust_list;
  
  if ((((mode == 0) && (g_current_request->optimize != 0)) && (g_current_section_kind == 0)) &&
     (((g_current_request->flags_13c & 1) == 0 && (g_current_request->cpu != 4)))) {
    if (g_pipeline_active == 0) {
      g_pipeline_active = 1;
      pipeline();
    }
    do {
      if (g_pipeline_end_of_stream != 0) {
        g_pipeline_active = 0;
        if (g_held_section_record.op != OP_DUMMY_00) {
          stock_memcpy(rec,&g_held_section_record,0x18);
          stock_memcpy(&g_held_section_record,&g_zero_psd,0x18);
          return (int)rec;
        }
        g_pipeline_active = 0;
        return 0;
      }
      sched_rec = read_next_scheduled_pipeline_record(rec);
    } while (sched_rec == (psd *)0x0);
    return (int)rec;
  }
  if ((((mode == 0) && ((g_current_request->optimize != 0 && (g_current_section_kind == 0)))) &&
      ((g_current_request->flags_13c & 1) == 0)) && (g_current_request->cpu == 4)) {
    g_pipeline_active = 1;
    g_pipeline_end_of_stream = 0;
    g_scope_stack[0x46] = (debug_scope *)0x0;
    if (g_superscalar_draining == 1) {
      sched_rec = drain_next_superscalar_scheduled_record(rec);
      return (int)sched_rec;
    }
    if (g_superscalar_stream_ended == 0) {
      sched_rec = read_next_superscalar_scheduled_record(rec);
      if (sched_rec != (psd *)0x0) {
        return (int)rec;
      }
    }
    else {
      g_superscalar_stream_ended = 0;
    }
    g_pipeline_active = 0;
    if (g_held_section_record.op != OP_DUMMY_00) {
      stock_memcpy(rec,&g_held_section_record,0x18);
      stock_memcpy(&g_held_section_record,&g_zero_psd,0x18);
      return (int)rec;
    }
    g_pipeline_active = 0;
    return 0;
  }
LAB_004241b8:
  if (g_expanded_record_count <= g_expanded_record_read_index) {
    g_expanded_record_read_index = 0;
    g_expanded_record_count = 0;
    bytes_read = read_file_bytes(g_backend_record_input,(char *)op_byte,1);
    if ((bytes_read == 0) && (g_backend_continuation_opened == 0)) {
      close_status = _fclose(g_backend_record_input);
      if (close_status == -1) {
        report_message_at_source_line(0,0,0xce5,(char *)0x0);
      }
      g_backend_record_input = stock_fopen(g_current_request->sud_path,&s_rb_00441e68);
      if (g_backend_record_input == (FILE *)0x0) {
        report_message_at_source_line(0,0,0xce4,(char *)0x0);
      }
      g_backend_continuation_opened = 1;
      bytes_read = read_file_bytes(g_backend_record_input,(char *)op_byte,1);
    }
    if (bytes_read == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    else if (bytes_read == 0) {
      return 0;
    }
    rec->op = op_byte[0];
    if ((((rec->op == OP_PRGRAM) || (rec->op == OP_CONST)) || (rec->op == OP_DATA)) ||
       (((rec->op == OP_BSS || (rec->op == OP_B_ASM)) || (OP_B_ASM < rec->op)))) {
      read_backend_record_payload(g_backend_record_input,rec,rec->op);
    }
    adjust_list = g_stack_adjust_list;
    switch(rec->op) {
    case OP_ENTER:
      goto switchD_00424679_caseD_20;
    case OP_EXIT:
      expand_exit_epilogue(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_RETURN:
      expand_return(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_CALL:
      expand_call(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_JUMP:
      expand_jump(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_JUMPT:
    case OP_JUMPF:
      expand_conditional_jump(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_MV_LOC:
      expand_move_local(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_MVA_LC:
      expand_mva_lc_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_MVA_PC:
      expand_mva_pc_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_MOVI:
      if ((g_current_request->debug != 0) && ((rec->ea2->type & 0x1f) == 1)) {
        g_last_movi_immediate = rec->ea1->disp;
      }
      expand_movi_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_MVA_FC:
      expand_mva_fc_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_MOVIF:
      expand_movif_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_FPRSET:
      expand_fprset_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_EXTLD:
      expand_extld_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_EXTST:
      expand_extst_record(rec);
      adjust_list = g_stack_adjust_list;
      break;
    case OP_MOV:
      if (((((g_current_request->flags_13d & 4) != 0) && ((rec->flg & 0x40) == 0)) &&
          ((rec->ea1->type & 0x1f) == 1)) &&
         (((rec->ea2->type & 0x1f) == 1 && (rec->ea2->base == REG_R0)))) {
        expand_mov_to_r0_with_nop(rec);
        adjust_list = g_stack_adjust_list;
      }
      break;
    case OP_ADD:
    case OP_SUB:
      if (((g_current_request->debug != 0) && ((rec->ea1->type & 0x1f) == 1)) &&
         (((rec->ea2->type & 0x1f) == 1 && (rec->ea2->base == REG_R15)))) {
        new_node = pool_alloc(8);
        new_node->amount = g_last_movi_immediate;
        adjust_list = new_node;
        if (g_stack_adjust_list != (stack_adjust_node *)0x0) {
          for (tail_node = g_stack_adjust_list; tail_node->next != (stack_adjust_node *)0x0;
              tail_node = tail_node->next) {
          }
          tail_node->next = new_node;
          adjust_list = g_stack_adjust_list;
        }
      }
      break;
    case OP_RTE:
    case OP_BRA:
    case OP_JMP:
    case OP_RTS:
      flag_bytes_read = read_file_bytes(g_lit_input,pool_flag,1);
      if (flag_bytes_read == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      adjust_list = g_stack_adjust_list;
      if (pool_flag[0] == '\x01') {
        rec->flg = rec->flg | 0x10;
        adjust_list = g_stack_adjust_list;
      }
    }
    goto switchD_00424679_caseD_2d;
  }
  stock_memcpy(rec,g_expanded_records + g_expanded_record_read_index,0x18);
  stock_memcpy(g_expanded_records + g_expanded_record_read_index,&g_zero_psd,0x18);
  g_expanded_record_read_index = g_expanded_record_read_index + 1;
  goto LAB_004248c3;
switchD_00424679_caseD_20:
  expand_enter_prologue(rec);
  adjust_list = g_stack_adjust_list;
  if (g_expanded_record_count != 0) {
switchD_00424679_caseD_2d:
    g_stack_adjust_list = adjust_list;
    if (rec->op == OP_LINE) {
      g_line_filno = rec->filno;
      g_line_linno = rec->linno;
    }
    if ((g_current_request->optimize == 0) ||
       ((((rec->op != OP_LINE && (rec->op != OP_BBGN)) && (rec->op != OP_BEND)) &&
        ((rec->op != OP_SWBGN && (rec->op != OP_SWEND)))))) {
      if (((g_current_request->optimize != 0) && (g_pipeline_active == 1)) &&
         (((((rec->op == OP_CONST || (rec->op == OP_DATA)) || (rec->op == OP_BSS)) ||
           (rec->op == OP_PRGRAM)) && (g_held_section_record.op == OP_DUMMY_00)))) {
        stock_memcpy(&g_held_section_record,rec,0x18);
        return 0;
      }
      if (rec->op == OP_FLABEL) {
        rec->filno = g_line_filno;
        rec->linno = g_line_linno;
        g_function_label = *(short *)&rec->ea1;
      }
      if (g_expanded_record_count != 0) {
        stock_memcpy(rec,g_expanded_records + g_expanded_record_read_index,0x18);
        stock_memcpy(g_expanded_records + g_expanded_record_read_index,&g_zero_psd,0x18);
        g_expanded_record_read_index = g_expanded_record_read_index + 1;
      }
LAB_004248c3:
      if ((rec->flg & 0x40) == 0) {
        if ((((((rec->op == OP_RTE) || (rec->op == OP_BRA)) || (rec->op == OP_BT_S)) ||
             ((rec->op == OP_BF_S || (rec->op == OP_BSRF)))) ||
            (((rec->op == OP_BRAF || ((rec->op == OP_BSR || (rec->op == OP_JMP)))) ||
             (rec->op == OP_JSR)))) || (rec->op == OP_RTS)) {
          if (g_delay_slot_record.op == OP_DUMMY_00) {
            g_delay_slot_record.op = OP_NOP;
          }
          if ((((g_next_delay_slot_record.op == OP_DUMMY_00) && (g_last_was_delayed_branch == 1)) &&
              ((g_current_request->flags_13c & 1) == 0)) && (g_current_request->cpu != 4)) {
            g_next_delay_slot_record.op = OP_NOP;
          }
          g_last_was_delayed_branch = 1;
        }
        else {
          g_last_was_delayed_branch = 0;
        }
        return (int)rec;
      }
      if (g_delay_slot_record.op == OP_DUMMY_00) {
        stock_memcpy(&g_delay_slot_record,rec,0x18);
      }
      else {
        stock_memcpy(&g_next_delay_slot_record,rec,0x18);
      }
      stock_memcpy(rec,&g_zero_psd,0x18);
    }
  }
  goto LAB_004241b8;
#undef bytes_read
#undef op_byte
#undef tail_node
#undef new_node
#undef pool_flag
}



