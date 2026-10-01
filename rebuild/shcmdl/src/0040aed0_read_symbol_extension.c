#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040aed0
// name : read_symbol_extension
// size : 150
// sig  : void read_symbol_extension(symbol * sym)


int __cdecl read_symbol_extension(symbol *sym)

{
  unsigned char _frec_b[11];
#define flag_bits (*(byte *)(_frec_b + 0))
#define val16 (*(undefined2 *)(_frec_b + 1))
#define val32 (*(int *)(_frec_b + 3))
#define ext34 (*(int *)(_frec_b + 7))
  
  read_or_fail(g_sym_file,(char *)&flag_bits,1);
  sym->ext_flags = flag_bits;
  if ((flag_bits & 2) != 0) {
    if ((flag_bits & 4) == 0) {
      read_or_fail(g_sym_file,(char *)&val32,4);
      sym->ext_30 = val32;
    }
    else {
      read_or_fail(g_sym_file,(char *)&val16,2);
      *(undefined2 *)&sym->ext_30 = val16;
    }
  }
  if ((flag_bits & 1) != 0) {
    read_or_fail(g_sym_file,(char *)&ext34,4);
    sym->ext_34 = ext34;
  }
  return;
#undef flag_bits
#undef val16
#undef val32
#undef ext34
}



