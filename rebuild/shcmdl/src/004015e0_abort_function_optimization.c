#include "decls.h"
#include "imports.h"
#include <setjmp.h>
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_break_jumps
#define g_cfg_break_jumps (*(block_list * *)(g_sd + 0x267b8))
#undef g_cfg_continue_jumps
#define g_cfg_continue_jumps (*(block_list * *)(g_sd + 0x26f0c))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_return_preds
#define g_return_preds (*(block_list * *)(g_sd + 0x26ee4))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004015e0
// name : abort_function_optimization
// size : 347
// sig  : int abort_function_optimization(void)


int __cdecl abort_function_optimization(void)

{
  label_rec **bucket;
  label_rec *lab;
  label_rec *next_label;
  
  bucket = g_label_hash;
  do {
    lab = *bucket;
    while (lab != (label_rec *)0x0) {
      next_label = lab->next;
      free_list_cells((node_list *)lab->gotos);
      pool_free(lab,0x10);
      lab = next_label;
    }
    *bucket = (label_rec *)0x0;
    bucket = bucket + 1;
  } while (bucket < &DAT_00458ee0);
  free_list_cells((node_list *)g_cfg_pending_jumps);
  free_list_cells((node_list *)g_cfg_continue_jumps);
  free_list_cells((node_list *)g_cfg_break_jumps);
  free_list_cells((node_list *)g_return_preds);
  g_return_preds = (block_list *)0x0;
  g_cfg_break_jumps = (block_list *)0x0;
  g_cfg_continue_jumps = (block_list *)0x0;
  g_function_aborted = 1;
  g_cfg_pending_jumps = (block_list *)0x0;
  free_merge_tables();
  cse_free_tables();
  free_induction_tables();
  free_register_allocation_tables();
  free_all_bblocks();
  free_loop_tree(g_loop_tree);
  g_loop_tree = (loop *)0x0;
  free_du_tables();
  pool_release_free_lists();
  report_message(100,g_func_node,g_symtab[g_func_node->symx].name);
  if ((g_inline_flags & 6) == 6) {
    reset_inline_state();
  }
  if (g_options->optimize != 0) {
    write_reg_header(g_func_node->symx,0,0);
    write_reg_trailer(g_func_node->symx);
  }
  reset_symbol_leaf_numbers();
  reset_il_node_pool();
                    /* WARNING: Subroutine does not return */
  longjmp(*(jmp_buf *)&g_error_jmp_buf,1);
}
