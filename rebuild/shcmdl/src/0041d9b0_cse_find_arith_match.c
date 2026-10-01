#include "decls.h"
#include "imports.h"

// entry: 0041d9b0
// name : cse_find_arith_match
// size : 296
// sig  : il_node * cse_find_arith_match(il_node * node)


il_node * __cdecl cse_find_arith_match(il_node *node)

{
  il_node *piVar1;
  il_node *piVar2;
  int lhs_vn;
  uint hash;
  int iVar3;
  uint sign;
  int cand_rhs_vn;
  int rhs_vn;
  byte cand_type;
  node_list *item;
  byte node_type;
  il_op op;
  
  piVar1 = node->child;
  piVar2 = piVar1->next;
  if (piVar1->cse_head == piVar1) {
    return (il_node *)0x0;
  }
  if (piVar2 != (il_node *)0x0) {
    if (piVar2->cse_head == piVar2) {
      return (il_node *)0x0;
    }
    if (piVar2 != (il_node *)0x0) {
      iVar3 = (int)(short)piVar2->pp;
      goto LAB_0041d9eb;
    }
  }
  iVar3 = 0;
LAB_0041d9eb:
  lhs_vn = (int)(short)piVar1->pp;
  op = node->op;
  hash = lhs_vn + (char)op + iVar3;
  sign = (int)hash >> 0x1f;
  if (piVar2 == (il_node *)0x0) {
    rhs_vn = 0;
  }
  else {
    rhs_vn = (int)(short)piVar2->pp;
  }
  item = g_expr_hash[((hash ^ sign) - sign & 0x7f ^ sign) - sign];
  do {
    if (item == (node_list *)0x0) {
      return (il_node *)0x0;
    }
    piVar1 = item->node;
    cand_rhs_vn = 0;
    iVar3 = (int)(short)piVar1->child->pp;
    piVar2 = piVar1->child->next;
    if (piVar2 != (il_node *)0x0) {
      cand_rhs_vn = (int)(short)piVar2->pp;
    }
    if (piVar1->op == op) {
      cand_type = piVar1->type;
      node_type = node->type;
      if ((((cand_type ^ node_type) & 0xfc) == 0) ||
         (((((node_type & 0xe0) == 0 && ((cand_type & 0xe0) == 0)) && ((node_type & 0xf8) != 0)) &&
          ((((cand_type & 0xf8) != 0 && ((node_type & 0xf8) != 8)) &&
           (((cand_type & 0xf8) != 8 && (((cand_type ^ node_type) & 4) == 0)))))))) {
        if ((iVar3 == lhs_vn) && (cand_rhs_vn == rhs_vn)) {
          return piVar1;
        }
        if (((cand_rhs_vn == lhs_vn) && (iVar3 == rhs_vn)) && (((&g_op_class)[(char)op] & 8) != 0))
        {
          return piVar1;
        }
      }
    }
    item = item->next;
  } while( true );
}



