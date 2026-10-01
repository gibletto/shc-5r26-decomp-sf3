#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040b010
// name : read_symbol_name_length
// size : 33
// sig  : char read_symbol_name_length(void)


char __cdecl read_symbol_name_length(void)

{
  unsigned char _frec_1[1];
#define len (*(char *)(_frec_1 + 0))
  
  read_or_fail(g_sym_file,&len,1);
  return len;
#undef len
}



