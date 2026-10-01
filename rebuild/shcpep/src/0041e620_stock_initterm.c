#include "decls.h"
#include "imports.h"

// entry: 0041e620
// name : stock_initterm
// size : 32
// sig  : void stock_initterm(undefined4 * pfbegin, undefined4 * pfend)


int __cdecl stock_initterm(undefined4 *pfbegin,undefined4 *pfend)

{
  for (; pfbegin < pfend; pfbegin = pfbegin + 1) {
    if ((code *)*pfbegin != 0) {
      (*(code *)*pfbegin)();
    }
  }
  return;
}



