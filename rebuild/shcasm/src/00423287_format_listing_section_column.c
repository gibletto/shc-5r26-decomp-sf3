#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x10b2c))
#undef g_listing_section_field
#define g_listing_section_field (*(char * *)(g_sd + 0x13140))


// entry: 00423287
// name : format_listing_section_column
// size : 104
// sig  : void __cdecl format_listing_section_column(short section_kind)


int __cdecl format_listing_section_column(short section_kind)

{
  unsigned char _frec_2c[44];
#define i (*(int *)(_frec_2c + 0))
#define section_name (*(char (*)[36])(_frec_2c + 4))
  int name_len;
  
  name_len = build_section_name(section_name,g_current_section,section_kind);
  for (i = 0; (i < 3 && (i < (char)name_len)); i = i + 1) {
    g_listing_section_field[i] = section_name[i];
  }
  return;
#undef i
#undef section_name
}
