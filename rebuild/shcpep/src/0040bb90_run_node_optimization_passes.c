#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_line_kind5
#define g_line_kind5 (*(char *)(g_sd + 0x21f8))


// entry: 0040bb90
// name : run_node_optimization_passes
// size : 309
// sig  : void run_node_optimization_passes(code_node * block)


int __cdecl run_node_optimization_passes(code_node *block)

{
  psd *prev_rec;
  psd *rec;
  int n;
  code_node *node;
  
  PEPPASS(0, form_predecrement_postincrement_addressing(block));
  PEPPASS(1, merge_repeated_and_or_immediates(block));
  PEPPASS(2, load_compare_operand_into_r0(block));
  PEPPASS(3, fold_register_move_into_unary_op(block));
  PEPPASS(4, rewrite_repeated_movi_per_register(block));
  PEPPASS(5, fold_address_add_into_following_load(block));
  PEPPASS(6, retarget_result_to_copy_destination(block));
  PEPPASS(7, reuse_loaded_constants_and_copies(block));
  PEPPASS(8, delete_redundant_loads(block));
  PEPPASS(9, delete_redundant_memory_loads(block));
  PEPPASS(10, delete_store_load_pairs(block));
  PEPPASS(11, delete_dead_stores(block));
  PEPPASS(12, fold_add_immediates(block));
  PEPPASS(13, derive_constant_loads_from_previous(block));
  for (node = block; node != (code_node *)0x0; node = node->next) {
    rec = node->psd;
    n = 0xf;
    do {
      if ((rec->op == OP_LINE) && (g_line_kind5 = '\x01', *(char *)&rec->ea1 != '\x05')) {
        g_line_kind5 = '\0';
      }
      if ((((rec->op == OP_CMP_EQ) || (rec->op == OP_TST)) && (g_line_kind5 == '\0')) &&
         ((prev_rec = find_previous_psd_record(block,rec), prev_rec != (psd *)0x0 &&
          (prev_rec->op == OP_AND)))) {
        fuse_and_imm_with_zero_test(rec,prev_rec);
      }
      if ((((g_current_request->cpu != 0) && ((rec->op == OP_JUMPT || (rec->op == OP_JUMPF)))) &&
          (prev_rec = find_previous_psd_record(block,rec), prev_rec != (psd *)0x0)) &&
         ((prev_rec->op == OP_CMP_EQ || (prev_rec->op == OP_TST)))) {
        fold_decrement_test_into_dt(block,prev_rec);
      }
      rec = rec + 1;
      n = n + -1;
    } while (n != 0);
  }
  return;
}



