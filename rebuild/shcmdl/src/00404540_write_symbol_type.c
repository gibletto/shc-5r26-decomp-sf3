#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 00404540
// name : write_symbol_type
// size : 23
// sig  : void write_symbol_type(char type)


int __cdecl write_symbol_type(char type)

{
  write_symbol_bytes(g_sym_file,&type,1);
  return;
}



