#include "decls.h"
#include "imports.h"

// entry: 0043ed90
// name : stock_strlen
// size : 119
// sig  : uint stock_strlen(char * str)


uint __cdecl stock_strlen(char *str)

{
  uint *p;
  uint *chunk_ptr;
  uint chunk;
  
  p = (uint *)str;
  do {
    if (((uint)p & 3) == 0) goto LAB_0043edac;
    chunk = *p;
    p = (uint *)((int)p + 1);
  } while ((char)chunk != '\0');
LAB_0043eddf:
  return (uint)((int)p + (-1 - (int)str));
LAB_0043edac:
  do {
    do {
      chunk_ptr = p;
      p = chunk_ptr + 1;
    } while (((*chunk_ptr ^ 0xffffffff ^ *chunk_ptr + 0x7efefeff) & 0x81010100) == 0);
    chunk = *chunk_ptr;
    if ((char)chunk == '\0') {
      return (int)chunk_ptr - (int)str;
    }
    if ((char)(chunk >> 8) == '\0') {
      return (uint)((int)chunk_ptr + (1 - (int)str));
    }
    if ((chunk & 0xff0000) == 0) {
      return (uint)((int)chunk_ptr + (2 - (int)str));
    }
  } while ((chunk & 0xff000000) != 0);
  goto LAB_0043eddf;
}



