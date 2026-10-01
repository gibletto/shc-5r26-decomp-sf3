#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00408040
// name : write_asa_data_symbol_record
// size : 312
// sig  : void write_asa_data_symbol_record(short kind, short symx)


int __cdecl write_asa_data_symbol_record(short kind,short symx)

{
  unsigned char _frec_5[5];
#define rec_kind (*(byte *)(_frec_5 + 0))
#define sym_loc (*(uint *)(_frec_5 + 1))
  
  if ((g_symbol_table[symx].attr & 1) == 0) {
    if ((g_symbol_table[symx].attr & 2) == 0) {
      if (kind == 7) {
        sym_loc = g_current_section->const_loc;
      }
      else if (kind == 8) {
        sym_loc = g_current_section->data_loc;
      }
      else if (kind == 9) {
        sym_loc = g_current_section->bss_loc;
      }
    }
    else {
      sym_loc = g_current_section->data_loc;
    }
  }
  else {
    sym_loc = g_current_section->data_loc;
  }
  rec_kind = (byte)kind;
  if (g_symbol_table[symx].sclass == '\x01') {
    rec_kind = (byte)kind | 0x80;
  }
  write_bytes_or_fail((char *)&rec_kind,1,g_asa_file);
  write_bytes_or_fail((char *)&symx,2,g_asa_file);
  write_bytes_or_fail((char *)g_current_section,2,g_asa_file);
  write_bytes_or_fail((char *)&sym_loc,4,g_asa_file);
  write_asa_symbol_name(g_symbol_table[symx].name);
  write_asa_attribute_byte(g_symbol_table[symx].attr);
  write_bytes_or_fail(&g_symbol_table[symx].reg,1,g_asa_file);
  return;
#undef rec_kind
#undef sym_loc
}



