#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_dag_block
#define g_dag_block (*(bblock * *)(g_sd + 0x1e724))
#undef g_du_tables
#define g_du_tables (*(dutbl * *)(g_sd + 0x1e788))


// entry: 0040a810
// name : new_web
// size : 67
// sig  : void new_web(il_node * node)


int __cdecl new_web(il_node *node)

{
  dutbl *du;
  
  if (g_make_du != '\0') {
    du = pool_alloc(0x20);
    if (du == (dutbl *)0x0) {
      free_def_tables_and_abort();
    }
    node->duptr = du;
    du->block = g_dag_block;
    du->node = node;
    du->all_next = g_du_tables;
    g_du_tables = du;
  }
  return;
}



