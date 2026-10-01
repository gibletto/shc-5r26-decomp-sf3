#include "decls.h"
#include "imports.h"

// entry: 00411e70
// name : replace_breaks_with_goto
// size : 57
// sig  : void replace_breaks_with_goto(il_node * node, short labno)


int __cdecl replace_breaks_with_goto(il_node *node,short labno)

{
  il_node *sub;
  
  for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
    replace_breaks_with_goto(sub,labno);
  }
  if (node->op == IL_BREAK) {
    node->symx = labno;
    node->op = IL_GOTO;
  }
  return;
}



