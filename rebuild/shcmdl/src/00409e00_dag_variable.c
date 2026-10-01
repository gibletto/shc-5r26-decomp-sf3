#include "decls.h"
#include "imports.h"

// entry: 00409e00
// name : dag_variable
// size : 391
// sig  : void dag_variable(il_node * node)


int __cdecl dag_variable(il_node *node)

{
  byte type;
  byte type_class;
  ushort leaf_flags;
  il_op parent_op;
  
  parent_op = node->parent->op;
  if ((parent_op != IL_AMPER) && (type = node->type, (type & 2) == 0)) {
    (*(unsigned char *)((char *)&leaf_flags + 0)) = g_leaf_table[node->nleaf].flag;
    (*(unsigned char *)((char *)&leaf_flags + 1)) = g_leaf_table[node->nleaf].unknown_0f;
    if ((leaf_flags & 2) == 0) {
      if ((((&g_op_class)[(char)parent_op] & 0x20) != 0) && (node->parent->child == node))
      goto LAB_00409f7d;
      if (g_leaf_table[node->nleaf].lastnd == (il_node *)0x0) {
        type_class = type & 0xf0;
        if ((((type_class == 0x60) || (type_class == 0x70)) || (type_class == 0x80)) ||
           (((type_class == 0x90 || ((type & 0xf8) == 0x48)) || ((leaf_flags & 7) != 0)))) {
          if (g_cse_cond_depth == '\0') {
            start_common_chain(node);
            g_leaf_table[node->nleaf].lastnd = node;
            record_defined_leaf(node);
          }
          else {
            clear_common_links(node);
          }
          goto LAB_00409f51;
        }
        start_common_chain(node);
        g_leaf_table[node->nleaf].lastnd = node;
        record_defined_leaf(node);
        new_web(node);
      }
      else {
        link_common_chain(g_leaf_table[node->nleaf].lastnd,node);
        if ((node->refchn == (il_node *)0x0) &&
           (((&g_op_class)[(char)node->cmnexp->op] & 0x20) != 0)) {
          type = node->type & 0xf0;
          if ((type != 0x60) &&
             ((((type != 0x70 && (type != 0x80)) && (type != 0x90)) &&
              (((node->type & 0xf8) != 0x48 && ((g_leaf_table[node->nleaf].flag & 7) == 0)))))) {
            new_web(node);
            goto LAB_00409f58;
          }
        }
LAB_00409f51:
        node->duptr = (dutbl *)0x0;
      }
LAB_00409f58:
      if (g_make_du != '\0') {
        record_block_use(node);
        node->flag = node->flag & 0xfe7f;
        return;
      }
      goto LAB_00409f7d;
    }
  }
  clear_common_links(node);
LAB_00409f7d:
  node->flag = node->flag & 0xfe7f;
  return;
}



