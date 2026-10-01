#include "decls.h"
#include "imports.h"

// entry: 0041d050
// name : select_bitfield_routine
// size : 43
// sig  : short select_bitfield_routine(short selector, uchar type)


short __cdecl select_bitfield_routine(short selector,uchar type)

{
  int size_class;
  
  size_class = (int)(short)(char)((type & 0x1c) >> 2);
  if (selector == 0x102) {
    return *(short *)(&g_bitfield_extract_routines + size_class * 4);
  }
  return *(short *)(&g_bitfield_store_routines + size_class * 4);
}



