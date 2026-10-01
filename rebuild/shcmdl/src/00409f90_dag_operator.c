#include "decls.h"
#include "imports.h"

// entry: 00409f90
// name : dag_operator
// size : 114
// sig  : void dag_operator(il_node * node)


int __cdecl dag_operator(il_node *node)

{
  il_node *piVar1;
  bool all_numbered;
  
  all_numbered = true;
  piVar1 = node->child;
  do {
    if (piVar1 == (il_node *)0x0) {
LAB_00409fb4:
      if (!all_numbered) {
        clear_common_links(node);
        return;
      }
      piVar1 = find_equal_operator(node);
      if (piVar1 != (il_node *)0x0) {
        link_common_chain(piVar1,node);
        return;
      }
      if (g_cse_cond_depth != '\0') {
        clear_common_links(node);
        return;
      }
      start_common_chain(node);
      add_operator_to_hash(node);
      return;
    }
    if (piVar1->pp == 0) {
      all_numbered = false;
      goto LAB_00409fb4;
    }
    piVar1 = piVar1->next;
  } while( true );
}



