#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00420130
// name : new_label_number
// size : 44
// sig  : int new_label_number(void)


int __cdecl new_label_number(void)

{
  int *counter;
  int rc;
  
  counter = &g_options->label_count;
  if (*counter < 0x7fff) {
    g_inline_new_labels = g_inline_new_labels + 1;
    *counter = *counter + 1;
    return CONCAT22((short)((uint)g_options >> 0x10),(short)g_options->label_count);
  }
  rc = abort_function_optimization();
  return rc;
}



