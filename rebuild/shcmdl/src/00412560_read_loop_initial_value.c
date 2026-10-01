#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00412560
// name : read_loop_initial_value
// size : 48
// sig  : void read_loop_initial_value(il_node * def)


int __cdecl read_loop_initial_value(il_node *def)

{
  il_node *rhs;
  
  if (((def->op == IL_ASSIGN) && (rhs = def->child->next, rhs->op == IL_CONST)) &&
     ((rhs->type & 0xe0) == 0)) {
    g_loop_init = rhs->val;
    return;
  }
  g_cur_loop->flag = g_cur_loop->flag | 0x100;
  return;
}



