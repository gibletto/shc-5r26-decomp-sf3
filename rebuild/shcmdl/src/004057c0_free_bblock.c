#include "decls.h"
#include "imports.h"

// entry: 004057c0
// name : free_bblock
// size : 211
// sig  : void free_bblock(bblock * block)


int __cdecl free_bblock(bblock *block)

{
  node_list *cell;
  node_list *next_cell;
  
  cell = block->ilnode;
  while (cell != (node_list *)0x0) {
    next_cell = cell->next;
    pool_free(cell,8);
    cell = next_cell;
  }
  free_list_cells((node_list *)block->suclst);
  free_list_cells((node_list *)block->prelst);
  pool_free(block->sets->kill,0x20);
  pool_free(block->sets->gen,0x20);
  pool_free(block->sets->def,0x40);
  pool_free(block->sets->reach_out,0x20);
  pool_free(block->sets->use,0x40);
  pool_free(block->sets,0x14);
  pool_free(block->d_in,0x20);
  pool_free(block->out,0x40);
  pool_free(block->l_in,0x40);
  pool_free(block,0x68);
  return;
}



