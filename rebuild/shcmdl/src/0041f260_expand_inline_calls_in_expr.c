#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_call_list
#define g_inline_call_list (*(inline_group * *)(g_sd + 0xdeb8))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041f260
// name : expand_inline_calls_in_expr
// size : 167
// sig  : void expand_inline_calls_in_expr(il_node * expr, il_node * stmt)


int __cdecl expand_inline_calls_in_expr(il_node *expr,il_node *stmt)

{
  inline_call *cand;
  il_node *anchor;
  
  g_inline_call_list = (inline_group *)0x0;
  g_inline_cond_depth = 0;
  find_inline_calls(expr);
  if (g_inline_call_list != (inline_group *)0x0) {
    anchor = find_enclosing_stmt(stmt);
    for (cand = g_inline_call_list->calls; cand != (inline_call *)0x0; cand = cand->next) {
      g_inline_new_symbols = 0;
      g_inline_new_labels = 0;
      expand_inline_call(cand,anchor);
      g_symtab[cand->callee].inline_symbols = g_inline_new_symbols;
      g_symtab[cand->callee].inline_labels = g_inline_new_labels;
    }
    free_inline_group(g_inline_call_list);
  }
  return;
}



