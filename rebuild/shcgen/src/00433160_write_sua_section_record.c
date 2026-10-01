#include "decls.h"
#include "imports.h"

// entry: 00433160
// name : write_sua_section_record
// size : 24
// sig  : void write_sua_section_record(FILE * out, psd * rec)


int __cdecl write_sua_section_record(FILE *out,psd *rec)

{
  write_sua_bytes(out,(char *)&rec->filno,2);
  return;
}



