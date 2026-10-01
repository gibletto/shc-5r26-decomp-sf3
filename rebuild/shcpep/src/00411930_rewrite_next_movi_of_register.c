#include "decls.h"
#include "imports.h"

// entry: 00411930
// name : rewrite_next_movi_of_register
// size : 219
// sig  : void rewrite_next_movi_of_register(code_node * node, psd * movi)


int __cdecl rewrite_next_movi_of_register(code_node *node,psd *movi)

{
  uchar reg;
  byte effect;
  psd *next_movi;
  int iVar1;
  psd *ppVar2;
  byte changed;
  psd_op op;
  
  changed = 0;
  reg = movi->ea2->base;
  next_movi = find_next_psd_record(node,movi);
  if (next_movi != (psd *)0x0) {
    while ((next_movi->op != OP_MOVI || (next_movi->ea2->base != reg))) {
      effect = record_changes_register(next_movi,reg);
      changed = changed | effect;
      op = next_movi->op;
      if ((op == OP_JSR) ||
         ((((op == OP_BSR || (op == OP_CALL)) || (op == OP_TRAPA)) || (op == OP_BSRF)))) {
        effect = call_register_effect(next_movi,reg,0);
        changed = changed | effect;
      }
      next_movi = find_next_psd_record(node,next_movi);
      if (next_movi == (psd *)0x0) {
        return;
      }
    }
    rewrite_next_movi_of_register(node,next_movi);
    if ((changed == 0) && (iVar1 = is_movi_feeding_stack_add(node,next_movi), iVar1 == 0)) {
      if ((next_movi->op == OP_MOVI) &&
         ((next_movi->ea1->labels == (label_ref *)0x0 &&
          (ppVar2 = find_next_psd_record(node,next_movi), ppVar2 == (psd *)0x0)))) {
        return;
      }
      rewrite_movi_from_previous_value(movi,next_movi);
    }
  }
  return;
}



