#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041f1a0
// name : call_arguments_use_stack
// size : 120
// sig  : int call_arguments_use_stack(gen_node * arg)


int __cdecl call_arguments_use_stack(gen_node *arg)

{
  int uses_stack;
  gen_node *operand;
  node_desc *desc;
  
  uses_stack = 0;
  if ((arg != (gen_node *)0x0) && (arg->op == IL_ARG)) {
    if (((g_request->cpu == 4) || ((arg->parent->type & 0xf8) != 0x30)) &&
       ((arg->parent->type & 0xe0) != 0x60)) {
      operand = arg->child;
      if (operand->op != IL_E_ARG) {
        while (((desc = operand->desc, (desc->flags2 & 8) == 0 || (desc->target_regs != 0)) ||
               (desc->ftarget_regs != 0))) {
          operand = operand->next;
          if (operand->op == IL_E_ARG) {
            return uses_stack;
          }
        }
        return 1;
      }
    }
    else {
      uses_stack = 1;
    }
  }
  return uses_stack;
}



