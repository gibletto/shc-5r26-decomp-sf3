#include "decls.h"
#include "imports.h"

// entry: 004036a0
// name : cse_number_statements
// size : 51
// sig  : void cse_number_statements(il_node * node)


int __cdecl cse_number_statements(il_node *node)

{
  il_node *child;
  
  for (child = node->child; child != (il_node *)0x0; child = child->next) {
    if (child->op == IL_BLOCK) {
      cse_number_statements(child);
    }
    else if (child->op != IL_NULL) {
      cse_number_expression(child);
    }
  }
  return;
}



