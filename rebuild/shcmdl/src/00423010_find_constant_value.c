#include "decls.h"
#include "imports.h"

// entry: 00423010
// name : find_constant_value
// size : 123
// sig  : il_node * find_constant_value(il_node * id)


il_node * __cdecl find_constant_value(il_node *id)

{
  il_node *result;
  il_node *def;
  node_list *link;
  il_op op;
  il_node *rhs;
  
  result = (il_node *)0x0;
  def = id->cmnexp;
  if ((id->op == IL_ID) && (def != (il_node *)0x0)) {
    op = def->op;
    if (op == IL_ASSIGN) {
      rhs = def->child->next;
      if ((rhs->op == IL_CONST) && (((def->child->type ^ rhs->type) & 0xfc) == 0)) {
        return rhs;
      }
    }
    if (op == IL_CONST) {
      return def;
    }
    if ((((op == IL_ID) && (def->duptr != (dutbl *)0x0)) &&
        (link = def->duptr->links, link != (node_list *)0x0)) &&
       ((link->next == (node_list *)0x0 && (link->node->op == IL_ASSIGN)))) {
      def = link->node->child;
      rhs = def->next;
      if ((rhs->op == IL_CONST) && (((def->type ^ rhs->type) & 0xfc) == 0)) {
        result = rhs;
      }
    }
  }
  return result;
}



