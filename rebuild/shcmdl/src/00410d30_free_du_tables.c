#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_du_tables
#define g_du_tables (*(dutbl * *)(g_sd + 0x1e788))


// entry: 00410d30
// name : free_du_tables
// size : 247
// sig  : void free_du_tables(void)


int __cdecl free_du_tables(void)

{
  short i;
  dutbl *du;
  node_list *link;
  node_list *next;
  dutbl *next_du;
  
  next_du = g_du_tables;
  while (du = next_du, du != (dutbl *)0x0) {
    next_du = du->all_next;
    link = du->links;
    while (link != (node_list *)0x0) {
      next = link->next;
      pool_free(link,8);
      link = next;
    }
    du->node->duptr = (dutbl *)0x0;
    pool_free(du,0x20);
    if ((g_debug_flags & 0x4000) != 0) {
      FID_conflict__wprintf(s_free_dutbl__x_00435434,du);
    }
  }
  i = 0;
  g_du_tables = (dutbl *)0x0;
  do {
    if (g_leaf_table[i].gen != (uint *)0x0) {
      if ((g_debug_flags & 0x4000) != 0) {
        FID_conflict__wprintf(s_free_dpvtp__x_00435424,g_leaf_table[i].gen);
      }
      pool_free(g_leaf_table[i].gen,0x20);
      g_leaf_table[i].gen = (uint *)0x0;
    }
    if (g_leaf_table[i].use != (uint *)0x0) {
      if ((g_debug_flags & 0x4000) != 0) {
        FID_conflict__wprintf(s_free_upvtp__x_00435414,g_leaf_table[i].use);
      }
      pool_free(g_leaf_table[i].use,0x40);
      g_leaf_table[i].use = (uint *)0x0;
    }
    i = i + 1;
  } while (i < 0x800);
  return;
}



