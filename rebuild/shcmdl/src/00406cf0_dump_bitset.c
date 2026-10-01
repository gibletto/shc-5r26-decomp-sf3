#include "decls.h"
#include "imports.h"

// entry: 00406cf0
// name : dump_bitset
// size : 112
// sig  : void dump_bitset(uint * bits, int nwords, char * title)


int __cdecl dump_bitset(uint *bits,int nwords,char *title)

{
  char bit;
  int i;
  
  FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s______s_____00433ed0,title);
  if (0 < nwords) {
    do {
      i = 0;
      do {
        bit = (char)i;
        i = i + 1;
        FID_conflict__fwprintf
                  ((FILE *)&stock_stdout,(wchar_t *)&g_str_percent_1d,
                   (uint)((1 << (0x1fU - bit & 0x1f) & *bits) != 0));
      } while (i < 0x20);
      bits = bits + 1;
      FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)&g_str_newline);
      nwords = nwords + -1;
    } while (nwords != 0);
  }
  return;
}



