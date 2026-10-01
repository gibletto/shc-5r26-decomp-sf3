#include "decls.h"
#include "imports.h"

// entry: 00402227
// name : append_sized_value_to_data_record
// size : 155
// sig  : int append_sized_value_to_data_record(uchar * value, short size_code)


int __cdecl append_sized_value_to_data_record(uchar *value,short size_code)

{
  undefined4 written;
  
  if (size_code == 0) {
    append_object_record_byte(*value,0x1c);
    written = 1;
  }
  else if (size_code == 1) {
    append_object_record_word((int)*(short *)value,0x1c);
    written = 2;
  }
  else if (size_code == 2) {
    append_object_record_long(*(int *)value,0x1c);
    written = 4;
  }
  return written;
}



