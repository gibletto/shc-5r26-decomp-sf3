#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00411ed0
// name : merge_repeated_and_or_immediates
// size : 509
// sig  : void merge_repeated_and_or_immediates(code_node * node)


int __cdecl merge_repeated_and_or_immediates(code_node *node)

{
  char cVar1;
  uint use_lo;
  psd *rec;
  uint merged_imm;
  psd *andor_rec;
  uint def_hi;
  uint def_lo;
  psd_op op;
  uint use_hi;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    _printf(s_imandor_start__nodeptr___08lx_00426900,node);
    dump_node_list_debug(node);
  }
  andor_rec = node->psd;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_imandor_start__cp___08lx_004268e4,andor_rec);
  }
  do {
    if (andor_rec == (psd *)0x0) {
      if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
        dump_node_list_debug(g_current_node_list);
        _printf(s_imandor_end__004268d4);
      }
      return;
    }
    if ((((andor_rec->op == OP_AND) || (andor_rec->op == OP_OR)) &&
        ((andor_rec->ea1->type & 0x1f) == 7)) &&
       (use_lo = is_record_volatile(andor_rec), use_lo == 0)) {
      compute_record_register_masks(andor_rec);
      def_hi = g_rec_def_mask_hi;
      def_lo = g_rec_def_mask_lo;
      use_hi = g_rec_use_mask_hi;
      use_lo = g_rec_use_mask_lo;
      rec = find_next_psd_record(node,andor_rec);
      while (rec != (psd *)0x0) {
        if (((rec->op == andor_rec->op) && ((rec->ea1->type & 0x1f) == 7)) &&
           ((cVar1 = operands_equal(rec->ea2,andor_rec->ea2), cVar1 == '\x01' &&
            (merged_imm = is_record_volatile(rec), merged_imm == 0)))) {
          merged_imm = andor_rec->ea1->disp;
          if (andor_rec->op == OP_AND) {
            merged_imm = merged_imm & rec->ea1->disp;
          }
          else {
            merged_imm = merged_imm | rec->ea1->disp;
          }
          andor_rec->ea1->disp = merged_imm;
          delete_psd_record(rec);
        }
        else {
          op = rec->op;
          if ((((op == OP_CALL) || (op == OP_JSR)) ||
              ((op == OP_BSR || (((op == OP_BSRF || (op == OP_TRAPA)) || (op == OP_SLEEP)))))) ||
             (((op == OP_NON_10 ||
               (compute_record_register_masks(rec), (g_rec_def_mask_lo & use_lo) != 0)) ||
              (((g_rec_def_mask_hi & use_hi) != 0 ||
               (((g_rec_use_mask_lo & def_lo) != 0 || ((g_rec_use_mask_hi & def_hi) != 0))))))))
          break;
        }
        rec = find_next_psd_record(node,rec);
        if (((byte)g_stage_flags & 2) != 0) {
          _printf(s_cp___08lx_0042503c,rec);
        }
      }
    }
    andor_rec = find_next_psd_record(node,andor_rec);
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_cp___08lx_0042503c,andor_rec);
    }
  } while( true );
}



