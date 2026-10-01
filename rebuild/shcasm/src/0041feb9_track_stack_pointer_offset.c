#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_stack_adjust_list
#define g_stack_adjust_list (*(stack_adjust_node * *)(g_sd + 0xcf28))
#undef g_stack_offset_temp
#define g_stack_offset_temp (*(FILE * *)(g_sd + 0xcefc))


// entry: 0041feb9
// name : track_stack_pointer_offset
// size : 1016
// sig  : void __cdecl track_stack_pointer_offset(psd *rec)


int __cdecl track_stack_pointer_offset(psd *rec)

{
  unsigned char _frec_14[20];
#define sp_delta (*(int *)(_frec_14 + 0))
#define cur_location (*(uint *)(_frec_14 + 4))
#define out_loc (*(uint *)(_frec_14 + 8))
#define out_offset (*(uint *)(_frec_14 + 12))
  stack_adjust_node *ptr;
  symbol *func_sym;
  uint nwritten;
  short aux_ix;
  
  if (OP_DUMMY_3F < rec->op) {
    func_sym = find_symbol_by_id(g_debug_function_label);
    ptr = g_stack_adjust_list;
    aux_ix = func_sym->aux_index;
    sp_delta = 0;
    if ((((g_aux_record_table[aux_ix].flags & 0x4000) == 0) ||
        ((g_aux_record_table[aux_ix].flags & 0x1800) == 0)) ||
       (g_aux_record_table[aux_ix].stack_offset_count != 0)) {
      if (rec->op == OP_ADD) {
        if (((rec->ea2->type & 0x1f) == 1) && (rec->ea2->base == REG_R15)) {
          if ((rec->ea1->type & 0x1f) == 7) {
            sp_delta = rec->ea1->disp;
          }
          else if ((rec->ea1->type & 0x1f) == 1) {
            sp_delta = g_stack_adjust_list->amount;
            g_stack_adjust_list = g_stack_adjust_list->next;
            pool_free(ptr,8);
          }
        }
      }
      else if (rec->op == OP_SUB) {
        if (((rec->ea2->type & 0x1f) == 1) && (rec->ea2->base == REG_R15)) {
          if ((rec->ea1->type & 0x1f) == 7) {
            sp_delta = -rec->ea1->disp;
          }
          else if ((rec->ea1->type & 0x1f) == 1) {
            sp_delta = -g_stack_adjust_list->amount;
            g_stack_adjust_list = g_stack_adjust_list->next;
            pool_free(ptr,8);
          }
        }
      }
      else if (((rec->op == OP_JSR) || (rec->op == OP_BSRF)) && ((rec->flg & 4) != 0)) {
        sp_delta = -g_stack_adjust_list->amount;
        g_stack_adjust_list = g_stack_adjust_list->next;
        pool_free(ptr,8);
      }
    }
    else {
      if (rec->op != OP_MOV) {
        return;
      }
      if ((rec->ea1->type & 0x1f) != 1) {
        return;
      }
      if (rec->ea1->base != REG_R0) {
        return;
      }
      if ((rec->ea2->type & 0x1f) != 1) {
        return;
      }
      if (rec->ea2->base != REG_R15) {
        return;
      }
      cur_location = g_location_counter;
      store_u32_big_endian(&cur_location,&out_loc);
      nwritten = write_file_bytes(g_stack_offset_temp,(char *)&out_loc,4);
      if (nwritten == 0xffffffff) {
        report_message_at_source_line(0,0,0xce7,(char *)0x0);
      }
      g_aux_record_table[aux_ix].stack_offset_count =
           g_aux_record_table[aux_ix].stack_offset_count + 1;
    }
    if (((rec->ea1 == (ea *)0x0) || ((rec->ea1->type & 0x1f) != 4)) || (rec->ea1->base != REG_R15))
    {
      if (((rec->ea2 != (ea *)0x0) && ((rec->ea2->type & 0x1f) == 3)) && (rec->ea2->base == REG_R15)
         ) {
        sp_delta = sp_delta + -4;
      }
    }
    else {
      sp_delta = sp_delta + 4;
    }
    if (sp_delta != 0) {
      cur_location = g_location_counter;
      store_u32_big_endian(&cur_location,&out_loc);
      g_stack_pointer_offset = g_stack_pointer_offset + sp_delta;
      if (g_stack_pointer_offset < 1) {
        store_u32_big_endian((uint *)&g_stack_pointer_offset,&out_offset);
        nwritten = write_file_bytes(g_stack_offset_temp,(char *)&out_loc,8);
        if (nwritten == 0xffffffff) {
          report_message_at_source_line(0,0,0xce7,(char *)0x0);
        }
        g_aux_record_table[aux_ix].stack_offset_count =
             g_aux_record_table[aux_ix].stack_offset_count + 1;
      }
    }
  }
  return;
#undef sp_delta
#undef cur_location
#undef out_loc
#undef out_offset
}
