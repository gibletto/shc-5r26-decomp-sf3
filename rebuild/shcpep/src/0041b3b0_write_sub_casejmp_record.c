#include "decls.h"
#include "imports.h"

// entry: 0041b3b0
// name : write_sub_casejmp_record
// size : 88
// sig  : void write_sub_casejmp_record(FILE * out, psd * rec)


int __cdecl write_sub_casejmp_record(FILE *out,psd *rec)

{
  write_sub_bytes(out,(char *)&rec->expno,4);
  write_sub_bytes(out,(char *)&rec->filno,2);
  write_sub_bytes(out,(char *)&rec->linno,2);
  write_sub_bytes(out,(char *)&rec->ea1,4);
  write_sub_bytes(out,(char *)&rec->ea2,4);
  return;
}



