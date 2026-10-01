#include "decls.h"
#include "imports.h"

// entry: 0041bf80
// name : write_sub_section_record
// size : 24
// sig  : void write_sub_section_record(FILE * out, psd * rec)


int __cdecl write_sub_section_record(FILE *out,psd *rec)

{
  write_sub_bytes(out,(char *)&rec->filno,2);
  return;
}



