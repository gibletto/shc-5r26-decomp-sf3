#include "decls.h"
#include "imports.h"

// entry: 004022cc
// name : append_sized_value_to_repeat_data_record
// size : 158
// sig  : int append_sized_value_to_repeat_data_record(int value, short size_code)


int __cdecl append_sized_value_to_repeat_data_record(int value,short size_code)

{
  undefined4 written;
  
  if (size_code == 0) {
    append_object_record_byte((uchar)value,0x9c);
    written = 1;
  }
  else if (size_code == 1) {
    append_object_record_word((int)(short)value,0x9c);
    written = 2;
  }
  else if (size_code == 2) {
    append_object_record_long(value,0x9c);
    written = 4;
  }
  return written;
}



