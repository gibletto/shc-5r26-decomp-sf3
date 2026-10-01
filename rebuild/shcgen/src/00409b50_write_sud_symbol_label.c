#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sud_const_dc_count_field
#define g_sud_const_dc_count_field (*(char * *)(g_sd + 0x1fe58))
#undef g_sud_data_dc_count_field
#define g_sud_data_dc_count_field (*(char * *)(g_sd + 0x1fa1c))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00409b50
// name : write_sud_symbol_label
// size : 177
// sig  : void write_sud_symbol_label(void)


int __cdecl write_sud_symbol_label(void)

{
  unsigned char _frec_c[12];
#define rec_tag (*(char *)(_frec_c + 0))
#define symx_lo (*(undefined1 *)(_frec_c + 1))
#define symx_hi (*(undefined1 *)(_frec_c + 2))
#define rec_zero (*(undefined1 (*)[5])(_frec_c + 3))
#define zero_dword (*(undefined4 *)(_frec_c + 8))
  short kind;
  int byte_i;
  ushort i;
  uint uVar1;
  
  zero_dword = 0;
  uVar1 = (int)g_sud_symx >> 0x1f;
  if (((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 1) == 0) ||
     ((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 2) != 0)) {
    g_sud_data_dc_count_field = (char *)0x0;
    g_sud_data_dc_count = 0;
    kind = 8;
  }
  else {
    g_sud_const_dc_count_field = (char *)0x0;
    g_sud_const_dc_count = 0;
    kind = 7;
  }
  write_asa_record(kind,g_sud_symx);
  symx_lo = (undefined1)g_sud_symx;
  rec_tag = '\x18';
  symx_hi = (*(unsigned char *)((char *)&g_sud_symx + 1));
  i = 0;
  do {
    byte_i = (int)(short)i;
    i = i + 1;
    rec_zero[byte_i] = *(undefined1 *)((int)&zero_dword + byte_i);
  } while (i < 4);
  append_sud_bytes(&rec_tag,7,'\0');
  return;
#undef rec_tag
#undef symx_lo
#undef symx_hi
#undef rec_zero
#undef zero_dword
}



