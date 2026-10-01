#include "decls.h"
#include "imports.h"

// entry: 004099f0
// name : unlink_block_from_target_label_refs
// size : 94
// sig  : void unlink_block_from_target_label_refs(code_node * block)


int __cdecl unlink_block_from_target_label_refs(code_node *block)

{
  short labno;
  label_block_ref *ref;
  symbol *sym;
  short sym_number;
  
  if ((block != (code_node *)0x0) && (labno = block->target_labno, labno != 0)) {
    sym = g_symbol_hash[labno % 0x3fd];
    sym_number = sym->number;
    while (sym_number != labno) {
      sym = sym->hash_next;
      sym_number = sym->number;
    }
    if (sym != (symbol *)0x0) {
      for (ref = sym->ref_blocks; ref != (label_block_ref *)0x0; ref = ref->next) {
        if ((ref->block != (code_node *)0x0) && (block == ref->block)) {
          ref->block = (code_node *)0x0;
        }
      }
    }
  }
  return;
}



