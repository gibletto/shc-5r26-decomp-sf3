#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_defined_leaves
#define g_defined_leaves (*(int * *)(g_sd + 0x267a8))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040a6e0
// name : invalidate_memory_leaf_values
// size : 223
// sig  : void invalidate_memory_leaf_values(void)


int __cdecl invalidate_memory_leaf_values(void)

{
  byte type_class;
  undefined4 *cell;
  ushort *flag_ptr;
  il_node *last;
  short leafno;
  undefined4 *next_cell;
  undefined4 *prev;
  undefined4 *prev_link;
  short symno;
  
  prev = &g_defined_leaves;
  next_cell = g_defined_leaves;
  while (cell = next_cell, prev_link = prev, cell != (undefined4 *)0x0) {
    leafno = *(short *)(cell + 1);
    next_cell = (undefined4 *)*cell;
    symno = g_leaf_table[leafno].symno;
    if (0 < symno) {
      type_class = g_symtab[symno].type & 0xf8;
    }
    prev = cell;
    if ((((g_leaf_table[leafno].flag & 5) != 0) ||
        ((0 < symno && (((type_class == 0x60 || (type_class == 0x68)) || (type_class == 0x70))))))
       && ((((0 < symno && (type_class != 0x48)) && (type_class != 0x80)) &&
           ((type_class != 0x88 && (type_class != 0x90)))))) {
      last = g_leaf_table[leafno].lastnd;
      if (last->refchn == (il_node *)0x0) {
        if (((&g_op_class)[(char)last->op] & 0x20) == 0) {
          last->flag = last->flag | 0x180;
        }
      }
      else {
        flag_ptr = &last->refchn->flag;
        *flag_ptr = *flag_ptr | 0x180;
      }
      g_leaf_table[*(short *)(cell + 1)].lastnd = (il_node *)0x0;
      *prev_link = *cell;
      pool_free(cell,8);
      prev = prev_link;
    }
  }
  return;
}



