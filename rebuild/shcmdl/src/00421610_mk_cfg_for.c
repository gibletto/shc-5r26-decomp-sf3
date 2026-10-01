#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_break_jumps
#define g_cfg_break_jumps (*(block_list * *)(g_sd + 0x267b8))
#undef g_cfg_continue_jumps
#define g_cfg_continue_jumps (*(block_list * *)(g_sd + 0x26f0c))
#undef g_cfg_cur_block
#define g_cfg_cur_block (*(bblock * *)(g_sd + 0x26868))
#undef g_cfg_cur_loop
#define g_cfg_cur_loop (*(loop * *)(g_sd + 0x2684c))
#undef g_cfg_last_loop
#define g_cfg_last_loop (*(loop * *)(g_sd + 0x1e728))
#undef g_cfg_last_stmt
#define g_cfg_last_stmt (*(node_list * *)(g_sd + 0x267ec))
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))
#undef g_cfg_pending_jumps
#define g_cfg_pending_jumps (*(block_list * *)(g_sd + 0x1e718))


// entry: 00421610
// name : mk_cfg_for
// size : 769
// sig  : void mk_cfg_for(il_node * stmt)


int __cdecl mk_cfg_for(il_node *stmt)

{
  loop *plVar1;
  int pos;
  il_node *piVar2;
  il_node *piVar3;
  loop *lp;
  bblock *continue_target;
  byte *flag_byte;
  bblock *loop_start;
  block_list *saved_breaks;
  block_list *saved_continues;
  
  saved_continues = g_cfg_continue_jumps;
  plVar1 = g_cfg_cur_loop;
  saved_breaks = g_cfg_break_jumps;
  g_cfg_break_jumps = (block_list *)0x0;
  g_cfg_continue_jumps = (block_list *)0x0;
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  if (stmt->parent->op != IL_BLOCK) {
    wrap_in_block_pair(stmt);
  }
  if (stmt->child->op == IL_NULL) {
    cfg_start_block(1);
  }
  else {
    flag_byte = (byte *)((int)&stmt->flag + 1);
    *flag_byte = *flag_byte | 0x20;
    pos = operand_index(stmt);
    piVar2 = copy_tree(0,stmt->child);
    insert_operands(stmt->parent,piVar2,pos);
    piVar3 = alloc_node();
    piVar3->op = IL_NULL;
    replace_operand(stmt,piVar3,1);
    cfg_append_statement(piVar2);
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
  }
  lp = new_loop(stmt);
  lp->pre = g_cfg_cur_block;
  lp->flag = lp->flag | 1;
  loop_start = g_cfg_next_block;
  g_cfg_last_stmt = (node_list *)0x0;
  cfg_append_statement(stmt->child->next->next->next);
  g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,loop_start);
  g_cfg_last_stmt = (node_list *)0x0;
  cfg_add_statement(stmt->child->next);
  continue_target = loop_start;
  piVar2 = stmt->child->next;
  if (piVar2->next->op != IL_NULL) {
    if ((lp->flag & 0x20) == 0) {
      if (piVar2->op != IL_BLOCK) {
        wrap_in_block_pair(piVar2);
      }
      *(byte *)&stmt->flag = (byte)stmt->flag | 1;
      piVar2 = copy_tree(0,stmt->child->next->next);
      piVar2->filn = 0;
      piVar2->line = 0;
      piVar2->listno = 0;
      piVar3 = last_operand(stmt->child->next);
      insert_before(piVar3,piVar2);
      piVar3 = alloc_node();
      piVar3->op = IL_NULL;
      replace_operand(stmt,piVar3,3);
    }
    else {
      continue_target = g_cfg_next_block;
      if (g_cfg_last_stmt != (node_list *)0x0) {
        g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
        g_cfg_last_stmt = (node_list *)0x0;
      }
      piVar2 = stmt->child->next->next;
    }
    cfg_append_statement(piVar2);
  }
  if (g_cfg_continue_jumps != (block_list *)0x0) {
    add_edges_from_list_and_free(g_cfg_continue_jumps,continue_target);
  }
  if (g_cfg_last_stmt != (node_list *)0x0) {
    g_cfg_pending_jumps = new_list_cell(g_cfg_pending_jumps,g_cfg_cur_block);
    g_cfg_last_stmt = (node_list *)0x0;
  }
  add_edges_from_list_and_free(g_cfg_pending_jumps,loop_start);
  g_cfg_pending_jumps = new_list_cell((block_list *)0x0,loop_start);
  g_cfg_pending_jumps =
       (block_list *)
       append_node_list((node_list *)g_cfg_pending_jumps,(node_list *)g_cfg_break_jumps);
  g_cfg_last_stmt = (node_list *)0x0;
  g_cfg_last_loop = lp;
  g_cfg_break_jumps = saved_breaks;
  g_cfg_cur_loop = plVar1;
  g_cfg_continue_jumps = saved_continues;
  lp->start = loop_start;
  lp->exit = g_cfg_cur_block;
  cfg_start_block(1);
  for (plVar1 = lp->child; plVar1 != (loop *)0x0; plVar1 = plVar1->next) {
    lp->flag = lp->flag | plVar1->flag & 0xffcc;
  }
  return;
}



