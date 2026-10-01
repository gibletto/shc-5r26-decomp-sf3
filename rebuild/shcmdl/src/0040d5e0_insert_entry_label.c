#include "decls.h"
#include "imports.h"

// entry: 0040d5e0
// name : insert_entry_label
// size : 35
// sig  : il_node * insert_entry_label(il_node * stmt)


il_node * __cdecl insert_entry_label(il_node *stmt)

{
  il_node *node;
  
  node = alloc_node();
  node->op = IL_GLABEL;
  node->symx = -1;
  insert_before(stmt,node);
  return node;
}



