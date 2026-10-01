#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00412180
// name : find_loop_induction
// size : 508
// sig  : void find_loop_induction(il_node * node)


int __cdecl find_loop_induction(il_node *node)

{
  il_node *piVar1;
  node_list *def;
  byte bVar2;
  int iVar3;
  il_node *init;
  il_node *step_val;
  node_list *step_link;
  short blkno;
  dutbl *du;
  bool have_init;
  bool have_step;
  node_list *step_item;
  
  for (piVar1 = node->child; piVar1 != (il_node *)0x0; piVar1 = piVar1->next) {
    find_loop_induction(piVar1);
  }
  have_step = false;
  have_init = false;
  if ((((node->cmnexp != (il_node *)0x0) && (du = node->cmnexp->duptr, du != (dutbl *)0x0)) &&
      (1 < du->count)) && (du->count < 3)) {
    step_item = step_link;
    for (def = du->links; def != (node_list *)0x0; def = def->next) {
      piVar1 = def->node;
      blkno = piVar1->duptr->block->number;
      step_link = step_item;
      if (blkno < g_cur_loop->start->number) {
        if (have_init) goto LAB_004122a0;
        iVar3 = blkno + -1;
        bVar2 = (byte)(iVar3 >> 0x1f);
        if ((g_cur_loop->start->domlst[(int)(iVar3 + (iVar3 >> 0x1f & 0x1fU)) >> 5] &
            1 << ((((byte)iVar3 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2 & 0x1f)) == 0) {
          have_init = false;
          g_cur_loop->flag = g_cur_loop->flag | 0x100;
          break;
        }
        have_init = true;
        init = piVar1;
      }
      else if ((blkno <= g_cur_loop->exit->number) && ((piVar1->flag & 0x1000) == 0)) {
        if (!have_step) {
          have_step = true;
          iVar3 = step_def_unusable(piVar1);
          step_val = piVar1;
          if ((iVar3 == 0) && (iVar3 = step_can_be_bypassed(def), step_link = def, iVar3 == 0))
          goto LAB_00412282;
        }
LAB_004122a0:
        g_cur_loop->flag = g_cur_loop->flag | 0x100;
        break;
      }
LAB_00412282:
      step_item = step_link;
    }
    if ((have_init) && (have_step)) {
      if ((g_cur_loop->fath != (loop *)0x0) &&
         (init->cmnexp->duptr->block->number < g_cur_loop->fath->start->number)) {
        g_cur_loop->flag = g_cur_loop->flag | 0x1000;
      }
      if ((((g_cur_loop->flag & 1) != 0) &&
          (step_item->node->duptr->block->number != g_cur_loop->start->number)) ||
         (((g_cur_loop->flag & 2) != 0 &&
          (step_item->node->duptr->block->number != g_cur_loop->exit->number)))) {
        g_cur_loop->init_def = init;
        g_cur_loop->step_def = step_val;
      }
      read_loop_initial_value(init);
      read_loop_step(step_val);
    }
  }
  return;
}



