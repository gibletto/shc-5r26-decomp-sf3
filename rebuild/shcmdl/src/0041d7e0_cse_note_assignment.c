#include "decls.h"
#include "imports.h"

// entry: 0041d7e0
// name : cse_note_assignment
// size : 162
// sig  : void cse_note_assignment(il_node * assign)


int __cdecl cse_note_assignment(il_node *assign)

{
  il_node *node;
  byte kind;
  ushort leaf_flags;
  il_op lhs_op;
  
  node = assign->child;
  lhs_op = node->op;
  if (((lhs_op == IL_ID) && ((node->type & 2) == 0)) &&
     ((*(unsigned char *)((char *)&leaf_flags + 0)) = g_leaf_table[node->nleaf].flag,
     (*(unsigned char *)((char *)&leaf_flags + 1)) = g_leaf_table[node->nleaf].unknown_0f, (leaf_flags & 2) == 0)) {
    kind = node->type & 0xf0;
    if ((((kind != 0x60) && (kind != 0x70)) && (kind != 0x80)) && (kind != 0x90)) {
joined_r0x0041d861:
      if ((leaf_flags & 5) == 0) goto LAB_0041d86d;
    }
  }
  else if (((&g_op_class)[(char)lhs_op] & 0x10) == 0) {
    if (lhs_op != IL_ID) goto LAB_0041d86d;
    if ((((node->type & 2) == 0) && (kind = node->type & 0xf0, kind != 0x60)) &&
       ((kind != 0x70 && ((kind != 0x80 && (kind != 0x90)))))) {
      (*(unsigned char *)((char *)&leaf_flags + 0)) = g_leaf_table[node->nleaf].flag;
      (*(unsigned char *)((char *)&leaf_flags + 1)) = g_leaf_table[node->nleaf].unknown_0f;
      goto joined_r0x0041d861;
    }
  }
  g_memory_clobbered = 1;
LAB_0041d86d:
  cse_clear_node(node);
  cse_clear_node(assign);
  return;
}



