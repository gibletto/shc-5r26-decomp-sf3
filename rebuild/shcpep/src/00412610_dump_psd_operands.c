#include "decls.h"
#include "imports.h"

// entry: 00412610
// name : dump_psd_operands
// size : 56
// sig  : int dump_psd_operands(psd * rec)


int __cdecl dump_psd_operands(psd *rec)

{
  int number;
  
  number = 1;
  if (rec->ea1 != (ea *)0x0) {
    number = 2;
    dump_ea_operand(rec->ea1,1);
  }
  if (rec->ea2 != (ea *)0x0) {
    dump_ea_operand(rec->ea2,number);
  }
  return 0;
}



