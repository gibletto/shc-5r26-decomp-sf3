#include "decls.h"
#include "imports.h"

// entry: 0040d610
// name : make_goto_entry_label
// size : 15
// sig  : il_node * make_goto_entry_label(void)


il_node * make_goto_entry_label(void)

{
  il_node *node;
  
  node = alloc_node();
  node->op = IL_GOTO;
  node->symx = -1;
  return node;
}
