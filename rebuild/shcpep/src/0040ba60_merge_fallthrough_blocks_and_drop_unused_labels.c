#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))


// entry: 0040ba60
// name : merge_fallthrough_blocks_and_drop_unused_labels
// size : 298
// sig  : void merge_fallthrough_blocks_and_drop_unused_labels(void)


int __cdecl merge_fallthrough_blocks_and_drop_unused_labels(void)

{
  byte kind;
  code_node *last_node;
  code_node *block;
  code_node *prev;
  
  prev = (code_node *)0x0;
  block = g_current_node_list;
  do {
    if (block == (code_node *)0x0) {
      return;
    }
    if ((block->labno != 0) && (g_section_end == 1)) {
      g_current_symbol = g_symbol_hash[block->labno % 0x3fd];
      do {
        if (g_current_symbol->number == block->labno) break;
        g_current_symbol = g_current_symbol->hash_next;
      } while (g_current_symbol != (symbol *)0x0);
      if ((((g_current_symbol != (symbol *)0x0) && (g_current_symbol->number == block->labno)) &&
          ((((kind = g_current_symbol->type & 0x1f, kind == 2 ||
             ((kind == 3 && ((g_current_symbol->flags & 0x20) != 0)))) ||
            ((kind == 4 && ((g_current_symbol->flags & 0x20) != 0)))) || (kind == 5)))) &&
         ((g_current_symbol->ref_count == 0 && (g_current_symbol->label_psd == block->psd)))) {
        block->labno = 0;
      }
    }
    if ((((prev != (code_node *)0x0) && ((prev->flags & 1) == 0)) && (prev->target_labno == 0)) &&
       (prev->next_block->labno == 0)) {
      last_node = find_last_node_of_block(prev);
      last_node->next = block;
      prev->flags = prev->flags | block->flags;
      prev->psd_count = prev->psd_count + block->psd_count;
      *(short *)prev->unknown_02 = *(short *)prev->unknown_02 + *(short *)block->unknown_02;
      prev->target_labno = block->target_labno;
      prev->next_block = block->next_block;
      block->flags = '\0';
      block->psd_count = '\0';
      block->unknown_02[0] = '\0';
      block->unknown_02[1] = '\0';
      block->labno = 0;
      block->target_labno = 0;
      block->next_block = (code_node *)0x0;
      block = prev;
    }
    prev = block;
    block = block->next_block;
  } while( true );
}



