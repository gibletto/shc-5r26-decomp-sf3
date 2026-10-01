#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_call_list
#define g_inline_call_list (*(inline_group * *)(g_sd + 0xdeb8))
#undef g_inline_candidates_tail
#define g_inline_candidates_tail (*(inline_call * *)(g_sd + 0xdf28))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041fd50
// name : find_inline_calls
// size : 571
// sig  : void find_inline_calls(il_node * expr)


int __cdecl find_inline_calls(il_node *expr)

{
  int iVar1;
  inline_call *cand;
  short *callee_symx;
  short callee;
  il_op op;
  il_node *operand;
  
  for (operand = expr->child; operand != (il_node *)0x0; operand = operand->next) {
    op = expr->op;
    if ((((op == IL_COND) || (op == IL_AND)) || (op == IL_OR)) &&
       (iVar1 = operand_index(operand), iVar1 == 2)) {
      g_inline_cond_depth = g_inline_cond_depth + 1;
    }
    find_inline_calls(operand);
  }
  switch(expr->op) {
  case IL_CALL:
    callee = expr->child->symx;
    callee_symx = &expr->child->symx;
    if ((g_symtab[callee].no_inline != '\0') && ((expr->flag2 & 0x40) == 0)) {
      expr->flag2 = expr->flag2 | 0x40;
      report_message(0x578,expr,g_symtab[*callee_symx].name);
      return;
    }
    if (g_inline_cond_depth == 0) {
      if (((int)g_symbol_limit < g_options->symbol_count + g_symtab[callee].inline_symbols) ||
         (0x7fff < g_options->label_count + g_symtab[callee].inline_labels)) {
        if (((g_symtab[callee].inline_flags & 1) == 0) && ((expr->flag2 & 0x40) == 0)) {
          expr->flag2 = expr->flag2 | 0x40;
          report_message(0x578,expr,g_symtab[callee].name);
          return;
        }
      }
      else {
        iVar1 = 0;
        if ((g_symtab[callee].inline_body != (inline_body *)0x0) &&
           (iVar1 = check_inline_call_args(expr), iVar1 == 1)) {
          cand = pool_alloc(0x10);
          if (cand == (inline_call *)0x0) {
            abort_function_optimization();
          }
          cand->call = expr;
          cand->callee = expr->child->symx;
          cand->result = 0;
          cand->return_label = 0;
          cand->next = (inline_call *)0x0;
          if (g_inline_call_list != (inline_group *)0x0) {
            g_inline_candidates_tail->next = cand;
            g_inline_candidates_tail = cand;
            return;
          }
          g_inline_call_list = new_inline_group(cand);
          g_inline_candidates_tail = cand;
          return;
        }
        if ((((iVar1 == -1) || (iVar1 == -2)) && ((g_symtab[callee].inline_flags & 1) == 0)) &&
           ((expr->flag2 & 0x40) == 0)) {
          expr->flag2 = expr->flag2 | 0x40;
          report_message(0x578,expr,g_symtab[callee].name);
          return;
        }
      }
    }
    else if (((g_symtab[callee].inline_body != (inline_body *)0x0) &&
             ((g_symtab[callee].inline_flags & 1) == 0)) && ((expr->flag2 & 0x40) == 0)) {
      expr->flag2 = expr->flag2 | 0x40;
      report_message(0x578,expr,g_symtab[*callee_symx].name);
      return;
    }
    break;
  case IL_AND:
  case IL_OR:
  case IL_COND:
    g_inline_cond_depth = g_inline_cond_depth + -1;
  }
  return;
}



