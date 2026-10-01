#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_nhandle
#define stock_nhandle (*(unsigned int *)(g_sd + 0x15ba4))


// entry: 00439750
// name : stock_isatty
// size : 42
// sig  : uchar stock_isatty(uint fh)


uchar __cdecl stock_isatty(uint fh)

{
  if (stock_nhandle <= fh) {
    return '\0';
  }
  return *(byte *)(*(int *)((int)&stock_pioinfo + ((int)(fh & 0xffffffe7) >> 3)) + 4 +
                  (fh & 0x1f) * 8) & 0x40;
}



