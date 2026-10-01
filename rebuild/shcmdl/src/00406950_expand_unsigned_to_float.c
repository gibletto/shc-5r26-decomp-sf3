#include "decls.h"
#include "imports.h"

// entry: 00406950
// name : expand_unsigned_to_float
// size : 355
// sig  : il_node * expand_unsigned_to_float(il_node * assign)


il_node * __cdecl expand_unsigned_to_float(il_node *assign)

{
  il_node *expr;
  il_node *temp;
  il_node *piVar1;
  il_node *cast;
  byte src_type;
  
  cast = assign->child->next;
  if ((cast->op == IL_CAST) && ((cast->type & 0xf8) == 0x28)) {
    src_type = cast->child->type;
    if (((src_type & 0xe0) == 0) &&
       ((((src_type & 0xf8) != 0 && ((src_type & 0xf8) != 8)) && ((src_type & 4) != 0)))) {
      expr = copy_tree(2,cast->child);
      expr = make_node(IL_CAST,'\x18',expr,(il_node *)0x0,(il_node *)0x0);
      expr = make_node(IL_CAST,cast->type,expr,(il_node *)0x0,(il_node *)0x0);
      temp = new_temp_id(cast->type);
      expr = make_node(IL_ASSIGN,cast->type,temp,expr,(il_node *)0x0);
      piVar1 = new_const_node('\x10',0);
      piVar1 = make_node(IL_CAST,cast->type,piVar1,(il_node *)0x0,(il_node *)0x0);
      expr = make_node(IL_LT,'\x10',expr,piVar1,(il_node *)0x0);
      temp = copy_tree(1,temp);
      piVar1 = new_node(IL_CONST,'(');
      *(undefined1 *)&piVar1->val = 0;
      *(undefined1 *)((int)&piVar1->val + 1) = 0;
      *(undefined1 *)((int)&piVar1->val + 2) = 0x80;
      *(undefined1 *)((int)&piVar1->val + 3) = 0x4f;
      piVar1 = make_node(IL_ADD,cast->type,temp,piVar1,(il_node *)0x0);
      temp = copy_tree(1,temp);
      expr = make_node(IL_COND,cast->type,expr,piVar1,temp);
      replace_and_free_node(cast->child,expr);
    }
  }
  return assign;
}



