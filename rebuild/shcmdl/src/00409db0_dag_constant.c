#include "decls.h"
#include "imports.h"

// entry: 00409db0
// name : dag_constant
// size : 69
// sig  : void dag_constant(il_node * node)


int __cdecl dag_constant(il_node *node)

{
  il_node *head;
  
  head = find_equal_constant(node);
  if (head != (il_node *)0x0) {
    link_common_chain(head,node);
    return;
  }
  if (g_cse_cond_depth != '\0') {
    clear_common_links(node);
    return;
  }
  start_common_chain(node);
  add_constant_to_hash(node);
  return;
}



