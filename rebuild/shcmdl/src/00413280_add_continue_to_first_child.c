#include "decls.h"
#include "imports.h"

// entry: 00413280
// name : add_continue_to_first_child
// size : 50
// sig  : il_node * add_continue_to_first_child(il_node * stmt)


il_node * __cdecl add_continue_to_first_child(il_node *stmt)

{
  il_node *pos;
  il_node *piVar1;
  
  piVar1 = stmt->child;
  pos = alloc_node();
  pos->op = IL_EMPTY;
  piVar1->child = pos;
  pos->parent = piVar1;
  piVar1 = alloc_node();
  piVar1->op = IL_CONTINUE;
  insert_before(pos,piVar1);
  return piVar1;
}



