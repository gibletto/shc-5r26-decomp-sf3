#include "decls.h"
#include "imports.h"

// entry: 004133d0
// name : new_temporary_leaf
// size : 110
// sig  : int new_temporary_leaf(void)


int __cdecl new_temporary_leaf(void)

{
  short leafno;
  undefined4 in_EAX;
  int iVar1;
  short symno;
  
  g_temp_symx = g_temp_symx + -1;
  g_leaf_count = g_leaf_count + 1;
  iVar1 = CONCAT22((short)((uint)in_EAX >> 0x10),g_leaf_count);
  symno = g_temp_symx;
  if (0x7ff < g_leaf_count) {
    iVar1 = abort_function_optimization();
    iVar1 = CONCAT22((short)((uint)iVar1 >> 0x10),g_leaf_count);
    symno = g_temp_symx;
  }
  leafno = (short)iVar1;
  g_temp_symx = symno;
  g_leaf_count = leafno;
  g_leaf_table[leafno].lastnd = (il_node *)0x0;
  g_leaf_table[leafno].symno = symno;
  g_leaf_table[leafno].flag = '\0';
  g_leaf_table[leafno].unknown_0f = '\0';
  g_leaf_table[leafno].gen = (uint *)0x0;
  g_leaf_table[leafno].use = (uint *)0x0;
  return iVar1;
}
