#include "decls.h"
#include "imports.h"

// entry: 0041f6a0
// name : clear_line_info
// size : 46
// sig  : void clear_line_info(il_node * tree)


int __cdecl clear_line_info(il_node *tree)

{
  il_node *child;
  
  for (child = tree->child; child != (il_node *)0x0; child = child->next) {
    clear_line_info(child);
  }
  tree->filn = 0;
  tree->line = 0;
  tree->listno = 0;
  return;
}



