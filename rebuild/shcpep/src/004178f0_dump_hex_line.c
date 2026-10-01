#include "decls.h"
#include "imports.h"

// entry: 004178f0
// name : dump_hex_line
// size : 161
// sig  : int dump_hex_line(int count, uchar * bytes)


int __cdecl dump_hex_line(int count,uchar *bytes)

{
  int i;
  byte ch;
  byte *p;
  
  i = 0;
  if (0 < count) {
    do {
      p = bytes + i;
      i = i + 1;
      _printf(s__02x_00427c58,(uint)*p);
    } while (i < count);
  }
  if (i < 0x12) {
    i = 0x12 - i;
    do {
      _printf(s_sp_sp_sp_00427c54);
      i = i + -1;
    } while (i != 0);
  }
  i = 0;
  if (0 < count) {
    do {
      ch = bytes[i];
      if ((((ch < 0x20) || (0x5f < ch)) && ((ch < 0xa1 || (0xdf < ch)))) &&
         ((ch < 0x61 || (0x7d < ch)))) {
        _printf(s_dot_00427c4c);
      }
      else {
        _printf(s_pct_c_00427c50,(uint)ch);
      }
      i = i + 1;
    } while (i < count);
  }
  _printf(s_nl_00427c48);
  return 0;
}



