#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040b040
// name : read_symbol_name
// size : 75
// sig  : char * read_symbol_name(uchar len)


char * __cdecl read_symbol_name(uchar len)

{
  char *buf;
  
  if (len != '\0') {
    buf = stock_calloc(1,len + 1);
    if (buf != (char *)0x0) {
      read_or_fail(g_sym_file,buf,(uint)len);
      return buf;
    }
    fatal_error(0xbcd);
  }
  return (char *)0x0;
}



