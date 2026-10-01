#include "decls.h"
#include "imports.h"

// entry: 004055b0
// name : cfg_add_edge
// size : 62
// sig  : void cfg_add_edge(bblock * from, bblock * to)


int __cdecl cfg_add_edge(bblock *from,bblock *to)

{
  block_list *succ;
  
  succ = from->suclst;
  while( true ) {
    if (succ == (block_list *)0x0) {
      succ = new_list_cell(from->suclst,to);
      from->suclst = succ;
      succ = new_list_cell(to->prelst,from);
      to->prelst = succ;
      return;
    }
    if (succ->block == to) break;
    succ = succ->next;
  }
  return;
}



