#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))


// entry: 0041d6b0
// name : cse_number_memory_ref
// size : 298
// sig  : void cse_number_memory_ref(il_node * node, bblock * block)


int __cdecl cse_number_memory_ref(il_node *node,bblock *block)

{
  node_list *item;
  ushort addr_vn;
  bool found;
  il_op op;
  il_node *ref;
  
  op = node->parent->op;
  if ((op == IL_AMPER) || ((node->type & 2) != 0)) {
    cse_clear_node(node);
  }
  else if ((((&g_op_class)[(char)op] & 0x20) == 0) || (node->parent->child != node)) {
    addr_vn = node->child->pp;
    if (addr_vn == 0) {
      cse_clear_node(node);
      return;
    }
    found = false;
    item = g_memory_refs;
    if (g_memory_refs != (node_list *)0x0) {
      op = node->op;
      do {
        ref = item->node;
        if ((((ref->op == op) && (((ref->type ^ node->type) & 0xfc) == 0)) &&
            (ref->child->pp == addr_vn)) &&
           ((found = true, op == IL_ASTER ||
            (((node->val == ref->val && (node->val2 == ref->val2)) &&
             ((op != IL_B_QUALIFY || ((node->boff == ref->boff && (node->bsiz == ref->bsiz))))))))))
        break;
        found = false;
        item = item->next;
      } while (item != (node_list *)0x0);
    }
    *(byte *)&node->flag2 = (byte)node->flag2 | 8;
    if (!found) {
      if (g_cse_cond_depth == '\0') {
        cse_new_class(node,block);
        cse_record_memory_ref(node,block);
        return;
      }
      cse_clear_node(node);
      return;
    }
    if (g_memory_clobbered != 0) {
      cse_clear_node(node);
      return;
    }
    cse_join_class(item->node,node);
    node->cse_block = block;
    return;
  }
  return;
}



