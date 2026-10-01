#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00412e9e
// name : emit_object_record_kind_table
// size : 81
// sig  : void emit_object_record_kind_table(void)


int __cdecl emit_object_record_kind_table(void)

{
  if (g_current_request->code == 1) {
    append_object_record_bytes
              (&g_record_kind_table_debug + ((g_current_request->debug != 0) - 1 & 0x20),0x1e,0);
  }
  return;
}
