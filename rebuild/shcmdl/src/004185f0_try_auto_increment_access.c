#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_iv_update_stmt
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))


// entry: 004185f0
// name : try_auto_increment_access
// size : 446
// sig  : int try_auto_increment_access(il_node * expr, il_node * temp, iv_use * use)


int __cdecl try_auto_increment_access(il_node *expr,il_node *temp,iv_use *use)

{
  il_node *node;
  il_node *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  il_node *parent;
  int res;
  il_op parent_op;
  
  res = 1;
  node = new_node(IL_CONST,'\x10');
  piVar1 = copy_tree(0,use->incr);
  node->child = piVar1;
  piVar1->parent = node;
  strip_negations(node->child);
  uVar2 = fold_and_check_overflow(node->child);
  piVar1 = (il_node *)0x0;
  if (uVar2 == 0) {
    parent = temp->parent;
    parent_op = parent->op;
    if ((parent_op == IL_ASTER) || (parent_op == IL_ASSIGN)) {
      if ((parent_op == IL_ASSIGN) && (parent = parent->parent, parent->op != IL_ASTER)) {
        free_tree(node);
        return 1;
      }
      piVar1 = parent;
      if (parent->parent->op == IL_CAST) {
        piVar1 = parent->parent;
      }
    }
  }
  if (piVar1 != (il_node *)0x0) {
    iVar3 = induction_step(g_iv_update_stmt);
    if (iVar3 == 1) {
      if (((piVar1->parent->op & IL_NON_F0) != IL_A_ADD) ||
         (iVar3 = operand_index(piVar1), iVar3 != 2)) goto LAB_00418799;
      piVar1 = new_node(IL_POI,temp->type);
      uVar2 = node->child->val;
      uVar4 = (int)uVar2 >> 0x1f;
      piVar1->val = (uVar2 ^ uVar4) - uVar4;
      insert_parent(temp,piVar1);
    }
    else {
      if ((((piVar1 == (il_node *)0x0) || (iVar3 = induction_step(g_iv_update_stmt), iVar3 != -1))
          || ((piVar1->parent->op & IL_NON_F0) != IL_A_ADD)) ||
         (iVar3 = operand_index(piVar1), iVar3 != 1)) goto LAB_00418799;
      piVar1 = new_node(IL_PRD,temp->type);
      uVar2 = node->child->val;
      uVar4 = (int)uVar2 >> 0x1f;
      uVar4 = (uVar2 ^ uVar4) - uVar4;
      piVar1->val = uVar4;
      insert_parent(temp,piVar1);
      piVar1 = new_node(IL_ADD,expr->parent->type);
      insert_parent(expr,piVar1);
      piVar1 = new_const_node(expr->parent->type,uVar4);
      insert_after(expr,piVar1);
    }
    res = 0;
  }
LAB_00418799:
  free_tree(node);
  return res;
}



