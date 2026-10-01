#include "decls.h"
#include "imports.h"

// entry: 004325f0
// name : write_sua_cent_record
// size : 24
// sig  : void write_sua_cent_record(FILE * out, psd * rec)


int __cdecl write_sua_cent_record(FILE *out,psd *rec)

{
  write_sua_bytes(out,(char *)&rec->ea1,2);
  return;
}



