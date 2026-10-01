#include "decls.h"
#include "imports.h"

// entry: 0042b060
// name : fill_case_table_record
// size : 53
// sig  : void fill_case_table_record(psd * rec, psd_op op, short count, short labno)


int __cdecl fill_case_table_record(psd *rec,psd_op op,short count,short labno)

{
  zero_words((uint *)rec,6);
  rec->filno = count;
  rec->op = op;
  if (op == OP_CTBL) {
    rec->linno = labno;
    return;
  }
  *(short *)&rec->ea1 = labno;
  return;
}



