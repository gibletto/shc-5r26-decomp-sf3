#include "decls.h"
#include "imports.h"

// entry: 00422850
// name : narrow_compound_assignment
// size : 409
// sig  : il_node * narrow_compound_assignment(il_node * node)


il_node * __cdecl narrow_compound_assignment(il_node *node)

{
  il_node *old_node;
  byte narrow_type;
  int iVar1;
  int rhs_signed;
  il_node **inner_ptr;
  byte node_type;
  il_op op;
  il_node *rhs;
  byte rhs_type;
  
  node_type = node->type;
  narrow_type = node_type & 0xfc;
  rhs_type = node->child->next->type;
  iVar1 = classify_size_conversion(narrow_type,rhs_type & 0xfc,0xff);
  if ((iVar1 < 1) || (2 < iVar1)) {
    return node;
  }
  rhs = node->child->next;
  op = node->op;
  if ((op == IL_A_DIV) || (op == IL_A_MOD)) {
    if (((node_type & 0xe0) != 0) || (iVar1 = 1, (node_type & 4) == 0)) {
      iVar1 = 0;
    }
    if (((rhs_type & 0xe0) != 0) || (rhs_signed = 1, (rhs_type & 4) == 0)) {
      rhs_signed = 0;
    }
    if (iVar1 != rhs_signed) {
      return node;
    }
    op = rhs->op;
    if ((((((op & IL_NON_F0) == IL_CAST) || ((op & IL_NON_F0) == IL_CALL)) && (op != IL_CALL)) &&
        (((char)op < '.' && (op != IL_ASTER)))) &&
       ((op != IL_AMPER && (old_node = rhs->child, old_node->op == IL_CAST)))) {
      inner_ptr = &old_node->child;
      if (((*inner_ptr)->type & 2) == 0) {
        iVar1 = classify_size_conversion(narrow_type,rhs_type & 0xfc,(*inner_ptr)->type & 0xfc);
        if ((iVar1 != 2) && (iVar1 != 6)) {
          return node;
        }
        rhs->type = narrow_type;
        (*inner_ptr)->type = narrow_type;
        replace_node(old_node,*inner_ptr);
        *inner_ptr = (il_node *)0x0;
        free_node(old_node);
      }
    }
  }
  else if ((('O' < (char)op) && ((char)op < 'U')) || (('[' < (char)op && ((char)op < '_')))) {
    op = rhs->op;
    if ((('?' < (char)op) && ((char)op < 'E')) || (('K' < (char)op && ((char)op < 'O')))) {
      rhs->type = narrow_type;
      cast_operands_to_node_type(rhs);
      return node;
    }
    if ((op == IL_MINUS) || (op == IL_CMPL)) {
      rhs->type = narrow_type;
      cast_operands_to_node_type(rhs);
      return node;
    }
  }
  return node;
}



