#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 00404560
// name : write_symbol_aggregate_size
// size : 33
// sig  : void write_symbol_aggregate_size(uchar type, int size)


int __cdecl write_symbol_aggregate_size(uchar type,int size)

{
  if (0x5f < (type & 0xe0)) {
    write_symbol_bytes(g_sym_file,(char *)&size,4);
  }
  return;
}



