#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_loop
#define g_inline_loop (*(il_node * *)(g_sd + 0xde54))


// entry: 00416100
// name : inline_redirect_continue
// size : 214
// sig  : void inline_redirect_continue(il_node * stmt)


int __cdecl inline_redirect_continue(il_node *stmt)

{
  il_node *piVar1;
  uint labno;
  il_node *node;
  il_op op;
  
  if (g_inline_loop != (il_node *)0x0) {
    piVar1 = alloc_node();
    piVar1->op = IL_GOTO;
    replace_and_free_node(stmt,piVar1);
    if (g_inline_continue_label == 0) {
      labno = new_symbol(0,'\v');
      g_inline_continue_label = (short)labno;
      piVar1->symx = g_inline_continue_label;
      if (g_inline_loop->op == IL_FOR) {
        piVar1 = g_inline_loop->child->next;
        if (piVar1->op != IL_BLOCK) {
          wrap_stmt_in_scope(piVar1);
        }
        piVar1 = g_inline_loop->child->next;
      }
      else {
        piVar1 = g_inline_loop->child;
        if (g_inline_loop->op == IL_WHILE) {
          op = piVar1->op;
        }
        else {
          op = piVar1->op;
        }
        if (op != IL_BLOCK) {
          wrap_stmt_in_scope(piVar1);
        }
        piVar1 = g_inline_loop->child;
      }
      node = new_glabel_stmt(g_inline_continue_label);
      piVar1 = last_operand(piVar1);
      insert_before(piVar1,node);
      return;
    }
    piVar1->symx = g_inline_continue_label;
  }
  return;
}



