#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_cur_loop
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#undef g_cfg_last_loop
#define g_cfg_last_loop (*(loop * *)(g_sd + 0x1e728))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))


// entry: 00421a80
// name : new_loop
// size : 156
// sig  : loop * new_loop(il_node * stmt)


loop * __cdecl new_loop(il_node *stmt)

{
  loop *lp;
  
  g_loop_count = g_loop_count + 1;
  if (0x80 < g_loop_count) {
    cfg_out_of_memory();
  }
  lp = pool_alloc(0x3c);
  if (lp == (loop *)0x0) {
    cfg_out_of_memory();
  }
  if (g_loop_tree == (loop *)0x0) {
    g_loop_tree = lp;
  }
  lp->node = stmt;
  if (g_cfg_last_loop != (loop *)0x0) {
    g_cfg_last_loop->next = lp;
    lp->front = g_cfg_last_loop;
    lp->fath = g_cfg_cur_loop;
    g_cfg_last_loop = (loop *)0x0;
    g_cfg_cur_loop = lp;
    return lp;
  }
  if (g_cfg_cur_loop != (loop *)0x0) {
    g_cfg_cur_loop->child = lp;
    lp->fath = g_cfg_cur_loop;
  }
  g_cfg_cur_loop = lp;
  return lp;
}



