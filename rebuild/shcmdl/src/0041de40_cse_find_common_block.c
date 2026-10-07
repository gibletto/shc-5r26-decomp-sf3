#include "decls.h"
#include "imports.h"
#include "gcserules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cse_split_first
#define g_cse_split_first (*(il_node * *)(g_sd + 0x267d4))
#undef g_cse_split_head
#define g_cse_split_head (*(il_node * *)(g_sd + 0x26f04))


// entry: 0041de40
// name : cse_find_common_block
// size : 539
// sig  : bblock * cse_find_common_block(il_node * node, int memory_kind)


bblock * __cdecl cse_find_common_block(il_node *node,int memory_kind)

{
  bblock *b;
  bblock *pbVar1;
  char not_cond;
  bblock *dom;
  undefined3 extraout_var = 0;
  int killed;
  il_node *piVar2;
  node_list *item;
  il_node *cur;
  bblock *blk;
  bool loop_pre;
  loop *lp;
  node_list *next_item;
  il_node *prev;
  
  loop_pre = false;
  b = node->cse_next->cse_block;
  g_cse_split_head = (il_node *)0x0;
  g_cse_split_first = (il_node *)0x0;
  pbVar1 = node->cse_block;
  piVar2 = node->cse_next;
  prev = node;
  while( true ) {
    cur = piVar2;
    dom = pbVar1;
    if (((cur == (il_node *)0x0) || (b == (bblock *)0x0)) ||
       (dom = find_common_dominator(pbVar1,b), dom == (bblock *)0x0)) goto LAB_0041dfcd;
    lp = dom->lptbl;
    if ((lp != (loop *)0x0) && (lp->start->number == dom->number)) {
      loop_pre = true;
      dom = lp->pre;
    }
    if (pbVar1->number != dom->number) break;
    item = dom->ilnode;
    if (item != (node_list *)0x0) {
      do {
        piVar2 = tree_contains_node(item->node,node);
        if (piVar2 != (il_node *)0x0) break;
        item = item->next;
      } while (item != (node_list *)0x0);
      if ((item != (node_list *)0x0) &&
         (killed = stmts_modify_expr(item,node,memory_kind,2), killed != 0)) {
        piVar2 = cse_drop_class_head(node);
        GCSE_REINSERT(piVar2,node);
        goto LAB_0041dfcb;
      }
    }
LAB_0041df7e:
    if ((dom->number != b->number) &&
       (killed = cse_paths_kill_expr(dom,b,cur,memory_kind), killed != 0)) {
      prev->cse_next = cur->cse_next;
      node->refcnt = node->refcnt - 1;
      cur->cse_next = (il_node *)0x0;
      cse_add_to_split_class(cur);
      cur = prev;
      if (node->refcnt < 2) goto LAB_0041dfcb;
    }
    piVar2 = cur->cse_next;
    if (piVar2 == (il_node *)0x0) goto LAB_0041dfcd;
    b = piVar2->cse_block;
    for (blk = dom->f_next; pbVar1 = dom, prev = cur, blk != (bblock *)0x0; blk = blk->f_next) {
      *(byte *)&blk->flag = (byte)blk->flag & 0xbf;
    }
  }
  if (!loop_pre) {
    item = dom->ilnode;
    loop_pre = false;
    next_item = item->next;
    while (next_item != (node_list *)0x0) {
      item = item->next;
      next_item = item->next;
    }
    not_cond = is_not_control_condition(item->node);
    if ((CONCAT31(extraout_var,not_cond) == 0) &&
       (killed = stmts_modify_expr(item,node,memory_kind,2), killed != 0)) {
      piVar2 = cse_drop_class_head(node);
      GCSE_REINSERT(piVar2,node);
      goto LAB_0041dfcb;
    }
  }
  killed = cse_paths_kill_expr(dom,pbVar1,node,memory_kind);
  if (killed == 0) {
    for (pbVar1 = dom->f_next; pbVar1 != (bblock *)0x0; pbVar1 = pbVar1->f_next) {
      *(byte *)&pbVar1->flag = (byte)pbVar1->flag & 0xbf;
    }
    goto LAB_0041df7e;
  }
  piVar2 = cse_drop_class_head(node);
  GCSE_REINSERT(piVar2,node);
LAB_0041dfcb:
  dom = (bblock *)0x0;
LAB_0041dfcd:
  if (g_cse_split_head != (il_node *)0x0) {
    cse_reinsert_class(g_cse_split_head);
  }
  return dom;
}



