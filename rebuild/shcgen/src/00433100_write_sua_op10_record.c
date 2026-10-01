#include "decls.h"
#include "imports.h"

// entry: 00433100
// name : write_sua_op10_record
// size : 94
// sig  : void write_sua_op10_record(FILE * out, psd * rec)


int __cdecl write_sua_op10_record(FILE *out,psd *rec)

{
  g_sua_filno = rec->filno;
  g_sua_linno = rec->linno;
  write_sua_bytes(out,(char *)&rec->filno,2);
  write_sua_bytes(out,(char *)&rec->linno,2);
  write_sua_bytes(out,(char *)&rec->ea1,4);
  write_sua_bytes(out,(char *)&rec->ea2,4);
  return;
}



