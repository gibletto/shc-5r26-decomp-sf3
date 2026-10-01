#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sud_const_dc_count_field
#define g_sud_const_dc_count_field (*(char * *)(g_sd + 0x1fe58))
#undef g_sud_data_dc_count_field
#define g_sud_data_dc_count_field (*(char * *)(g_sd + 0x1fa1c))
#undef g_sud_dc_header
#define g_sud_dc_header (*(char *)(g_sd + 0x1e4b8))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00409a50
// name : begin_sud_dc_record
// size : 247
// sig  : void begin_sud_dc_record(ushort elem_type)


int __cdecl begin_sud_dc_record(ushort elem_type)

{
  unsigned char _frec_8[8];
#define rec_header (*(char *)(_frec_8 + 0))
#define rec_size_code (*(byte *)(_frec_8 + 1))
#define rec_unit (*(undefined1 (*)[6])(_frec_8 + 2))
  short size_code;
  int byte_i;
  ushort i;
  uint uVar1;
  
  uVar1 = (int)g_sud_symx >> 0x1f;
  if (((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 1) == 0) ||
     ((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 2) != 0)) {
    g_sud_data_dc_count_field = (char *)0x0;
    g_sud_data_dc_count = 0;
  }
  else {
    g_sud_const_dc_count_field = (char *)0x0;
    g_sud_const_dc_count = 0;
  }
  if (elem_type != 0x98) {
    g_sud_dc_header = '\b';
    size_code = dc_size_code_of_type((uchar)elem_type);
    DAT_0045e4b9 = (byte)size_code;
    if (DAT_0045e4b9 < 2) {
      g_sud_dc_unit = 1;
    }
    else if (DAT_0045e4b9 == 2) {
      if (((elem_type & 0xf8) == 0x30) || ((elem_type & 0xf8) == 0x38)) {
        g_sud_dc_unit = 2;
      }
      else {
        g_sud_dc_unit = 1;
      }
    }
    rec_header = g_sud_dc_header;
    i = 0;
    do {
      byte_i = (int)(short)i;
      i = i + 1;
      rec_unit[byte_i] = *(undefined1 *)((int)&g_sud_dc_unit + byte_i);
    } while (i < 4);
    rec_size_code = DAT_0045e4b9;
    append_sud_bytes(&rec_header,6,'\x02');
  }
  return;
#undef rec_header
#undef rec_size_code
#undef rec_unit
}



