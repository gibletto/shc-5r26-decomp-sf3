#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041d1a0
// name : select_arithmetic_routine
// size : 2293
// sig  : short select_arithmetic_routine(gen_node * node)


short __cdecl select_arithmetic_routine(gen_node *node)

{
  byte type_class;
  byte type_bits;
  ea *right_ea;
  ea *left_ea;
  gen_node *right;
  short local_2;
  node_desc *desc;
  char div_mode;
  gen_node *left;
  il_op op;
  
  left = node->child;
  right = (gen_node *)0x0;
  if (left != (gen_node *)0x0) {
    right = left->next;
  }
  op = node->op;
  switch(op) {
  case IL_ADD:
  case IL_A_ADD:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return 0x20;
    }
    if (type_bits == 0x28) {
      return 0x1f;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case IL_SUB:
  case IL_A_SUB:
    type_bits = right->type & 0xf8;
    if (type_bits != 0x30) {
      if (type_bits == 0x28) {
        return 0x23;
      }
      report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return local_2;
    }
    if ((op == IL_A_SUB) && ((left->type & 0xf8) != 0x30)) {
      return 0x24;
    }
    return ((node->desc->flags2 & 0x80) == 0) + 0x24;
  default:
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case IL_MUL:
  case IL_A_MUL:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return 0x29;
    }
    if (type_bits == 0x28) {
      return 0x28;
    }
    if ((type_bits != 0x10) && (type_bits != 0x18)) {
      report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return local_2;
    }
    return 0xd;
  case IL_DIV:
  case IL_A_DIV:
    break;
  case IL_MOD:
  case IL_A_MOD:
    type_bits = right->type;
    type_class = type_bits & 0xf8;
    if ((type_class != 0x18) && (type_class != 0x10)) {
      if (type_class == 8) {
        if ((((type_bits & 4) == 0) && ((type_bits & 0xe0) != 0x80)) && ((type_bits & 0xe0) != 0x40)
           ) {
          return 8;
        }
        return 0xb;
      }
      if (type_class != 0) {
        report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        return local_2;
      }
      if ((((type_bits & 4) == 0) && ((type_bits & 0xe0) != 0x80)) && ((type_bits & 0xe0) != 0x40))
      {
        return 7;
      }
      return 10;
    }
    if (((type_bits & 4) != 0) || (((type_bits & 0xe0) == 0x80 || ((type_bits & 0xe0) == 0x40)))) {
      return 0xc;
    }
    div_mode = g_request->div_routine_variant;
    if (div_mode == '\0') {
      return 9;
    }
    if (div_mode != '\x01') {
      if (div_mode != '\x02') {
        report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        return local_2;
      }
      return 0xae;
    }
    return 0xad;
  case IL_SR:
  case IL_A_SR:
    if ((((node->type & 4) == 0) && (type_bits = node->type & 0xe0, type_bits != 0x80)) &&
       (type_bits != 0x40)) {
      return 0x10;
    }
    return 0xf;
  case IL_A_SL:
    return 0xe;
  case IL_EQ:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return (-(ushort)(node->desc->false_label == 0) & 0xfffe) + 0x3e;
    }
    if (type_bits == 0x28) {
      return (-(ushort)(node->desc->false_label == 0) & 0xfffe) + 0x3d;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case IL_NE:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return (-(ushort)(node->desc->false_label == 0) & 2) + 0x3c;
    }
    if (type_bits == 0x28) {
      return (-(ushort)(node->desc->false_label == 0) & 2) + 0x3b;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case IL_LT:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return (-(ushort)((node->desc->flags2 & 0x80) == 0) & 2) + 0x40;
    }
    if (type_bits == 0x28) {
      desc = left->desc;
      type_bits = 0;
      left_ea = desc->mem_ea;
      if (left_ea != (ea *)0x0) {
        type_bits = left_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (left_ea = &desc->dest, (left_ea->type & 0x1f) == 0)) &&
         (left_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        left_ea = &desc->value;
      }
      desc = right->desc;
      type_bits = 0;
      right_ea = desc->mem_ea;
      if (right_ea != (ea *)0x0) {
        type_bits = right_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (right_ea = &desc->dest, (right_ea->type & 0x1f) == 0)) &&
         (right_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        right_ea = &desc->value;
      }
      if ((left_ea->base != '\0') && (right_ea->base != '\x01')) {
        return 0x41;
      }
      return 0x3f;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case IL_LE:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return (-(ushort)((node->desc->flags2 & 0x80) == 0) & 2) + 0x44;
    }
    if (type_bits == 0x28) {
      desc = left->desc;
      type_bits = 0;
      left_ea = desc->mem_ea;
      if (left_ea != (ea *)0x0) {
        type_bits = left_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (left_ea = &desc->dest, (left_ea->type & 0x1f) == 0)) &&
         (left_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        left_ea = &desc->value;
      }
      desc = right->desc;
      type_bits = 0;
      right_ea = desc->mem_ea;
      if (right_ea != (ea *)0x0) {
        type_bits = right_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (right_ea = &desc->dest, (right_ea->type & 0x1f) == 0)) &&
         (right_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        right_ea = &desc->value;
      }
      if ((left_ea->base != '\0') && (right_ea->base != '\x01')) {
        return 0x45;
      }
      return 0x43;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case IL_GT:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return (-(ushort)((node->desc->flags2 & 0x80) == 0) & 0xfffe) + 0x42;
    }
    if (type_bits == 0x28) {
      desc = left->desc;
      type_bits = 0;
      left_ea = desc->mem_ea;
      if (left_ea != (ea *)0x0) {
        type_bits = left_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (left_ea = &desc->dest, (left_ea->type & 0x1f) == 0)) &&
         (left_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        left_ea = &desc->value;
      }
      desc = right->desc;
      type_bits = 0;
      right_ea = desc->mem_ea;
      if (right_ea != (ea *)0x0) {
        type_bits = right_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (right_ea = &desc->dest, (right_ea->type & 0x1f) == 0)) &&
         (right_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        right_ea = &desc->value;
      }
      if ((left_ea->base != '\0') && (right_ea->base != '\x01')) {
        return 0x3f;
      }
      return 0x41;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  case IL_GE:
    type_bits = right->type & 0xf8;
    if (type_bits == 0x30) {
      return (-(ushort)((node->desc->flags2 & 0x80) == 0) & 0xfffe) + 0x46;
    }
    if (type_bits == 0x28) {
      desc = left->desc;
      type_bits = 0;
      left_ea = desc->mem_ea;
      if (left_ea != (ea *)0x0) {
        type_bits = left_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (left_ea = &desc->dest, (left_ea->type & 0x1f) == 0)) &&
         (left_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        left_ea = &desc->value;
      }
      desc = right->desc;
      type_bits = 0;
      right_ea = desc->mem_ea;
      if (right_ea != (ea *)0x0) {
        type_bits = right_ea->type & 0x1f;
      }
      if (((type_bits == 0) && (right_ea = &desc->dest, (right_ea->type & 0x1f) == 0)) &&
         (right_ea = &g_ea_pop, (desc->flags2 & 8) == 0)) {
        right_ea = &desc->value;
      }
      if ((left_ea->base != '\0') && (right_ea->base != '\x01')) {
        return 0x43;
      }
      return 0x45;
    }
    report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
    return local_2;
  }
  type_bits = right->type;
  type_class = type_bits & 0xf8;
  if (type_class == 0x30) {
    if ((op == IL_A_DIV) && ((left->type & 0xf8) != 0x30)) {
      return 0x2b;
    }
    return ((node->desc->flags2 & 0x80) == 0) + 0x2b;
  }
  if (type_class == 0x28) {
    return 0x2a;
  }
  if ((type_class != 0x18) && (type_class != 0x10)) {
    if (type_class == 8) {
      if ((((type_bits & 4) == 0) && ((type_bits & 0xe0) != 0x80)) && ((type_bits & 0xe0) != 0x40))
      {
        return 2;
      }
      return 5;
    }
    if (type_class != 0) {
      report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return local_2;
    }
    if ((((type_bits & 4) == 0) && ((type_bits & 0xe0) != 0x80)) && ((type_bits & 0xe0) != 0x40)) {
      return 1;
    }
    return 4;
  }
  if (((type_bits & 4) != 0) || (((type_bits & 0xe0) == 0x80 || ((type_bits & 0xe0) == 0x40)))) {
    return 6;
  }
  div_mode = g_request->div_routine_variant;
  if (div_mode == '\0') {
    return 3;
  }
  if (div_mode != '\x01') {
    if (div_mode != '\x02') {
      report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return local_2;
    }
    return 0xac;
  }
  return 0xab;
}



