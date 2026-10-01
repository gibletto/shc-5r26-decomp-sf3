#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 004044f0
// name : write_symbol_name_length
// size : 23
// sig  : void write_symbol_name_length(char len)


int __cdecl write_symbol_name_length(char len)

{
  write_symbol_bytes(g_sym_file,&len,1);
  return;
}



