#include "decls.h"
#include "imports.h"

// entry: 00408390
// name : number_expps
// size : 105
// sig  : void number_expps(il_node * node)


int __cdecl number_expps(il_node *node)

{
  int pos;
  il_node *child;
  bool skip;
  
  child = node->child;
  do {
    if (child == (il_node *)0x0) {
      return;
    }
    if ((char)child->op < ' ') {
      number_expps(child);
    }
    else {
      skip = false;
      if (child->op == IL_NULL) {
        if (node->op == IL_FOR) {
          pos = operand_index(child);
          if (pos != 2) goto LAB_004083cb;
        }
        else if (node->op == IL_RETURN) {
LAB_004083cb:
          skip = true;
        }
      }
      if (!skip) {
        child->expp = (ushort)g_expp_counter;
        g_expp_counter = g_expp_counter + 1;
      }
    }
    child = child->next;
  } while( true );
}



