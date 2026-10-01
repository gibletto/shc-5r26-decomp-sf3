#include "decls.h"
#include "imports.h"

// entry: 00402180
// name : append_object_record_byte
// size : 49
// sig  : int append_object_record_byte(uchar value, short tag)


int __cdecl append_object_record_byte(uchar value,short tag)

{
  unsigned char _frec_8[8];
#define byte_buf (*(uchar (*)[4])(_frec_8 + 0))
  
  byte_buf[0] = value;
  append_object_record_bytes(byte_buf,1,(int)tag);
  return 1;
#undef byte_buf
}



