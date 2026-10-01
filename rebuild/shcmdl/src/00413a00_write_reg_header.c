#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1e72c))


// entry: 00413a00
// name : write_reg_header
// size : 82
// sig  : void write_reg_header(short func_symx, int flag1, int flag2)


int __cdecl write_reg_header(short func_symx,int flag1,int flag2)

{
  unsigned char _frec_4[4];
#define rec (*(short *)(_frec_4 + 0))
#define no_flag1 (*(undefined1 *)(_frec_4 + 2))
#define no_flag2 (*(undefined1 *)(_frec_4 + 3))
  uint got;
  
  no_flag1 = flag1 == 0;
  rec = func_symx;
  no_flag2 = flag2 == 0;
  got = write_bytes(g_reg_file,(char *)&rec,4);
  if (got == 0xffffffff) {
    fatal_error(0xce7);
  }
  return;
#undef rec
#undef no_flag1
#undef no_flag2
}



