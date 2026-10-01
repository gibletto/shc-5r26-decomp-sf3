#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))


// entry: 00413850
// name : remove_unused_parameter_assignments
// size : 115
// sig  : void remove_unused_parameter_assignments(void)


int __cdecl remove_unused_parameter_assignments(void)

{
  il_node *node;
  il_node **node_link;
  node_list *item;
  node_list **link;
  node_list *next;
  
  item = g_f_chain->ilnode;
  if (item != (node_list *)0x0) {
    node_link = &g_func_node->child->child;
    link = &g_f_chain->ilnode;
    while (item != (node_list *)0x0) {
      node = item->node;
      next = item->next;
      if (((node->flag & 0x10) == 0) || (node->child->lreg != 0)) {
        node_link = &node->next;
        link = &item->next;
        item = next;
      }
      else {
        *link = next;
        pool_free(item,8);
        *node_link = node->next;
        free_tree(node->child);
        free_node(node);
        item = next;
      }
    }
  }
  return;
}



