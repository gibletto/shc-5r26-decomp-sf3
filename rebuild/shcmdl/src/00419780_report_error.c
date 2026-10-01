#include "decls.h"
#include "imports.h"

// entry: 00419780
// name : report_error
// size : 18
// sig  : void report_error(int errcode)


int __cdecl report_error(int errcode)

{
  report_message(errcode,(il_node *)0x0,(char *)0x0);
  return;
}



