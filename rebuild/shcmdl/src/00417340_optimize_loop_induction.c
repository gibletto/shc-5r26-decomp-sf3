#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_iv_copy_list
#define g_iv_copy_list (*(node_list * *)(g_sd + 0x3a00))
#undef g_iv_cur_block
#define g_iv_cur_block (*(bblock * *)(g_sd + 0xdb64))
#undef g_iv_update_stmt
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00417340
// name : optimize_loop_induction
// size : 406
// sig  : void optimize_loop_induction(loop * lp)


int __cdecl optimize_loop_induction(loop *lp)

{
  bblock *blk;
  il_node *rhs_base;
  il_node *rhs;
  node_list *stmt;
  il_op test_op;
  
  if (lp->child != (loop *)0x0) {
    optimize_loop_induction(lp->child);
  }
  if (lp->next != (loop *)0x0) {
    optimize_loop_induction(lp->next);
  }
  g_cur_loop = lp;
  g_iv_update_stmt = (il_node *)0x0;
  g_iv_reduced_count = 0;
  g_iv_tested_count = 0;
  g_iv_copy_list = (node_list *)0x0;
  g_iv_count = 1;
  if ((lp->flag & 1) == 0) {
    blk = lp->exit;
  }
  else {
    blk = lp->start;
  }
  g_loop_test = blk->ilnode->node;
  test_op = g_loop_test->op;
  if ((((test_op == IL_LT) || (test_op == IL_GT)) || (test_op == IL_LE)) ||
     ((test_op == IL_GE || (test_op == IL_NE)))) {
    rhs = g_loop_test->child->next;
    rhs_base = rhs;
    if (rhs->op == IL_CAST) {
      rhs_base = rhs->child;
    }
    if ((rhs->invno != '\0') ||
       (((rhs_base->op == IL_ID && (0 < rhs_base->symx)) &&
        (g_symtab[rhs_base->symx].sclass < '\x05')))) {
      blk = lp->start;
      if (lp->exit->bn_next != blk) {
        do {
          if (g_iv_count < 4) {
            find_basic_induction_vars(blk);
          }
          else {
            g_cur_loop->flag = g_cur_loop->flag | 0x80;
          }
          blk = blk->bn_next;
        } while (g_cur_loop->exit->bn_next != blk);
      }
      if ((g_cur_loop->flag & 0x80) == 0) {
        blk = g_cur_loop->start;
        if (g_cur_loop->exit->bn_next != blk) {
          do {
            g_iv_cur_block = blk;
            find_derived_induction_vars(blk->ilnode);
            blk = blk->bn_next;
          } while (g_cur_loop->exit->bn_next != blk);
        }
        strength_reduce_induction_vars();
      }
      blk = g_cur_loop->start;
      if (g_cur_loop->exit->bn_next != blk) {
        do {
          for (stmt = blk->ilnode; stmt != (node_list *)0x0; stmt = stmt->next) {
            clear_induction_numbers(stmt->node);
            clear_induction_marks(stmt->node);
          }
          blk = blk->bn_next;
        } while (g_cur_loop->exit->bn_next != blk);
      }
      free_induction_tables();
    }
  }
  return;
}



