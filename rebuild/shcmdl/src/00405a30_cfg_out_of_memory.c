#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_break_jumps
#define g_cfg_break_jumps (*(block_list * *)(g_sd + 0x267b8))
#undef g_cfg_continue_jumps
#define g_cfg_continue_jumps (*(block_list * *)(g_sd + 0x26f0c))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))
#undef g_return_preds
#define g_return_preds (*(block_list * *)(g_sd + 0x26ee4))


// entry: 00405a30
// name : cfg_out_of_memory
// size : 150
// sig  : void cfg_out_of_memory(void)


int __cdecl cfg_out_of_memory(void)

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
  g_cfg_pending_jumps = (block_list *)0x0;
  abort_function_optimization();
  return;
}



