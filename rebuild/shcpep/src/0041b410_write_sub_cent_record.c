#include "decls.h"
#include "imports.h"

// entry: 0041b410
// name : write_sub_cent_record
// size : 24
// sig  : void write_sub_cent_record(FILE * out, psd * rec)


int __cdecl write_sub_cent_record(FILE *out,psd *rec)

{
  write_sub_bytes(out,(char *)&rec->ea1,2);
  return;
}



