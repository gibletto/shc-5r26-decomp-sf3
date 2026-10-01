#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041f8d0
// name : try_evaluate_right_operand_first
// size : 350
// sig  : short try_evaluate_right_operand_first(gen_node * node, gen_node * left, gen_node * right)


short __cdecl try_evaluate_right_operand_first(gen_node *node,gen_node *left,gen_node *right)

{
  byte ea_kind;
  ushort shared;
  uint right_regs;
  ea *op;
  short swapped;
  uchar *flags_ptr;
  node_desc *left_desc;
  ushort left_temp;
  char node_pr;
  node_desc *right_desc;
  
  swapped = 0;
  if (((node->desc->flags2 & 0x40) == 0) && (node->op != IL_ARG)) {
    left_desc = left->desc;
    right_desc = right->desc;
    left_temp = left_desc->temp_regs;
    if (((right_desc->reused_regs & (left_temp | left_desc->cached_regs)) == 0) &&
       ((((left_desc->reused_regs & (right_desc->cached_regs | right_desc->temp_regs)) == 0 &&
         ((right_desc->freused_regs & (left_desc->ftemp_regs | left_desc->fcached_regs)) == 0)) &&
        ((left_desc->freused_regs & (right_desc->ftemp_regs | right_desc->freused_regs)) == 0)))) {
      shared = right_desc->temp_regs & left_desc->reused_regs;
      if ((shared == 0) || ((right_desc->reused_regs & shared) != 0)) {
        op = right_desc->mem_ea;
        ea_kind = 0;
        if (op != (ea *)0x0) {
          ea_kind = op->type & 0x1f;
        }
        if (((ea_kind == 0) && (op = &right_desc->dest, (op->type & 0x1f) == 0)) &&
           (op = &g_ea_pop, (right_desc->flags2 & 8) == 0)) {
          op = &right_desc->value;
        }
        right_regs = ea_register_mask(op);
        if ((((int)(short)left_temp & right_regs) == 0) &&
           ((((g_request->cpu != 4 || (g_request->unknown_155[2] != '\0')) ||
             ((node_pr = node->desc->fpscr_pr, node_pr == '\0' &&
              ((left->desc->fpscr_pr == '\0' && (right->desc->fpscr_pr == '\0')))))) ||
            ((node_pr == '\x01' &&
             ((left->desc->fpscr_pr == '\x01' && (right->desc->fpscr_pr == '\x01')))))))) {
          flags_ptr = &node->desc->flags2;
          *flags_ptr = *flags_ptr | 0x80;
          invalidate_register_contents
                    ((int)(short)(left->desc->temp_regs & right->desc->cached_regs));
          swapped = 1;
        }
      }
      else {
        left_desc->cached_regs = left_desc->cached_regs | left_desc->reused_regs;
      }
    }
  }
  return swapped;
}



