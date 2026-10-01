#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_block
#define g_current_block (*(code_node * *)(g_sd + 0x5c38))
#undef g_current_input_record
#define g_current_input_record (*(psd * *)(g_sd + 0x5bbc))
#undef g_pushed_back_record
#define g_pushed_back_record (*(psd * *)(g_sd + 0x5bc0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 0040d040
// name : advance_sua_record_stream
// size : 1071
// sig  : void advance_sua_record_stream(void)


int __cdecl advance_sua_record_stream(void)

{
  char status;
  ea *new_ea;
  psd_op op;
  aux_reg_range *range;
  symbol *sym;
  short sym_number;
  
  if (g_input_finished != 1) {
    if (g_reuse_input_record == 1) {
      g_reuse_input_record = 0;
      return;
    }
    if ((g_pushed_back_record == (psd *)0x0) || (g_pushed_back_record->op == OP_DUMMY)) {
      status = read_sua_record(g_current_input_record);
      if (status == -1) {
        g_input_finished = 1;
        g_block_complete = 1;
        g_section_end = 1;
        return;
      }
    }
    else {
      copy_psd_record(g_pushed_back_record,g_current_input_record);
      clear_psd_record(g_pushed_back_record);
      pool_free(g_pushed_back_record,0x18);
      g_pushed_back_record = (psd *)0x0;
    }
    op = g_current_input_record->op;
    if (op == OP_DUMMY) {
      g_in_program_section = 0;
      g_input_finished = 1;
      g_section_end = 1;
      g_block_complete = 1;
      g_reuse_input_record = 0;
      g_block_code_count = 0;
      return;
    }
    if ((OP_DSTR < op) && (op < OP_NON_10)) {
      g_section_end = 1;
      g_block_complete = 1;
      if (g_current_input_record->op == OP_PROGRAM) {
        g_reuse_input_record = 0;
        g_in_program_section = 1;
      }
      else {
        g_in_program_section = 0;
        g_input_finished = 1;
      }
    }
    op = g_current_input_record->op;
    if ((((OP_DSTR < op) && (op < OP_NON_10)) || (op == OP_LABEL)) ||
       (((op == OP_FLABEL || (op == OP_CLABEL)) || (op == OP_DLABEL)))) {
      g_reuse_input_record = 1;
      g_block_complete = 1;
      if (g_current_block != (code_node *)0x0) {
        g_current_block->flags = g_current_block->flags | 2;
      }
      if (g_current_input_record->op == OP_FLABEL) {
        g_section_end = 1;
        g_block_code_count = 0;
        sym = g_symbol_hash[*(short *)&g_current_input_record->ea1 % 0x3fd];
        sym_number = sym->number;
        while (sym_number != *(short *)&g_current_input_record->ea1) {
          sym = sym->hash_next;
          sym_number = sym->number;
        }
        g_stream_func_aux_index = (int)sym->aux_index;
        count_record_label_references(g_current_input_record);
        if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 1) != 0) {
          _printf(s_____function_name_____s_____00426794,sym->name);
          for (range = g_aux_record_table[g_stream_func_aux_index].ranges;
              range != (aux_reg_range *)0x0; range = range->next) {
            _printf(s_____start_expno_____00426780);
            _printf(s_str_00426770,range->start_expno);
            _printf(s_____end_expno_____0042675c);
            _printf(s_str_00426750,range->end_expno);
            _printf(s_____before_reg_____0042673c);
            _printf(s_str_00426770,(int)range->before_reg);
            _printf(s_____after_reg_____00426728);
            _printf(s_str_00426750,(int)range->after_reg);
          }
        }
      }
    }
    op = g_current_input_record->op;
    if ((((OP_CALL < op) && (op < OP_MOV_LOC)) || ((op == OP_EXIT || (op == OP_RETURN)))) ||
       ((((((OP_SETT < op && (op < OP_BSR)) || (op == OP_JMP)) || ((OP_JSR < op && (op < OP_BSRF))))
         || (op == OP_BRAF)) || ((op == OP_RTE || (op == OP_NON_10)))))) {
      g_block_complete = 1;
    }
    if (*(short *)(&g_op_is_code_record + (uint)g_current_input_record->op * 2) == 1) {
      g_block_code_count = g_block_code_count + 1;
      if ((((g_current_input_record->op < OP_PROGRAM) || (OP_BSS < g_current_input_record->op)) &&
          (apply_function_register_remap(g_current_input_record), g_entry_arg_move_pending == 1)) &&
         ((('\x03' < g_aux_record_table[g_stream_func_aux_index].reg28 &&
           (g_aux_record_table[g_stream_func_aux_index].reg28 < '\b')) &&
          (g_current_input_record->expno != 0)))) {
        if (g_current_input_record->op != OP_DUMMY) {
          g_pushed_back_record = (psd *)alloc_zeroed_flushing_blocks(0x18);
          copy_psd_record(g_current_input_record,g_pushed_back_record);
        }
        clear_psd_record(g_current_input_record);
        g_current_input_record->op = OP_MOV;
        g_current_input_record->flg = '\x02';
        g_current_input_record->tmp = -1;
        new_ea = (ea *)alloc_zeroed_flushing_blocks(0xc);
        g_current_input_record->ea1 = new_ea;
        g_current_input_record->ea1->type = '\x01';
        g_current_input_record->ea1->base = g_aux_record_table[g_stream_func_aux_index].reg28;
        new_ea = (ea *)alloc_zeroed_flushing_blocks(0xc);
        g_current_input_record->ea2 = new_ea;
        g_current_input_record->ea2->type = '\x01';
        g_current_input_record->ea2->base = '\0';
        g_entry_arg_move_pending = 0;
      }
      if (0xef < g_block_code_count) {
        g_block_complete = 1;
        g_reuse_input_record = 1;
        if (g_current_block != (code_node *)0x0) {
          g_current_block->flags = g_current_block->flags | 2;
        }
      }
    }
  }
  return;
}



