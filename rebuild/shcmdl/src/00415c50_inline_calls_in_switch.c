#include "decls.h"
#include "imports.h"

// entry: 00415c50
// name : inline_calls_in_switch
// size : 35
// sig  : void inline_calls_in_switch(il_node * stmt)


int __cdecl inline_calls_in_switch(il_node *stmt)

{
  expand_inline_calls_in_expr(stmt->child,stmt);
  expand_inline_calls_in_stmt(stmt->child->next);
  return;
}



