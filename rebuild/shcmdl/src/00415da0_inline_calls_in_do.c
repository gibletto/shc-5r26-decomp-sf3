#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_call_list
#define g_inline_call_list (*(inline_group * *)(g_sd + 0xdeb8))
#undef g_inline_loop
#define g_inline_loop (*(il_node * *)(g_sd + 0xde54))


// entry: 00415da0
// name : inline_calls_in_do
// size : 194
// sig  : void inline_calls_in_do(il_node * stmt)


int __cdecl inline_calls_in_do(il_node *stmt)

{
  inline_call *cand;
  il_node *last;
  inline_group *group;
  short saved_label;
  il_node *saved_loop;
  
  saved_loop = g_inline_loop;
  saved_label = g_inline_continue_label;
  g_inline_continue_label = 0;
  g_inline_loop = (il_node *)0x0;
  g_inline_call_list = (inline_group *)0x0;
  g_inline_cond_depth = 0;
  find_inline_calls(stmt->child->next);
  group = (inline_group *)0x0;
  if (g_inline_call_list != (inline_group *)0x0) {
    g_inline_loop = stmt;
    group = g_inline_call_list;
  }
  expand_inline_calls_in_stmt(stmt->child);
  if (group != (inline_group *)0x0) {
    if (stmt->child->op != IL_BLOCK) {
      wrap_stmt_in_scope(stmt->child);
    }
    last = last_operand(stmt->child);
    for (cand = group->calls; cand != (inline_call *)0x0; cand = cand->next) {
      expand_inline_call(cand,last);
    }
    free_inline_group(group);
  }
  g_inline_loop = saved_loop;
  g_inline_continue_label = saved_label;
  return;
}



