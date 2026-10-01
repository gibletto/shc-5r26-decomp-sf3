#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef _g_loop_limit
#define _g_loop_limit (*(unsigned int *)(g_sd + 0x267bc))
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_loop_limit
#define g_loop_limit (*(unsigned int *)(g_sd + 0x267bc))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))


// entry: 00411630
// name : read_loop_limit
// size : 424
// sig  : void read_loop_limit(il_node * test)


/* WARNING: Removing unreachable block (ram,0x004117a6) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl read_loop_limit(il_node *test)

{
  il_node *limit;
  char limit_byte;
  
  limit = test->child->next;
  if ((limit->op == IL_CONST) && ((limit->type & 0xe0) == 0)) {
    _g_loop_limit = limit->val;
    limit_byte = g_loop_limit;
    switch(g_loop_test->child->type & 0x1c) {
    case 0:
      if ((-0x81 < (int)_g_loop_limit) && ((int)_g_loop_limit < 0x80)) {
        _g_loop_limit = (int)limit_byte;
        return;
      }
      g_cur_loop->flag = g_cur_loop->flag | 0x100;
      g_cur_loop->lstep = 0;
      return;
    case 4:
      if ((-1 < (int)_g_loop_limit) && ((int)_g_loop_limit < 0x100)) {
        _g_loop_limit = _g_loop_limit & 0xff;
        return;
      }
      g_cur_loop->flag = g_cur_loop->flag | 0x100;
      g_cur_loop->lstep = 0;
      return;
    case 8:
      if ((-0x8001 < (int)_g_loop_limit) && ((int)_g_loop_limit < 0x8000)) {
        _g_loop_limit = (int)*(short *)&_g_loop_limit;
        return;
      }
      g_cur_loop->flag = g_cur_loop->flag | 0x100;
      g_cur_loop->lstep = 0;
      return;
    case 0xc:
      if ((-1 < (int)_g_loop_limit) && ((int)_g_loop_limit < 0x10000)) {
        _g_loop_limit = _g_loop_limit & 0xffff;
        return;
      }
      g_cur_loop->flag = g_cur_loop->flag | 0x100;
      g_cur_loop->lstep = 0;
      return;
    case 0x10:
    case 0x18:
      if (((int)_g_loop_limit < (-0x7fffffff - 1)) || (0x7fffffff < (int)_g_loop_limit)) {
        g_cur_loop->flag = g_cur_loop->flag | 0x100;
        g_cur_loop->lstep = 0;
        return;
      }
      break;
    case 0x14:
    case 0x1c: ;
    }
  }
  else {
    g_cur_loop->flag = g_cur_loop->flag | 0x100;
    g_cur_loop->lstep = 0;
  }
  return;
}



