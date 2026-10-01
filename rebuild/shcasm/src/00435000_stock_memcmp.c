#include "decls.h"
#include "imports.h"

// entry: 00435000
// name : stock_memcmp
// size : 31
// sig  : int stock_memcmp(uchar * buf1, uchar * buf2, int count)


int __cdecl stock_memcmp(uchar *buf1,uchar *buf2,int count)

{
  int result;
  bool below;
  bool equal;
  
  below = false;
  result = 0;
  equal = true;
  if (count != 0) {
    do {
      if (count == 0) break;
      count = count + -1;
      below = *buf1 < *buf2;
      equal = *buf1 == *buf2;
      buf1 = buf1 + 1;
      buf2 = buf2 + 1;
    } while (equal);
    if (!equal) {
      result = (1 - (uint)below) - (uint)(below != 0);
    }
  }
  return result;
}



