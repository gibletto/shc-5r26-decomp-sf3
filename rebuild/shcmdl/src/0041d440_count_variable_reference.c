#include "decls.h"
#include "imports.h"

// entry: 0041d440
// name : count_variable_reference
// size : 343
// sig  : void count_variable_reference(il_node * id, bblock * block)


int __cdecl count_variable_reference(il_node *id,bblock *block)

{
  il_node *head;
  byte kind;
  ushort leaf_flags;
  il_op parent_op;
  byte ty;
  
  parent_op = id->parent->op;
  if ((parent_op != IL_AMPER) && (ty = id->type, (ty & 2) == 0)) {
    (*(unsigned char *)((char *)&leaf_flags + 0)) = g_leaf_table[id->nleaf].flag;
    (*(unsigned char *)((char *)&leaf_flags + 1)) = g_leaf_table[id->nleaf].unknown_0f;
    if ((leaf_flags & 2) == 0) {
      if ((((&g_op_class)[(char)parent_op] & 0x20) != 0) && (id->parent->child == id)) {
        return;
      }
      head = g_leaf_table[id->nleaf].lastnd;
      if (head == (il_node *)0x0) {
        kind = ty & 0xf0;
        if (((kind != 0x60) && (kind != 0x70)) &&
           ((kind != 0x80 && (((kind != 0x90 && ((ty & 0xf8) != 0x48)) && ((leaf_flags & 7) == 0))))
           )) {
          cse_new_class(id,block);
          g_leaf_table[id->nleaf].lastnd = id;
          cse_record_variable(id,block);
          return;
        }
        if (g_cse_cond_depth == '\0') {
          cse_new_class(id,block);
          g_leaf_table[id->nleaf].lastnd = id;
          cse_record_variable(id,block);
          return;
        }
        cse_clear_node(id);
        return;
      }
      kind = ty & 0xf0;
      if ((((kind != 0x60) && (kind != 0x70)) && (kind != 0x80)) &&
         (((kind != 0x90 && ((ty & 0xf8) != 0x48)) && ((leaf_flags & 7) == 0)))) {
        cse_join_class(head,id);
        id->cse_block = block;
        return;
      }
      if (g_memory_clobbered != 0) {
        cse_clear_node(id);
        return;
      }
      cse_join_class(head,id);
      id->cse_block = block;
      return;
    }
  }
  cse_clear_node(id);
  return;
}



