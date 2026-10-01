#include "decls.h"
#include "imports.h"

// entry: 0041e6b0
// name : cse_replace_with_temp
// size : 774
// sig  : il_node * cse_replace_with_temp(il_node * use_stmt, il_node * node, bblock * block)


il_node * __cdecl cse_replace_with_temp(il_node *use_stmt,il_node *node,bblock *block)

{
  unsigned char _frec_c[12];
#define res (*(il_node * *)(_frec_c + 0))
#define skip_cast (*(il_node * *)(_frec_c + 4))
#define temp (*(il_node * *)(_frec_c + 8))
  byte ty;
  int iVar1;
  int child_rank;
  il_node *piVar2;
  il_node *piVar3;
  char eligible;
  bool appended;
  bblock *blk;
  ushort count;
  bool found;
  node_list *item;
  il_node *member;
  il_op parent_op;
  uchar *type_ptr;
  
  eligible = '\0';
  skip_cast = (il_node *)0x0;
  if (node->op == IL_CAST) {
    iVar1 = node_type_rank(node);
    child_rank = node_type_rank(node->child);
    if ((child_rank < iVar1) || (child_rank == 4)) {
      eligible = '\x01';
    }
  }
  else {
    eligible = '\x01' - (node->op == IL_NOT);
  }
  if (eligible == '\0') {
    return node;
  }
  type_ptr = &node->type;
  ty = *type_ptr;
  if (((((ty & 0xe0) != 0) && ((ty & 0xf8) != 0x28)) && ((ty & 0xf8) != 0x40)) &&
     (((ty & 0xf0) != 0x80 && ((ty & 0xf0) != 0x90)))) {
    return node;
  }
  if (node->cse_head != node) {
    return node;
  }
  piVar2 = node->parent;
  for (member = node; member != (il_node *)0x0; member = member->cse_next) {
    piVar3 = member;
    if ((((member->op == IL_CAST) && ((member->type & 0xe0) == 0)) &&
        ((member->child->op == IL_ID && ((ty = member->child->type & 0xf8, ty == 8 || (ty == 0))))))
       && ((parent_op = member->parent->op, parent_op == IL_MUL || (parent_op == IL_A_MUL)))) {
      if (node == member) {
        return node;
      }
      node->refcnt = node->refcnt - 1;
      piVar3 = skip_cast;
    }
    skip_cast = piVar3;
  }
  count = node->refcnt;
  if (count < 2) {
    return node;
  }
  if (count <= piVar2->refcnt) {
    if (count < 2) {
      return node;
    }
    parent_op = piVar2->op;
    if ((char)parent_op < 'P') {
      return node;
    }
    if ('_' < (char)parent_op) {
      return node;
    }
  }
  ty = *type_ptr;
  if (((ty & 0xf0) == 0x80) || ((ty & 0xf0) == 0x90)) {
    ty = 0x40;
  }
  appended = false;
  if (use_stmt == (il_node *)0x0) {
    piVar2 = cse_append_temp_assign(block,node,ty);
    temp = piVar2->child;
    node = temp->next;
    appended = true;
    res = node;
  }
  else {
    res = new_node(IL_ASSIGN,ty);
    res->filn = node->filn;
    res->line = node->line;
    res->listno = node->listno;
    temp = new_temp_id(ty);
    *(byte *)&temp->flag2 = (byte)temp->flag2 | 0x20;
    if ((((node->op == IL_CAST) && ((*type_ptr & 0xe0) == 0)) && (node->child->op == IL_ID)) &&
       (((ty = node->child->type & 0xf8, ty == 8 || (ty == 0)) &&
        ((parent_op = node->parent->op, parent_op == IL_MUL || (parent_op == IL_A_MUL)))))) {
      insert_parent(skip_cast,res);
      insert_before(skip_cast,temp);
      for (item = block->ilnode; item != (node_list *)0x0; item = item->next) {
        if (item->node == skip_cast) {
          item->node = res;
          break;
        }
      }
      goto LAB_0041e8ef;
    }
    insert_parent(node,res);
    insert_before(node,temp);
    for (item = block->ilnode; item != (node_list *)0x0; item = item->next) {
      if (item->node == node) {
        item->node = res;
        break;
      }
    }
  }
  skip_cast = (il_node *)0x0;
LAB_0041e8ef:
  piVar2 = node->cse_next;
  do {
    while( true ) {
      member = piVar2;
      if (member == (il_node *)0x0) {
        return res;
      }
      if ((skip_cast != member) &&
         ((((member->op != IL_CAST || ((member->type & 0xe0) != 0)) ||
           ((member->child->op != IL_ID || ((ty = member->child->type & 0xf8, ty != 8 && (ty != 0)))
            ))) || ((parent_op = member->parent->op, parent_op != IL_MUL && (parent_op != IL_A_MUL))
                   )))) break;
      piVar2 = member->cse_next;
    }
    piVar3 = copy_tree(1,temp);
    piVar2 = member->cse_next;
    iVar1 = operand_index(member);
    replace_operand(member->parent,piVar3,iVar1);
    if ((node->cse_next == member) && (appended)) {
      res = piVar3;
    }
    found = false;
    for (blk = block; blk != (bblock *)0x0; blk = blk->f_next) {
      for (item = blk->ilnode; item != (node_list *)0x0; item = item->next) {
        if (item->node == member) {
          found = true;
          item->node = piVar3;
          break;
        }
      }
      if (found) break;
    }
  } while( true );
#undef res
#undef skip_cast
#undef temp
}



