#include "decls.h"
#include "imports.h"

// entry: 0041b430
// name : write_sub_ctbl_record
// size : 43
// sig  : void write_sub_ctbl_record(FILE * out, psd * rec)


int __cdecl write_sub_ctbl_record(FILE *out,psd *rec)

{
  write_sub_bytes(out,(char *)&rec->filno,2);
  write_sub_bytes(out,(char *)&rec->linno,2);
  return;
}



