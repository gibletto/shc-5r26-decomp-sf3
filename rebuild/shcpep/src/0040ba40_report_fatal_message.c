#include "decls.h"
#include "imports.h"

// entry: 0040ba40
// name : report_fatal_message
// size : 31
// sig  : void __cdecl report_fatal_message(short filno,short linno,short msgno)


int __cdecl report_fatal_message(short filno,short linno,short msgno)

{
  report_compiler_message(filno,(int)linno,msgno,(char *)0x0);
  return;
}
