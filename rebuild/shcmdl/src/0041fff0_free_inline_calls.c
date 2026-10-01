#include "decls.h"
#include "imports.h"

// entry: 0041fff0
// name : free_inline_calls
// size : 30
// sig  : void free_inline_calls(inline_call * cand)


int __cdecl free_inline_calls(inline_call *cand)

{
  inline_call *next;
  
  while (cand != (inline_call *)0x0) {
    next = cand->next;
    pool_free(cand,0x10);
    cand = next;
  }
  return;
}



