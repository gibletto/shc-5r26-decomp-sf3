#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040b100
// name : read_symbol_byte_06
// size : 33
// sig  : char read_symbol_byte_06(void)


char __cdecl read_symbol_byte_06(void)

{
  unsigned char _frec_1[1];
#define val_read (*(char *)(_frec_1 + 0))
  
  read_or_fail(g_sym_file,&val_read,1);
  return val_read;
#undef val_read
}



