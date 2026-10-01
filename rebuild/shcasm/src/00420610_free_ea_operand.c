#include "decls.h"
#include "imports.h"

// entry: 00420610
// name : free_ea_operand
// size : 95
// sig  : void __cdecl free_ea_operand(ea *op)


int __cdecl free_ea_operand(ea *op)

{
  label_ref *lab_ref;
  label_ref *next_ref;
  
  if (op != (ea *)0x0) {
    lab_ref = op->labels;
    while (lab_ref != (label_ref *)0x0) {
      next_ref = lab_ref->next;
      pool_free(lab_ref,8);
      lab_ref = next_ref;
    }
    pool_free(op,0xc);
  }
  return;
}
