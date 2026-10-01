#include "decls.h"
#include "imports.h"

// entry: 00409a50
// name : clear_block_flags_and_labels
// size : 24
// sig  : void clear_block_flags_and_labels(code_node * block)


int __cdecl clear_block_flags_and_labels(code_node *block)

{
  if (block != (code_node *)0x0) {
    block->labno = 0;
    block->flags = '\0';
    block->target_labno = 0;
    block->psd_count = '\0';
  }
  return;
}



