#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_convert_table
#define g_convert_table (*(unsigned char * *)(g_sd + 0x18f8))


// entry: 004067e0
// name : convert_constant
// size : 187
// sig  : void convert_constant(uchar to_type, uchar from_type, uint * src, uint * dst)


int __cdecl convert_constant(uchar to_type,uchar from_type,uint *src,uint *dst)

{
  int to_class;
  int from_class;
  
  to_class = type_arith_class(to_type);
  from_class = type_arith_class(from_type);
  if (*(code **)((&g_convert_table)[from_class] + to_class * 4) == 0) {
    *dst = *src;
    if (to_class == 3) {
      dst[1] = src[1];
    }
    if (to_class == 4) {
      dst[1] = src[1];
      dst[2] = src[2];
    }
  }
  else {
    (**(code **)((&g_convert_table)[from_class] + to_class * 4))(src,dst);
  }
  if ((to_type & 0xf8) == 0) {
    if ((((to_type & 0xe0) == 0) && ((to_type & 4) != 0)) || ((*dst & 0x80) == 0)) {
      *dst = *dst & 0xff;
    }
    else {
      *dst = *dst | 0xffffff00;
    }
  }
  if ((to_type & 0xf8) == 8) {
    if ((((to_type & 0xe0) != 0) || ((to_type & 4) == 0)) && ((*dst & 0x8000) != 0)) {
      *dst = *dst | 0xffff0000;
      return;
    }
    *dst = *dst & 0xffff;
  }
  return;
}



