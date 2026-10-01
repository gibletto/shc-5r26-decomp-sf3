#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1e72c))


// entry: 00414570
// name : write_lreg_symbols
// size : 259
// sig  : void write_lreg_symbols(lreg * lr)


int __cdecl write_lreg_symbols(lreg *lr)

{
  unsigned char _frec_4[4];
#define cnt (*(ushort *)(_frec_4 + 0))
#define sym_index (*(short *)(_frec_4 + 2))
  short bound_symx;
  uint got;
  lreg *bound;
  
  sym_index = get_lreg_symx(lr);
  cnt = (ushort)(-1 < sym_index);
  if (lr->bind != (lreg *)0x0) {
    for (bound = lr->bind->bakbind; bound != (lreg *)0x0; bound = bound->bakbind) {
      bound_symx = get_lreg_symx(bound);
      if (0 < bound_symx) {
        cnt = cnt + 1;
      }
    }
  }
  got = write_bytes(g_reg_file,(char *)&cnt,2);
  if (got == 0xffffffff) {
    fatal_error(0xce7);
  }
  if (cnt != 0) {
    if ((0 < sym_index) && (got = write_bytes(g_reg_file,(char *)&sym_index,2), got == 0xffffffff))
    {
      fatal_error(0xce7);
    }
    for (bound = lr->bakbind; bound != (lreg *)0x0; bound = bound->bakbind) {
      sym_index = get_lreg_symx(bound);
      if ((0 < sym_index) && (got = write_bytes(g_reg_file,(char *)&sym_index,2), got == 0xffffffff)
         ) {
        fatal_error(0xce7);
      }
    }
  }
  return;
#undef cnt
#undef sym_index
}



