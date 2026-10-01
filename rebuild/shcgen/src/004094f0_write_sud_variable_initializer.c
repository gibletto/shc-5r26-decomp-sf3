#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_int_file
#define g_int_file (*(FILE * *)(g_sd + 0x1f98c))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004094f0
// name : write_sud_variable_initializer
// size : 273
// sig  : int write_sud_variable_initializer(ushort first_type)


int __cdecl write_sud_variable_initializer(ushort first_type)

{
  unsigned char _frec_1[1];
#define close_marker (*(char *)(_frec_1 + 0))
  byte type_class;
  short size_code;
  int result;
  uint uVar1;
  
  uVar1 = (int)g_sud_symx >> 0x1f;
  type_class = g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 0xe0;
  if ((type_class != 0x60) && (type_class != 0x80)) {
    align_sud_location_counter();
    set_symbol_address_from_location_counter();
    write_sud_symbol_label();
    g_sud_dc_header = 8;
    size_code = dc_size_code_of_type((uchar)first_type);
    DAT_0045e4b9 = (byte)size_code;
    if (DAT_0045e4b9 < 2) {
      g_sud_dc_unit = 1;
    }
    else if (DAT_0045e4b9 == 2) {
      if (((first_type & 0xf8) == 0x30) || ((first_type & 0xf8) == 0x38)) {
        g_sud_dc_unit = 2;
      }
      else {
        g_sud_dc_unit = 1;
      }
    }
    append_sud_bytes(&g_sud_dc_header,2,'\0');
    append_sud_bytes((char *)&g_sud_dc_unit,4,'\0');
    result = write_sud_scalar_initializer(first_type);
    read_bytes_or_fail(&close_marker,1,g_int_file);
    return result;
  }
  result = write_sud_aggregate_initializer(first_type);
  return result;
#undef close_marker
}



