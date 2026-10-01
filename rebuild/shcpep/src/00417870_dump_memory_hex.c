#include "decls.h"
#include "imports.h"

// entry: 00417870
// name : dump_memory_hex
// size : 118
// sig  : int dump_memory_hex(uchar * addr, char * title, int size)


int __cdecl dump_memory_hex(uchar *addr,char *title,int size)

{
  int iVar1;
  int lines_left;
  int remaining;
  
  if (addr != (uchar *)0x0) {
    _printf(s__08lx__00427c04,addr);
    _printf(s_sp_pct_s_nl_00427bfc,title);
    iVar1 = (int)(size + -1 + (size + -1 >> 0x1f & 0xfU)) >> 4;
    lines_left = iVar1 + 1;
    if (0 < lines_left) {
      do {
        remaining = size + -0x10;
        if (-1 < remaining) {
          size = 0x10;
        }
        iVar1 = dump_hex_line(size,addr);
        lines_left = lines_left + -1;
        size = remaining;
        addr = addr + 0x10;
      } while (lines_left != 0);
    }
    return iVar1;
  }
  _printf(s_str_00427c0c);
  return 0;
}



