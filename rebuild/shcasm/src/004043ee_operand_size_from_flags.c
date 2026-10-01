#include "decls.h"
#include "imports.h"

// entry: 004043ee
// name : operand_size_from_flags
// size : 137
// sig  : int operand_size_from_flags(psd * rec)


int __cdecl operand_size_from_flags(psd *rec)

{
  byte size_code;
  int nbytes;
  
  size_code = rec->flg & 3;
  if (size_code == 0) {
    nbytes = 1;
  }
  else if (size_code == 1) {
    nbytes = 2;
  }
  else if (size_code == 2) {
    nbytes = 4;
  }
  else {
    report_message_at_source_line(0,0,0x1321,(char *)0x0);
  }
  return nbytes;
}



