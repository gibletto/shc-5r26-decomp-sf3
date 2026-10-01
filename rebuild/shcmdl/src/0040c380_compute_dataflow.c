#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040c380
// name : compute_dataflow
// size : 353
// sig  : void compute_dataflow(char mode)


int __cdecl compute_dataflow(char mode)

{
  int next_ofs;
  int ofs;
  bblock *blk;
  
  for (blk = g_f_chain; blk != (bblock *)0x0; blk = blk->f_next) {
    if (mode == '\x03') {
      if ((g_debug_flags & 0x100000) != 0) {
        FID_conflict__fwprintf
                  ((FILE *)&stock_stdout,(wchar_t *)s_____Make_Block_NO_ld_DEF_____00435028,
                   (int)blk->number);
      }
      build_kill_or_def_set(blk->startpp,blk->endpp,blk->sets->def,0x10);
    }
    if ((g_debug_flags & 0x100000) != 0) {
      FID_conflict__fwprintf
                ((FILE *)&stock_stdout,(wchar_t *)s_____Make_Block_NO_ld_KILL_____00435004,
                 (int)blk->number);
    }
    build_kill_or_def_set(blk->startpp,blk->endpp,blk->sets->kill,8);
  }
  if (mode == '\x03') {
    solve_live_variables();
  }
  solve_reaching_definitions();
  build_ud_du_chains();
  blk = g_f_chain;
  if ((g_debug_flags & 0x100000) != 0) {
    if (mode == '\x03') {
      FID_conflict__wprintf(s_funcname__s_00434ff4,g_symtab[g_func_node->symx].name);
      dump_live_sets();
    }
    dump_reaching_sets();
    dump_du_chains();
    blk = g_f_chain;
  }
  for (; blk != (bblock *)0x0; blk = blk->f_next) {
    ofs = 0;
    do {
      next_ofs = ofs + 4;
      *(undefined4 *)((int)blk->sets->gen + ofs) = 0;
      *(undefined4 *)((int)blk->sets->kill + ofs) = 0;
      *(undefined4 *)((int)blk->sets->reach_out + ofs) = 0;
      ofs = next_ofs;
    } while (next_ofs < 0x20);
    ofs = 0;
    do {
      next_ofs = ofs + 4;
      *(undefined4 *)((int)blk->sets->use + ofs) = 0;
      *(undefined4 *)((int)blk->sets->def + ofs) = 0;
      ofs = next_ofs;
    } while (next_ofs < 0x40);
  }
  return;
}



