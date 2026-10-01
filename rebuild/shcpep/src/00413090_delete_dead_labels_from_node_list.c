#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_stage_flags
#define g_stage_flags (*(unsigned int *)(g_sd + 0x6d64))


// entry: 00413090
// name : delete_dead_labels_from_node_list
// size : 309
// sig  : void delete_dead_labels_from_node_list(void)


int __cdecl delete_dead_labels_from_node_list(void)

{
  psd *label_rec;
  byte sym_kind;
  code_node *block;
  short labno;
  short sym_number;
  
  for (block = g_current_node_list; block != (code_node *)0x0; block = block->next_block) {
    labno = block->labno;
    if (labno != 0) {
      g_current_symbol = g_symbol_hash[labno % 0x3fd];
      sym_number = g_current_symbol->number;
      while (sym_number != labno) {
        g_current_symbol = g_current_symbol->hash_next;
        sym_number = g_current_symbol->number;
      }
      if ((g_stage_flags & 8) != 0) {
        _printf(s_labno___d__reference_count___ld_00427710,(int)labno,g_current_symbol->ref_count);
      }
      if (((g_section_end == 1) && (g_current_symbol != (symbol *)0x0)) &&
         ((((sym_kind = g_current_symbol->type & 0x1f, sym_kind == 2 ||
            ((sym_kind == 3 && ((g_current_symbol->flags & 0x20) != 0)))) ||
           ((sym_kind == 4 && ((g_current_symbol->flags & 0x20) != 0)))) || (sym_kind == 5)))) {
        label_rec = g_current_symbol->label_psd;
        if (label_rec != (psd *)0x0) {
          delete_branch_to_next_label(label_rec);
          invert_cond_branch_over_jump(label_rec);
          if (g_current_symbol->ref_count == 0) {
            delete_psd_record(label_rec);
            g_current_symbol->label_psd = (psd *)0x0;
          }
        }
        if (g_current_symbol->ref_count == 0) {
          block->labno = 0;
        }
      }
    }
    if ((g_stage_flags & 8) != 0) {
      _printf(s_dellab_end__labno__d_004276f8,(int)block->labno);
    }
  }
  return;
}



