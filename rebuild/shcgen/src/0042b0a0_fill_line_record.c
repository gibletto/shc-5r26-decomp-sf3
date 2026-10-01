#include "decls.h"
#include "imports.h"

// entry: 0042b0a0
// name : fill_line_record
// size : 49
// sig  : void fill_line_record(psd * rec, psd_op op, short filno, ushort linno, char flag)


int __cdecl fill_line_record(psd *rec,psd_op op,short filno,ushort linno,char flag)

{
  zero_words((uint *)rec,6);
  rec->filno = filno;
  rec->op = op;
  rec->linno = linno;
  *(char *)&rec->ea1 = flag;
  return;
}



