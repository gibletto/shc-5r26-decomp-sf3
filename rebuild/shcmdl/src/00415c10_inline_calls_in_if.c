#include "decls.h"
#include "imports.h"

// entry: 00415c10
// name : inline_calls_in_if
// size : 53
// sig  : void inline_calls_in_if(il_node * stmt)


int __cdecl inline_calls_in_if(il_node *stmt)

{
  expand_inline_calls_in_expr(stmt->child,stmt);
  expand_inline_calls_in_stmt(stmt->child->next);
  expand_inline_calls_in_stmt(stmt->child->next->next);
  return;
}



