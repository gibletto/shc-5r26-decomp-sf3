#include "decls.h"
#include "imports.h"

// entry: 00418ca0
// name : clear_induction_marks
// size : 41
// sig  : void clear_induction_marks(il_node * tree)


int __cdecl clear_induction_marks(il_node *tree)

{
  il_node *child;
  
  for (child = tree->child; child != (il_node *)0x0; child = child->next) {
    clear_induction_marks(child);
  }
  tree->ivno = 0;
  tree->invno = '\0';
  return;
}



