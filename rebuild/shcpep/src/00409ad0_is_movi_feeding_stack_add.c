#include "decls.h"
#include "imports.h"

// entry: 00409ad0
// name : is_movi_feeding_stack_add
// size : 93
// sig  : int is_movi_feeding_stack_add(code_node * node, psd * rec)


int __cdecl is_movi_feeding_stack_add(code_node *node,psd *rec)

{
  psd *next_rec;
  
  if ((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) {
    next_rec = find_next_psd_record(node,rec);
    if (((next_rec != (psd *)0x0) &&
        (((next_rec->op == OP_ADD || (next_rec->op == OP_SUB)) && (next_rec->ea2->base == '\x0f'))))
       && (((next_rec->ea1->type & 0x1f) == 1 && (rec->ea2->base == next_rec->ea1->base)))) {
      return 1;
    }
  }
  return 0;
}



