#include "decls.h"
#include "imports.h"
#include "argconst.h"

// entry: 00404010
// name : cse_replace_with_temporary
// size : 380
// sig  : il_node * cse_replace_with_temporary(il_node * node, node_list * stmt, bblock * block)


il_node * __cdecl cse_replace_with_temporary(il_node *node,node_list *stmt,bblock *block)

{
  bool bVar1;
  int iVar2;
  int child_rank;
  il_node *parent;
  il_node *temp;
  il_node *temp_copy;
  byte type;
  bblock *blk;
  node_list *cell;
  il_node *member;
  il_node *next_member;
  il_op parent_op;
  ushort refcnt;
  
  if (node->op == IL_CAST) {
    iVar2 = node_type_rank(node);
    child_rank = CAST_OPERAND_RANK(node->child);
    if ((iVar2 <= child_rank) && (child_rank != 4)) {
      bVar1 = false;
      goto LAB_00404046;
    }
  }
  bVar1 = true;
LAB_00404046:
  parent = node;
  if (((bVar1) &&
      ((((type = node->type, (type & 0xe0) == 0 || ((type & 0xf8) == 0x28)) ||
        ((type & 0xf8) == 0x40)) || (((type & 0xf0) == 0x80 || ((type & 0xf0) == 0x90)))))) &&
     (node->cse_head == node)) {
    refcnt = node->refcnt;
    if ((1 < refcnt) &&
       ((node->parent->refcnt < refcnt ||
        (((1 < refcnt && (parent_op = node->parent->op, 'O' < (char)parent_op)) &&
         ((char)parent_op < '`')))))) {
      g_cse_changed = '\x01';
      type = node->type;
      if (((type & 0xf0) == 0x80) || ((type & 0xf0) == 0x90)) {
        type = 0x40;
      }
      parent = new_node(IL_ASSIGN,type);
      parent->filn = node->filn;
      parent->line = node->line;
      parent->listno = node->listno;
      temp = new_temp_id(type);
      insert_parent(node,parent);
      insert_before(node,temp);
      next_member = node->cse_next;
joined_r0x00404122:
      member = next_member;
      if (member != (il_node *)0x0) {
        temp_copy = copy_tree(1,temp);
        next_member = member->cse_next;
        iVar2 = operand_index(member);
        replace_operand(member->parent,temp_copy,iVar2);
        bVar1 = false;
        for (blk = block; blk != (bblock *)0x0; blk = blk->f_next) {
          for (cell = blk->ilnode; cell != (node_list *)0x0; cell = cell->next) {
            if (cell->node == member) {
              bVar1 = true;
              cell->node = temp_copy;
              break;
            }
          }
          if (bVar1) break;
        }
        goto joined_r0x00404122;
      }
    }
  }
  return parent;
}



