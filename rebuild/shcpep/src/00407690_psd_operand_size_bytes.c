#include "decls.h"
#include "imports.h"

// entry: 00407690
// name : psd_operand_size_bytes
// size : 83
// sig  : int psd_operand_size_bytes(psd * rec)


int __cdecl psd_operand_size_bytes(psd *rec)

{
  byte size_bits;
  int local_4;
  
  size_bits = rec->flg & 3;
  if ((rec->flg & 3U) == 0) {
    return 1;
  }
  if (size_bits != 1) {
    if (size_bits != 2) {
      report_compiler_message(0,0,0x1321,(char *)0x0);
      return local_4;
    }
    return 4;
  }
  return 2;
}



