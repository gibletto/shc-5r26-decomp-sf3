#include "decls.h"
#include "imports.h"

// entry: 0042b150
// name : fill_section_record
// size : 33
// sig  : void fill_section_record(psd * rec, psd_op op, short section)


int __cdecl fill_section_record(psd *rec,psd_op op,short section)

{
  zero_words((uint *)rec,6);
  rec->filno = section;
  rec->op = op;
  return;
}



