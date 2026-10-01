#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 00404510
// name : write_symbol_name
// size : 34
// sig  : void write_symbol_name(uchar len, char * name)


int __cdecl write_symbol_name(uchar len,char *name)

{
  if (len != '\0') {
    write_symbol_bytes(g_sym_file,name,(uint)len);
  }
  return;
}



