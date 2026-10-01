#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 004044a0
// name : write_symbol_class_short
// size : 51
// sig  : void write_symbol_class_short(char sclass, short value)


int __cdecl write_symbol_class_short(char sclass,short value)

{
  switch(sclass) {
  case '\x03':
  case '\x04':
  case '\t':
  case '\v':
    write_symbol_bytes(g_sym_file,(char *)&value,2);
  }
  return;
}



