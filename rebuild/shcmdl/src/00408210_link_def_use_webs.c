#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))


// entry: 00408210
// name : link_def_use_webs
// size : 47
// sig  : void link_def_use_webs(void)


int __cdecl link_def_use_webs(void)

{
  bblock *block;
  node_list *stmt;
  
  for (block = g_f_chain; block != (bblock *)0x0; block = block->f_next) {
    for (stmt = block->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
      link_def_use_webs_in_tree(stmt->node);
    }
  }
  return;
}



