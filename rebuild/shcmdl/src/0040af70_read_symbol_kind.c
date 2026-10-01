#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040af70
// name : read_symbol_kind
// size : 33
// sig  : char read_symbol_kind(void)


char __cdecl read_symbol_kind(void)

{
  unsigned char _frec_1[1];
#define kind_val (*(char *)(_frec_1 + 0))
  
  read_or_fail(g_sym_file,&kind_val,1);
  return kind_val;
#undef kind_val
}



