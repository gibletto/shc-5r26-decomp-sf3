#include "decls.h"
#include "imports.h"

// entry: 00413360
// name : make_id_equals_const
// size : 57
// sig  : il_node * __cdecl make_id_equals_const(short symx,uint value)


il_node * __cdecl make_id_equals_const(short symx,uint value)

{
  il_node *piVar1;
  il_node *op2;
  
  piVar1 = new_node(IL_ID,'\x10');
  piVar1->symx = symx;
  op2 = new_const_node('\x10',value);
  piVar1 = make_node(IL_EQ,'\x10',piVar1,op2,(il_node *)0x0);
  return piVar1;
}
