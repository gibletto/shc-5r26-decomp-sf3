#include "decls.h"
#include "imports.h"

// entry: 00411e30
// name : fold_register_move_into_unary_op
// size : 153
// sig  : void fold_register_move_into_unary_op(code_node * node)


int __cdecl fold_register_move_into_unary_op(code_node *node)

{
  psd *rec;
  psd *unary_rec;
  psd *following;
  psd_op op;
  ea *src_ea;
  
  unary_rec = find_next_psd_record(node,node->psd);
  rec = node->psd;
  while (unary_rec != (psd *)0x0) {
    op = unary_rec->op;
    if ((((((op == OP_EXTU) || (op == OP_EXTS)) || (op == OP_NOT)) || (op == OP_NEG)) &&
        ((((src_ea = unary_rec->ea1, (src_ea->type & 0x1f) == 1 &&
           ((unary_rec->ea2->type & 0x1f) == 1)) &&
          ((unary_rec->ea2->base == src_ea->base &&
           ((rec->op == OP_MOV && ((rec->ea1->type & 0x1f) == 1)))))) &&
         ((rec->ea2->type & 0x1f) == 1)))) && (rec->ea2->base == src_ea->base)) {
      src_ea->base = rec->ea1->base;
      delete_psd_record(rec);
    }
    following = find_next_psd_record(node,unary_rec);
    rec = unary_rec;
    unary_rec = following;
  }
  return;
}



