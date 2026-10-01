#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_int_file
#define g_int_file (*(FILE * *)(g_sd + 0x1f98c))


// entry: 0040a2e0
// name : skip_int_close_marker
// size : 41
// sig  : void skip_int_close_marker(void)


int __cdecl skip_int_close_marker(void)

{
  unsigned char _frec_1[1];
#define marker (*(char *)(_frec_1 + 0))
  
  read_bytes_or_fail(&marker,1,g_int_file);
  if (marker == -0x10) {
    g_int_nesting_depth = g_int_nesting_depth + -1;
  }
  return;
#undef marker
}



