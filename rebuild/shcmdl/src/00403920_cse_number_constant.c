#include "decls.h"
#include "imports.h"

// entry: 00403920
// name : cse_number_constant
// size : 69
// sig  : void cse_number_constant(il_node * node)


int __cdecl cse_number_constant(il_node *node)

{
  il_node *head;
  
  head = cse_find_constant(node);
  if (head != (il_node *)0x0) {
    cse_join_value_class(head,node);
    return;
  }
  if (g_cse_cond_depth != '\0') {
    cse_clear_value_number(node);
    return;
  }
  cse_new_value_number(node);
  cse_add_constant(node);
  return;
}



