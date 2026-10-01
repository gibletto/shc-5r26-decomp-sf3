#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_dt_loop
#define g_dt_loop (*(loop * *)(g_sd + 0x26844))


// entry: 0040bfd0
// name : rewrite_loop_count_down
// size : 650
// sig  : void rewrite_loop_count_down(il_node * cond, il_node * step, il_node * init, char mode)


int __cdecl rewrite_loop_count_down(il_node *cond,il_node *step,il_node *init,char mode)

{
  byte type;
  uint value;
  byte kind;
  il_node *piVar1;
  il_node *piVar2;
  il_node *piVar3;
  il_node *node;
  uint count;
  byte bVar4;
  uint overflow;
  uint limit;
  il_op op;
  
  bVar4 = 0;
  piVar3 = init->child->next;
  value = piVar3->val;
  piVar1 = cond->child;
  limit = piVar1->next->val;
  op = cond->op;
  if ((op == IL_LT) || (op == IL_LE)) {
    if ((piVar1->type & 4) != 0) {
      bVar4 = value < limit;
      goto LAB_0040c070;
    }
    bVar4 = 1;
    if ((int)value < (int)limit) goto LAB_0040c070;
  }
  else {
    if ((op != IL_GT) && (op != IL_GE)) {
      if (op == IL_NE) {
        if (((piVar1->type & 4) == 0) || (g_dt_loop->lstep != -1)) {
          bVar4 = 1;
        }
        else {
          bVar4 = 2;
        }
      }
      goto LAB_0040c070;
    }
    if ((piVar1->type & 4) != 0) {
      bVar4 = -(limit < value) & 2;
      goto LAB_0040c070;
    }
    bVar4 = 1;
    if ((int)limit < (int)value) goto LAB_0040c070;
  }
  bVar4 = 0;
LAB_0040c070:
  if (bVar4 != 0) {
    if (bVar4 == 2) {
      count = value - limit;
    }
    else {
      count = limit - value;
    }
    overflow = 0;
    if ((value != 0) && (limit != 0)) {
      type = init->child->type;
      kind = type & 0xf8;
      if ((kind == 0) || (kind == 8)) {
        overflow = check_value_range(type,count);
      }
      else {
        piVar1 = new_const_node(piVar3->type,value);
        piVar2 = new_const_node(cond->child->next->type,limit);
        piVar3 = piVar2;
        if (bVar4 == 2) {
          piVar3 = piVar1;
          piVar1 = piVar2;
        }
        piVar3 = make_node(IL_SUB,init->child->type,piVar3,piVar1,(il_node *)0x0);
        overflow = check_arith_overflow(piVar3,count);
        free_tree(piVar3);
      }
    }
    if (overflow == 0) {
      g_dt_opt_changed = 1;
      bVar4 = init->child->type;
      if ((bVar4 & 4) == 0) {
        count = (int)(limit - value) >> 0x1f;
        count = (limit - value ^ count) - count;
      }
      piVar3 = new_const_node(bVar4,count);
      piVar1 = copy_tree(0,cond);
      piVar2 = copy_tree(0,init);
      node = copy_tree(0,init);
      insert_before(g_dt_loop->node,node);
      append_list_item(&g_dt_loop->pre->ilnode,node);
      replace_and_free_node(node->child->next,piVar3);
      if (cond->op != IL_NE) {
        cond->op = IL_NE;
      }
      if (0 < g_dt_loop->lstep) {
        negate_step_operator(step);
      }
      if (limit != 0) {
        piVar3 = new_const_node(cond->child->type,0);
        replace_and_free_node(cond->child->next,piVar3);
        if (mode == '\x02') {
          assign_final_value_after_loop(piVar1,piVar2);
        }
      }
      free_tree(piVar1);
    }
  }
  return;
}



