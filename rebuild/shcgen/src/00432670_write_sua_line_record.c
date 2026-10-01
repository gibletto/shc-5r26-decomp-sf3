#include "decls.h"
#include "imports.h"

// entry: 00432670
// name : write_sua_line_record
// size : 79
// sig  : void write_sua_line_record(FILE * out, psd * rec)


int __cdecl write_sua_line_record(FILE *out,psd *rec)

{
  g_sua_filno = rec->filno;
  g_sua_linno = rec->linno;
  write_sua_bytes(out,(char *)&rec->filno,2);
  write_sua_bytes(out,(char *)&rec->linno,2);
  write_sua_bytes(out,(char *)&rec->ea1,1);
  return;
}



