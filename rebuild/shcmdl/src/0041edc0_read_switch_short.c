#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_switch_file
#define g_switch_file (*(FILE * *)(g_sd + 0x1e734))


// entry: 0041edc0
// name : read_switch_short
// size : 34
// sig  : short read_switch_short(void)


short __cdecl read_switch_short(void)

{
  unsigned char _frec_2[2];
#define val_read (*(short *)(_frec_2 + 0))
  
  read_or_fail(g_switch_file,(char *)&val_read,2);
  return val_read;
#undef val_read
}



