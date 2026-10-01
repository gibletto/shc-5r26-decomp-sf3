#include "decls.h"
#include "imports.h"

// entry: 00408600
// name : dump_tree
// size : 77
// sig  : void dump_tree(il_node * node, short depth, char * title)


int __cdecl dump_tree(il_node *node,short depth,char *title)

{
  FID_conflict__wprintf(s_______________________TREE_DUMP__0043487c);
  FID_conflict__wprintf(s_str_00434868,title);
  _fflush((FILE *)&stock_stdout);
  dump_tree_rec(node,(int)depth);
  _fflush((FILE *)&stock_stdout);
  return;
}



