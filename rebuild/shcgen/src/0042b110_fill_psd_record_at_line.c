#include "decls.h"
#include "imports.h"

// entry: 0042b110
// name : fill_psd_record_at_line
// size : 56
// sig  : void fill_psd_record_at_line(psd * rec, psd_op op, short filno, ushort linno, int value1, int value2)


int __cdecl fill_psd_record_at_line(psd *rec,psd_op op,short filno,ushort linno,int value1,int value2)

{
  zero_words((uint *)rec,6);
  rec->filno = filno;
  rec->op = op;
  rec->linno = linno;
  rec->ea1 = (ea *)value1;
  rec->ea2 = (ea *)value2;
  return;
}



