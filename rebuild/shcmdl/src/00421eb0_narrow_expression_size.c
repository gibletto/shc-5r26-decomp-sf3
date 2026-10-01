#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00421eb0
// name : narrow_expression_size
// size : 1422
// sig  : il_node * narrow_expression_size(il_node * node)


il_node * __cdecl narrow_expression_size(il_node *node)

{
  byte bVar1;
  uint kind;
  il_node *operand;
  int iVar2;
  int sign_b;
  il_node *cur;
  byte inner_type;
  uint sign_mask;
  byte bVar3;
  byte bVar4;
  byte wide_type;
  byte left_type;
  byte op_type;
  il_op op;
  il_node **operands;
  
  op = node->op;
  if (((((((char)op < ' ') || ((op & IL_NON_F0) == IL_CALL)) || ('g' < (char)op)) ||
       ((op == IL_CAST || (op == IL_PLUS)))) || (op == IL_ASTER)) ||
     (((op == IL_AMPER || (op == IL_NOT)) ||
      ((op == IL_SL || ((op == IL_SR || ((op & IL_NON_F8) == IL_EQ)))))))) {
    return node;
  }
  if ((op & IL_NON_F0) == IL_A_ADD) {
    if (((op == IL_A_SL) || (op == IL_A_SR)) || (op == IL_ASSIGN)) {
      return node;
    }
    operand = node->child->next;
    if (operand->op != IL_CAST) {
      bVar1 = operand->type & 0xf8;
      if ((bVar1 != 0) && (bVar1 != 8)) {
        operand = narrow_compound_assignment(node);
        return operand;
      }
      return node;
    }
    kind = classify_size_conversion(node->type,operand->type,operand->child->type);
    if (((node->op == IL_A_DIV) || (node->op == IL_A_MOD)) &&
       (sign_mask = (int)kind >> 0x1f, ((kind ^ sign_mask) - sign_mask & 1 ^ sign_mask) != sign_mask
       )) {
      return node;
    }
    if ((int)kind < 5) {
      if (kind != 0) {
        operand = node->child->next;
        replace_node(operand,operand->child);
        free_node(operand);
      }
    }
    else {
      node->child->next->type = node->type & 0xfc;
    }
    if (((byte)g_debug_flags & 0x10) != 0) {
      dump_tree(node,1,s_short_size_change_00435c08);
      return node;
    }
  }
  else if ((op & IL_NON_F8) == IL_EQ) {
    operands = &node->child;
    operand = *operands;
    if ((operand->op == IL_CAST) && (operand->next->op == IL_CAST)) {
      bVar1 = operand->child->type;
      bVar4 = operand->next->child->type;
      bVar3 = bVar4 & 0xfc;
      left_type = bVar1 & 0xfc;
      iVar2 = classify_size_conversion(left_type,node->type,bVar3);
      if (iVar2 != 0) {
        if (((bVar1 & 0xe0) != 0) || (iVar2 = 1, (bVar1 & 4) == 0)) {
          iVar2 = 0;
        }
        if (((bVar4 & 0xe0) != 0) || (sign_b = 1, (bVar4 & 4) == 0)) {
          sign_b = 0;
        }
        if (iVar2 != sign_b) {
          return node;
        }
        if ((char)left_type < (char)bVar3) {
          (*operands)->type = bVar3;
        }
        else {
          operand = *operands;
          replace_node(operand,operand->child);
          free_node(operand);
        }
        if ((char)bVar3 < (char)left_type) {
          (*operands)->next->type = left_type;
        }
        else {
          operand = (*operands)->next;
          replace_node(operand,operand->child);
          free_node(operand);
        }
      }
      if (((byte)g_debug_flags & 0x10) != 0) {
        dump_tree(node,1,s_short_size_change_00435c08);
        return node;
      }
    }
  }
  else if (node->parent->op == IL_CAST) {
    bVar1 = node->parent->type;
    bVar4 = bVar1 & 0xfc;
    operand = node->child;
    op_type = node->type & 0xfc;
    wide_type = 0xff;
    for (; operand != (il_node *)0x0; operand = operand->next) {
      op = node->op;
      if (operand->op == IL_CAST) {
        if (((op != IL_SL) && (op != IL_SR)) || (iVar2 = operand_index(operand), iVar2 != 2)) {
          op = node->op;
          bVar3 = operand->child->type;
          inner_type = bVar3 & 0xfc;
          if (((((op & IL_NON_F0) == IL_CAST) || ((op & IL_NON_F0) == IL_CALL)) && (op != IL_CALL))
             || ((op == IL_SL || (op == IL_SR)))) {
            if (inner_type != bVar4) {
              return node;
            }
          }
          else if (((inner_type ^ bVar4) & 0xf8) == 0) {
            if (((op == IL_DIV) || (op == IL_MOD)) || (op == IL_SR)) {
              if (((bVar3 & 0xe0) != 0) || (iVar2 = 1, (bVar3 & 4) == 0)) {
                iVar2 = 0;
              }
              if (((bVar1 & 0xe0) != 0) || (sign_b = 1, (bVar1 & 4) == 0)) {
                sign_b = 0;
              }
              if (iVar2 != sign_b) {
                return node;
              }
            }
          }
          else {
            if (wide_type != 0xff) {
              return node;
            }
            if (op != IL_MUL) {
              wide_type = inner_type;
            }
          }
        }
      }
      else {
        if ((op == IL_DIV) || (op == IL_MOD)) {
          return node;
        }
        if (((op == IL_SL) || (op == IL_SR)) && (iVar2 = operand_index(operand), iVar2 == 1)) {
          return node;
        }
      }
    }
    kind = classify_size_conversion(bVar4,op_type,wide_type);
    if (kind != 0) {
      sign_mask = (int)kind >> 0x1f;
      if ((((kind ^ sign_mask) - sign_mask & 1 ^ sign_mask) != sign_mask) &&
         (((op = node->op, op == IL_DIV || (op == IL_MOD)) || (op == IL_SR)))) {
        return node;
      }
      operand = node->child;
      while (operand != (il_node *)0x0) {
        cur = operand;
        if (operand->op == IL_CAST) {
          bVar1 = operand->child->type & 0xfc;
          if (((node->op != IL_SL) && (node->op != IL_SR)) ||
             (iVar2 = operand_index(operand), iVar2 != 2)) {
            op = node->op;
            if (op == IL_DIV) {
LAB_0042230c:
              bVar3 = wide_type;
              if ((char)wide_type <= (char)bVar4) {
                bVar3 = bVar4;
              }
              if (bVar3 != bVar1) {
LAB_00422336:
                if (((op == IL_DIV) || (op == IL_MOD)) || (op == IL_SR)) {
                  bVar1 = wide_type;
                  if ((char)wide_type <= (char)bVar4) {
                    bVar1 = bVar4;
                  }
                  operand->type = bVar1;
                }
                else {
                  operand->type = bVar4;
                }
                goto LAB_0042237d;
              }
            }
            else if (((op == IL_MOD) || (op == IL_SR)) || (bVar1 != bVar4)) {
              if (((op == IL_DIV) || (op == IL_MOD)) || (op == IL_SR)) goto LAB_0042230c;
              goto LAB_00422336;
            }
            cur = operand->child;
            replace_node(operand,cur);
            free_node(operand);
          }
        }
        else if ((node->op != IL_SL) && (node->op != IL_SR)) {
          cur = new_node(IL_CAST,bVar4);
          insert_parent(operand,cur);
        }
LAB_0042237d:
        operand = cur->next;
      }
      if ((kind == 4) && (((op = node->op, op == IL_DIV || (op == IL_MOD)) || (op == IL_SR)))) {
        node->type = wide_type;
      }
      else {
        node->type = bVar4;
        operand = node->parent;
        replace_node(operand,node);
        free_node(operand);
      }
      if (((byte)g_debug_flags & 0x10) != 0) {
        dump_tree(node,1,s_short_size_change_00435c08);
        return node;
      }
    }
  }
  else if ((op == IL_B_AND) && (iVar2 = is_condition_operand(node), iVar2 != 0)) {
    operand = node->child;
    if (((operand->op == IL_CAST) && ((op = operand->next->op, op == IL_CAST || (op == IL_CONST))))
       || ((operand->op == IL_CONST && (operand->next->op == IL_CAST)))) {
      node = narrow_bit_test_to_char(operand,operand->next);
    }
  }
  return node;
}



