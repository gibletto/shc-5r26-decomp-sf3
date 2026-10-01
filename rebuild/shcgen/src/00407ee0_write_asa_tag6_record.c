#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))


// entry: 00407ee0
// name : write_asa_tag6_record
// size : 34
// sig  : void write_asa_tag6_record(char kind)


int __cdecl write_asa_tag6_record(char kind)

{
  unsigned char _frec_1[1];
#define rec_kind (*(char *)(_frec_1 + 0))
  
  rec_kind = kind;
  write_bytes_or_fail(&rec_kind,1,g_asa_file);
  return;
#undef rec_kind
}



