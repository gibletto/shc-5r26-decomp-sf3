#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_bn_chain
#define g_bn_chain (*(bblock * *)(g_sd + 0x26ef8))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))


// entry: 0040b790
// name : invert_loop_to_guarded_do
// size : 901
// sig  : void invert_loop_to_guarded_do(loop * lp)


int __cdecl invert_loop_to_guarded_do(loop *lp)

{
  bblock *pbVar1;
  char blocked;
  il_node *stmt;
  il_node *cond;
  uint flags;
  il_node *parent;
  il_node *empty;
  block_list *next_item;
  block_list *block;
  bblock *blk;
  short exit_no;
  block_list *item;
  bblock *other_succ;
  short start_no;
  
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x20) != 0) {
    FID_conflict__wprintf(s_jdgdevlop_start_00434fa8);
    dump_loop_table(g_loop_tree);
    dump_loop_tree_titled(lp,s_jdgdevlop_start_00434f98);
    dump_block_table(g_f_chain,s_jdgdevlop_start_00434f98);
  }
  blk = lp->start;
  item = blk->suclst->next;
  if (item == (block_list *)0x0) {
    return;
  }
  pbVar1 = blk->suclst->block;
  if ((pbVar1->lptbl != lp) && (item->block->lptbl != lp)) {
    return;
  }
  if (pbVar1 == blk) {
    return;
  }
  if (item->block == blk) {
    return;
  }
  stmt = lp->node->child;
  if (lp->node->op == IL_FOR) {
    stmt = stmt->next->next->next;
  }
  else {
    stmt = stmt->next;
  }
  blocked = condition_defs_block_inversion(lp,stmt);
  if (blocked != '\0') {
    return;
  }
  stmt = lp->node;
  if (stmt->op == IL_FOR) {
    delete_operand(stmt,3);
    delete_operand(stmt,1);
    cond = stmt->child->next;
    if (cond->op == IL_NULL) {
      cond->op = IL_CONST;
      stmt->child->next->type = '\x10';
      stmt->child->next->val = 1;
      stmt->child->next->nodes = '\x01';
    }
  }
  cond = copy_tree(0,stmt->child->next);
  stmt->op = IL_DO;
  flags = lp->flag & 0xfffffffe;
  lp->flag = flags;
  lp->flag = flags | 2;
  lp->flag = flags | 0x402;
  parent = new_node(IL_IF,'\0');
  insert_parent(stmt,parent);
  insert_before(stmt,cond);
  empty = new_node(IL_EMPTY,'\0');
  stmt->next = empty;
  stmt->parent = parent;
  blk = lp->exit;
  lp->flag = lp->flag & 0xfffe;
  start_no = lp->start->number;
  pbVar1 = blk->bn_next;
  exit_no = blk->number;
  blk->bn_next = lp->start;
  lp->exit = lp->start;
  item = lp->pre->suclst;
  next_item = item->next;
  while (next_item != (block_list *)0x0) {
    item = item->next;
    next_item = item->next;
  }
  next_item = pool_alloc(8);
  item->next = next_item;
  next_item = lp->start->suclst;
  blk = next_item->block;
  other_succ = next_item->next->block;
  if (blk->number < other_succ->number) {
    next_item = item->next;
    if (blk->lptbl != lp) {
      next_item->block = other_succ;
      item->block = lp->start->suclst->block;
      next_item = lp->start->suclst->next;
      goto LAB_0040b9a8;
    }
  }
  else {
    next_item = item->next;
    if (other_succ->lptbl == lp) {
      next_item->block = other_succ;
      item->block = lp->start->suclst->block;
      next_item = lp->start->suclst->next;
      goto LAB_0040b9a8;
    }
  }
  next_item->block = blk;
  item->block = lp->start->suclst->next->block;
  next_item = lp->start->suclst;
LAB_0040b9a8:
  lp->start = next_item->block;
  item = item->block->prelst;
  next_item = item->next;
  while (next_item != (block_list *)0x0) {
    item = item->next;
    next_item = item->next;
  }
  next_item = pool_alloc(8);
  item->next = next_item;
  next_item->block = lp->pre;
  item = lp->start->prelst;
  next_item = item->next;
  while (next_item != (block_list *)0x0) {
    item = item->next;
    next_item = item->next;
  }
  next_item = pool_alloc(8);
  item->next = next_item;
  next_item->block = lp->pre;
  item = lp->exit->prelst;
  if (item != (block_list *)0x0) {
    next_item = item;
    do {
      block = item;
      if (block->block->number == lp->pre->number) {
        next_item->next = block->next;
        if (block == next_item) {
          lp->exit->prelst = (block_list *)0x0;
        }
        pool_free(block,8);
        break;
      }
      item = block->next;
      next_item = block;
    } while (block->next != (block_list *)0x0);
  }
  append_list_item(&lp->pre->ilnode,cond);
  lp->pre->bn_next = lp->start;
  lp->exit->bn_next = pbVar1;
  lp->start->number = start_no;
  lp->exit->number = exit_no;
  blk = lp->start->bn_next;
  while (start_no = start_no + 1, pbVar1 = g_bn_chain, start_no < exit_no) {
    blk->number = start_no;
    blk = blk->bn_next;
  }
  for (; pbVar1 != (bblock *)0x0; pbVar1 = pbVar1->bn_next) {
    *(byte *)&pbVar1->flag = (byte)pbVar1->flag & 0xfe;
    pbVar1->f_next = (bblock *)0x0;
    pbVar1->b_next = (bblock *)0x0;
  }
  g_f_chain = (bblock *)0x0;
  link_blocks_reverse_postorder(g_bn_chain);
  compute_dominators();
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 0x20) != 0) {
    FID_conflict__wprintf(s_jdgdevlop_end_00434f88);
    dump_loop_table(g_loop_tree);
    dump_loop_tree_titled(lp,s_jdgdevlop_start_00434f98);
    dump_block_table(g_f_chain,s_jdgdevlop_start_00434f98);
  }
  return;
}



