#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_fold_warnings
#define g_fold_warnings (*(unsigned short *)(g_sd + 0x26ef4))


// entry: 004068a0
// name : report_fold_warnings
// size : 100
// sig  : void report_fold_warnings(il_node * node)


int __cdecl report_fold_warnings(il_node *node)

{
  if ((g_fold_warnings & 2) != 0) {
    report_message(0x4b1,node,(char *)0x0);
  }
  if ((g_fold_warnings & 4) != 0) {
    report_message(0x4b0,node,(char *)0x0);
  }
  if ((g_fold_warnings & 8) != 0) {
    report_message(0x9c5,node,(char *)0x0);
  }
  g_fold_warnings = 0;
  return;
}



