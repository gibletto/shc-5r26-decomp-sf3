#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 004060b0
// name : opt_exp
// size : 400
// sig  : il_node * opt_exp(il_node * node)


il_node * __cdecl opt_exp(il_node *node)

{
  il_node *piVar1;
  il_node *piVar2;
  il_node *piVar3;
  ushort flag;
  byte *flag_hi;
  il_op op;
  
  flag = node->flag;
  node->flag = flag & 0xfffd;
  node->flag = flag & 0xffbd;
  node->flag = flag & 0xf7bd;
  if (g_opt_exp_identical_only != 0) {
    piVar1 = simplify_identical_operands(node);
    piVar2 = piVar1;
    if (piVar1 == node) {
      piVar3 = piVar1->child;
      while ((piVar2 = piVar1, piVar3 != (il_node *)0x0 &&
             (piVar2 = opt_exp(piVar3), piVar2->parent == piVar1))) {
        piVar3 = piVar2->next;
      }
    }
    piVar2->nodes = '\x01';
    if (piVar2->op == IL_CALL) {
      flag_hi = (byte *)((int)&piVar2->flag + 1);
      *flag_hi = *flag_hi | 8;
    }
    for (piVar1 = piVar2->child; piVar1 != (il_node *)0x0; piVar1 = piVar1->next) {
      piVar2->nodes = piVar2->nodes + piVar1->nodes;
      piVar2->flag = piVar2->flag | piVar1->flag & 0x800;
    }
    return piVar2;
  }
  piVar2 = optimize_array_index(node);
  piVar1 = narrow_expression_size(piVar2);
  set_value_used_flag(piVar1);
  piVar2 = piVar1->child;
  while ((piVar3 = piVar1, piVar2 != (il_node *)0x0 &&
         (piVar3 = opt_exp(piVar2), piVar3->parent == piVar1))) {
    piVar2 = piVar3->next;
  }
  if ((piVar3 == node) && ('\x1f' < (char)piVar3->op)) {
    piVar3 = discard_unused_values(piVar3);
    op = piVar3->op;
    if ((op != IL_ID) && ((op != IL_CONST && (op != IL_NULL)))) {
      piVar2 = fold_constants(piVar3);
      piVar2 = optimize_shift_chain(piVar2);
      piVar2 = reassociate_expression(piVar2);
      piVar2 = apply_pattern_rule(piVar2);
      if (((g_options->optimize != 0) && (g_function_aborted == 0)) &&
         ((g_options->cpu == 4 || ((g_options->cpu == 2 && (g_options->fpu_mode == '\x03')))))) {
        piVar2 = expand_unsigned_float_assign(piVar2);
      }
      piVar3 = discard_unused_values(piVar2);
    }
  }
  piVar3->nodes = '\x01';
  if (piVar3->op == IL_CALL) {
    flag_hi = (byte *)((int)&piVar3->flag + 1);
    *flag_hi = *flag_hi | 8;
  }
  for (piVar2 = piVar3->child; piVar2 != (il_node *)0x0; piVar2 = piVar2->next) {
    piVar3->nodes = piVar3->nodes + piVar2->nodes;
    piVar3->flag = piVar3->flag | piVar2->flag & 0x800;
  }
  return piVar3;
}



