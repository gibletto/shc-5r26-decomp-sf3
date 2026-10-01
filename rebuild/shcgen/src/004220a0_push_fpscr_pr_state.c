#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_fpscr_pr_stack
#define g_fpscr_pr_stack (*(int * *)(g_sd + 0x1f984))


// entry: 004220a0
// name : push_fpscr_pr_state
// size : 33
// sig  : void push_fpscr_pr_state(void)


int __cdecl push_fpscr_pr_state(void)

{
  undefined4 *save;
  
  save = alloc_zeroed(8);
  *save = g_fpscr_pr_stack;
  g_fpscr_pr_stack = save;
  *(char *)(save + 1) = g_fpscr_pr;
  return;
}



