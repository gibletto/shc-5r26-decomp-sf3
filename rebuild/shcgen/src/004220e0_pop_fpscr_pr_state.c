#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_fpscr_pr_stack
#define g_fpscr_pr_stack (*(int * *)(g_sd + 0x1f984))


// entry: 004220e0
// name : pop_fpscr_pr_state
// size : 26
// sig  : void pop_fpscr_pr_state(void)


int __cdecl pop_fpscr_pr_state(void)

{
  undefined4 *ptr;
  
  ptr = g_fpscr_pr_stack;
  g_fpscr_pr_stack = (undefined4 *)*g_fpscr_pr_stack;
  pool_free(ptr,8);
  return;
}



