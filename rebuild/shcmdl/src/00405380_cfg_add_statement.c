#include "decls.h"
#include "imports.h"

// entry: 00405380
// name : cfg_add_statement
// size : 217
// sig  : void cfg_add_statement(il_node * stmt)


int __cdecl cfg_add_statement(il_node *stmt)

{
  il_node *child;
  
  switch(stmt->op) {
  case IL_BLOCK:
    child = stmt->child;
    if (child != (il_node *)0x0) {
      while (child->op != IL_E_BLOCK) {
        cfg_add_statement(child);
        child = child->next;
        if (child == (il_node *)0x0) {
          return;
        }
      }
    }
    break;
  default:
    cfg_append_statement(stmt);
    return;
  case IL_EMPTY:
    break;
  case IL_SWITCH:
    mk_cfg_switch(stmt);
    return;
  case IL_IF:
    mk_cfg_if(stmt);
    return;
  case IL_FOR:
    mk_cfg_for(stmt);
    return;
  case IL_WHILE:
    mk_cfg_while(stmt);
    return;
  case IL_DO:
    mk_cfg_do(stmt);
    return;
  case IL_RETURN:
    cfg_return(stmt);
    return;
  case IL_BREAK:
    cfg_break(stmt);
    return;
  case IL_CONTINUE:
    cfg_continue(stmt);
    return;
  case IL_GOTO:
    g_has_goto = '\x01';
    cfg_goto(stmt);
    return;
  case IL_GLABEL:
    cfg_label(stmt);
    return;
  case IL_DLABEL:
    g_switch_has_default = 1;
  case IL_CLABEL:
    cfg_case_label(stmt);
  }
  return;
}



