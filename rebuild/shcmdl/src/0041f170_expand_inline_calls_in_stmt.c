#include "decls.h"
#include "imports.h"

// entry: 0041f170
// name : expand_inline_calls_in_stmt
// size : 161
// sig  : void expand_inline_calls_in_stmt(il_node * stmt)


int __cdecl expand_inline_calls_in_stmt(il_node *stmt)

{
  il_node *child;
  il_node *next;
  
  do {
    switch(stmt->op) {
    case IL_BLOCK:
      child = stmt->child;
      if (stmt->child == (il_node *)0x0) {
        return;
      }
      do {
        if (child->op == IL_E_BLOCK) {
          return;
        }
        next = child->next;
        expand_inline_calls_in_stmt(child);
        child = next;
      } while (next != (il_node *)0x0);
      return;
    default:
      expand_inline_calls_in_expr(stmt,stmt);
      return;
    case IL_EMPTY:
    case IL_BREAK:
    case IL_GOTO:
      return;
    case IL_SWITCH:
      inline_calls_in_switch(stmt);
      return;
    case IL_IF:
      inline_calls_in_if(stmt);
      return;
    case IL_FOR:
      inline_calls_in_for(stmt);
      return;
    case IL_WHILE:
      inline_calls_in_while(stmt);
      return;
    case IL_DO:
      inline_calls_in_do(stmt);
      return;
    case IL_RETURN:
      expand_inline_calls_in_expr(stmt->child,stmt);
      return;
    case IL_CONTINUE:
      inline_redirect_continue(stmt);
      return;
    case IL_GLABEL:
    case IL_CLABEL:
    case IL_DLABEL:
      stmt = stmt->child;
    }
  } while( true );
}



