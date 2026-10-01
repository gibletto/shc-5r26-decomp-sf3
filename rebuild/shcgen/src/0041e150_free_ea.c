#include "decls.h"
#include "imports.h"

// entry: 0041e150
// name : free_ea
// size : 50
// sig  : void free_ea(ea * operand)


int __cdecl free_ea(ea *operand)

{
  label_ref *ptr;
  label_ref *next_ref;
  
  if (operand != (ea *)0x0) {
    ptr = operand->labels;
    while (ptr != (label_ref *)0x0) {
      next_ref = ptr->next;
      pool_free(ptr,8);
      ptr = next_ref;
    }
    pool_free(operand,0xc);
  }
  return;
}



