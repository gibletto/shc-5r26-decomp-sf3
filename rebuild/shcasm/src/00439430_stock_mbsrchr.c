#include "decls.h"
#include "imports.h"

// entry: 00439430
// name : stock_mbsrchr
// size : 110
// sig  : char * __cdecl stock_mbsrchr(uchar *str,uint ch)


char * __cdecl stock_mbsrchr(uchar *str,uint ch)

{
  byte *found;
  char *result;
  byte *next;
  byte cur_ch;
  
  found = (byte *)0x0;
  if (stock_mbcodepage == 0) {
    result = _strrchr((char *)str,ch);
    return result;
  }
  do {
    cur_ch = *str;
    if ((*(byte *)((int)&stock_mbctype + cur_ch + 1) & 4) == 0) {
      next = str;
      if (cur_ch == ch) {
LAB_00439490:
        found = str;
        next = found;
      }
    }
    else {
      next = str + 1;
      if (str[1] == 0) {
        str = next;
        if (found == (byte *)0x0) goto LAB_00439490;
      }
      else if (CONCAT11(cur_ch,str[1]) == ch) {
        found = str;
      }
    }
    str = next + 1;
    if (*next == 0) {
      return (char *)found;
    }
  } while( true );
}
