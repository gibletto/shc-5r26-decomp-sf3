#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041db10
// name : resolve_macro_psd_op
// size : 1407
// sig  : ushort resolve_macro_psd_op(gen_node * node, ushort macro_op, uchar * size_out)


ushort __cdecl resolve_macro_psd_op(gen_node *node,ushort macro_op,uchar *size_out)

{
  byte type_bits;
  uchar size_code;
  int iVar1;
  int iVar2;
  gen_node *right;
  char builtin_id;
  bool is_unsigned;
  gen_node *operand;
  
  right = (gen_node *)0x0;
  operand = node->child;
  if (operand != (gen_node *)0x0) {
    right = operand->next;
  }
  *size_out = '\x02';
  if (macro_op < 0x301) {
    if (macro_op != 0x300) {
      if (macro_op == 0x200) {
LAB_0041dbef:
        switch(node->op) {
        case IL_MINUS:
          return 0x78;
        default:
          report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
          return macro_op;
        case IL_CMPL:
          return 0x83;
        case IL_B_AND:
          return (-(ushort)((node->desc->flags7 & 1) == 0) & 0xfffb) + 0x85;
        case IL_B_XOR:
        case IL_A_XOR:
          return 0x82;
        case IL_B_OR:
        case IL_A_OR:
          return 0x81;
        case IL_A_AND:
          return 0x80;
        case IL_ARG:
          goto switchD_0041dc02_caseD_78;
        }
      }
      goto LAB_0041dbbf;
    }
  }
  else {
    if (macro_op < 0x501) {
      if (macro_op == 0x500) goto LAB_0041dbef;
      if (macro_op != 0x400) goto LAB_0041dbbf;
      type_bits = node->type & 0xf8;
      if ((type_bits == 0) || (type_bits == 8)) {
        if (((right->type & 4) == 0) &&
           ((type_bits = right->type & 0xe0, type_bits != 0x80 && (type_bits != 0x40)))) {
          return 0x70;
        }
        return 0x71;
      }
      if ((((type_bits != 0x10) && (type_bits != 0x18)) && ((node->type & 0xe0) != 0x40)) ||
         (iVar1 = mul_fits_16bit_multiply(node), iVar1 == 0)) {
        if (g_request->cpu != 0) {
          return 0x6f;
        }
        report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        return 0x6f;
      }
      if (operand->op == IL_CAST) {
        if (right->op != IL_CAST) goto LAB_0041de25;
        type_bits = operand->child->type;
        if ((((type_bits & 4) != 0) || (type_bits = type_bits & 0xe0, type_bits == 0x80)) ||
           (iVar1 = 0, type_bits == 0x40)) {
          iVar1 = 1;
        }
        type_bits = right->child->type;
        if ((((type_bits & 4) != 0) || (type_bits = type_bits & 0xe0, type_bits == 0x80)) ||
           (iVar2 = 0, type_bits == 0x40)) {
          iVar2 = 1;
        }
        if (iVar1 != iVar2) {
          return 0x70;
        }
      }
      if (right->op == IL_CAST) {
        type_bits = right->child->type;
        if ((type_bits & 4) != 0) {
          return 0x71;
        }
        type_bits = type_bits & 0xe0;
        if (type_bits == 0x80) {
          return 0x71;
        }
        if (type_bits == 0x40) {
          return 0x71;
        }
      }
LAB_0041de25:
      if ((operand->op == IL_CAST) &&
         (((type_bits = operand->child->type, (type_bits & 4) != 0 ||
           (type_bits = type_bits & 0xe0, type_bits == 0x80)) || (type_bits == 0x40)))) {
        return 0x71;
      }
      return 0x70;
    }
    if (macro_op < 0x701) {
      if (macro_op == 0x700) {
        switch(node->op) {
        case IL_LT:
        case IL_GE:
          return 0x55;
        case IL_LE:
        case IL_GT:
          return 0x56;
        default:
          report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
          return 0x700;
        }
      }
      if (macro_op == 0x600) {
        if ((((right->type & 4) == 0) && (type_bits = right->type & 0xe0, type_bits != 0x80)) &&
           (type_bits != 0x40)) {
          switch(node->op) {
          case IL_LT:
          case IL_GE:
            return 0x52;
          case IL_LE:
          case IL_GT:
            return 0x54;
          default:
            report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0)
            ;
            return 0x600;
          }
        }
        switch(node->op) {
        case IL_LT:
        case IL_GE:
          return 0x51;
        case IL_LE:
        case IL_GT:
          return 0x53;
        default:
          report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
          return 0x600;
        }
      }
LAB_0041dbbf:
      report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
      return macro_op;
    }
    if (macro_op < 0x1601) {
      if (macro_op != 0x1600) {
        if (macro_op == 0x800) {
          switch(node->op) {
          case IL_LT:
          case IL_GE:
            return 0x56;
          case IL_LE:
          case IL_GT:
            return 0x55;
          default:
            report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0)
            ;
            return 0x800;
          }
        }
        goto LAB_0041dbbf;
      }
    }
    else if (macro_op != 0x1700) {
      if (macro_op == 0x2300) {
        if (((((node->type & 4) == 0) && (type_bits = node->type & 0xe0, type_bits != 0x80)) &&
            (type_bits != 0x40)) &&
           (((operand->op != IL_CAST || (operand->child == (gen_node *)0x0)) ||
            (((type_bits = operand->child->type, (type_bits & 4) == 0 &&
              (((type_bits & 0xe0) != 0x80 && ((type_bits & 0xe0) != 0x40)))) ||
             (((type_bits & 0xf8) != 0 && ((type_bits & 0xf8) != 8)))))))) {
          return 0x48;
        }
        return 0x58;
      }
      if (macro_op != 0x4200) goto LAB_0041dbbf;
    }
  }
  if (macro_op == 0x300) {
    iVar1 = node_value_size(operand);
    iVar2 = node_value_size(node);
    if (iVar2 <= iVar1) goto LAB_0041dd1a;
  }
  else {
LAB_0041dd1a:
    if (macro_op != 0x1600) {
      operand = node;
      if ((((node->type & 4) != 0) || (type_bits = node->type & 0xe0, type_bits == 0x80)) ||
         (is_unsigned = false, type_bits == 0x40)) {
        is_unsigned = true;
      }
      goto LAB_0041dd5b;
    }
  }
  if ((((operand->type & 4) != 0) || (type_bits = operand->type & 0xe0, type_bits == 0x80)) ||
     (is_unsigned = false, type_bits == 0x40)) {
    is_unsigned = true;
  }
LAB_0041dd5b:
  size_code = psd_size_code_of_node(operand);
  *size_out = size_code;
  return 0x7c - !is_unsigned;
switchD_0041dc02_caseD_78:
  builtin_id = node->desc->builtin;
  if (builtin_id == '\r') {
    return 0x80;
  }
  if (builtin_id == '\x0e') {
    return 0x81;
  }
  if (builtin_id == '\x0f') {
    return 0x82;
  }
  report_codegen_message(0x11fc,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  return macro_op;
}



