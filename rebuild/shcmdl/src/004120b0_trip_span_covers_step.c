#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_loop_limit
#define g_loop_limit (*(int *)(g_sd + 0x267bc))


// entry: 004120b0
// name : trip_span_covers_step
// size : 135
// sig  : char trip_span_covers_step(il_node * test)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char __cdecl trip_span_covers_step(il_node *test)

{
  uint span;
  int diff;
  uint sign;
  
  span = 0;
  switch(test->op) {
  case IL_NE:
  case IL_LT:
    span = _g_loop_limit - g_loop_init;
    if ((test->op == IL_NE) && (g_cur_loop->lstep < 0)) {
      span = g_loop_init - _g_loop_limit;
    }
    break;
  case IL_LE:
    diff = _g_loop_limit - g_loop_init;
    goto LAB_0041211f;
  case IL_GT:
    span = g_loop_init - _g_loop_limit;
    break;
  case IL_GE:
    diff = g_loop_init - _g_loop_limit;
LAB_0041211f:
    span = diff + 1;
  }
  sign = g_cur_loop->lstep >> 0x1f;
  return (g_cur_loop->lstep ^ sign) - sign <= span;
}



