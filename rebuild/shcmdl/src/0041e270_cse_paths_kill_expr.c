#include "decls.h"
#include "imports.h"

// entry: 0041e270
// name : cse_paths_kill_expr
// size : 220
// sig  : int cse_paths_kill_expr(bblock * dom, bblock * block, il_node * expr, int memory_kind)


int __cdecl cse_paths_kill_expr(bblock *dom,bblock *block,il_node *expr,int memory_kind)

{
  int killed;
  short dom_no;
  bool in_loop;
  block_list *pred;
  
  in_loop = false;
  if ((block->flag & 0x40U) != 0) {
    if ((block->flag & 0x80U) != 0) {
      return 1;
    }
    killed = stmts_modify_expr(block->ilnode,expr,memory_kind,3);
    if (killed != 0) {
      *(byte *)&block->flag = (byte)block->flag | 0x80;
    }
    return killed;
  }
  if ((block->lptbl != (loop *)0x0) && (dom->number <= block->lptbl->start->number)) {
    in_loop = true;
  }
  killed = stmts_modify_expr(block->ilnode,expr,memory_kind,(-(uint)!in_loop & 0xfffffffe) + 3);
  if (killed != 0) {
    *(byte *)&block->flag = (byte)block->flag | 0x80;
    return 1;
  }
  *(byte *)&block->flag = (byte)block->flag | 0x40;
  dom_no = dom->number;
  pred = block->prelst;
  while( true ) {
    if (pred == (block_list *)0x0) {
      return 0;
    }
    if ((pred->block->number != dom_no) &&
       (killed = cse_paths_kill_expr(dom,pred->block,expr,memory_kind), killed != 0)) break;
    pred = pred->next;
  }
  return 1;
}



