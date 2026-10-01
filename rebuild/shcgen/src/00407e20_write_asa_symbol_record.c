#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00407e20
// name : write_asa_symbol_record
// size : 182
// sig  : void write_asa_symbol_record(short kind, short symx)


int __cdecl write_asa_symbol_record(short kind,short symx)

{
  unsigned char _frec_1[1];
#define rec_kind (*(char *)(_frec_1 + 0))
  
  rec_kind = (char)kind;
  if ((kind == 1) && (g_symbol_table[symx].sclass == '\x01')) {
    rec_kind = -0x7f;
  }
  write_bytes_or_fail(&rec_kind,1,g_asa_file);
  write_bytes_or_fail((char *)&symx,2,g_asa_file);
  write_bytes_or_fail((char *)g_current_section,2,g_asa_file);
  write_bytes_or_fail((char *)&g_current_section->location,4,g_asa_file);
  if (kind == 5) {
    write_asa_symbol_name(g_symbol_table[symx].name);
  }
  return;
#undef rec_kind
}



