#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_deref_count_cursor
#define g_deref_count_cursor (*(short * *)(g_sd + 0x1fa18))


// entry: 0041bf60
// name : reset_r0_variable_candidates
// size : 70
// sig  : void reset_r0_variable_candidates(void)


/* WARNING: Removing unreachable block (ram,0x0041bf73) */

int __cdecl reset_r0_variable_candidates(void)

{
  g_r0_variable = 0;
  g_deref_total = 0;
  g_deref_count_cursor = &g_deref_counts;
  g_r0_used = 0;
  return;
}



