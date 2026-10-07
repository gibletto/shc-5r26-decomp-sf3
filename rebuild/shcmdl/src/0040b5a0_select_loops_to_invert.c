#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040b5a0
// name : select_loops_to_invert
// size : 493
// sig  : void __cdecl select_loops_to_invert(loop *lp)


int __cdecl select_loops_to_invert(loop *lp)

{
  il_node *expr;
  il_node *lhs;
  il_op op;
  
  if (lp != (loop *)0x0) {
    if (lp->next != (loop *)0x0) {
      select_loops_to_invert(lp->next);
    }
    LOOP_LOG(lp);
    if (((lp->child == (loop *)0x0) ||
        (select_loops_to_invert(lp->child), LOOP_SPEED(1))) &&
       (((lp->repet == 0 && ((lp->flag & 0x8000) == 0)) || ((lp->flag & 0x1000) != 0)))) {
      expr = lp->node;
      op = expr->op;
      if (((op != IL_FOR) || (expr->child->next->next->op == IL_NULL)) && (op != IL_DO)) {
        if (op == IL_FOR) {
          expr = expr->child->next->next->next;
        }
        else if (op == IL_WHILE) {
          expr = expr->child->next;
        }
        if (((char)expr->op < '`') || ('g' < (char)expr->op)) {
          if (LOOP_SPEED(2)) {
            LOOP_INVERT(lp);
          }
        }
        else {
          expr = expr->child;
          lhs = expr;
          if (expr->op == IL_CAST) {
            lhs = expr->child;
          }
          expr = expr->next;
          if (expr->op == IL_CAST) {
            expr = expr->child;
          }
          if (((lhs->type & 0xf8) == 0x30) || ((expr->type & 0xf8) == 0x30)) {
            if (LOOP_SPEED(4)) {
              LOOP_INVERT(lp);
              return;
            }
          }
          else if (((lhs->op == IL_ID) &&
                   (((((0 < lhs->symx && ('\x04' < g_symtab[lhs->symx].sclass)) &&
                      (g_symtab[lhs->symx].sclass < '\t')) &&
                     ((g_leaf_table[lhs->nleaf].flag & 0xe) == 0)) || (lhs->symx < 0)))) ||
                  (lhs->op == IL_CONST)) {
            if (((expr->op == IL_ID) &&
                ((((0 < expr->symx && ('\x04' < g_symtab[expr->symx].sclass)) &&
                  ((g_symtab[expr->symx].sclass < '\t' &&
                   ((g_leaf_table[expr->nleaf].flag & 0xe) == 0)))) || (expr->symx < 0)))) ||
               (expr->op == IL_CONST)) {
              LOOP_INVERT(lp);
              return;
            }
            if (LOOP_SPEED(8)) {
              LOOP_INVERT(lp);
              return;
            }
          }
          else if (LOOP_SPEED(16)) {
            LOOP_INVERT(lp);
            return;
          }
        }
      }
    }
  }
  return;
}
