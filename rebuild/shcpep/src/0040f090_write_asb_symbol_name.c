#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))


// entry: 0040f090
// name : write_asb_symbol_name
// size : 132
// sig  : void write_asb_symbol_name(void)


int __cdecl write_asb_symbol_name(void)

{
  unsigned char _frec_1[1];
#define name_size (*(byte *)(_frec_1 + 0))
  int len;
  uint written;
  
  len = string_length(g_current_symbol->name);
  name_size = (byte)len;
  written = write_file_bytes(g_asb_output,(char *)&name_size,1);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  if (name_size != 0) {
    written = write_file_bytes(g_asb_output,g_current_symbol->name,(uint)name_size);
    if (written == 0xffffffff) {
      report_fatal_message(0,0,0xce7);
    }
  }
  return;
#undef name_size
}



