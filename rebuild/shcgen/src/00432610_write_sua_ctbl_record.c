#include "decls.h"
#include "imports.h"

// entry: 00432610
// name : write_sua_ctbl_record
// size : 43
// sig  : void write_sua_ctbl_record(FILE * out, psd * rec)


int __cdecl write_sua_ctbl_record(FILE *out,psd *rec)

{
  write_sua_bytes(out,(char *)&rec->filno,2);
  write_sua_bytes(out,(char *)&rec->linno,2);
  return;
}



