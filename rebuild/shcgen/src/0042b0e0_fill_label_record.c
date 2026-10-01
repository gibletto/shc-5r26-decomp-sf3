#include "decls.h"
#include "imports.h"

// entry: 0042b0e0
// name : fill_label_record
// size : 41
// sig  : void fill_label_record(psd * rec, psd_op op, short labno, short sptravel)


int __cdecl fill_label_record(psd *rec,psd_op op,short labno,short sptravel)

{
  zero_words((uint *)rec,6);
  *(short *)&rec->ea1 = labno;
  rec->op = op;
  rec->sptravel = (int)sptravel;
  return;
}



