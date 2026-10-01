#include "decls.h"
#include "imports.h"

// entry: 004021ec
// name : append_object_record_long
// size : 59
// sig  : int append_object_record_long(int value, short tag)


int __cdecl append_object_record_long(int value,short tag)

{
  unsigned char _frec_8[8];
#define long_be (*(uint *)(_frec_8 + 0))
  
  store_u32_big_endian((uint *)&value,&long_be);
  append_object_record_bytes((uchar *)&long_be,4,(int)tag);
  return 4;
#undef long_be
}



