#include "decls.h"
#include "imports.h"

// entry: 00406ac0
// name : expand_float_to_unsigned
// size : 363
// sig  : il_node * expand_float_to_unsigned(il_node * assign)


il_node * __cdecl expand_float_to_unsigned(il_node *assign)

{
  il_node *expr;
  il_node *temp;
  il_node *piVar1;
  il_node *cast;
  byte type;
  
  cast = assign->child->next;
  if ((((cast->op == IL_CAST) && (type = cast->type, (type & 0xe0) == 0)) && ((type & 0xf8) != 0))
     && ((((type & 0xf8) != 8 && ((type & 4) != 0)) && ((cast->child->type & 0xf8) == 0x28)))) {
    expr = copy_tree(2,cast->child);
    temp = new_temp_id(cast->child->type);
    expr = make_node(IL_ASSIGN,cast->child->type,temp,expr,(il_node *)0x0);
    piVar1 = new_node(IL_CONST,'(');
    *(undefined1 *)&piVar1->val = 0;
    *(undefined1 *)((int)&piVar1->val + 1) = 0;
    *(undefined1 *)((int)&piVar1->val + 2) = 0;
    *(undefined1 *)((int)&piVar1->val + 3) = 0x4f;
    expr = make_node(IL_GT,'\x10',expr,piVar1,(il_node *)0x0);
    temp = copy_tree(1,temp);
    piVar1 = new_node(IL_CONST,'(');
    *(undefined1 *)&piVar1->val = 0;
    *(undefined1 *)((int)&piVar1->val + 1) = 0;
    *(undefined1 *)((int)&piVar1->val + 2) = 0x80;
    *(undefined1 *)((int)&piVar1->val + 3) = 0x4f;
    piVar1 = make_node(IL_SUB,cast->child->type,temp,piVar1,(il_node *)0x0);
    temp = copy_tree(1,temp);
    expr = make_node(IL_COND,cast->child->type,expr,piVar1,temp);
    expr = make_node(IL_CAST,'\x18',expr,(il_node *)0x0,(il_node *)0x0);
    replace_and_free_node(cast->child,expr);
  }
  return assign;
}



