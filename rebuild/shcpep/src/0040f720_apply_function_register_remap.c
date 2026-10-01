#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 0040f720
// name : apply_function_register_remap
// size : 227
// sig  : void __cdecl apply_function_register_remap(psd *rec)


int __cdecl apply_function_register_remap(psd *rec)

{
  int reg;
  uint is_volatile;
  aux_record *aux;
  ea *dst_ea;
  psd_op op;
  aux_reg_range *range;
  ea *src_ea;
  
  aux = g_aux_record_table + g_stream_func_aux_index;
  if (aux->ranges != (aux_reg_range *)0x0) {
    if ((g_reg_remap_expno != rec->expno) || (rec->op == OP_FLABEL)) {
      reg = 0;
      g_reg_remap_expno = rec->expno;
      do {
        (&g_reg_remap_table)[reg] = (char)reg;
        reg = reg + 1;
      } while (reg < 0x6d);
      for (range = aux->ranges; range != (aux_reg_range *)0x0; range = range->next) {
        if (((uint)range->start_expno <= (uint)rec->expno) &&
           ((uint)rec->expno <= (uint)range->end_expno)) {
          (&g_reg_remap_table)[range->before_reg] = range->after_reg;
        }
      }
    }
    op = rec->op;
    if (((((((op != OP_CASEJMP) && (op != OP_LINE)) && (op != OP_CTBL)) &&
          (((op != OP_CENT && (op != OP_BBGN)) && ((op != OP_BEND && (op != OP_NON_10)))))) &&
         ((op < OP_LABEL || (OP_FLABEL < op)))) &&
        ((shift_record_registers(rec), rec->op == OP_MOV &&
         ((((src_ea = rec->ea1, src_ea != (ea *)0x0 && (dst_ea = rec->ea2, dst_ea != (ea *)0x0)) &&
           ((src_ea->type & 0x1f) == 1)) &&
          (((dst_ea->type & 0x1f) == 1 && (dst_ea->base == src_ea->base)))))))) &&
       (is_volatile = is_record_volatile(rec), is_volatile == 0)) {
      delete_psd_record(rec);
    }
  }
  return;
}
