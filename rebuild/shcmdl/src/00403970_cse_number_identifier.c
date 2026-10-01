#include "decls.h"
#include "imports.h"

// entry: 00403970
// name : cse_number_identifier
// size : 260
// sig  : void cse_number_identifier(il_node * node)


int __cdecl cse_number_identifier(il_node *node)

{
  byte type_class;
  short leafno;
  il_op parent_op;
  
  parent_op = node->parent->op;
  if (parent_op != IL_AMPER) {
    type_class = node->type & 0xf0;
    if ((((type_class != 0x60) && (type_class != 0x70)) && ((node->type & 2) == 0)) &&
       (leafno = node->nleaf, (g_leaf_table[leafno].flag & 7) == 0)) {
      if ((((&g_op_class)[(char)parent_op] & 0x20) != 0) && (node->parent->child == node)) {
        if (g_leaf_table[leafno].lastnd != (il_node *)0x0) {
          cse_count_leaf_redefinition(node);
          cse_clear_value_number(node);
          return;
        }
        cse_new_value_number(node);
        g_leaf_table[node->nleaf].lastnd = node;
        cse_record_leaf_definition(node);
        return;
      }
      if (g_leaf_table[leafno].lastnd != (il_node *)0x0) {
        cse_join_value_class(g_leaf_table[leafno].lastnd,node);
        return;
      }
      if (((g_cse_nesting == '\0') && (g_cse_cond_depth == '\0')) &&
         (g_cse_has_goto_or_label != '\x01')) {
        cse_new_value_number(node);
        g_leaf_table[node->nleaf].lastnd = node;
        cse_record_leaf_definition(node);
        return;
      }
      cse_clear_value_number(node);
      return;
    }
  }
  cse_clear_value_number(node);
  return;
}



