#include "decls.h"
#include "imports.h"

// entry: 00432640
// name : write_sua_label_record
// size : 43
// sig  : void write_sua_label_record(FILE * out, psd * rec)


int __cdecl write_sua_label_record(FILE *out,psd *rec)

{
  write_sua_bytes(out,(char *)&rec->ea1,2);
  write_sua_bytes(out,(char *)&rec->sptravel,4);
  return;
}



