#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00411eb0
// name : make_unrolled_limit
// size : 198
// sig  : il_node * make_unrolled_limit(il_node * limit, char type)


il_node * __cdecl make_unrolled_limit(il_node *limit,char type)

{
  il_node *four;
  il_node *piVar1;
  il_node *node;
  uint sign;
  il_op op;
  
  four = new_node(IL_CONST,'\x10');
  four->val = 4;
  if (four->type != type) {
    four = make_node(IL_CAST,type,four,(il_node *)0x0,(il_node *)0x0);
  }
  piVar1 = new_node(IL_CONST,'\x10');
  sign = g_cur_loop->lstep >> 0x1f;
  piVar1->val = (g_cur_loop->lstep ^ sign) - sign;
  if (piVar1->type != type) {
    piVar1 = make_node(IL_CAST,type,piVar1,(il_node *)0x0,(il_node *)0x0);
  }
  four = make_node(IL_MUL,type,piVar1,four,(il_node *)0x0);
  if (g_cur_loop->lstep < 1) {
    op = IL_ADD;
  }
  else {
    op = IL_SUB;
  }
  piVar1 = new_node(op,type);
  node = copy_tree(0,limit);
  insert_parent(node,piVar1);
  four->parent = piVar1;
  piVar1->child->next = four;
  return piVar1;
}



