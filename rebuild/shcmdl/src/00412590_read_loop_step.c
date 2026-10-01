#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00412590
// name : read_loop_step
// size : 334
// sig  : void read_loop_step(il_node * def)


int __cdecl read_loop_step(il_node *def)

{
  il_op iVar1;
  il_node *piVar2;
  il_node *piVar3;
  
  iVar1 = def->op;
  if (((iVar1 == IL_PRI) && ((def->type & 0xe0) == 0)) ||
     ((iVar1 == IL_POI && ((def->type & 0xe0) == 0)))) {
    g_cur_loop->lstep = 1;
    return;
  }
  if (((iVar1 == IL_PRD) && ((def->type & 0xe0) == 0)) ||
     ((iVar1 == IL_POD && ((def->type & 0xe0) == 0)))) {
    g_cur_loop->lstep = -1;
    return;
  }
  if (((iVar1 == IL_A_ADD) && ((def->type & 0xe0) == 0)) &&
     (piVar2 = def->child->next, piVar2->op == IL_CONST)) {
    g_cur_loop->lstep = piVar2->val;
    return;
  }
  if (((iVar1 == IL_A_SUB) && ((def->type & 0xe0) == 0)) &&
     (piVar2 = def->child->next, piVar2->op == IL_CONST)) {
    g_cur_loop->lstep = -piVar2->val;
    return;
  }
  if ((iVar1 != IL_ASSIGN) || ((def->type & 0xe0) != 0)) {
    g_cur_loop->flag = g_cur_loop->flag | 0x100;
    return;
  }
  piVar2 = def->child;
  piVar3 = piVar2->next;
  if (piVar3->op != IL_ADD) {
    if (piVar3->op != IL_SUB) {
      g_cur_loop->flag = g_cur_loop->flag | 0x100;
      return;
    }
    if ((piVar3->child->nleaf == piVar2->nleaf) &&
       (piVar2 = piVar3->child->next, piVar2->op == IL_CONST)) {
      g_cur_loop->lstep = -piVar2->val;
      return;
    }
    g_cur_loop->flag = g_cur_loop->flag | 0x100;
    return;
  }
  piVar3 = piVar3->child;
  if ((piVar3->nleaf == piVar2->nleaf) && (piVar3->next->op == IL_CONST)) {
    g_cur_loop->lstep = piVar3->next->val;
    return;
  }
  if ((piVar3->next->nleaf == piVar2->nleaf) && (piVar3->op == IL_CONST)) {
    g_cur_loop->lstep = piVar3->val;
    return;
  }
  g_cur_loop->flag = g_cur_loop->flag | 0x100;
  return;
}



