#include "decls.h"
#include "imports.h"

// entry: 0040a120
// name : dag_assignment
// size : 597
// sig  : void dag_assignment(il_node * node)


int __cdecl dag_assignment(il_node *node)

{
  byte type_class;
  il_node *head;
  byte *flag_hi;
  ushort *flag_ptr;
  ushort leaf_flags;
  ushort leaf_flags2;
  il_node *lhs;
  il_op lhs_op;
  
  lhs = node->child;
  lhs_op = lhs->op;
  if (((lhs_op == IL_ID) && ((lhs->type & 2) == 0)) && ((g_leaf_table[lhs->nleaf].flag & 2) == 0)) {
    if (node->op == IL_ASSIGN) {
      clear_common_links(lhs);
      head = g_leaf_table[lhs->nleaf].lastnd;
      if (head == (il_node *)0x0) {
        record_defined_leaf(lhs);
      }
      else if (head->refchn == (il_node *)0x0) {
        if (((&g_op_class)[(char)head->op] & 0x20) == 0) {
          head->flag = head->flag | 0x180;
        }
      }
      else {
        flag_ptr = &head->refchn->flag;
        *flag_ptr = *flag_ptr | 0x180;
      }
    }
    else {
      head = g_leaf_table[lhs->nleaf].lastnd;
      if (head == (il_node *)0x0) {
        start_common_chain(lhs);
        type_class = lhs->type & 0xf0;
        if (((type_class == 0x60) || (type_class == 0x70)) ||
           ((g_leaf_table[lhs->nleaf].flag & 7) != 0)) {
          lhs->duptr = (dutbl *)0x0;
        }
        else {
          new_web(lhs);
        }
        record_defined_leaf(lhs);
      }
      else {
        link_common_chain(head,lhs);
        if ((((lhs->refchn == (il_node *)0x0) &&
             (((&g_op_class)[(char)lhs->cmnexp->op] & 0x20) != 0)) &&
            (type_class = lhs->type & 0xf0, type_class != 0x60)) &&
           ((type_class != 0x70 && ((g_leaf_table[lhs->nleaf].flag & 7) == 0)))) {
          new_web(lhs);
        }
        else {
          lhs->duptr = (dutbl *)0x0;
        }
      }
      lhs->flag = lhs->flag | 0x180;
      if (g_make_du != '\0') {
        record_block_use(lhs);
      }
    }
    node->cmnexp = node;
    node->refcnt = 0;
    node->refchn = (il_node *)0x0;
    if (((node->op == IL_POI) || (node->op == IL_POD)) || (node->child->type != node->type)) {
      node->pp = 0;
    }
    else {
      g_value_number = g_value_number + 1;
      node->pp = g_value_number;
    }
    g_leaf_table[lhs->nleaf].lastnd = node;
    type_class = lhs->type & 0xf0;
    if (((type_class == 0x60) || (type_class == 0x70)) ||
       ((type_class == 0x80 ||
        ((type_class == 0x90 ||
         ((*(unsigned char *)((char *)&leaf_flags + 0)) = g_leaf_table[lhs->nleaf].flag,
         (*(unsigned char *)((char *)&leaf_flags + 1)) = g_leaf_table[lhs->nleaf].unknown_0f, (leaf_flags & 5) != 0)))))) {
      free_dag_node_list();
      node->duptr = (dutbl *)0x0;
      return;
    }
    new_web(node);
    if ((head != (il_node *)0x0) && (((&g_op_class)[(char)head->op] & 0x20) != 0)) {
      flag_hi = (byte *)((int)&node->flag + 1);
      *flag_hi = *flag_hi | 0x10;
      return;
    }
  }
  else {
    if (((&g_op_class)[(char)lhs_op] & 0x10) != 0) {
      clear_common_links(node);
      invalidate_memory_leaf_values();
      free_dag_node_list();
      return;
    }
    if (((lhs_op == IL_ID) && ((lhs->type & 2) == 0)) &&
       ((((type_class = lhs->type & 0xf0, type_class == 0x60 ||
          ((type_class == 0x70 || (type_class == 0x80)))) || (type_class == 0x90)) ||
        ((*(unsigned char *)((char *)&leaf_flags2 + 0)) = g_leaf_table[lhs->nleaf].flag,
        (*(unsigned char *)((char *)&leaf_flags2 + 1)) = g_leaf_table[lhs->nleaf].unknown_0f, (leaf_flags2 & 5) != 0)))) {
      clear_common_links(node);
      free_dag_node_list();
      return;
    }
    clear_common_links(node);
  }
  return;
}



