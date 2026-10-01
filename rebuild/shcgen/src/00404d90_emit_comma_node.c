#include "decls.h"
#include "imports.h"

// entry: 00404d90
// name : emit_comma_node
// size : 51
// sig  : void emit_comma_node(gen_node * node)


int __cdecl emit_comma_node(gen_node *node)

{
  emit_node_code(node->child);
  if (node->child != (gen_node *)0x0) {
    emit_node_code(node->child->next);
    return;
  }
  emit_node_code((gen_node *)0x0);
  return;
}



