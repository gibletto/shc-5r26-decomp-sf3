#include "decls.h"
#include "imports.h"

// entry: 0041d3e0
// name : count_common_expression
// size : 82
// sig  : void count_common_expression(il_node * node, bblock * block)


int __cdecl count_common_expression(il_node *node,bblock *block)

{
  il_node *head;
  
  head = find_equal_constant(node);
  if (head != (il_node *)0x0) {
    cse_join_class(head,node);
    node->cse_block = block;
    return;
  }
  if (g_cse_cond_depth != '\0') {
    cse_clear_node(node);
    return;
  }
  cse_new_class(node,block);
  cse_hash_constant(node);
  return;
}



