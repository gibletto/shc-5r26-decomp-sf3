#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))


// entry: 0040b130
// name : drop_pr_save_restore_if_no_calls
// size : 340
// sig  : void drop_pr_save_restore_if_no_calls(void)


int __cdecl drop_pr_save_restore_if_no_calls(void)

{
  psd *rec;
  code_node *block;
  bool has_flabel;
  psd_op op;
  
  has_flabel = false;
  block = g_current_node_list;
  if ((g_aux_record_table[g_current_aux_index].flags & 0x8000) == 0) {
    for (; block != (code_node *)0x0; block = block->next_block) {
      for (rec = block->psd; rec != (psd *)0x0; rec = find_next_psd_record(block,rec)) {
        if (rec->op == OP_FLABEL) {
          has_flabel = true;
          goto LAB_0040b184;
        }
      }
    }
LAB_0040b184:
    block = g_current_node_list;
    if (has_flabel) {
      for (; block != (code_node *)0x0; block = block->next_block) {
        for (rec = block->psd; rec != (psd *)0x0; rec = find_next_psd_record(block,rec)) {
          op = rec->op;
          if (op == OP_JSR) {
            return;
          }
          if (op == OP_BSR) {
            return;
          }
          if (op == OP_CALL) {
            return;
          }
          if (op == OP_TRAPA) {
            return;
          }
          if (op == OP_BSRF) {
            return;
          }
        }
      }
      g_aux_record_table[g_current_aux_index].flags =
           g_aux_record_table[g_current_aux_index].flags | 0x8000;
      for (block = g_current_node_list; block != (code_node *)0x0; block = block->next_block) {
        for (rec = block->psd; rec != (psd *)0x0; rec = find_next_psd_record(block,rec)) {
          if (((((rec->op == OP_LDS) && (rec->ea1->base == '\x0f')) &&
               ((rec->ea1->type & 0x1f) == 4)) &&
              ((rec->ea2->base == 'f' && ((rec->ea2->type & 0x1f) == 6)))) ||
             ((((rec->op == OP_STS && ((rec->ea1->base == 'f' && ((rec->ea1->type & 0x1f) == 6))))
               && (rec->ea2->base == '\x0f')) && ((rec->ea2->type & 0x1f) == 3)))) {
            delete_psd_record(rec);
          }
        }
      }
    }
  }
  return;
}



