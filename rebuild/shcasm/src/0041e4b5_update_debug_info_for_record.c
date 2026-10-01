#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_expno_register_variables
#define g_expno_register_variables (*(register_variable ** *)(g_sd + 0x13008))
#undef g_expno_use_list
#define g_expno_use_list (*(expno_use * *)(g_sd + 0x10c80))
#undef g_stack_offset_temp
#define g_stack_offset_temp (*(FILE * *)(g_sd + 0xcefc))


// entry: 0041e4b5
// name : update_debug_info_for_record
// size : 1024
// sig  : void __cdecl update_debug_info_for_record(psd *rec)


int __cdecl update_debug_info_for_record(psd *rec)

{
  unsigned char _frec_18[24];
#define use_node (*(expno_use * *)(_frec_18 + 0))
#define cur_location (*(uint *)(_frec_18 + 4))
#define out_loc (*(uint *)(_frec_18 + 8))
#define out_offset (*(uint (*)[2])(_frec_18 + 12))
  short aux_index;
  short saved_count;
  int iVar1;
  symbol *func_sym;
  uint nwritten;
  expno_use *new_use;
  
  if ((((OP_BEND < rec->op) && (rec->op < OP_DUMMY_1C)) || (g_debug_prev_op == 0x90)) ||
     (g_debug_prev_op == 0x91)) {
    if ((rec->op < OP_LABEL) || (OP_FLABEL < rec->op)) {
      if (g_current_request->optimize != 0) {
        iVar1 = update_register_variable_map();
        close_debug_scope_range(1,iVar1);
      }
    }
    else {
      if ((g_current_request->optimize != 0) && (g_debug_function_label != 0)) {
        iVar1 = update_register_variable_map();
        close_debug_scope_range(0,iVar1);
        if (rec->op == OP_FLABEL) {
          flush_register_variable_map();
          free_expno_register_variable_table();
          close_debug_scope_range(0,0);
          close_debug_scope_range(0,0);
        }
      }
      if (rec->op == OP_FLABEL) {
        g_debug_function_label = *(short *)&rec->ea1;
      }
    }
    flush_source_line_ranges(0);
    iVar1 = g_stack_pointer_offset;
    if ((rec->op < OP_LABEL) || (OP_FLABEL < rec->op)) {
      if (g_current_request->optimize != 0) {
        open_debug_scope_range(1);
      }
    }
    else {
      if (rec->op == OP_FLABEL) {
        if (g_current_request->optimize != 0) {
          load_function_register_variable_map();
          open_debug_scope_range(0);
          open_debug_scope_range(0);
        }
        g_stack_pointer_offset = 0;
      }
      else {
        func_sym = find_symbol_by_id(g_debug_function_label);
        aux_index = func_sym->aux_index;
        g_stack_pointer_offset = -g_aux_record_table[aux_index].frame_size - rec->sptravel;
        saved_count = count_saved_registers(aux_index);
        g_stack_pointer_offset = g_stack_pointer_offset + saved_count * -4;
        if (((int)(short)g_aux_record_table[aux_index].flags & 0x8000U) == 0) {
          g_stack_pointer_offset = g_stack_pointer_offset + -4;
        }
        if (g_stack_pointer_offset != iVar1) {
          cur_location = g_location_counter;
          store_u32_big_endian(&cur_location,&out_loc);
          store_u32_big_endian((uint *)&g_stack_pointer_offset,out_offset);
          nwritten = write_file_bytes(g_stack_offset_temp,(char *)&out_loc,8);
          if (nwritten == 0xffffffff) {
            report_message_at_source_line(0,0,0xce7,(char *)0x0);
          }
          g_aux_record_table[aux_index].stack_offset_count =
               g_aux_record_table[aux_index].stack_offset_count + 1;
        }
      }
      if (g_current_request->optimize != 0) {
        open_debug_scope_range(0);
      }
    }
  }
  record_source_line_range(rec);
  track_stack_pointer_offset(rec);
  if (((g_current_request->optimize != 0) &&
      (g_expno_register_variables != (register_variable **)0x0)) && (rec->expno != 0)) {
    if (g_expno_use_list == (expno_use *)0x0) {
      g_expno_use_list = pool_alloc(0xc);
      g_expno_use_list->expno = rec->expno;
      g_expno_use_list->count = g_expno_use_list->count + 1;
    }
    else {
      for (use_node = g_expno_use_list; use_node != (expno_use *)0x0; use_node = use_node->next) {
        if (rec->expno == use_node->expno) {
          use_node->count = use_node->count + 1;
          break;
        }
        if ((use_node->next == (expno_use *)0x0) || ((uint)use_node->next->expno < (uint)rec->expno)
           ) {
          new_use = pool_alloc(0xc);
          new_use->expno = rec->expno;
          new_use->count = new_use->count + 1;
          new_use->next = use_node->next;
          use_node->next = new_use;
          break;
        }
      }
    }
  }
  if ((g_debug_prev_op == 0x98) || (g_debug_prev_op == 0x97)) {
    g_debug_prev_op = 0x91;
  }
  else {
    g_debug_prev_op = rec->op;
  }
  return;
#undef use_node
#undef cur_location
#undef out_loc
#undef out_offset
}
