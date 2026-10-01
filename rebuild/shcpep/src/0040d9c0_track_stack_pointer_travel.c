#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 0040d9c0
// name : track_stack_pointer_travel
// size : 460
// sig  : void track_stack_pointer_travel(code_node * node, psd * rec)


int __cdecl track_stack_pointer_travel(code_node *node,psd *rec)

{
  uchar changed;
  int delta;
  psd *prev_rec;
  aux_record *aux;
  short labno;
  ea *opnd;
  
  switch(rec->op) {
  case OP_PROGRAM:
  case OP_NON_10:
  case OP_CASEJMP:
  case OP_CTBL:
  case OP_CENT:
  case OP_LINE:
    goto switchD_0040d9da_caseD_c;
  default:
    opnd = rec->ea1;
    if (((opnd != (ea *)0x0) && ((opnd->type & 0x1f) == 4)) && (opnd->base == '\x0f')) {
      delta = psd_operand_size_bytes(rec);
      g_cur_sptravel = g_cur_sptravel - delta;
    }
    opnd = rec->ea2;
    if (opnd != (ea *)0x0) {
      if (((opnd->type & 0x1f) == 3) && (opnd->base == '\x0f')) {
        delta = psd_operand_size_bytes(rec);
        g_cur_sptravel = g_cur_sptravel + delta;
      }
      if (((rec->ea2->type & 0x1f) == 4) && (rec->ea2->base == '\x0f')) {
        delta = psd_operand_size_bytes(rec);
        g_cur_sptravel = g_cur_sptravel - delta;
      }
    }
    break;
  case OP_LABEL:
  case OP_CLABEL:
  case OP_DLABEL:
  case OP_FLABEL:
    g_cur_sptravel = rec->sptravel;
    break;
  case OP_CALL:
    labno = rec->ea1->labels->labno1;
    if (labno < 0xb7) {
      delta = *(int *)(&g_runtime_call_sptravel + labno * 4);
LAB_0040db20:
      g_cur_sptravel = g_cur_sptravel + delta;
    }
    break;
  case OP_MOV_LOC:
  case OP_MOVA_LC:
    rec->sptravel = g_cur_sptravel;
    break;
  case OP_ADD:
  case OP_SUB:
    if (((rec->ea2->type & 0x1f) == 1) && (rec->ea2->base == '\x0f')) {
      if ((rec->ea1->type & 0x1f) == 7) {
        g_cur_sptravel = g_cur_sptravel - rec->ea1->disp;
      }
      else {
        prev_rec = find_previous_psd_record(node,rec);
        if ((((prev_rec != (psd *)0x0) && (prev_rec->op == OP_MOVI)) &&
            (changed = record_changes_register(prev_rec,rec->ea1->base), changed == '\x01')) &&
           ((prev_rec->ea1->type & 0x1f) == 7)) {
          if (rec->op == OP_ADD) {
            g_cur_sptravel = g_cur_sptravel - prev_rec->ea1->disp;
          }
          if (rec->op == OP_SUB) {
            delta = prev_rec->ea1->disp;
            goto LAB_0040db20;
          }
        }
      }
    }
  }
  if (0x7fffffff - g_aux_record_table[g_current_aux_index].frame_size < g_cur_sptravel) {
    report_compiler_message(rec->filno,(uint)rec->linno,0xc84,(char *)0x0);
  }
  aux = g_aux_record_table + g_current_aux_index;
  delta = aux->frame_size + g_cur_sptravel;
  if (aux->max_stack < delta) {
    aux->max_stack = delta;
  }
switchD_0040d9da_caseD_c:
  return;
}



