#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 004179a0
// name : is_sole_def_in_loop
// size : 83
// sig  : int is_sole_def_in_loop(dutbl * web, il_node * def)


int __cdecl is_sole_def_in_loop(dutbl *web,il_node *def)

{
  node_list *link;
  loop *lp;
  short lpno;
  
  link = web->links;
  if (link == (node_list *)0x0) {
    return 1;
  }
  do {
    lp = link->node->duptr->block->lptbl;
    if (lp != (loop *)0x0) {
      lpno = lp->lpnumber;
      if (lpno < g_cur_loop->lpnumber) {
        return 0;
      }
      if ((lpno == g_cur_loop->lpnumber) && (link->node != def)) {
        return 0;
      }
    }
    link = link->next;
    if (link == (node_list *)0x0) {
      return 1;
    }
  } while( true );
}



