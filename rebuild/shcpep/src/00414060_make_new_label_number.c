#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned int *)(g_sd + 0x6d64))


// entry: 00414060
// name : make_new_label_number
// size : 104
// sig  : int make_new_label_number(void)


int __cdecl make_new_label_number(void)

{
  int labno;
  
  if ((g_stage_flags & 8) != 0) {
    _printf(s_dc_mklab_start__g_labno___ld_00427878,(int)g_last_labno);
  }
  if ((g_last_labno + 1 < 0x8000) && (g_label_alloc_disabled != 1)) {
    g_last_labno = g_last_labno + 1;
    labno = (int)g_last_labno;
  }
  else {
    labno = 0;
  }
  if ((g_stage_flags & 8) != 0) {
    _printf(s_dc_mklab_end__labno___ld_0042785c,labno);
  }
  return labno;
}



