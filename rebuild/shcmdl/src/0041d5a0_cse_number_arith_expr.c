#include "decls.h"
#include "imports.h"

// entry: 0041d5a0
// name : cse_number_arith_expr
// size : 271
// sig  : void cse_number_arith_expr(il_node * node, bblock * block)


int __cdecl cse_number_arith_expr(il_node *node,bblock *block)

{
  byte kind;
  il_node *piVar1;
  bool all_numbered;
  ushort leaf_flags;
  bool touches_memory;
  
  touches_memory = false;
  all_numbered = true;
  piVar1 = node->child;
  do {
    if (piVar1 == (il_node *)0x0) {
LAB_0041d609:
      if (touches_memory) {
        *(byte *)&node->flag2 = (byte)node->flag2 | 8;
      }
      if (!all_numbered) {
        cse_clear_node(node);
        return;
      }
      piVar1 = cse_find_arith_match(node);
      if (piVar1 == (il_node *)0x0) {
        if (g_cse_cond_depth != '\0') {
          cse_clear_node(node);
          return;
        }
        cse_new_class(node,block);
        cse_hash_arith_expr(node,block);
        return;
      }
      if ((node->flag2 & 8) == 0) {
        cse_join_class(piVar1,node);
        node->cse_block = block;
        return;
      }
      if (g_memory_clobbered == 0) {
        cse_join_class(piVar1,node);
        node->cse_block = block;
        return;
      }
      cse_clear_node(node);
      return;
    }
    if (piVar1->pp == 0) {
      all_numbered = false;
      goto LAB_0041d609;
    }
    if ((!touches_memory) &&
       ((((piVar1->parent->op == IL_AMPER ||
          ((*(unsigned char *)((char *)&leaf_flags + 0)) = g_leaf_table[piVar1->nleaf].flag,
          (*(unsigned char *)((char *)&leaf_flags + 1)) = g_leaf_table[piVar1->nleaf].unknown_0f, (leaf_flags & 7) != 0)) ||
         (kind = piVar1->type & 0xf0, kind == 0x60)) ||
        (((kind == 0x70 || (kind == 0x80)) || ((kind == 0x90 || ((piVar1->flag2 & 8) != 0)))))))) {
      touches_memory = true;
    }
    piVar1 = piVar1->next;
  } while( true );
}



