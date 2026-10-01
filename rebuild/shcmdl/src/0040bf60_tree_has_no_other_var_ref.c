#include "decls.h"
#include "imports.h"

// entry: 0040bf60
// name : tree_has_no_other_var_ref
// size : 103
// sig  : char tree_has_no_other_var_ref(il_node * node, il_node * def1, il_node * def2, il_node * var)


char __cdecl tree_has_no_other_var_ref(il_node *node,il_node *def1,il_node *def2,il_node *var)

{
  char ok;
  il_node *sub;
  
  ok = '\x01';
  sub = node->child;
  while ((sub != (il_node *)0x0 && (ok = tree_has_no_other_var_ref(sub,def1,def2,var), ok != '\0')))
  {
    sub = sub->next;
  }
  if ((((var->symx == node->symx) && (var != node)) && (def2 != node)) &&
     (((def2->child != node && (def1 != node)) && (def1->child != node)))) {
    ok = '\0';
  }
  return ok;
}



