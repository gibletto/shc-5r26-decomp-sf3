#include "decls.h"
#include "imports.h"

// entry: 00419300
// name : check_arith_overflow
// size : 532
// sig  : uint check_arith_overflow(il_node * op, uint value)


uint __cdecl check_arith_overflow(il_node *op,uint value)

{
  char sign_case;
  uint lhs_u;
  uint local_4;
  int lhs;
  int rhs;
  uint rhs_u;
  
  if (((op->type & 0xe0) == 0) && ((op->type & 4) != 0)) {
    lhs_u = op->child->val;
    rhs_u = op->child->next->val;
    switch(op->op) {
    case IL_ADD:
      if (lhs_u < rhs_u) {
        lhs_u = rhs_u;
      }
      return (uint)(value <= lhs_u);
    case IL_SUB:
      return -(uint)(lhs_u < rhs_u) & 2;
    default:
      return value;
    case IL_MUL:
      return (uint)(value / rhs_u != lhs_u);
    case IL_SL:
      goto switchD_0041935f_caseD_48;
    }
  }
  lhs = op->child->val;
  rhs = op->child->next->val;
  if ((lhs < 1) || (rhs < 1)) {
    if ((-1 < lhs) || (sign_case = '\x02', -1 < rhs)) {
      sign_case = (lhs < 1) + '\x03';
    }
  }
  else {
    sign_case = '\x01';
  }
  switch(op->op) {
  case IL_ADD:
    break;
  case IL_SUB:
    switch(sign_case) {
    case '\x01':
    case '\x02':
      return 0;
    case '\x03':
      return value >> 0x1f;
    case '\x04':
      return -(uint)((value & 0x80000000) == 0) & 2;
    default:
      return local_4;
    }
  default:
    return local_4;
  case IL_MUL:
    return (uint)((int)value / rhs != lhs);
  case IL_SL:
    if ((-1 < rhs) && (rhs < 0x1f)) {
      return (uint)((int)value / *(int *)(&g_pow2_table + rhs * 4) != lhs);
    }
    return 1;
  }
  switch(sign_case) {
  case '\x01':
    goto switchD_0041941b_caseD_1;
  case '\x02':
    if (((int)value < lhs) && ((int)value < rhs)) {
      return 0;
    }
    return 2;
  case '\x03':
  case '\x04':
    return 0;
  default:
    return local_4;
  }
switchD_0041935f_caseD_48:
  if (rhs_u < 0x20) {
    return (uint)(value / *(uint *)(&g_pow2_table + rhs_u * 4) != lhs_u);
  }
  return 1;
switchD_0041941b_caseD_1:
  if ((lhs < (int)value) && (rhs < (int)value)) {
    return 0;
  }
  return 1;
}



