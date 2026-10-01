#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 00404420
// name : write_symbol_init_info
// size : 89
// sig  : void write_symbol_init_info(symbol * sym)


int __cdecl write_symbol_init_info(symbol *sym)

{
  uint size;
  uchar *flags_byte;
  
  flags_byte = &sym->ext_flags;
  write_symbol_bytes(g_sym_file,(char *)flags_byte,1);
  if ((*flags_byte & 2) != 0) {
    if ((*flags_byte & 4) == 0) {
      size = 4;
    }
    else {
      size = 2;
    }
    write_symbol_bytes(g_sym_file,(char *)&sym->ext_30,size);
  }
  if ((*flags_byte & 1) != 0) {
    write_symbol_bytes(g_sym_file,(char *)&sym->ext_34,4);
  }
  return;
}



