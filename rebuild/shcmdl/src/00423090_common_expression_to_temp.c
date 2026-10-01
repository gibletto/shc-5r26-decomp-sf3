#include "decls.h"
#include "imports.h"
#include "argconst.h"

// entry: 00423090
// name : common_expression_to_temp
// size : 722
// sig  : il_node * common_expression_to_temp(il_node * node, node_list * stmt, bblock * block)


il_node * __cdecl common_expression_to_temp(il_node *node,node_list *stmt,bblock *block)

{
  char conditional;
  int child_rank;
  il_node *temp_copy;
  int iVar1;
  byte bVar2;
  il_node *cur_ref;
  il_node *scaled_ref;
  byte type;
  il_node *assign;
  il_node *temp;
  bool candidate;
  node_list *link;
  il_op parent_op;
  il_node *ref;
  ushort ref_count;
  il_op ref_parent_op;
  
  candidate = false;
  switch(node->op) {
  case IL_CAST:
    iVar1 = node_type_rank(node);
    child_rank = CAST_OPERAND_RANK(node->child);
    if ((((iVar1 <= child_rank) && (child_rank != 4)) && (child_rank != 5)) && (child_rank != 6))
    goto switchD_004230b4_caseD_21;
  case IL_PLUS:
  case IL_MINUS:
  case IL_ASTER:
  case IL_CMPL:
  case IL_QUALIFY:
  case IL_ADD:
  case IL_SUB:
  case IL_MUL:
  case IL_DIV:
  case IL_MOD:
  case IL_SL:
  case IL_SR:
  case IL_B_AND:
  case IL_B_XOR:
  case IL_B_OR:
    candidate = true;
  default:
switchD_004230b4_caseD_21:
    if (((candidate) &&
        (((bVar2 = node->type, (bVar2 & 0xe0) == 0 || ((bVar2 & 0xf8) == 0x28)) ||
         (((bVar2 & 0xf8) == 0x40 || (((bVar2 & 0xf0) == 0x80 || ((bVar2 & 0xf0) == 0x90)))))))) &&
       (node->cmnexp == node)) {
      parent_op = node->parent->op;
      scaled_ref = (il_node *)0x0;
      for (ref = node; ref != (il_node *)0x0; ref = ref->refchn) {
        cur_ref = ref;
        if (((((ref->op == IL_CAST) && ((ref->type & 0xe0) == 0)) && (ref->child->op == IL_ID)) &&
            ((bVar2 = ref->child->type & 0xf8, bVar2 == 8 || (bVar2 == 0)))) &&
           ((ref_parent_op = ref->parent->op, ref_parent_op == IL_MUL || (ref_parent_op == IL_A_MUL)
            ))) {
          node->refcnt = node->refcnt - 1;
          cur_ref = scaled_ref;
        }
        scaled_ref = cur_ref;
      }
      ref_count = node->refcnt;
      if ((1 < ref_count) &&
         ((node->parent->refcnt < ref_count ||
          (((1 < ref_count && ('O' < (char)parent_op)) && ((char)parent_op < '`')))))) {
        bVar2 = node->type;
        if (((bVar2 & 0xf0) == 0x80) || (type = bVar2, (bVar2 & 0xf0) == 0x90)) {
          type = 0x40;
        }
        if ((((node->op == IL_CAST) && ((bVar2 & 0xe0) == 0)) && (node->child->op == IL_ID)) &&
           (((bVar2 = node->child->type & 0xf8, bVar2 == 8 || (bVar2 == 0)) &&
            ((parent_op = node->parent->op, parent_op == IL_MUL || (parent_op == IL_A_MUL)))))) {
          if ((scaled_ref != (il_node *)0x0) &&
             (conditional = is_conditionally_evaluated(scaled_ref), conditional != '\0')) {
            return node;
          }
          assign = new_node(IL_ASSIGN,type);
          assign->filn = scaled_ref->filn;
          assign->line = scaled_ref->line;
          assign->listno = scaled_ref->listno;
          temp = new_temp_id(type);
          insert_parent(scaled_ref,assign);
          insert_before(scaled_ref,temp);
        }
        else {
          assign = new_node(IL_ASSIGN,type);
          assign->filn = node->filn;
          assign->line = node->line;
          assign->listno = node->listno;
          temp = new_temp_id(type);
          insert_parent(node,assign);
          scaled_ref = (il_node *)0x0;
          insert_before(node,temp);
        }
        ref = node->refchn;
        while (cur_ref = ref, node = assign, cur_ref != (il_node *)0x0) {
          if ((scaled_ref == cur_ref) ||
             ((((cur_ref->op == IL_CAST && ((cur_ref->type & 0xe0) == 0)) &&
               (cur_ref->child->op == IL_ID)) &&
              (((bVar2 = cur_ref->child->type & 0xf8, bVar2 == 8 || (bVar2 == 0)) &&
               ((parent_op = cur_ref->parent->op, parent_op == IL_MUL || (parent_op == IL_A_MUL)))))
              ))) {
            ref = cur_ref->refchn;
          }
          else {
            temp_copy = copy_tree(1,temp);
            unlink_from_common_expression_chains(cur_ref);
            ref = cur_ref->refchn;
            iVar1 = operand_index(cur_ref);
            replace_operand(cur_ref->parent,temp_copy,iVar1);
            for (link = block->ilnode; link != (node_list *)0x0; link = link->next) {
              if (link->node == cur_ref) {
                link->node = temp_copy;
              }
            }
          }
        }
      }
    }
    return node;
  }
}



