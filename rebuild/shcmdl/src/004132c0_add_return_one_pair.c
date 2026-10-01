#include "decls.h"
#include "imports.h"

// entry: 004132c0
// name : add_return_one_pair
// size : 106
// sig  : il_node * add_return_one_pair(il_node * stmt)


il_node * __cdecl add_return_one_pair(il_node *stmt)

{
  il_node *value;
  il_node *pos;
  il_node *node;
  
  value = new_const_node('\x10',1);
  pos = alloc_node();
  pos->op = IL_RETURN;
  pos->child = value;
  value->parent = pos;
  stmt->child = pos;
  pos->parent = stmt;
  value = new_const_node('\x10',1);
  value = make_node(IL_MINUS,'\x10',value,(il_node *)0x0,(il_node *)0x0);
  node = alloc_node();
  node->op = IL_RETURN;
  node->child = value;
  value->parent = node;
  insert_before(pos,node);
  return node;
}



