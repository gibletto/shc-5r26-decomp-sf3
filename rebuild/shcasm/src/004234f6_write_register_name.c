#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_DAT_004419d0
#define PTR_DAT_004419d0 (*(unsigned char * *)(g_sd + 0x69d0))


// entry: 004234f6
// name : write_register_name
// size : 38
// sig  : void __cdecl write_register_name(short stream,short regno)


int __cdecl write_register_name(short stream,short regno)

{
  put_text_at_column(stream,(&PTR_DAT_004419d0)[regno],2);
  return;
}
