#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1e72c))


// entry: 00413a60
// name : write_reg_trailer
// size : 63
// sig  : void write_reg_trailer(short func_symx)


int __cdecl write_reg_trailer(short func_symx)

{
  unsigned char _frec_4[4];
#define rec (*(char (*)[2])(_frec_4 + 0))
#define sym_index (*(short *)(_frec_4 + 2))
  uint got;
  
  sym_index = func_symx;
  rec[0] = '\0';
  rec[1] = '\0';
  got = write_bytes(g_reg_file,rec,4);
  if (got == 0xffffffff) {
    fatal_error(0xce7);
  }
  return;
#undef rec
#undef sym_index
}



