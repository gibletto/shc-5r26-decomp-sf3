#include "decls.h"
#include "imports.h"

// entry: 0043ee10
// name : stock_strcpy
// size : 134
// sig  : char * stock_strcpy(char * dest, char * source)


/* Library Function - Multiple Matches With Different Base Names
    __mbscpy
    _strcpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl stock_strcpy(char *dest,char *source)

{
  uint uVar1;
  uint *dst;
  byte ch;
  uint chunk;
  
  dst = (uint *)dest;
  while (((uint)source & 3) != 0) {
    ch = (byte)*(uint *)source;
    uVar1 = (uint)ch;
    source = (char *)((int)source + 1);
    if (ch == 0) goto LAB_0043eef0;
    *(byte *)dst = ch;
    dst = (uint *)((int)dst + 1);
  }
  do {
    chunk = *(uint *)source;
    uVar1 = *(uint *)source;
    source = (char *)((int)source + 4);
    if (((chunk ^ 0xffffffff ^ chunk + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar1 == '\0') {
LAB_0043eef0:
        *(byte *)dst = (byte)uVar1;
        return dest;
      }
      if ((char)(uVar1 >> 8) == '\0') {
        *(short *)dst = (short)uVar1;
        return dest;
      }
      if ((uVar1 & 0xff0000) == 0) {
        *(short *)dst = (short)uVar1;
        *(byte *)((int)dst + 2) = 0;
        return dest;
      }
      if ((uVar1 & 0xff000000) == 0) {
        *dst = uVar1;
        return dest;
      }
    }
    *dst = uVar1;
    dst = dst + 1;
  } while( true );
}



