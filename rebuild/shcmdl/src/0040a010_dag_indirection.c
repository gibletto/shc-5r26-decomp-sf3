#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 0040a010
// name : dag_indirection
// size : 258
// sig  : void dag_indirection(il_node * node)


int __cdecl dag_indirection(il_node *node)

{
  il_op iVar1;
  node_list *cell;
  ushort base_vn;
  bool found;
  il_node *ref;
  
  iVar1 = node->parent->op;
  if ((iVar1 == IL_AMPER) || ((node->type & 2) != 0)) {
    clear_common_links(node);
  }
  else if ((((&g_op_class)[(char)iVar1] & 0x20) == 0) || (node->parent->child != node)) {
    base_vn = node->child->pp;
    if (base_vn == 0) {
      clear_common_links(node);
      return;
    }
    found = false;
    cell = g_memory_refs;
    if (g_memory_refs != (node_list *)0x0) {
      iVar1 = node->op;
      do {
        ref = cell->node;
        if ((((ref->op == iVar1) && (((ref->type ^ node->type) & 0xfc) == 0)) &&
            (ref->child->pp == base_vn)) &&
           ((found = true, iVar1 == IL_ASTER ||
            (((node->val == ref->val && (node->val2 == ref->val2)) &&
             ((iVar1 != IL_B_QUALIFY || ((node->boff == ref->boff && (node->bsiz == ref->bsiz)))))))
            ))) break;
        found = false;
        cell = cell->next;
      } while (cell != (node_list *)0x0);
    }
    if (found) {
      link_common_chain(cell->node,node);
      return;
    }
    if (g_cse_cond_depth == '\0') {
      start_common_chain(node);
      add_memory_reference(node);
      return;
    }
    clear_common_links(node);
    return;
  }
  return;
}



