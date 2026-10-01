#include "decls.h"
#include "imports.h"

// entry: 00403eb0
// name : cse_replace_in_block
// size : 38
// sig  : void cse_replace_in_block(bblock * block)


int __cdecl cse_replace_in_block(bblock *block)

{
  node_list *stmt;
  il_node *replaced;
  
  for (stmt = block->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
    replaced = cse_replace_in_tree(stmt->node,stmt,block);
    stmt->node = replaced;
  }
  return;
}



