#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00404fd0
// name : copy_loop_body_blocks
// size : 377
// sig  : void copy_loop_body_blocks(loop * lp, int copies)


int __cdecl copy_loop_body_blocks(loop *lp,int copies)

{
  unsigned char _frec_8[8];
#define blk (*(bblock * *)(_frec_8 + 0))
  node_list **head;
  il_node *pos;
  il_node *copy;
  node_list *cell;
  node_list *last_cell;
  
  pos = lp->node;
  if (pos->op == IL_DO) {
    pos = pos->child;
    blk = lp->start;
  }
  else if (pos->op == IL_FOR) {
    pos = pos->child->next;
    blk = lp->exit;
  }
  else {
    pos = pos->child;
    blk = lp->exit;
  }
  head = &blk->ilnode;
  last_cell = *head;
  if (last_cell != (node_list *)0x0) {
    cell = last_cell->next;
    while (cell != (node_list *)0x0) {
      last_cell = last_cell->next;
      cell = last_cell->next;
    }
    if (pos->op != IL_BLOCK) {
      wrap_in_block_pair(pos);
      pos = pos->parent;
    }
    pos = last_operand(pos);
    while (copies = copies + -1, -1 < copies) {
      for (cell = *head; cell != last_cell; cell = cell->next) {
        if (cell->node->op != IL_EMPTY) {
          copy = copy_tree(0,cell->node);
          insert_before(pos,copy);
          append_list_item(head,copy);
        }
      }
      if (cell->node->op != IL_EMPTY) {
        copy = copy_tree(0,cell->node);
        insert_before(pos,copy);
        append_list_item(head,copy);
      }
    }
    if (((*(unsigned char *)((char *)&g_debug_flags + 1)) & 0x10) != 0) {
      dump_tree(lp->node,0,s_after_cp_lpblk_00433628);
      FID_conflict__wprintf(s_B_d__00433620,(int)blk->number);
      FID_conflict__wprintf(s____tcount____d_0043360c,(int)blk->tcount);
      FID_conflict__wprintf(s____ilnode___004335fc);
      dump_ilnode_list(*head);
      FID_conflict__wprintf(&g_str_newline);
    }
  }
  return;
#undef blk
}



