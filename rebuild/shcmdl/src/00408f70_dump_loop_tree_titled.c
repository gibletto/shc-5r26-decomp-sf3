#include "decls.h"
#include "imports.h"

// entry: 00408f70
// name : dump_loop_tree_titled
// size : 47
// sig  : void dump_loop_tree_titled(loop * lp, char * title)


int __cdecl dump_loop_tree_titled(loop *lp,char *title)

{
  FID_conflict__wprintf(s___loop_table_dump_____s____00434c7c,title);
  dump_loop_tree(lp,0);
  FID_conflict__wprintf(s____________00434c70);
  return;
}



