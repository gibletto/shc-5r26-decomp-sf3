#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041aed0
// name : mark_node_clobbering_r0
// size : 304
// sig  : void mark_node_clobbering_r0(gen_node * node)


int __cdecl mark_node_clobbering_r0(gen_node *node)

{
  byte has_fpu;
  gen_node *right;
  gen_node *operand;
  byte type_class;
  uchar *flags_ptr;
  
  if ((node->type & 0xe0) == 0x20) {
    type_class = node->type & 0xf8;
    if (type_class == 0x28) {
      if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
        has_fpu = 1;
      }
      else {
        has_fpu = -(g_request->cpu == 4) & 2;
      }
      if (has_fpu != 0) {
        return;
      }
    }
    if ((type_class != 0x30) || (g_request->cpu != 4)) {
      flags_ptr = &node->desc->flags7;
      *flags_ptr = *flags_ptr | 0x20;
      return;
    }
  }
  else {
    switch(node->op) {
    case IL_CALL:
    case IL_B_QUALIFY:
    case IL_DIV:
    case IL_MOD:
    case IL_A_DIV:
    case IL_A_MOD:
      flags_ptr = &node->desc->flags7;
      *flags_ptr = *flags_ptr | 0x20;
      return;
    case IL_MUL:
    case IL_A_MUL:
      if (g_request->cpu < 1) {
        operand = node->child;
        right = (gen_node *)0x0;
        if (operand != (gen_node *)0x0) {
          right = operand->next;
        }
        if ((right->op != IL_CONST) && (operand->op != IL_CONST)) {
          flags_ptr = &node->desc->flags7;
          *flags_ptr = *flags_ptr | 0x20;
          return;
        }
      }
      break;
    case IL_SL:
    case IL_SR:
    case IL_A_SL:
    case IL_A_SR:
      if (g_request->cpu < 2) {
        if (node->child == (gen_node *)0x0) {
          operand = (gen_node *)0x0;
        }
        else {
          operand = node->child->next;
        }
        if (operand->op != IL_CONST) {
          flags_ptr = &node->desc->flags7;
          *flags_ptr = *flags_ptr | 0x20;
          return;
        }
      }
      break;
    case IL_B_AND:
    case IL_B_XOR:
    case IL_B_OR:
    case IL_A_AND:
    case IL_A_XOR:
    case IL_A_OR:
      operand = node->child;
      if (operand->op != IL_CONST) {
        if (operand == (gen_node *)0x0) {
          operand = (gen_node *)0x0;
        }
        else {
          operand = operand->next;
        }
        if (operand->op != IL_CONST) {
          return;
        }
      }
      flags_ptr = &node->desc->flags7;
      *flags_ptr = *flags_ptr | 0x20;
      return;
    case IL_EQ:
    case IL_NE:
    case IL_LT:
    case IL_LE:
    case IL_GT:
    case IL_GE:
      operand = node->child;
      if (operand->op != IL_CONST) {
        if (operand == (gen_node *)0x0) {
          operand = (gen_node *)0x0;
        }
        else {
          operand = operand->next;
        }
        if (operand->op != IL_CONST) {
          return;
        }
      }
      flags_ptr = &node->desc->flags7;
      *flags_ptr = *flags_ptr | 0x20;
    }
  }
  return;
}



