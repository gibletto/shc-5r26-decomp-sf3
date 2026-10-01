#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040afa0
// name : read_symbol_kind_short
// size : 78
// sig  : short read_symbol_kind_short(char kind)


short __cdecl read_symbol_kind_short(char kind)

{
  unsigned char _frec_2[2];
#define val_read (*(short *)(_frec_2 + 0))
  
  switch(kind) {
  case '\x03':
  case '\x04':
  case '\t':
  case '\v':
    read_or_fail(g_sym_file,(char *)&val_read,2);
    return val_read;
  default:
    return 0;
  }
#undef val_read
}



