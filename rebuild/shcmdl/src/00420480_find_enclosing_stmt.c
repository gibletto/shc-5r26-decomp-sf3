#include "decls.h"
#include "imports.h"

// entry: 00420480
// name : find_enclosing_stmt
// size : 44
// sig  : il_node * find_enclosing_stmt(il_node * expr)


il_node * __cdecl find_enclosing_stmt(il_node *expr)

{
  il_node *stmt;
  
  do {
    stmt = expr;
    if (stmt == (il_node *)0x0) break;
    expr = stmt->parent;
  } while ('\x1f' < (char)stmt->parent->op);
  if (stmt->parent->op != IL_BLOCK) {
    wrap_stmt_in_scope(stmt);
  }
  return stmt;
}



