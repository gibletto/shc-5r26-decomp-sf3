#include "decls.h"
#include "imports.h"

// entry: 00403a80
// name : cse_number_operator
// size : 130
// sig  : void cse_number_operator(il_node * node)


int __cdecl cse_number_operator(il_node *node)

{
  il_node *piVar1;
  bool all_numbered;
  
  all_numbered = true;
  piVar1 = node->child;
  do {
    if (piVar1 == (il_node *)0x0) {
LAB_00403aa1:
      if (!all_numbered) {
        cse_clear_value_number(node);
        return;
      }
      piVar1 = cse_find_expression(node);
      if (piVar1 != (il_node *)0x0) {
        cse_join_value_class(piVar1,node);
        return;
      }
      if (((g_cse_nesting == '\0') && (g_cse_cond_depth == '\0')) &&
         (g_cse_has_goto_or_label != '\x01')) {
        cse_new_value_number(node);
        cse_add_expression(node);
        return;
      }
      cse_clear_value_number(node);
      return;
    }
    if (piVar1->pp == 0) {
      all_numbered = false;
      goto LAB_00403aa1;
    }
    piVar1 = piVar1->next;
  } while( true );
}



