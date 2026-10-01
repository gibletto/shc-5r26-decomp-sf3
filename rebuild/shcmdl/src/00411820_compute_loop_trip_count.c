#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef _g_loop_limit
#define _g_loop_limit (*(unsigned int *)(g_sd + 0x267bc))
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_loop_limit
#define g_loop_limit (*(unsigned int *)(g_sd + 0x267bc))


// entry: 00411820
// name : compute_loop_trip_count
// size : 811
// sig  : void compute_loop_trip_count(il_node * test)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl compute_loop_trip_count(il_node *test)

{
  char covers;
  uint uVar1;
  uint span;
  int iVar2;
  int *repet_p;
  il_op op;
  bool runs;
  
  uVar1 = g_cur_loop->flag;
  if ((uVar1 & 0x97c) != 0) {
    return;
  }
  op = test->op;
  if ((op == IL_LE) || (op == IL_GE)) {
    iVar2 = g_cur_loop->lstep;
    if ((test->child->type & 4) == 0) {
      if ((((0 < iVar2) && (op == IL_LE)) && (g_loop_init <= (int)_g_loop_limit)) ||
         (((iVar2 < 0 && (op == IL_GE)) && ((int)_g_loop_limit <= g_loop_init)))) goto LAB_00411955;
    }
    else if ((((0 < iVar2) && (op == IL_LE)) && ((uint)g_loop_init <= _g_loop_limit)) ||
            (((iVar2 < 0 && (op == IL_GE)) && (_g_loop_limit <= (uint)g_loop_init))))
    goto LAB_00411955;
  }
  else {
    iVar2 = g_cur_loop->lstep;
    if ((test->child->type & 4) == 0) {
      if ((((0 < iVar2) && ((op == IL_LT || (op == IL_NE)))) && (g_loop_init < (int)_g_loop_limit))
         || (((iVar2 < 0 && ((op == IL_GT || (op == IL_NE)))) && ((int)_g_loop_limit < g_loop_init))
            )) goto LAB_00411955;
    }
    else if (((0 < iVar2) &&
             (((op == IL_LT || (op == IL_NE)) && ((uint)g_loop_init < _g_loop_limit)))) ||
            (((iVar2 < 0 && ((op == IL_GT || (op == IL_NE)))) && (_g_loop_limit < (uint)g_loop_init)
             ))) {
LAB_00411955:
      runs = true;
      goto LAB_0041195e;
    }
  }
  runs = false;
LAB_0041195e:
  if (!runs) {
    g_cur_loop->flag = uVar1 | 0x100;
    g_cur_loop->repet = 0;
    return;
  }
  covers = trip_span_covers_step(test);
  if (covers == '\0') {
    g_cur_loop->flag = g_cur_loop->flag | 0x100;
    g_cur_loop->repet = 0;
    return;
  }
  switch(test->op) {
  case IL_NE:
    break;
  default:
    g_cur_loop->flag = g_cur_loop->flag | 0x100;
    return;
  case IL_LT:
    uVar1 = g_cur_loop->lstep >> 0x1f;
    g_cur_loop->repet =
         ((_g_loop_limit - g_loop_init) - 1) / ((g_cur_loop->lstep ^ uVar1) - uVar1) + 1;
    return;
  case IL_LE:
    uVar1 = g_cur_loop->lstep >> 0x1f;
    g_cur_loop->repet = (_g_loop_limit - g_loop_init) / ((g_cur_loop->lstep ^ uVar1) - uVar1) + 1;
    return;
  case IL_GT:
    uVar1 = g_cur_loop->lstep >> 0x1f;
    g_cur_loop->repet =
         ((g_loop_init - _g_loop_limit) - 1) / ((g_cur_loop->lstep ^ uVar1) - uVar1) + 1;
    return;
  case IL_GE:
    uVar1 = g_cur_loop->lstep >> 0x1f;
    g_cur_loop->repet = (g_loop_init - _g_loop_limit) / ((g_cur_loop->lstep ^ uVar1) - uVar1) + 1;
    return;
  }
  uVar1 = g_cur_loop->lstep;
  if ((int)uVar1 < 1) {
    span = g_loop_init - _g_loop_limit;
    uVar1 = (uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f);
  }
  else {
    span = _g_loop_limit - g_loop_init;
  }
  g_cur_loop->repet = span % uVar1;
  repet_p = &g_cur_loop->repet;
  if (*repet_p != 0) {
    g_cur_loop->flag = g_cur_loop->flag | 0x100;
    g_cur_loop->flag = g_cur_loop->flag | 0x8000;
    g_cur_loop->repet = 0;
    return;
  }
  uVar1 = g_cur_loop->lstep;
  if ((int)uVar1 < 1) {
    iVar2 = g_loop_init - _g_loop_limit;
  }
  else {
    iVar2 = _g_loop_limit - g_loop_init;
  }
  if (0 < (int)uVar1) {
    *repet_p = (iVar2 - 1U) / uVar1 + 1;
    return;
  }
  *repet_p = (iVar2 - 1U) / ((uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)) + 1;
  return;
}



