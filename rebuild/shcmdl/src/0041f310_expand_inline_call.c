#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041f310
// name : expand_inline_call
// size : 311
// sig  : void expand_inline_call(inline_call * cand, il_node * stmt)


int __cdecl expand_inline_call(inline_call *cand,il_node *stmt)

{
  il_node *piVar1;
  il_node *cur;
  int index;
  il_node *node;
  il_op parent_op;
  
  append_callee_scopes(g_func_node->symx,cand->callee);
  piVar1 = instantiate_inline_body(cand);
  insert_before(stmt,piVar1);
  add_scope_to_enclosing_block(piVar1);
  if (0 < cand->return_label) {
    cur = new_glabel_stmt(cand->return_label);
    insert_before(stmt,cur);
  }
  if (cand->result < 1) {
    cur = alloc_node();
    cur->op = IL_NULL;
    replace_and_free_node(cand->call,cur);
  }
  else {
    cur = new_node(IL_ID,g_symtab[cand->result].type);
    cur->symx = cand->result;
    replace_and_free_node(cand->call,cur);
    add_member_to_scope(g_func_node->child->symx,cur->symx);
  }
  parent_op = cur->parent->op;
  while ('\x1f' < (char)parent_op) {
    node = piVar1;
    if ((cur->parent->op == IL_COMMA) && (index = operand_index(cur), index == 2)) {
      node = copy_tree(0,cur->parent->child);
      insert_before(piVar1,node);
      piVar1 = alloc_node();
      piVar1->op = IL_NULL;
      replace_and_free_node(cur->parent->child,piVar1);
    }
    cur = cur->parent;
    piVar1 = node;
    parent_op = cur->parent->op;
  }
  return;
}



