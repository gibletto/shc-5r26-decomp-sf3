#include "decls.h"
#include "imports.h"

// entry: 00405920
// name : wrap_in_block_pair
// size : 57
// sig  : void wrap_in_block_pair(il_node * stmt)


int __cdecl wrap_in_block_pair(il_node *stmt)

{
  il_node *open_block;
  il_node *close_block;
  
  open_block = alloc_node();
  close_block = alloc_node();
  open_block->op = IL_BLOCK;
  close_block->op = IL_E_BLOCK;
  *(byte *)&open_block->val = (byte)open_block->val | 1;
  *(byte *)&close_block->val = (byte)close_block->val | 1;
  insert_parent(stmt,open_block);
  insert_after(stmt,close_block);
  return;
}



