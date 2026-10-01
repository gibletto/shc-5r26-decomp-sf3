#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040b090
// name : read_symbol_type
// size : 33
// sig  : char read_symbol_type(void)


char __cdecl read_symbol_type(void)

{
  unsigned char _frec_1[1];
#define type_byte (*(char *)(_frec_1 + 0))
  
  read_or_fail(g_sym_file,&type_byte,1);
  return type_byte;
#undef type_byte
}



