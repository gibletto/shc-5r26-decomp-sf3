#include "decls.h"
#include "imports.h"

// entry: 00409820
// name : find_last_node_of_block
// size : 21
// sig  : code_node * __cdecl find_last_node_of_block(code_node *node)


code_node * __cdecl find_last_node_of_block(code_node *node)

{
  code_node *next;
  
  next = node->next;
  while (next != (code_node *)0x0) {
    node = node->next;
    next = node->next;
  }
  return node;
}
