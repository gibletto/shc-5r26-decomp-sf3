#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))


// entry: 00408880
// name : write_asa_symbol_name
// size : 105
// sig  : void write_asa_symbol_name(char * name)


int __cdecl write_asa_symbol_name(char *name)

{
  unsigned char _frec_1[1];
#define len_byte (*(byte *)(_frec_1 + 0))
  int len;
  
  if (name != (char *)0x0) {
    len = string_length(name);
    len_byte = (byte)len;
    write_bytes_or_fail((char *)&len_byte,1,g_asa_file);
    write_bytes_or_fail(name,(uint)len_byte,g_asa_file);
    return;
  }
  len_byte = 0;
  write_bytes_or_fail((char *)&len_byte,1,g_asa_file);
  return;
#undef len_byte
}



