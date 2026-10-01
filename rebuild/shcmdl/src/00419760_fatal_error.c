#include "decls.h"
#include "imports.h"

// entry: 00419760
// name : fatal_error
// size : 31
// sig  : int __cdecl fatal_error(int errcode)


int __cdecl fatal_error(int errcode)

{
  int extraout_EAX;
  
  report_error(errcode);
  stock_exit(g_max_error_level * 2 + 1);
  return extraout_EAX;
}
