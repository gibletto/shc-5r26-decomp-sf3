#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 004198a0
// name : is_immediate_operand
// size : 1201
// sig  : int is_immediate_operand(il_node * op, int operand_no, uint value)


int __cdecl is_immediate_operand(il_node *op,int operand_no,uint value)

{
  unsigned char _frec_20[32];
#define terms (*(char (*)[32])(_frec_20 + 0))
  il_node *operand;
  uint argreg;
  byte kind;
  int result;
  il_op opc;
  
  if (((((op->type & 0xe0) == 0x20) ||
       (operand = nth_operand(operand_no,op), (operand->type & 0xe0) == 0x20)) &&
      ((opc = op->op, (char)opc < '_' || ('i' < (char)opc)))) &&
     (((char)opc < ' ' || ('-' < (char)opc)))) {
    return 0;
  }
  result = 0;
  switch(op->op) {
  case IL_ADD:
  case IL_A_ADD:
  case IL_EQ:
  case IL_NE:
    if ((-0x81 < (int)value) && ((int)value < 0x80)) {
      return 1;
    }
    break;
  case IL_SUB:
  case IL_A_SUB:
    if (((-0x80 < (int)value) && ((int)value < 0x80)) && (operand_no == 2)) {
      return 1;
    }
    break;
  case IL_MUL:
  case IL_A_MUL:
    if (((((((-0x8001 < (int)value) && ((int)value < 0x8000)) && ((op->child->next->type & 4) == 0))
          && (operand_no == 2)) ||
         (((-1 < (int)value && ((int)value < 0x10000)) &&
          (((op->child->next->type & 4) != 0 && (operand_no == 2)))))) &&
        ((operand = op->child, operand->op == IL_CAST && ((operand->type & 0xe0) == 0)))) &&
       ((kind = operand->type & 0xf8, kind != 0 &&
        ((kind != 8 && ((kind = operand->child->type & 0xf8, kind == 0 || (kind == 8)))))))) {
      return 1;
    }
    kind = op->type & 0xf8;
    if ((kind == 0) || (kind == 8)) {
      return 1;
    }
    if (((g_options->cpu == 0) && (g_options->unknown_20 != 0)) &&
       ((value == 0x32 || (value == 100)))) {
      return 1;
    }
    result = count_shift_add_terms(terms,value,(uint)((op->type & 4) == 0));
    if (result == 1) {
      return 1;
    }
    if (result != 2) {
      return 0;
    }
    result = 1;
    if (terms[0] == '\0') {
      result = 0;
      do {
        if (terms[result] == -1) {
          return 0;
        }
        result = result + 1;
      } while (result < 0x20);
      return 1;
    }
    break;
  case IL_DIV:
  case IL_A_DIV:
    if ((((op->type & 4) == 0) && (operand_no == 2)) && (value == 2)) {
      return 1;
    }
    break;
  case IL_MOD:
  case IL_A_MOD:
    result = count_shift_add_terms(terms,value,(uint)((op->type & 4) == 0));
    if (((result == 1) && (-1 < (int)value)) && (((int)value < 0x80 && (operand_no == 2)))) {
      return 1;
    }
    return 0;
  case IL_SL:
  case IL_A_SL:
    if (((operand_no == 2) && (-1 < (int)value)) && ((int)value < 0x20)) {
      return 1;
    }
    break;
  case IL_SR:
  case IL_A_SR:
    if (operand_no == 2) {
      if ((op->type & 4) == 0) {
        if (g_options->unknown_20 == 0) {
          if (((-1 < (int)value) && ((int)value < 7)) ||
             (((0xf < (int)value && ((int)value < 0x15)) ||
              (((0x17 < (int)value && ((int)value < 0x1c)) || (value == 0x1f)))))) {
            return 1;
          }
        }
        else if ((-1 < (int)value) && ((int)value < 0x20)) {
          return 1;
        }
      }
      else if ((-1 < (int)value) && ((int)value < 0x20)) {
        return 1;
      }
    }
    break;
  case IL_B_AND:
  case IL_A_AND:
    kind = op->type & 0xf8;
    if (((kind == 8) && (-1 < (int)value)) && ((int)value < 0x100)) {
      return 1;
    }
    if ((op->type & 4) == 0) {
      if (((kind == 0) && (-0x81 < (int)value)) && ((int)value < 0x80)) {
        return 1;
      }
    }
    else if (((kind == 0) && (-1 < (int)value)) && ((int)value < 0x100)) {
      return 1;
    }
    break;
  case IL_B_XOR:
  case IL_B_OR:
  case IL_A_XOR:
  case IL_A_OR:
    kind = op->type & 0xf8;
    if (((kind == 8) && (-1 < (int)value)) && ((int)value < 0x100)) {
      return 1;
    }
    if ((op->type & 4) == 0) {
      if (((kind == 0) && (-0x81 < (int)value)) && ((int)value < 0x80)) {
        return 1;
      }
    }
    else if (((kind == 0) && (-1 < (int)value)) && ((int)value < 0x100)) {
      return 1;
    }
    break;
  case IL_ASSIGN:
    if (op->child->op == IL_B_QUALIFY) {
      return 1;
    }
    break;
  case IL_LT:
  case IL_LE:
  case IL_GT:
  case IL_GE:
    if (((op->type & 4) == 0) && (value == 0)) {
      return 1;
    }
    break;
  case IL_ARG:
    if ((-0x81 < (int)value) && ((int)value < 0x80)) {
      operand = nth_operand(operand_no,op);
      argreg = argument_register_index(operand);
      if ((int)argreg < 5) {
        result = 1;
      }
    }
  }
  return result;
#undef terms
}



