#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 004195f0
// name : move_increment_out_of_do_test
// size : 272
// sig  : void move_increment_out_of_do_test(loop * lp)


int __cdecl move_increment_out_of_do_test(loop *lp)

{
  bblock *test_blk;
  il_node *piVar1;
  il_node *piVar2;
  il_op op;
  il_op rhs_op;
  
  if (lp->child != (loop *)0x0) {
    move_increment_out_of_do_test(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    move_increment_out_of_do_test(lp->next);
  }
  g_cur_loop = lp;
  if ((lp->flag & 1) == 0) {
    test_blk = lp->exit;
  }
  else {
    test_blk = lp->start;
  }
  piVar2 = test_blk->ilnode->node;
  op = piVar2->op;
  if ((((op != IL_LT) && (op != IL_GT)) && (op != IL_LE)) && ((op != IL_GE && (op != IL_NE)))) {
    return;
  }
  if ((lp->flag & 0x20) != 0) {
    return;
  }
  if (lp->node->op != IL_DO) {
    return;
  }
  piVar1 = piVar2->child;
  op = piVar1->op;
  if (op != IL_PRI) {
    if (((op != IL_PRD) && (rhs_op = piVar1->next->op, rhs_op != IL_PRI)) && (rhs_op != IL_PRD)) {
      return;
    }
    if ((op != IL_PRI) && (op != IL_PRD)) {
      piVar1 = copy_tree(0,piVar1->next->child);
      piVar2 = piVar2->child->next;
      goto LAB_004196b5;
    }
  }
  piVar1 = copy_tree(0,piVar1->child);
  piVar2 = piVar2->child;
LAB_004196b5:
  replace_node(piVar2,piVar1);
  piVar1 = g_cur_loop->node->child;
  if (piVar1->op != IL_BLOCK) {
    wrap_in_block_pair(piVar1);
  }
  piVar1 = last_operand(g_cur_loop->node->child);
  insert_before(piVar1,piVar2);
  g_do_test_changed = '\x01';
  return;
}



