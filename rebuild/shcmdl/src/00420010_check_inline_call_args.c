#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00420010
// name : check_inline_call_args
// size : 227
// sig  : int check_inline_call_args(il_node * call)


int __cdecl check_inline_call_args(il_node *call)

{
  byte param_kind;
  byte arg_kind;
  int nargs;
  il_node *arg;
  short *param;
  byte arg_type;
  short callee;
  il_op op;
  byte param_type;
  il_node *scan;
  
  callee = call->child->symx;
  nargs = 0;
  arg = call->child->next->child;
  scan = arg;
  op = arg->op;
  while (op != IL_E_ARG) {
    nargs = nargs + 1;
    scan = scan->next;
    op = scan->op;
  }
  if (nargs == *(char *)((int)g_symtab[callee].info + 6)) {
    if (arg->op != IL_E_ARG) {
      param = (g_symtab[callee].inline_body)->params;
      do {
        arg_type = arg->type;
        param_type = g_symtab[*param].type;
        param_kind = param_type & 0xe0;
        if (((((param_kind != 0) && (param_kind != 0x20)) && ((param_type & 0xf8) != 0x40)) ||
            (((arg_kind = arg_type & 0xe0, arg_kind != 0 && (arg_kind != 0x20)) &&
             (((arg_type & 0xf8) != 0x40 && ((arg_kind != 0x80 && ((arg_type & 0xf8) != 0x48))))))))
           && ((param_kind != 0x60 ||
               (((arg_type & 0xe0) != 0x60 || (((arg_type ^ param_type) & 0xfc) != 0)))))) {
          return -2;
        }
        arg = arg->next;
        param = param + 1;
      } while (arg->op != IL_E_ARG);
    }
    return 1;
  }
  return -1;
}



