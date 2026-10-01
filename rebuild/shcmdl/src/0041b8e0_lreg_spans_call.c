#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_call_list
#define g_call_list (*(node_cell * *)(g_sd + 0x164b0))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041b8e0
// name : lreg_spans_call
// size : 126
// sig  : int lreg_spans_call(lreg * lr)


int __cdecl lreg_spans_call(lreg *lr)

{
  int is_mac;
  node_cell *call;
  il_node *callee;
  ushort pp;
  undefined4 *range;
  short symx;
  
  call = g_call_list;
  do {
    if (call == (node_cell *)0x0) {
      return 0;
    }
    for (range = lr->life; range != (undefined4 *)0x0; range = (undefined4 *)*range) {
      pp = call->node->pp;
      if (((*(ushort *)(range[1] + 8) <= pp) && (pp <= *(ushort *)(range[1] + 10))) &&
         ((callee = call->node->child, callee->op != IL_ID ||
          ((symx = callee->symx, -1 < symx &&
           (is_mac = is_mac_builtin_name(g_symtab[symx].name), is_mac == 0)))))) {
        return 1;
      }
    }
    call = call->next;
  } while( true );
}



