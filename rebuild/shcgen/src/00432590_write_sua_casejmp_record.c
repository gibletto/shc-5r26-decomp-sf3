#include "decls.h"
#include "imports.h"

// entry: 00432590
// name : write_sua_casejmp_record
// size : 88
// sig  : void write_sua_casejmp_record(FILE * out, psd * rec)


int __cdecl write_sua_casejmp_record(FILE *out,psd *rec)

{
  write_sua_bytes(out,(char *)&rec->expno,4);
  write_sua_bytes(out,(char *)&rec->filno,2);
  write_sua_bytes(out,(char *)&rec->linno,2);
  write_sua_bytes(out,(char *)&rec->ea1,4);
  write_sua_bytes(out,(char *)&rec->ea2,4);
  return;
}



