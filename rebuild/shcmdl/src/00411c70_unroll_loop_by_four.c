#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00411c70
// name : unroll_loop_by_four
// size : 498
// sig  : void unroll_loop_by_four(loop * lp)


int __cdecl unroll_loop_by_four(loop *lp)

{
  il_node *limit;
  il_node *piVar1;
  il_node *piVar2;
  uint uVar3;
  uchar type;
  il_op op;
  
  if ((lp->repet != 0) && (lp->child == (loop *)0x0)) {
    g_cur_loop = lp;
    uVar3 = lp->repet;
    if ((uVar3 == 0) || (3 < uVar3)) {
      piVar1 = lp->node;
      op = piVar1->op;
      if (op == IL_FOR) {
        piVar2 = piVar1->child->next->next->next;
      }
      else {
        if (op != IL_WHILE) {
          if (op != IL_DO) {
            return;
          }
          if (lp->lstep == 0) {
            return;
          }
        }
        piVar2 = piVar1->child->next;
      }
      op = piVar2->op;
      if ((((op == IL_LT) || (op == IL_GT)) || (op == IL_LE)) || ((op == IL_GE || (op == IL_NE)))) {
        limit = piVar2->child->next;
        if (((limit->type & 0xe0) != 0x20) && (lp->lstep != 0)) {
          if ((uVar3 == 0) || ((uVar3 & 3) != 0)) {
            if (op != IL_NE) {
              piVar1 = make_unrolled_limit(limit,piVar2->child->type);
              piVar2 = new_node(IL_CONST,'\x10');
              insert_parent(piVar1,piVar2);
              uVar3 = fold_and_check_overflow(piVar1);
              if (uVar3 != 0) {
                free_tree(piVar2);
                return;
              }
              free_tree(piVar2);
              piVar1 = copy_tree(0,g_cur_loop->node);
              piVar1 = replicate_loop_body(piVar1);
              insert_before(g_cur_loop->node,piVar1);
              if ((g_cur_loop->flag & 0x10) != 0) {
                g_unroll_label_added = '\x01';
                uVar3 = new_symbol(0,'\v');
                piVar2 = new_glabel_stmt((short)uVar3);
                insert_after(g_cur_loop->node,piVar2);
                replace_breaks_with_goto(piVar1,(short)uVar3);
              }
              piVar1 = piVar1->child->next;
              if (g_cur_loop->node->op == IL_FOR) {
                piVar1 = piVar1->next->next;
                type = piVar1->child->type;
              }
              else {
                type = piVar1->child->type;
              }
              piVar1 = piVar1->child->next;
              piVar2 = make_unrolled_limit(piVar1,type);
              replace_node(piVar1,piVar2);
              replace_and_free_node(piVar2->child,piVar1);
            }
          }
          else {
            replicate_loop_body(piVar1);
            if (g_cur_loop->repet == 4) {
              g_cur_loop->repet = 1;
              return;
            }
          }
        }
      }
    }
  }
  return;
}



