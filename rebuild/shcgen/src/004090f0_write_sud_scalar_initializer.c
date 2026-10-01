#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_int_file
#define g_int_file (*(FILE * *)(g_sd + 0x1f98c))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004090f0
// name : write_sud_scalar_initializer
// size : 817
// sig  : int write_sud_scalar_initializer(ushort elem_type)


int __cdecl write_sud_scalar_initializer(ushort elem_type)

{
  unsigned char _frec_1c[28];
#define local_1c (*(char (*)[2])(_frec_1c + 0))
#define short_val (*(undefined2 *)(_frec_1c + 2))
#define str_length (*(ushort *)(_frec_1c + 4))
#define ref_symx (*(ushort *)(_frec_1c + 6))
#define reloc_flag (*(char (*)[4])(_frec_1c + 8))
#define int_val (*(undefined2 *)(_frec_1c + 12))
#define str_size (*(uint *)(_frec_1c + 16))
#define dbl_first (*(char (*)[4])(_frec_1c + 20))
#define dbl_second (*(char (*)[4])(_frec_1c + 24))
  char *bytes;
  
  str_size = 0;
  reloc_flag[0] = '\0';
  reloc_flag[1] = '\0';
  reloc_flag[2] = '\0';
  reloc_flag[3] = '\0';
  switch(elem_type & 0xf8) {
  case 0:
    read_bytes_or_fail((char *)&int_val,4,g_int_file);
    local_1c[0] = (char)int_val;
    append_sud_bytes(local_1c,1,'\0');
    append_sud_bytes(reloc_flag,4,'\0');
    advance_sud_location_counter(1);
    return 0;
  case 8:
    read_bytes_or_fail((char *)&int_val,4,g_int_file);
    short_val = int_val;
    append_sud_bytes((char *)&short_val,2,'\0');
    append_sud_bytes(reloc_flag,4,'\0');
    advance_sud_location_counter(2);
    return 0;
  case 0x10:
  case 0x18:
  case 0x28:
    read_bytes_or_fail((char *)&int_val,4,g_int_file);
    append_sud_bytes((char *)&int_val,4,'\0');
    append_sud_bytes(reloc_flag,4,'\0');
    advance_sud_location_counter(4);
    return 0;
  case 0x30:
  case 0x38:
    read_bytes_or_fail(dbl_first,8,g_int_file);
    if (g_request->unknown_028[2] == '\0') {
      append_sud_bytes(dbl_first,4,'\0');
      append_sud_bytes(reloc_flag,4,'\0');
      bytes = dbl_second;
    }
    else {
      append_sud_bytes(dbl_second,4,'\0');
      append_sud_bytes(reloc_flag,4,'\0');
      bytes = dbl_first;
    }
    append_sud_bytes(bytes,4,'\0');
    append_sud_bytes(reloc_flag,4,'\0');
    advance_sud_location_counter(8);
    return 0;
  case 0x40:
    read_bytes_or_fail((char *)&ref_symx,2,g_int_file);
    ref_symx = ref_symx + 0xb6;
    if ((g_symbol_table[ref_symx].type & 0xf8) == 0x48) {
      g_symbol_table[ref_symx].attr = g_symbol_table[ref_symx].attr & 0x7f;
    }
    if ((g_symbol_table[ref_symx].flags & 0x10) != 0) {
      report_codegen_message(0x7e4,1,0,0,g_symbol_table[ref_symx].name);
    }
    read_bytes_or_fail((char *)&int_val,4,g_int_file);
    reloc_flag[0] = '\x01';
    reloc_flag[1] = '\0';
    reloc_flag[2] = '\0';
    reloc_flag[3] = '\0';
    append_sud_bytes((char *)&int_val,4,'\0');
    append_sud_bytes(reloc_flag,4,'\0');
    append_sud_bytes((char *)&ref_symx,2,'\0');
    g_symbol_table[ref_symx].flags = g_symbol_table[ref_symx].flags | 8;
    advance_sud_location_counter(4);
    return 0;
  case 0x98:
    local_1c[1] = 0xb;
    append_sud_bytes(local_1c + 1,1,'\0');
    read_bytes_or_fail((char *)&str_length,2,g_int_file);
    str_size = (uint)str_length;
    append_sud_bytes((char *)&str_size,4,'\0');
    read_bytes_or_fail(&g_sud_string_buffer,str_size,g_int_file);
    append_sud_bytes(&g_sud_string_buffer,str_size,'\0');
    advance_sud_location_counter(str_size);
  }
  return 0;
#undef local_1c
#undef short_val
#undef str_length
#undef ref_symx
#undef reloc_flag
#undef int_val
#undef str_size
#undef dbl_first
#undef dbl_second
}



