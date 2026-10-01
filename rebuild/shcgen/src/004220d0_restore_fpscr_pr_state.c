#include "decls.h"
#include "imports.h"

// entry: 004220d0
// name : restore_fpscr_pr_state
// size : 14
// sig  : void restore_fpscr_pr_state(void)


int __cdecl restore_fpscr_pr_state(void)

{
  g_fpscr_pr = *(char *)(g_fpscr_pr_stack + 4);
  return;
}



