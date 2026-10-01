#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042b1e0
// name : make_new_label_number
// size : 62
// sig  : short make_new_label_number(void)


short __cdecl make_new_label_number(void)

{
  g_request->label_count = g_request->label_count + 1;
  if (0x7fff < g_request->label_count) {
    report_codegen_message(0xbc8,1,0,0,(char *)0x0);
  }
  return (short)g_request->label_count;
}



