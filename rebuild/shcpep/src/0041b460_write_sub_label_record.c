#include "decls.h"
#include "imports.h"

// entry: 0041b460
// name : write_sub_label_record
// size : 43
// sig  : void write_sub_label_record(FILE * out, psd * rec)


int __cdecl write_sub_label_record(FILE *out,psd *rec)

{
  write_sub_bytes(out,(char *)&rec->ea1,2);
  write_sub_bytes(out,(char *)&rec->sptravel,4);
  return;
}



