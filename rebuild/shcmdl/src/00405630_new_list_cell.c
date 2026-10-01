#include "decls.h"
#include "imports.h"

// entry: 00405630
// name : new_list_cell
// size : 39
// sig  : block_list * new_list_cell(block_list * next, bblock * item)


block_list * __cdecl new_list_cell(block_list *next,bblock *item)

{
  block_list *cell;
  
  cell = pool_alloc(8);
  if (cell == (block_list *)0x0) {
    cfg_out_of_memory();
  }
  cell->block = item;
  cell->next = next;
  return cell;
}



