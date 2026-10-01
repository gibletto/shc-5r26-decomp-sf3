#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sub_linno
#define g_sub_linno (*(unsigned short *)(g_sd + 0x5360))


// entry: 0041b490
// name : write_sub_line_record
// size : 79
// sig  : void write_sub_line_record(FILE * out, psd * rec)


int __cdecl write_sub_line_record(FILE *out,psd *rec)

{
  g_sub_filno = rec->filno;
  g_sub_linno = rec->linno;
  write_sub_bytes(out,(char *)&rec->filno,2);
  write_sub_bytes(out,(char *)&rec->linno,2);
  write_sub_bytes(out,(char *)&rec->ea1,1);
  return;
}



