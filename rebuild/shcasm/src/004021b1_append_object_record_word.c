#include "decls.h"
#include "imports.h"

// entry: 004021b1
// name : append_object_record_word
// size : 59
// sig  : int append_object_record_word(int value, short tag)


int __cdecl append_object_record_word(int value,short tag)

{
  unsigned char _frec_8[8];
#define word_be (*(ushort (*)[2])(_frec_8 + 0))
  
  store_u16_big_endian((ushort *)&value,word_be);
  append_object_record_bytes((uchar *)word_be,2,(int)tag);
  return 2;
#undef word_be
}



